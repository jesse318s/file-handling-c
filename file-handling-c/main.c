#include <stdio.h>

static void endScriptRemoval(char* inFileStringPtr, char* c1);
static void processScriptTags(char* inFileStringPtr, int* scriptIsClosedPtr);
static void processBreakTags(char* inFileStringPtr);
static void processTxtLines(FILE* inFile, FILE* outFile);

int main() {
	int numClosed;
	FILE* inFile;
	FILE* outFile;

	fopen_s(&inFile, "input.txt", "r");
	fopen_s(&outFile, "output.txt", "w");

	if (!inFile || !outFile) return 1;

	printf("Program ready\n\n\n");
	processTxtLines(inFile, outFile);
	numClosed = _fcloseall();
	printf("\nNumber of files closed successfully: %u", numClosed);
	return 0;
}

static void endScriptRemoval(char* inFileStringPtr, char* c1) {
	int count;

	for (count = 0; count < strlen(inFileStringPtr); ++count) {
		if (&inFileStringPtr[count] == c1) {
			inFileStringPtr[count] = '\n';
			break;
		}

		inFileStringPtr[count] = ' ';
	}

	printf("WARNING - inline script found: the script has been removed to resolve the issue\n\n");
}

static void processScriptTags(char* inFileStringPtr, int* scriptIsClosedPtr) {
	int count;
	char* c1;
	char* c2;
	char* c3;
	char* c4;
	char* c5;
	char* c6;
	char* c7;
	char* c8;
	char* c9;

	for (count = 0; count < strlen(inFileStringPtr); ++count) {
		if (count < 7) continue;

		c1 = &inFileStringPtr[count];
		c2 = &inFileStringPtr[count - 1];
		c3 = &inFileStringPtr[count - 2];
		c4 = &inFileStringPtr[count - 3];
		c5 = &inFileStringPtr[count - 4];
		c6 = &inFileStringPtr[count - 5];
		c7 = &inFileStringPtr[count - 6];
		c8 = &inFileStringPtr[count - 7];

		if (*c8 == '<' && *c7 == 's' && *c6 == 'c' && *c5 == 'r'
			&& *c4 == 'i' && *c3 == 'p' && *c2 == 't' && *c1 == '>') {
			*scriptIsClosedPtr = 0;
			*c1 = ' ';
			*c2 = ' ';
			*c3 = ' ';
			*c4 = ' ';
			*c5 = ' ';
			*c6 = ' ';
			*c7 = ' ';
			*c8 = ' ';
		};

		if (count < 8) continue;

		c1 = &inFileStringPtr[count];
		c2 = &inFileStringPtr[count - 1];
		c3 = &inFileStringPtr[count - 2];
		c4 = &inFileStringPtr[count - 3];
		c5 = &inFileStringPtr[count - 4];
		c6 = &inFileStringPtr[count - 5];
		c7 = &inFileStringPtr[count - 6];
		c8 = &inFileStringPtr[count - 7];
		c9 = &inFileStringPtr[count - 8];

		if (!(*c9 == '<' && *c8 == '/' && *c7 == 's' && *c6 == 'c' && *c5 == 'r'
			&& *c4 == 'i' && *c3 == 'p' && *c2 == 't' && *c1 == '>')) continue;

		endScriptRemoval(inFileStringPtr, c1);
		*scriptIsClosedPtr = 1;
	}

	if (*scriptIsClosedPtr == 1) return;

	printf(inFileStringPtr);

	for (count = 0; count < strlen(inFileStringPtr); ++count) {
		inFileStringPtr[count] = ' ';
	}
}

static void processBreakTags(char* inFileStringPtr) {
	int count;
	char* c1;
	char* c2;
	char* c3;
	char* c4;
	char* c5;
	char* c6;

	for (count = 0; count < strlen(inFileStringPtr); ++count) {
		if (count < 5) continue;

		c1 = &inFileStringPtr[count];
		c2 = &inFileStringPtr[count - 1];
		c3 = &inFileStringPtr[count - 2];
		c4 = &inFileStringPtr[count - 3];
		c5 = &inFileStringPtr[count - 4];
		c6 = &inFileStringPtr[count - 5];

		if (!(*c6 == '<' && *c5 == 'b' && *c4 == 'r' && *c3 == ' ' && *c2 == '/' && *c1 == '>')) continue;

		*c1 = ' ';
		*c2 = ' ';
		*c3 = ' ';
		*c4 = ' ';
		*c5 = ' ';
		*c6 = ' ';
		printf(inFileStringPtr);
		printf("WARNING - break tag found: the break tag has been removed to resolve the issue\n\n");
	}
}

static void processTxtLines(FILE* inFile, FILE* outFile) {
	char inFileString[999];
	int scriptIsClosed = 1;

	while (fgets(inFileString, 999, inFile)) {
		processScriptTags(inFileString, &scriptIsClosed);
		processBreakTags(inFileString);
		fprintf(outFile, inFileString);
	}
}