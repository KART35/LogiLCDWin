#include "log.h"

void logSys::putMessage(std::string mess, severity sev, errInfo info)
{

	std::string sevstr;
	switch (sev)
	{
	case severity::debug:
		sevstr = "[DBG]";
		break;
	case severity::error:
		sevstr = "[ERR]";
		break;
	case severity::info:
		sevstr = "[INF]";
		break;
	case severity::warn:
		sevstr = "[WAR]";
		break;
	default:
		sevstr = "[UNK]";
	}
	tm  now;
	time_t rawTime;
	time(&rawTime);
	localtime_s(&now, &rawTime);
	std::strstream time;
	time.clear();
	time << now.tm_hour << ":" << now.tm_min << ":" << now.tm_sec << std::ends;

	std::string tstr(time.str());


	std::ofstream f;
	f.open("log.txt", std::ios_base::app);
	f << tstr << " " << sevstr << ": " << mess
		<< " at " << info.get().line
		<< " in " << info.get().fName
		<< " (" << info.get().cName
		<< ") Code: " << info.get().errCode
		<< std::endl;
	f.close();

}