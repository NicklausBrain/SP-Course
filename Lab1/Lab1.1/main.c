#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>

const char* LAST_ERROR_KEY = "-e";
const char* SYSTEM_INFO_KEY = "-s";

void print_supported_args() {
	printf("Supported arguments:\n");
	printf("\t %s // prints last error\n", LAST_ERROR_KEY);
	printf("\t %s // prints system info\n", SYSTEM_INFO_KEY);
}

void generate_memory_error() {
	MEMORYSTATUSEX statex;
	statex.dwLength = sizeof(statex);
	GlobalMemoryStatusEx(&statex);

	byte* memory_buffer = LocalAlloc(
		LPTR,
		statex.ullTotalVirtual + 1); // try to allocate 1 byte more than ever possible

	// Handle error condition
	if (memory_buffer == NULL) {
		char* error_message;
		int last_error = GetLastError();
		FormatMessage(
			FORMAT_MESSAGE_ALLOCATE_BUFFER |
			FORMAT_MESSAGE_FROM_SYSTEM |
			FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			last_error,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			(LPTSTR)&error_message,
			0,
			NULL);

		printf(
			"LocalAlloc failed:\n\terror code: %d\n\terror message: %s\n",
			last_error,
			error_message);
	}
}

void print_system_info() {
	SYSTEM_INFO system_info;
	GetNativeSystemInfo(&system_info);
	switch (system_info.wProcessorArchitecture) {
	case PROCESSOR_ARCHITECTURE_MIPS: printf("This is a MIPS computer.\n"); break;
	case PROCESSOR_ARCHITECTURE_ALPHA: printf("This is an ALPHA computer.\n"); break;
	case PROCESSOR_ARCHITECTURE_PPC: printf("This is a PPC computer.\n"); break;
	case PROCESSOR_ARCHITECTURE_SHX: printf("This is a SHX computer.\n"); break;
	case PROCESSOR_ARCHITECTURE_ARM: printf("This is a ARM computer.\n"); break;
	case PROCESSOR_ARCHITECTURE_IA64: printf("This is an IA64 computer.\n"); break;
	case PROCESSOR_ARCHITECTURE_ALPHA64: printf("This is an ALPHA64 computer.\n"); break;
	case PROCESSOR_ARCHITECTURE_MSIL: printf("This is a MSIL computer.\n"); break;
	case PROCESSOR_ARCHITECTURE_AMD64: printf("This is an AMD64 computer.\n"); break;
	case PROCESSOR_ARCHITECTURE_IA32_ON_WIN64: printf("This is an IA32_ON_WIN64 computer.\n"); break;
	case PROCESSOR_ARCHITECTURE_NEUTRAL: printf("This is a NEUTRAL computer.\n"); break;
	case PROCESSOR_ARCHITECTURE_ARM64: printf("This is an ARM64 computer.\n"); break;
	case PROCESSOR_ARCHITECTURE_ARM32_ON_WIN64: printf("This is an ARM32_ON_WIN64 computer.\n"); break;
	case PROCESSOR_ARCHITECTURE_IA32_ON_ARM64: printf("This is an IA32_ON_ARM64 computer.\n"); break;
	}

	MEMORYSTATUSEX statex;
	statex.dwLength = sizeof(statex);
	GlobalMemoryStatusEx(&statex);
	printf("There is  %d percent of memory in use.\n", statex.dwMemoryLoad);
	printf("There are %llu total bytes of physical memory.\n", statex.ullTotalPhys);
	printf("There are %llu free  bytes of physical memory.\n", statex.ullAvailPhys);
	printf("There are %llu total bytes of paging file.\n", statex.ullTotalPageFile);
	printf("There are %llu free  bytes of paging file.\n", statex.ullAvailPageFile);
	printf("There are %llu total bytes of virtual memory.\n", statex.ullTotalVirtual);
	printf("There are %llu free  bytes of virtual memory.\n", statex.ullAvailVirtual);
}

int main(int argc, char** argv) {
	if (argc < 2) {
		printf("No arguments specified!\n");
		print_supported_args();
		exit(EXIT_FAILURE);
	}
	else if (strstr(argv[1], LAST_ERROR_KEY)) { // when -e
		printf("Trying to generate error by allocating unavaildable memory...\n");
		generate_memory_error(); // generate and describe an error
		exit(EXIT_SUCCESS);
	}
	else if (strstr(argv[1], SYSTEM_INFO_KEY)) {
		printf("Printing system info...\n");
		print_system_info();
		exit(EXIT_SUCCESS);
	}
	else {
		printf("Argument %s is not supported!", argv[1]);
		print_supported_args();
		exit(EXIT_FAILURE);
	}
}
