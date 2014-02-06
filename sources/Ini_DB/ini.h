#pragma once

class Ini
{
public:

	static bool Read(char* file, char* section, char* key, char* defaultValue, char* output, size_t outputSize);
	static bool Write(char* file, char* section, char* key, char* value);
	static bool Deletesection(char* file, char* section);
	static bool Deletekey(char* file, char* section, char* key);
};