#include "stdafx.h"

bool Ini::Read(char* file, char* section, char* key, char* defaultValue, char* output, size_t outputSize)
{
	if(GetPrivateProfileStringA(section, key, defaultValue, output, outputSize, file) == NULL)
	{
		return false;
	}

	if(GetLastError() == 2)
	{
		return false;
	}

	return true;
}

bool Ini::Write(char* file, char* section, char* key, char* value)
{
	if(WritePrivateProfileStringA(section, key, value, file) == FALSE)
	{
		return false;
	}

	return true;
}

bool Ini::Deletesection(char* file, char* section) 
{
   if(WritePrivateProfileStructA(section, NULL, NULL, 0, file) == NULL)
   {
	   return false;
   }
   return true;
}

bool Ini::Deletekey(char* file, char* section, char* key) 
{
   if(WritePrivateProfileStructA(section, key, NULL, 0, file) == NULL)
   {
	   return false;
   }
   return true;
}