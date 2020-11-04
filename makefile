SHELL:=/bin/bash

all:
	@source "/home/john/builds/emsdk/emsdk_env.sh" 2>/dev/null && \
	emcc graphx.c keypadc.c fileioc.c taxi/main.c taxi/gfx/*.c -O3 -o taxi.html \
	--js-library graphx.js --js-library keypadc.js --js-library tice.js \
	--pre-js keypadc_pre.js --pre-js fileioc_pre.js \
	-s EXPORTED_FUNCTIONS='["_main","_graphx_get_palette","_graphx_get_vram","_get_kb_Data"]' \
	-s EXPORTED_RUNTIME_METHODS='["ccall","cwrap"]' \
	-s ASYNCIFY -s FORCE_FILESYSTEM=1 -lidbfs.js --shell-file shell.html

clean:
	rm -f a.out.js a.out.wasm
	