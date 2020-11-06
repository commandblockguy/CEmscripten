# CEmscripten

A toolchain to compile C programs originally designed for the TI-84+CE calculator using [CEdev](https://github.com/CE-Programming/toolchain) to WebAssembly with minimal source modifications.

Currently, it is extremely incomplete - do not expect it to compile much of anything besides [Taxi Simulator](https://commandblockguy.xyz/demos/taxi/) without implementing many functions yourself.

Contributions are highly welcome - not just PRs, but also issues for bugs or feature requests, so that I can have some idea of what needs to be implemented.

This probably won't run on Windows.

## Usage
1. Clone this repository to your computer.
2. Set the CEMSCRIPTEN environment variable to the path to the repo.
3. Add this line to the end of your project's makefile: `include $(CEMSCRIPTEN)/makefile.mk`
4. Build the project with `make web`

## Limitations
- Currently, most functions are not implemented.
- There is no 24-bit type in WebAssembly. You should replace all instances of `uint24_t` and `int24_t` with `int` and `unsigned int`, respectively. If your program uses hardcoded sizes, this will likely break it, so just don't do that.
- Assembly functions will not compile, as this is not an emulator.
- Direct access to any hardware registers, besides vram, the LCD palette, or kb_Data will not work.
- The web browser uses an asynchronous model, while almost all C programs use a synchronous model. CEmscripten attempts to work around this by adding a short delay during some IO-related functions to allow the browser to process other events. You may also do this yourself by calling the delay() function.
