#include "stdafx.h"

#define INIDB_VERSION_NUMBER "1.2"

extern "C"
{
	__declspec(dllexport) void __stdcall RVExtension(char *output, int outputSize, const char *function) {
		outputSize -= 1;

		if(_stricmp(function, "version") == 0) {
			strncpy(output, INIDB_VERSION_NUMBER, outputSize);
		} else	{
			char* func = strtok((char*)function, ";");

			if(func) {
				if(_stricmp(func, "read") == 0) {

					char* file = strtok(NULL, ";");
					char* sec = strtok(NULL, ";");
					char* key = strtok(NULL, ";");

					if(file != NULL && sec != NULL && key != NULL) {
						char realFile[MAX_PATH] = {0};
						sprintf_s(realFile, MAX_PATH, "db\\%s.ini", file);
						char trueValue[8192] = {0};

						if(Ini::Read(logger.dirFile(realFile), sec, key, "c0f916b469c17e0f967c6774e0d837fac0f916b469c17e0f967c6774e0d837fa", trueValue, 8192)){
							if(_stricmp(trueValue, "c0f916b469c17e0f967c6774e0d837fac0f916b469c17e0f967c6774e0d837fa") == 0){
								strncpy(output, "[false];", outputSize);
							} else {
								sprintf_s(output, outputSize, "[true, '%s'];", trueValue);
							}
						} else {
							strncpy(output, "[false];", outputSize);
						}
					} else {
						strncpy(output, "[false];", outputSize);
					}
				} else if(_stricmp(func, "write") == 0)	{
					
					char* file = strtok(NULL, ";");
					char* sec = strtok(NULL, ";");
					char* key = strtok(NULL, ";");
					char* val = strtok(NULL, ";");

					if(file != NULL && sec != NULL && key != NULL && val != NULL) {

						char realFile[MAX_PATH] = {0};
						sprintf_s(realFile, MAX_PATH, "db\\%s.ini", file);
						
						if(Ini::Write(logger.dirFile(realFile), sec, key, val))	{
							strncpy(output, "[true];", outputSize);
						} else {
							strncpy(output, "[false];", outputSize);
						}
					} else {
						strncpy(output, "[false];", outputSize);
					}
				} else if(_stricmp(func, "deletesection") == 0)	{
					
					char* file = strtok(NULL, ";");
					char* sec = strtok(NULL, ";");
					
					if(file != NULL && sec != NULL) {
						char realFile[MAX_PATH] = {0};
						sprintf_s(realFile, MAX_PATH, "db\\%s.ini", file);
						
						if(Ini::Deletesection(logger.dirFile(realFile), sec))	{
							strncpy(output, "[true];", outputSize);
						} else {
							strncpy(output, "[false];", outputSize);
						}
					} else {
						strncpy(output, "[false];", outputSize);
					}
				} else if(_stricmp(func, "deletekey") == 0)	{
					
					char* file = strtok(NULL, ";");
					char* sec = strtok(NULL, ";");
					char* key = strtok(NULL, ";");
					
					if(file != NULL && sec != NULL) {
						char realFile[MAX_PATH] = {0};
						sprintf_s(realFile, MAX_PATH, "db\\%s.ini", file);
						
						if(Ini::Deletekey(logger.dirFile(realFile), sec, key))	{
							strncpy(output, "[true];", outputSize);
						} else {
							strncpy(output, "[false];", outputSize);
						}
					} else {
						strncpy(output, "[false];", outputSize);
					}
				} else if(_stricmp(func, "exists") == 0) {
					char* file = strtok(NULL, ";");

					if(file != NULL) {
						char realFile[MAX_PATH] = {0};

						sprintf_s(realFile, MAX_PATH, "db\\%s.ini", file);
						FILE* fp = fopen(logger.dirFile(realFile), "r");

						if(fp) {
							fclose(fp);
							strncpy(output, "[true, true];", outputSize);
						} else {
							strncpy(output, "[true, false];", outputSize);
						}
					} else {
						strncpy(output, "[false];", outputSize);
					}
				} else if(_stricmp(func, "delete") == 0) {
					char* file = strtok(NULL, ";");

					if(file != NULL) {
						char realFile[MAX_PATH] = {0};

						sprintf_s(realFile, MAX_PATH, "db\\%s.ini", file);

						if(DeleteFileA(logger.dirFile(realFile))) {
							strncpy(output, "[true];", outputSize);
						} else {
							strncpy(output, "[false];", outputSize);
						}
					} else {
						strncpy(output, "[false];", outputSize);
					}
				} else if(_stricmp(func, "crc") == 0) {
					char* toHash = strtok(NULL, ";");

					if(toHash != NULL) {
						sprintf_s(output, outputSize, "[true, '%X'];", crc32(toHash, strlen(toHash)));
					} else {
						strncpy(output, "[false];", outputSize);
					}
				} else if(_stricmp(func, "md5") == 0) {
					char* toHash = strtok(NULL, ";");

					if(toHash != NULL) {
						unsigned char digest[16];

						MD5_CTX context;
						MD5_Init(&context);
						MD5_Update(&context, toHash, strlen(toHash));
						MD5_Final(digest, &context);

						// Motherfuckin' magic.
						sprintf_s(output, outputSize, "[true, '%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x'];", 
							digest[0], digest[1], digest[2], digest[3], digest[4], digest[5], digest[6], 
							digest[7], digest[8], digest[9], digest[10], digest[11], digest[12], digest[13], 
							digest[14], digest[15]);
					} else {
						strncpy(output, "[false];", outputSize);
					}
				} else if(_stricmp(func, "b64_enc") == 0) {
					char* toHash = strtok(NULL, ";");

					if(toHash != NULL) {
						sprintf_s(output, outputSize, "[true, '%s'];", base64_encode((unsigned char*)toHash, strlen(toHash)).c_str());
					} else {
						strncpy(output, "[false];", outputSize);
					}
				} else if(_stricmp(func, "b64_dec") == 0) {
					char* toHash = strtok(NULL, ";");

					if(toHash != NULL) {
						sprintf_s(output, outputSize, "[true, '%s'];", base64_decode(toHash).c_str());
					} else {
						strncpy(output, "[false];", outputSize);
					}
				} else {
					strncpy(output, "[false];", outputSize);
				}
			} else {
				strncpy(output, "[false];", outputSize);
			}
		}
		return;
	}
};

BOOL APIENTRY DllMain( HMODULE hModule, DWORD dwReason, LPVOID lpReserved )
{
	if(dwReason == DLL_PROCESS_ATTACH)
	{
		logger.initialize(hModule);
		//logger.write("inidb.log", "Initialized!");
	}

	return TRUE;
}