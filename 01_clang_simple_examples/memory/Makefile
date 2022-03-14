COMPILE_FLAGS = --target=wasm32 -nostdlib -O0 -g -Wl,--no-entry -Wl,--export-all

memory.wasm: memory.c Makefile
	clang $(COMPILE_FLAGS) memory.c -o memory.wasm

all: memory.wasm

clean:
	rm -f memory.wasm
