#include "stdafx.h"

Logger logger;

void Logger::initialize(HMODULE module)
{
	if(GetModuleFileNameA(module, modulePath, MAX_PATH) != 0) 
	{
		for(size_t i = strlen(modulePath); i > 0; i--)
		{
			if(modulePath[i] == '\\'){ modulePath[i + 1] = 0; break; }
		}
	}
}

void Logger::write(char *file, char *log, ... )
{
	va_list va_alist;
	
	char logbuf[8192] = { 0 };
	
	FILE * fp = NULL;

	va_start( va_alist, log );

	_vsnprintf( logbuf + strlen( logbuf ), 
		sizeof( logbuf ) - strlen( logbuf ), 
		log, va_alist );

	va_end( va_alist );

	char path[ MAX_PATH ] = { 0 };

	strcat_s( path, modulePath );
	strcat_s( path, file );

	errno_t ErrorNumber = fopen_s( &fp, path, "a" );

	if ( ErrorNumber == 0 && fp )
	{
		fprintf_s( fp, "%s\n", logbuf );
		fclose( fp );
	}
}

char* Logger::dirFile(char* file)
{
	static char path[ MAX_PATH ];
	memset( path, 0, MAX_PATH );
	strcat_s( path, modulePath );
	strcat_s( path, file );
	return path;
}