#pragma once

class Logger
{
public:
	void initialize(HMODULE module);
	void write(char *file, char *log, ... );
	char* dir(){ return modulePath; }
	char* dirFile(char* file);

private:
	char modulePath[ MAX_PATH ];
};

extern Logger logger;