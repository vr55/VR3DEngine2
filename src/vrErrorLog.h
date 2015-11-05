#ifndef __VRERRORLOG_H__
#define __VRERRORLOG_H__

#include <windows.h>
#include <stdio.h>


#define MAX_ERROR_LOG_FILES		255


class vrErrorLog
{

public:
		vrErrorLog();

		bool Create( LPSTR strFileName );
		void WriteOut( const char *strString, ... );
		void WriteDate();
		void WriteTime();




private:
		LPSTR		strErrorLogFileName;
		FILE		*fHandle;


};

extern vrErrorLog	e_log;


#endif