#include <emscripten.h>
#include <stdio.h>
#include <string.h>
#include "fileioc.h"

FILE *files[16] = {NULL};

void ti_CloseAll(void) {
	while(!EM_ASM_INT({
		if(Module.fileioc.loaded == false) return false;
		FS.syncfs(false, () => {});
		return true;
	})) emscripten_sleep(50);
	for(int i = 0; i < 16; i++) {
		if(files[i]) {
			fclose(files[i]);
			files[i] = NULL;
		}
	}
}

void ti_Close(ti_var_t var) {
	for(int i = 0; i < 16; i++) {
		if(files[i] == var) {
			files[i] = NULL;
		}
	}
	fclose(var);
}

ti_var_t ti_Open(const char *name, const char *mode) {
	char buf[16] = "/calc/";
	strcpy(&buf[6], name);
	FILE *f = fopen(buf, mode);
	for(int i = 0; i < 16; i++) {
		if(!files[i]) {
			files[i] = f;
			break;
		}
	}
	//todo: fix if all slots used
	return f;
}
