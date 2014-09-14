#pragma once
#include "stdafx.h"
#include <windows.h>
#include <stdio.h>
#include <mmsystem.h>
#include <mmdeviceapi.h>
#include <avrt.h>
#include <Audioclient.h>
#include <iostream>
#include <thread>
#include <atomic>
#include <queue>
#include "log.h"

struct audPacket
{
	//int16_t la = 0;
	//int16_t lb = 0;
	//int16_t ra = 0;
	//int16_t rb = 0;
	double l = 0;
	double r = 0;
};
std::atomic<std::queue<audPacket> > data;
std::atomic<bool> die = false;
std::atomic<size_t> samp_size = 0;
audPacket bufferPack;
bool workerDead = false;

int audioTaskWorker()
{
	HRESULT hr = S_OK;
	IMMDevice *pMMDevice;
	//HMMIO hFile;
	bool bInt16(false);
	//PWAVEFORMATEX pwfx;
	LPCWSTR szFilename;

	//get the default audio device...

	IMMDeviceEnumerator *pMMDevEnum;
	hr = CoCreateInstance(
		__uuidof(MMDeviceEnumerator),
		NULL,
		CLSCTX_ALL,
		__uuidof(IMMDeviceEnumerator),
		(void**)&pMMDevEnum
		);
	if (FAILED(hr))
	{
		logSys::putMessage("CoCreateInstance(IMMDeviceEnumerator) failed", logSys::error, LOGINFO(hr));
		return hr;
	}
	hr = pMMDevEnum->GetDefaultAudioEndpoint(eRender, eConsole, &pMMDevice);
	pMMDevEnum->Release();
	if (FAILED(hr))
	{
		logSys::putMessage("CIMMDeviceEnumerator::GetDefaultAudioEndpoint failed", logSys::error, LOGINFO(hr));
		return hr;
	}
	//default device aquired!
	if (S_FALSE == hr) return 0; //noting to do here...

	//HRESULT hr;
	IAudioClient *audClient;
	hr = pMMDevice->Activate(__uuidof(IAudioClient), CLSCTX_ALL, NULL, (void**)&audClient);
	if (FAILED(hr))
	{
		logSys::putMessage("IMMDevice::Activate(IAudioClient) failed", logSys::error, LOGINFO(hr));
		return hr;
	}

	REFERENCE_TIME hnsDefDevPeriod;
	hr = audClient->GetDevicePeriod(&hnsDefDevPeriod, NULL);
	if (FAILED(hr))
	{
		logSys::putMessage("IAudioClient::GetDevicePeriod failed", logSys::error, LOGINFO(hr));
		return hr;
	}

	WAVEFORMATEX *wfx;
	hr = audClient->GetMixFormat(&wfx);
	if (FAILED(hr))
	{
		logSys::putMessage("IAudioClient::GetMixFormat failed", logSys::error, LOGINFO(hr));
		CoTaskMemFree(wfx);
		audClient->Release();
		return hr;
	}
	logSys::putMessage("wfx->wFormatTag = ", logSys::info, LOGINFO(wfx->wFormatTag));
	//bInt16 = true;
	if (bInt16) {
		// coerce int-16 wave format
		// can do this in-place since we're not changing the size of the format
		// also, the engine will auto-convert from float to int for us
		switch (wfx->wFormatTag) {
		case WAVE_FORMAT_IEEE_FLOAT:
			wfx->wFormatTag = WAVE_FORMAT_PCM;
			wfx->wBitsPerSample = 16;
			wfx->nBlockAlign = wfx->nChannels * wfx->wBitsPerSample / 8;
			wfx->nAvgBytesPerSec = wfx->nBlockAlign * wfx->nSamplesPerSec;
			logSys::putMessage("Audio format: IEEE float", logSys::info, LOGINFO(wfx->wFormatTag));
			break;

		case WAVE_FORMAT_EXTENSIBLE:
		{
									   // naked scope for case-local variable
									   PWAVEFORMATEXTENSIBLE pEx = reinterpret_cast<PWAVEFORMATEXTENSIBLE>(wfx);
									   if (IsEqualGUID(KSDATAFORMAT_SUBTYPE_IEEE_FLOAT, pEx->SubFormat)) {
										   pEx->SubFormat = KSDATAFORMAT_SUBTYPE_PCM;
										   pEx->Samples.wValidBitsPerSample = 16;
										   wfx->wBitsPerSample = 16;
										   wfx->nBlockAlign = wfx->nChannels * wfx->wBitsPerSample / 8;
										   wfx->nAvgBytesPerSec = wfx->nBlockAlign * wfx->nSamplesPerSec;
										   logSys::putMessage("Audio format: IEEE float", logSys::info, LOGINFO(wfx->wFormatTag));
									   }
									   else {
										   logSys::putMessage("Don't know how to coerce mix format to int-16", logSys::error, LOGINFO(hr));
										   CoTaskMemFree(wfx);
										   audClient->Release();
										   return E_UNEXPECTED;
									   }
		}
			break;

		default:
			logSys::putMessage("Don't know how to coerce WAVEFORMATEX with wFormatTag", logSys::error, LOGINFO(hr));
			CoTaskMemFree(wfx);
			audClient->Release();
			return E_UNEXPECTED;
		}
	}

	HANDLE hWakeUp = CreateWaitableTimer(NULL, FALSE, NULL);
	if (NULL == hWakeUp) {
		DWORD dwErr = GetLastError();
		logSys::putMessage("CreateWaitableTimer failed: last error", logSys::error, LOGINFO(dwErr));
		CoTaskMemFree(wfx);
		audClient->Release();
		return HRESULT_FROM_WIN32(dwErr);
	}
	UINT32 blkAlign = wfx->nBlockAlign;
	UINT32 nframes = 0;

	hr = audClient->Initialize(AUDCLNT_SHAREMODE_SHARED, AUDCLNT_STREAMFLAGS_LOOPBACK, 0, 0, wfx, 0);
	if (FAILED(hr)) {
		logSys::putMessage("IAudioClient::Initialize failed", logSys::error, LOGINFO(hr));
		CloseHandle(hWakeUp);
		audClient->Release();
		return hr;
	}
	samp_size = wfx->nChannels * (wfx->wBitsPerSample / 8);
	CoTaskMemFree(wfx);
	IAudioCaptureClient *pAudioCaptureClient;
	hr = audClient->GetService(
		__uuidof(IAudioCaptureClient),
		(void**)&pAudioCaptureClient
		);
	if (FAILED(hr)) {
		logSys::putMessage("IAudioClient::GetService(IAudioCaptureClient) failed", logSys::error, LOGINFO(hr));
		CloseHandle(hWakeUp);
		audClient->Release();
		return hr;
	}

	// register with MMCSS
	DWORD nTaskIndex = 0;
	HANDLE hTask = AvSetMmThreadCharacteristics(L"Capture", &nTaskIndex);
	if (NULL == hTask) {
		DWORD dwErr = GetLastError();
		logSys::putMessage("AvSetMmThreadCharacteristics failed", logSys::error, LOGINFO(dwErr));
		pAudioCaptureClient->Release();
		CloseHandle(hWakeUp);
		audClient->Release();
		return HRESULT_FROM_WIN32(dwErr);
	}

	// set the waitable timer
	LARGE_INTEGER liFirstFire;
	liFirstFire.QuadPart = -hnsDefDevPeriod / 2; // negative means relative time
	LONG lTimeBetweenFires = (LONG)hnsDefDevPeriod / 2 / (10 * 1000); // convert to milliseconds
	BOOL bOK = SetWaitableTimer(
		hWakeUp,
		&liFirstFire,
		lTimeBetweenFires,
		NULL, NULL, FALSE
		);
	if (!bOK) {
		DWORD dwErr = GetLastError();
		logSys::putMessage("SetWaitableTimer failed", logSys::error, LOGINFO(dwErr));
		AvRevertMmThreadCharacteristics(hTask);
		pAudioCaptureClient->Release();
		CloseHandle(hWakeUp);
		audClient->Release();
		return HRESULT_FROM_WIN32(dwErr);
	}

	// call IAudioClient::Start
	hr = audClient->Start();
	if (FAILED(hr)) {
		logSys::putMessage("IAudioClient::Start failed", logSys::error, LOGINFO(hr));
		AvRevertMmThreadCharacteristics(hTask);
		pAudioCaptureClient->Release();
		CloseHandle(hWakeUp);
		audClient->Release();
		return hr;
	}
	//SetEvent(hStartedEvent);

	// loopback capture loop
	//HANDLE waitArray[2] = { hStopEvent, hWakeUp };
	//DWORD dwWaitResult;

	bool bDone = false;
	bool bFirstPacket = true;
	int loopCnt = 0;
	while (!(bDone || die.load())) // run untill finished, or kill signal.
	{
		for (UINT32 nPasses = 0; !bDone; nPasses++) {
			//dwWaitResult = WaitForSingleObject(hWakeUp, INFINITE);
			/*
			if (die.load()) {
				logSys::putMessage("Received stop event", logSys::error, LOGINFO(dwWaitResult));
				bDone = true;
				continue; // exits loop
			}

			if (WAIT_OBJECT_0 + 1 != dwWaitResult) {
				logSys::putMessage("Unexpected WaitForMultipleObjects return value", logSys::error, LOGINFO(dwWaitResult));
				audClient->Stop();
				CancelWaitableTimer(hWakeUp);
				AvRevertMmThreadCharacteristics(hTask);
				pAudioCaptureClient->Release();
				CloseHandle(hWakeUp);
				audClient->Release();
				return E_UNEXPECTED;
			}
			*/
			// got a "wake up" event - see if there's data
			UINT32 nNextPacketSize;
			hr = pAudioCaptureClient->GetNextPacketSize(&nNextPacketSize);
			if (FAILED(hr)) {
				logSys::putMessage("IAudioCaptureClient::GetNextPacketSize failed", logSys::error, LOGINFO(hr));
				audClient->Stop();
				CancelWaitableTimer(hWakeUp);
				AvRevertMmThreadCharacteristics(hTask);
				pAudioCaptureClient->Release();
				CloseHandle(hWakeUp);
				audClient->Release();
				return hr;
			}

			if (0 == nNextPacketSize) {
				// no data yet
				continue;
			}

			// get the captured data
			BYTE *pData;
			UINT32 nNumFramesToRead;
			DWORD dwFlags;

			hr = pAudioCaptureClient->GetBuffer(
				&pData,
				&nNumFramesToRead,
				&dwFlags,
				NULL,
				NULL
				);
			if (FAILED(hr)) {
				logSys::putMessage("IAudioCaptureClient::GetBuffer failed", logSys::error, LOGINFO(hr));
				audClient->Stop();
				CancelWaitableTimer(hWakeUp);
				AvRevertMmThreadCharacteristics(hTask);
				pAudioCaptureClient->Release();
				CloseHandle(hWakeUp);
				audClient->Release();
				return hr;
			}

			if (bFirstPacket && AUDCLNT_BUFFERFLAGS_DATA_DISCONTINUITY == dwFlags) {
				logSys::putMessage("probably random glitch. carrying on...", logSys::info, LOGINFO(0));
			}
			else if (0 != dwFlags) {
				//AUDCLNT_BUFFERFLAGS_DATA_DISCONTINUITY; // 0x0001
				//AUDCLNT_BUFFERFLAGS_SILENT;             // 0x0010
				//AUDCLNT_BUFFERFLAGS_TIMESTAMP_ERROR;    // 0x0100

				logSys::putMessage("IAudioCaptureClient::GetBuffer set flags to ", logSys::error, LOGINFO(dwFlags));
				
				if ((dwFlags & AUDCLNT_BUFFERFLAGS_DATA_DISCONTINUITY) != 0)
				{
					logSys::putMessage("AUDCLNT_BUFFERFLAGS_DATA_DISCONTINUITY set", logSys::warn, LOGINFO(dwFlags));
					continue;
				}
				if ((dwFlags & AUDCLNT_BUFFERFLAGS_SILENT) != 0)
					logSys::putMessage("AUDCLNT_BUFFERFLAGS_SILENT set", logSys::error, LOGINFO(dwFlags));

				if ((dwFlags & AUDCLNT_BUFFERFLAGS_TIMESTAMP_ERROR) != 0)
					logSys::putMessage("AUDCLNT_BUFFERFLAGS_TIMESTAMP_ERROR set", logSys::error, LOGINFO(dwFlags));
				
				audClient->Stop();
				CancelWaitableTimer(hWakeUp);
				AvRevertMmThreadCharacteristics(hTask);
				pAudioCaptureClient->Release();
				CloseHandle(hWakeUp);
				audClient->Release();
				return E_UNEXPECTED;
			}

			if (0 == nNumFramesToRead) {
				logSys::putMessage("IAudioCaptureClient::GetBuffer said to read 0 frames", logSys::error, LOGINFO(nPasses));
				audClient->Stop();
				CancelWaitableTimer(hWakeUp);
				AvRevertMmThreadCharacteristics(hTask);
				pAudioCaptureClient->Release();
				CloseHandle(hWakeUp);
				audClient->Release();
				return E_UNEXPECTED;
			}


			
			audPacket * pak = (audPacket*)(void*)pData;
			bufferPack.l += pak->l;
			bufferPack.r += pak->r;
			if (loopCnt > 3)
			{
				bufferPack.l = bufferPack.l / 3;
				bufferPack.r = bufferPack.r / 3;
				data._My_val.push(bufferPack);
				loopCnt = 0;
			}
			loopCnt++;
			/*
			LONG lBytesToWrite = nNumFramesToRead * blkAlign;

#pragma prefast(suppress: __WARNING_INCORRECT_ANNOTATION, "IAudioCaptureClient::GetBuffer SAL annotation implies a 1-byte buffer")

			LONG lBytesWritten = mmioWrite(hFile, reinterpret_cast<PCHAR>(pData), lBytesToWrite);
			if (lBytesToWrite != lBytesWritten) {
				logSys::putMessage("IAudioCaptureClient::GetBuffer said to read 0 frames", logSys::error, LOGINFO(nPasses));
				printf("mmioWrite wrote %u bytes on pass %u after %u frames: expected %u bytes\n", lBytesWritten, nPasses, nframes, lBytesToWrite);
				audClient->Stop();
				CancelWaitableTimer(hWakeUp);
				AvRevertMmThreadCharacteristics(hTask);
				pAudioCaptureClient->Release();
				CloseHandle(hWakeUp);
				audClient->Release();
				return E_UNEXPECTED;
			}
			*/
			nframes += nNumFramesToRead;

			hr = pAudioCaptureClient->ReleaseBuffer(nNumFramesToRead);
			if (FAILED(hr)) {
				logSys::putMessage("IAudioCaptureClient::ReleaseBuffer failed", logSys::error, LOGINFO(hr));
				audClient->Stop();
				CancelWaitableTimer(hWakeUp);
				AvRevertMmThreadCharacteristics(hTask);
				pAudioCaptureClient->Release();
				CloseHandle(hWakeUp);
				audClient->Release();
				return hr;
			}
			bFirstPacket = false;
		}
	}
}
	void audioTask()
	{
		logSys::putMessage("Starting audio thread...", logSys::info, LOGINFO(0));
		HRESULT hr = S_OK;

		hr = CoInitialize(NULL);
		if (FAILED(hr)) {
			logSys::putMessage("CoInitialize failed", logSys::error, LOGINFO(hr));
			return;
		}
		int res = audioTaskWorker();
		logSys::putMessage("audio task worker returned", logSys::info, LOGINFO(res));
		CoUninitialize();
		workerDead = true;
	}
	/*
	audio frame size = wfx->nChannels * (wfx->wBitsPerSample / 8)
	*/
	class audioHandler
	{
		std::thread *worker;
	public:
		audioHandler()
		{
			worker = new std::thread(&audioTask);
		}

		~audioHandler()
		{
			die.store(true);
			worker->join();
		}
		void checkState()
		{
			if (workerDead)
			{
				//delete worker;
				worker = new std::thread(&audioTask);
				workerDead = false;
			}
		}
		int16_t getNext()
		{
			int16_t ret = 0;
			if (data._My_val.size() > 0)
			{
				ret = data._My_val.front().l;
				data._My_val.pop();
			}
			return ret;
		}

	};