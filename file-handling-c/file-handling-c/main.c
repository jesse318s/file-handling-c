#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 999
#define SCRIPT_TAG "<script>"
#define SCRIPT_TAG_CLOSE "</script>"

static void fillWithSpaces(char* str, const size_t length);
static void processScriptTags(char* inFileStringPtr, int* scriptIsClosedPtr);
static void processTxtLines(FILE* inFile, FILE* outFile);

int main() {
	FILE* inFile = NULL;
	FILE* outFile = NULL;

	fopen_s(&inFile, "input.txt", "r");
	fopen_s(&outFile, "output.txt", "w");

	if (!inFile || !outFile) {
		perror("Error: file could not be opened");

		if (inFile) fclose(inFile);

		if (outFile) fclose(outFile);

		return 1;
	}

	processTxtLines(inFile, outFile);
	fclose(inFile);
	fclose(outFile);
	printf("\nProgram execution complete\n");

	return 0;
}

static void fillWithSpaces(char* str, const size_t length) {
	for (size_t i = 0; i < length; ++i) {
		str[i] = ' ';
	}
}

static void processScriptTags(char* inFileStringPtr, int* scriptIsClosedPtr) {
	char* scriptStart = strstr(inFileStringPtr, SCRIPT_TAG);
	char* scriptEnd = strstr(inFileStringPtr, SCRIPT_TAG_CLOSE);

	if (scriptStart) {
		*scriptIsClosedPtr = 0;
		fillWithSpaces(inFileStringPtr, strlen(inFileStringPtr));
	}

	if (scriptEnd) {
		*scriptIsClosedPtr = 1;
		fillWithSpaces(inFileStringPtr, strlen(inFileStringPtr));
		inFileStringPtr[strlen(inFileStringPtr) - 1] = '\n';
		printf("WARNING - inline script found: the script has been removed\n\n");
	}

	if (*scriptIsClosedPtr == 0 && !scriptStart) {
		printf("%s", inFileStringPtr);
		fillWithSpaces(inFileStringPtr, strlen(inFileStringPtr));
	}
}

static void processTxtLines(FILE* inFile, FILE* outFile) {
	char inFileString[BUFFER_SIZE] = { '\0' };
	int scriptIsClosed = 1;

	while (fgets(inFileString, BUFFER_SIZE, inFile)) {
		if (inFileString[strlen(inFileString) - 1] != '\n' && !feof(inFile)) {
			fprintf(stderr, "Error: buffer overflow");

			return;
		}

		processScriptTags(inFileString, &scriptIsClosed);
		fprintf(outFile, "%s", inFileString);
	}
}