// parser for "notes" files
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
typedef int __stdcall T_esprfunc0001(LPCWSTR lpFileName, void *written_to, void *output, void *a4, int some_size);

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
	HMODULE hDll = LoadLibrary(L"lib/espr_notes.dll");
	if (!hDll) {
		fprintf(stderr, "Can't load espr_notes.dll file. Exiting with error <%lu>!\n", GetLastError());
		exit(-1);
	}
	cout << "[!] Imagebase = " << hDll << endl;

	// "Import" methods from DLL
	//
	// the file format detection function is,
	// int __stdcall esprfunc0001(LPCWSTR lpFileName, int simple_buffer_ctx, LPVOID lpBuffer, int a4, int a5)
	//
	T_esprfunc0001 *esprfunc0001 = (T_esprfunc0001*)GetProcAddress(hDll, "esprfunc0001");
	int buffer[512] = {0};
	int buffer2[512] = {0};
	int buffer3[512] = {0};
	// int a4 = 0, some_size = 0;

	esprfunc0001(inputFile, buffer2, buffer, buffer3, 16);

	cout << "All Done ;)" << endl;

	print_hex((unsigned char*)buffer, 108); // only 108 bytes are needed!

	return 0;
}
