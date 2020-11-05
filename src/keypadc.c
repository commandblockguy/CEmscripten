#include <stdbool.h>
#include <stdint.h>
#include <emscripten.h>

uint8_t kb_Data[8] = {0};

uint8_t *get_kb_Data(void){
	return kb_Data;
}

uint8_t kb_AnyKey(void) {
	emscripten_sleep(5);
	for(int i = 1; i < 8; i++) {
		if(kb_Data[i]) return true;
	}
	return false;
}
