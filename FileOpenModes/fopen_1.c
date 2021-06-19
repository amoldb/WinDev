#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define BUFFER_SIZE 128
int main(int argc, char* argv[])
{
	char 	rBuffer[BUFFER_SIZE];
	FILE* 	fp;
	size_t	bytes_written;
	size_t	strSize;

	if(argc != 2)
	{
		printf("Usage error: %s file_name\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	// Read mode.
	fp = fopen(argv[1], "r");
	if(fp == NULL)
	{
		printf("Failed to open file in read mode.\n");
		exit(EXIT_FAILURE);
	}
	printf("First line of file: %s", fgets(rBuffer, BUFFER_SIZE, fp));

	fclose(fp);
	fp = NULL;
	
	// Write mode.
	fp = fopen(argv[1], "w");
	if(fp == NULL)
	{
		printf("Failed to open file in write mode.\n");
		exit(EXIT_FAILURE);
	}
	strcpy(rBuffer, "Line written using fwrite function.");
	strSize = strlen(rBuffer);
	bytes_written = fwrite(rBuffer, sizeof(char), strSize, fp);
	printf("\n* [%zu] bytes written, and expected [%lld]\n", bytes_written, strSize);
	if(bytes_written != strSize)
	{
		printf("fwrite call fails.\n");
		exit(EXIT_FAILURE);
	}

	fclose(fp);
	fp = NULL;

	// Append mode.
	fp = fopen(argv[1], "a");
	if(fp == NULL)
	{
		printf("Failed to open file in append mode.\n");
		exit(EXIT_FAILURE);
	}
	strcpy(rBuffer, "Line appended using fwrite function.");
	strSize = strlen(rBuffer);
	bytes_written = fwrite(rBuffer, sizeof(char), strSize, fp);
	printf("\n* [%zu] bytes written, and expected [%lld]\n", bytes_written, strSize);
	if(bytes_written != strSize)
	{
		printf("fwrite call fails to append.\n");
		exit(EXIT_FAILURE);
	}

	fclose(fp);
	fp = NULL;

	// Read and write (r+) mode.
	fp = fopen(argv[1], "r+");
	if(fp == NULL)
	{
		printf("Failed to open file in read and write (r+) mode.\n");
		exit(EXIT_FAILURE);
	}
	printf("First line of file: %s", fgets(rBuffer, BUFFER_SIZE, fp));

	strcpy(rBuffer, "Line written using fwrite function in r+ mode.");
	strSize = strlen(rBuffer);
	bytes_written = fwrite(rBuffer, sizeof(char), strSize, fp);
	printf("\n* [%zu] bytes written, and expected [%lld]\n", bytes_written, strSize);
	if(bytes_written != strSize)
	{
		printf("fwrite call fails to write in r+ mode.\n");
		exit(EXIT_FAILURE);
	}
	fclose(fp);
	fp = NULL;

	// write (w+) mode.
	fp = fopen(argv[1], "w+");
	if(fp == NULL)
	{
		printf("Failed to open file in write (w+) mode.\n");
		exit(EXIT_FAILURE);
	}
	
	strcpy(rBuffer, "Line written using fwrite function in w+ mode.");
	strSize = strlen(rBuffer);
	bytes_written = fwrite(rBuffer, sizeof(char), strSize, fp);
	printf("\n* [%zu] bytes written, and expected [%lld]\n", bytes_written, strSize);
	if(bytes_written != strSize)
	{
		printf("fwrite call fails to write in w+ mode.\n");
		exit(EXIT_FAILURE);
	}
	fclose(fp);
	fp = NULL;

	// Append (a+) mode.
	fp = fopen(argv[1], "a+");
	if(fp == NULL)
	{
		printf("Failed to open file in write (w+) mode.\n");
		exit(EXIT_FAILURE);
	}
	
	printf("First line of file: %s", fgets(rBuffer, BUFFER_SIZE, fp));
	strcpy(rBuffer, "Line written using fwrite function in a+ mode.");
	strSize = strlen(rBuffer);
	bytes_written = fwrite(rBuffer, sizeof(char), strSize, fp);
	printf("\n* [%zu] bytes written, and expected [%lld]\n", bytes_written, strSize);
	if(bytes_written != strSize)
	{
		printf("fwrite call fails to write in w+ mode.\n");
		exit(EXIT_FAILURE);
	}
	fclose(fp);
	fp = NULL;

	// Mode modifier with w
	fp = fopen(argv[1], "wx");
	if(fp != NULL)
	{
		printf("fopen call fails: %s file overwritten.\n", argv[1]);
		exit(EXIT_FAILURE);
	}
	
	fclose(fp);
	fp = NULL;

	// Mode modifier with w+
	fp = fopen(argv[1], "w+x");
	if(fp != NULL)
	{
		printf("fopen call fails: %s file overwritten.\n", argv[1]);
		exit(EXIT_FAILURE);
	}
	
	fclose(fp);
	fp = NULL;
}
