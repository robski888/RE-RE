// parser for iWork '09 files
#include <windows.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <time.h>
#include <assert.h>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

typedef int __cdecl T_sub_100142C0(LPCWSTR lpFileName, int *simple_buffe_ctx);

#define DEBUG

#ifdef DEBUG
void print_hex(unsigned char *str, int len)
{
	int i;
	for (i = 0; i < len; ++i)
		printf("%02x", str[i]);
	printf("\n");
}
#endif

int main(int argc, char *argv[])
{
	if (argc < 2) {
		fprintf(stderr, "Usage: %s <.keynote file>\n", argv[0]);
		return -1;
	}

	// setup input
	wchar_t *inputFile;
	int len = mbstowcs(NULL, argv[1], 0);
	inputFile = new wchar_t[len+1];
	for (int i = 0; i < len; i++) {
		inputFile[i] = (char)argv[1][i];
	}
	inputFile[len] = L'\0';

	// Load DLL
	HMODULE hDll = LoadLibrary(L"lib/espr_office.dll");
	if (!hDll) {
		fprintf(stderr, "Can't load espr_office.dll file. Exiting with error <%lu>!\n", GetLastError());
		exit(-1);
	}
	cout << "[!] Imagebase = " << hDll << endl;

	// "Import" methods from DLL
	//
	// the file format detection function is,
	// int __stdcall esprfunc0001(LPCWSTR lpFileName, int simple_buffer_ctx, LPVOID lpBuffer, int a4, int a5)
	//
	// and esprfunc0001 calls sub_100142C0 function to parser iWork '09 files
	T_sub_100142C0 *sub_100142C0 = (T_sub_100142C0*)0x100142C0;
	int buffer[512] = {0};

	sub_100142C0(inputFile, buffer);

	cout << "[+] All Done ;)" << endl;

	print_hex((unsigned char*)buffer, 108); // only 108 bytes are needed!

	return 0;
}
