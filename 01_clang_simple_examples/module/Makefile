COMPILE_FLAGS = --target=wasm32 -nostdlib -Os -Wl,--no-entry -Wl,--export-all

add.wasm: add.c Makefile
	clang $(COMPILE_FLAGS) add.c -o add.wasm

all: add.wasm

clean:
	rm -f add.wasm
