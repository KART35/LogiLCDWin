#pragma once
#include "stdafx.h"
#include <stdio.h>
#include <string>
#include <ctime>
#include <strstream>
#include <fstream>

//! macro for logSys::putMessage. Usage: logSys::putMessage(LOGINFO(long))
#define LOGINFO(X) logSys::errInfo(__LINE__, __FUNCTION__, __FILE__, X )


namespace logSys{
	
	//! used to define how pear shaped things are
	typedef enum severity 
	{
		debug, //!< debugging messages. these should be disabled in release versions
		info, //!< info messages, not as verbose as debug
		warn, //! a recoverable error
		error //! a fatal error.
	};

	struct eInf_
	{
		unsigned int line = 0; //!< line the call to putMessage is from
		long errCode = 0; //!< error code, or other useful info
		std::string cName; //!< class or function name
		std::string fName; //!< file name
	};
	
	//! an easy to create data structure for error messages
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
	//! prints info in arguments to a log file with a timestamp
	void putMessage(std::string mess, severity sev, errInfo info);

}
