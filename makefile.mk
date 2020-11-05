INTERNAL_SOURCES := $(call rwildcard,$(CEMSCRIPTEN)/src,*.c)

web: $(NAME).html $(NAME).wasm $(NAME).js

$(NAME).html $(NAME).wasm $(NAME).js: $(INTERNAL_SOURCES) $(CSOURCES) $(USERHEADERS)
	emcc $(INTERNAL_SOURCES) $(CSOURCES) -O3 -o $(NAME).html \
	-isystem $(CEMSCRIPTEN)/include -Wno-main-return-type \
	--js-library $(CEMSCRIPTEN)/js/graphx.js --js-library $(CEMSCRIPTEN)/js/keypadc.js --js-library $(CEMSCRIPTEN)/js/tice.js \
	--pre-js $(CEMSCRIPTEN)/js/keypadc_pre.js --pre-js $(CEMSCRIPTEN)/js/fileioc_pre.js \
	-s EXPORTED_FUNCTIONS='["_main","_graphx_get_palette","_graphx_get_vram","_get_kb_Data"]' \
	-s EXPORTED_RUNTIME_METHODS='["ccall","cwrap"]' \
	-s ASYNCIFY -lidbfs.js --shell-file $(CEMSCRIPTEN)/shell.html

clean: web-clean

web-clean:
	@rm -rf $(NAME).html
	@rm -rf $(NAME).js
	@rm -rf $(NAME).wasm
