#include <dirent.h>
#include <emscripten.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "fileioc.h"

struct {
	FILE *file;
	void *data;
} files[16] = {NULL};

// todo: make this only sync when a file is closed, or something
void ti_CloseAll(void) {
	while(!EM_ASM_INT({
		if(Module.fileioc.loaded == false) return false;
		FS.syncfs(false, () => {});
		return true;
	})) emscripten_sleep(50);
	for(int i = 0; i < 16; i++) {
		if(files[i].file) {
			fclose(files[i].file);
			free(files[i].data);
			files[i].file = NULL;
			files[i].data = NULL;
		}
	}
}

// todo: write back data from pointer
void ti_Close(ti_var_t var) {
	if(!var) return;
	for(int i = 0; i < 16; i++) {
		if(files[i].file == var) {
			free(files[i].data);
			files[i].file = NULL;
			files[i].data = NULL;
		}
	}
	fclose(var);
}

ti_var_t ti_Open(const char *name, const char *mode) {
	char buf[16] = "/calc/";
	strcpy(&buf[6], name);
	FILE *f = fopen(buf, mode);
	for(int i = 0; i < 16; i++) {
		if(!files[i].file) {
			files[i].file = f;
			files[i].data = NULL;
			break;
		}
	}
	//todo: fix if all slots used
	return f;
}

char *ti_Detect(void **curr_search_posistion, const char *detection_string) {
	DIR *d = *curr_search_posistion;
	size_t length = strlen(detection_string);
	if(!d) d = opendir("/calc/");
	if(!d) return NULL;
	while(true) {
		struct dirent *dir = readdir(d);
		*curr_search_posistion = d;
		if(!dir)  {
			*curr_search_posistion = NULL;
			return NULL;
		}
		struct stat path_stat;
		stat(dir->d_name, &path_stat);
		if(S_ISREG(path_stat.st_mode)) {
			printf("%s\n", dir->d_name);
			FILE *f = fopen(dir->d_name, "r");
			if(!f) continue;
			char *file_header = malloc(length);
			if(!file_header) continue;
			fread(file_header, length, 1, f);
			bool matches = memcmp(detection_string, file_header, length) == 0;
			free(file_header);
			if(matches) {
				// pfft, who cares about memory leaks?
				// seriously, though, if there's a better way to do this please let me know
				char *path = malloc(strlen(dir->d_name));
				strcpy(path, dir->d_name);
				return path;
			}
		}
	}
	return NULL;
}

int ti_Delete(const char *name) {
	char buf[16] = "/calc/";
	strcpy(&buf[6], name);
	return remove(buf);
}

void *ti_GetDataPtr(const ti_var_t slot) {
	for(int i = 0; i < 16; i++) {
		if(files[i].file == slot) {
			FILE *f = files[i].file;
			int pos = ftell(f);
			if(files[i].data) return files[i].data + pos;
			fseek(f, 0, SEEK_END);
			int size = ftell(f);
			void *data = malloc(size);
			if(!data) return NULL;
			files[i].data = data;
			rewind(f);
			fread(data, size, 1, f);
			fseek(f, pos, SEEK_SET);
			return &data[pos];
		}
	}
	printf("ti_GetDataPtr couldn't find slot\n");
	return NULL;
}
