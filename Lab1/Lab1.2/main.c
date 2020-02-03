#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <Windows.h>

#define READ_BUFFER_SIZE 256

const char* ASCII_SOURCE_KEY = "-a";
const char* UNICODE_SOURCE_KEY = "-u";

void print_supported_args() {
	printf("Required arguments:\n");
	printf("\t %s // conver ASCII to UNICODE | ", ASCII_SOURCE_KEY);
	printf("%s // conver UNICODE to ASCII\n", UNICODE_SOURCE_KEY);
	printf("\t path to the source file\n");
	printf("\t path to the target file\n");
}

bool convert_to_unicode(HANDLE source_file, HANDLE target_file) {
	char buffer[READ_BUFFER_SIZE];
	int bytes_read = 0;
	do {
		bool read_result = ReadFile(
			source_file,
			&buffer,
			READ_BUFFER_SIZE,
			&bytes_read,
			NULL);

		if (!read_result) {
			printf("Reading source file failed\n");
			return false;
		}

		// 1. determine required unicode (UTF-16) buffer size
		int unicode_string_len = MultiByteToWideChar(
			CP_UTF8,
			0,
			buffer,
			bytes_read,
			NULL,
			0);
		// 2. allocate unicode (UTF-16) string
		wchar_t* unicode_string = calloc(unicode_string_len, sizeof(wchar_t));
		// 3. convert raw bytes to unicode
		MultiByteToWideChar(
			CP_UTF8,
			0,
			buffer,
			bytes_read,
			unicode_string,
			unicode_string_len);
		// 4. save result
		int bytes_written;
		bool write_result = WriteFile(
			target_file,
			unicode_string,
			unicode_string_len * sizeof(wchar_t),
			&bytes_written,
			NULL);

		free(unicode_string);

		if (!write_result) {
			printf("Writing target file failed\n");
			return false;
		}
	} while (bytes_read != 0); // EOF

	return true;
}

bool convert_to_ascii(HANDLE source_file, HANDLE target_file) {
	char buffer[READ_BUFFER_SIZE];
	int bytes_read = 0;
	do {
		// 0. start reading raw bytes
		bool read_result = ReadFile(
			source_file,
			&buffer,
			READ_BUFFER_SIZE,
			&bytes_read,
			NULL);

		if (!read_result) {
			printf("Reading source file failed\n");
			return false;
		}

		// 1. determine required unicode buffer size
		int unicode_string_len = MultiByteToWideChar(
			CP_UTF8,
			0,
			buffer,
			bytes_read,
			NULL,
			0);
		// 2. allocate unicode (UTF16) string
		wchar_t* unicode_string = calloc(unicode_string_len, sizeof(wchar_t));
		// 3. convert raw bytes to unicode
		MultiByteToWideChar(
			CP_UTF8,
			0,
			buffer,
			bytes_read,
			unicode_string,
			unicode_string_len);

		// 4. determine required ASCII string length
		int ascii_string_len = WideCharToMultiByte(
			CP_ACP,
			0,
			unicode_string,
			unicode_string_len,
			NULL,
			0,
			NULL,
			NULL);
		char* askii_string = calloc(ascii_string_len, sizeof(char));
		// 5. convert UTF-16 string to ASCII
		WideCharToMultiByte(
			CP_ACP,
			0,
			unicode_string,
			unicode_string_len,
			askii_string,
			ascii_string_len,
			NULL,
			NULL);
		free(unicode_string);
		// 5. save result
		int bytes_written;
		bool write_result = WriteFile(
			target_file,
			askii_string,
			ascii_string_len * sizeof(char),
			&bytes_written,
			NULL);
		free(askii_string);

		if (!write_result) {
			printf("Writing target file failed\n");
			return false;
		}
	} while (bytes_read != 0); // EOF

	return true;
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

	bool conversion_result = false;

	if (strstr(argv[1], ASCII_SOURCE_KEY)) {
		printf("Converting ASCII to Unicode...\n");
		conversion_result = convert_to_unicode(source_file, target_file);
	}

	if (strstr(argv[1], UNICODE_SOURCE_KEY)) {
		printf("Converting Unicode to ASCII...\n");
		conversion_result = convert_to_ascii(source_file, target_file);
	}

	CloseHandle(source_file);
	CloseHandle(target_file);

	if (conversion_result) {
		printf("Conversion succeeded!\n");
		exit(EXIT_SUCCESS);
	}
	else {
		printf("Conversion failed!\n");
		exit(EXIT_FAILURE);
	}
}
