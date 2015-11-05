#include "vrErrorLog.h"

#include <winnls.h>




//GLOBAL
vrErrorLog	e_log;
/////////////////


vrErrorLog::vrErrorLog()
{

	strErrorLogFileName = NULL;
}

//==============================================================//
//																//
//==============================================================//


bool vrErrorLog::Create( LPSTR strFileName )
{

FILE		*outfile;

outfile = fopen( strFileName, "a+t");		//создаем новый файл или открываем старый, если есть
if ( outfile == NULL ) return false;
//fprintf( outfile, "%s", message );

//fprintf( outfile, "Error Log File Started at %s %s\n\n", time, date );
fclose( outfile );

strErrorLogFileName = strFileName;

return true;


}




//==============================================================//
//																//
//==============================================================//
void vrErrorLog::WriteOut( const char *strString, ... )
{

FILE		*outfile;
char		strText[65536];
va_list		argumentPtr;
//char		time[32];


if ( strString == NULL ) return ;

va_start( argumentPtr, strString );
vsprintf( strText, strString, argumentPtr );
va_end( argumentPtr );

//if ( strErrorLogFileName == NULL ) strErrorLogFileName = "temp";

if ( strErrorLogFileName == NULL ) return;

outfile = fopen( strErrorLogFileName, "a+t");		//создаем новый файл или открываем старый, если есть
if ( outfile == NULL ) return;

//GetTimeFormat( LOCALE_SYSTEM_DEFAULT, TIME_FORCE24HOURFORMAT, NULL, "HH':'mm':'ss", time, 32 );

//fprintf( outfile, "[%s]", time );

fprintf( outfile, "%s", strText );
fclose( outfile );



}


//==============================================================//
//																//
//==============================================================//

void vrErrorLog::WriteDate()
{

char		time[32];
char		date[32];


GetTimeFormat( LOCALE_SYSTEM_DEFAULT, TIME_FORCE24HOURFORMAT, NULL, "HH':'mm':'ss", time, 32 );
GetDateFormat( LOCALE_SYSTEM_DEFAULT, NULL, NULL, "dddd ',' dd MMM yyyy", date, 32 );

WriteOut( "\n[%s %s]\n\n", time, date );

}

//==============================================================//
//																//
//==============================================================//


void vrErrorLog::WriteTime()
{
char		time[32];


GetTimeFormat( LOCALE_SYSTEM_DEFAULT, TIME_FORCE24HOURFORMAT, NULL, "HH':'mm':'ss", time, 32 );

WriteOut( "\n[%s] ", time );


}
