#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "include/dirent.h"
#include <limits.h>
#include <string.h>
#include <sys/stat.h>

#include <windows.h>

#define TRUE 1
#define FALSE 0

char buffer[256];
const char* name = "C:\\test\\result.txt";

void listdir(const char* name, int indent, const char* subname, FILE * fp);
void read256(const char* name);
int isValid(struct dirent* entry, int inden, char* name, char* subname);
void appendToFile(FILE* fp, const char* name);


int main(void)
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	char subname[100];
	scanf_s("%s", subname, (unsigned)sizeof(subname));
	FILE* fp = fopen(name, "w");
	listdir("C:\\test", 0, subname, fp);
	fclose(fp);
	read256(name);
	return 0;
}

void read256(const char* name) {
	printf("\nresult:\n");
	FILE* hi;
	char mystring[256];
	hi = fopen(name, "r");
	while (fgets(mystring, 256, hi) != NULL)
		puts(mystring);
	fclose(hi);
}

int isValid(struct dirent* entry, int inden, char* name, char* subname) {
	int len = -1;
	for (char* c = name+entry->d_namlen; c != name; c--) {
		if (*c == '.') {
			len = c - name;
			break;
		}
	}
	if (len == -1)
		len = entry->d_namlen;
	//printf("%s  -  %d-%d \n", name, len, entry->d_namlen);
	if (strlen(subname) <= len) {
		for (int i = 0; i < strlen(subname); i++)
			if (name[i] != subname[i])
				return FALSE;
		return TRUE;
	}
	else
		return FALSE;
}

void appendToFile(FILE* fp, const char* name) {
	FILE* fp2 = fopen(name, "r");
	while (fgets(buffer, 256, fp2) != NULL) {
		if (feof(fp2))
			buffer[strlen(buffer)] = '\0';
		fputs(buffer, fp);
	}
	//while ((c=fgetc(fp2))!=NULL && !feof(fp2))
	//	fputc(c, fp);
	fclose(fp2);
}

void listdir(char* name, int indent, char* subname, FILE* fp)
{
	DIR* dir;
	struct dirent* entry;

	if (!(dir = opendir(name)))
		return;

	while ((entry = readdir(dir)) != NULL) {
		if (entry->d_type == DT_DIR) {
			char path[1024];
			if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
				continue;
			snprintf(path, sizeof(path), "%s\\%s", name, entry->d_name);
			//printf("%*s[%s]\n", indent, "", entry->d_name);
			listdir(path, indent + 2, subname, fp);
		}
		else {
			int bl = isValid(entry, indent, entry->d_name, subname);
			if (bl == TRUE) {
				//printf("%*s- %s\\%s size:%d\n", indent, "", name, entry->d_name, entry->d_namlen);
				char buffer[100];
				sprintf(buffer, "%s\\%s", name, entry->d_name);
				printf("%s \n", buffer);
				appendToFile(fp, buffer);
			}
		}
	}
	closedir(dir);
}

