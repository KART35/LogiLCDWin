#pragma once
#include "stdafx.h"
#include <stdio.h>
#include <string>
#include <ctime>
#include <strstream>
#include <fstream>

#define LOGINFO(X) logSys::errInfo(__LINE__, __FUNCTION__, __FILE__, X )
namespace logSys{
	typedef enum severity {
		debug,
		info,
		warn,
		error
	};

	struct eInf_
	{
		unsigned int line = 0;
		long errCode = 0;
		std::string cName;
		std::string fName;
	};

	class errInfo
	{
	protected:
		eInf_ info;
	public:

		errInfo(int ln, std::string clName, std::string fileName, long eCode)
		{
			this->info.line = ln;
			this->info.cName = clName;
			this->info.fName = fileName;
			this->info.errCode = eCode;
		}
		eInf_ get()
		{
			return this->info;
		}
	};

	void putMessage(std::string mess, severity sev, errInfo info);

}