#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <Windows.h>

#define BUFFER_SIZE 256

const char* ASCII_SOURCE_KEY = "-a";
const char* UNICODE_SOURCE_KEY = "-u";

void print_supported_args() {
	printf("Required arguments:\n");
	printf("\t %s // conver ASCII to UNICODE | ", ASCII_SOURCE_KEY);
	printf("%s // conver UNICODE to ASCII\n", UNICODE_SOURCE_KEY);
	printf("\t path to the source file\n");
	printf("\t path to the target file\n");
}

int main(int argc, char** argv) {
	if (argc < 4 || !argv[2] || !argv[3]) {
		printf("Required arguments unspecified!\n");
		print_supported_args();
		exit(EXIT_FAILURE);
	}

	if (!strstr(argv[1], ASCII_SOURCE_KEY) && !strstr(argv[1], UNICODE_SOURCE_KEY)) {
		printf("Argument %s is not supported!", argv[1]);
		print_supported_args();
		exit(EXIT_FAILURE);
	}

	char* source_path = argv[2];
	char* target_path = argv[3];

	HANDLE source_file = CreateFile(
		source_path,
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	if (source_file == INVALID_HANDLE_VALUE) {
		printf("Unable to open the source file '%s'\n", source_path);
		exit(EXIT_FAILURE);
	}

	HANDLE target_file = CreateFile(
		target_path,
		GENERIC_WRITE,
		0,
		NULL,
		CREATE_NEW,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	if (target_file == NULL) {
		printf("Unable to open the target file '%s'\n", target_path);
		exit(EXIT_FAILURE);
	}

	if (strstr(argv[1], ASCII_SOURCE_KEY)) {
		printf("Converting ASCII to Unicode...\n");
		char buffer[BUFFER_SIZE];
		int bytes_read = 0;
		do {
			bool read_result = ReadFile(
				source_file,
				&buffer,
				BUFFER_SIZE,
				&bytes_read,
				NULL);

			// 1. determine required unicode buffer size
			int unicode_string_len = MultiByteToWideChar(
				CP_UTF8,
				0,
				buffer,
				bytes_read,
				NULL,
				0);
			// 2. allocate unicode string
			wchar_t* unicode_string = calloc(unicode_string_len, sizeof(wchar_t));
			// 3. convert
			MultiByteToWideChar(
				CP_UTF8,
				0,
				buffer,
				bytes_read,
				unicode_string,
				unicode_string_len);

			// printf("%ws", unicode_string); for debug
			// 4. Save result
			int bytes_written;
			bool write_result = WriteFile(
				target_file,
				unicode_string,
				unicode_string_len * sizeof(wchar_t),
				&bytes_written,
				NULL);
			// printf("%d", bytes_written); for debug
		} while (bytes_read != 0); // EOF
	}

	CloseHandle(source_file);
	CloseHandle(target_file);
	exit(EXIT_SUCCESS);
}
