WASI_SDK_PATH = ../wasi-sdk
ifndef WASI_SDK_PATH
$(error Download the WASI SDK (https://github.com/WebAssembly/wasi-sdk) and set $$WASI_SDK_PATH)
endif

CC = "$(WASI_SDK_PATH)/bin/clang" --sysroot="$(WASI_SDK_PATH)/share/wasi-sysroot"
CXX = "$(WASI_SDK_PATH)/bin/clang++" --sysroot="$(WASI_SDK_PATH)/share/wasi-sysroot"

# Optional dependency from binaryen for smaller builds
#WASM_OPT = wasm-opt
WASM_OPT = ../binaryen/bin/wasm-opt.exe
WASM_OPT_FLAGS = -Oz --zero-filled-memory --strip-producers --enable-bulk-memory

# Whether to build for debugging instead of release
DEBUG = 0

# Compilation flags
CFLAGS = -W -Wall -Wextra -Werror -Wno-unused -Wconversion -Wsign-conversion -MMD -MP -fno-exceptions -mbulk-memory
ifeq ($(DEBUG), 1)
	CFLAGS += -DDEBUG -O0 -g
else
	CFLAGS += -DNDEBUG -Oz -flto
endif

# Linker flags
LDFLAGS = -Wl,-zstack-size=14752,--no-entry,--import-memory -mexec-model=reactor \
	-Wl,--initial-memory=65536,--max-memory=65536,--stack-first
ifeq ($(DEBUG), 1)
	LDFLAGS += -Wl,--export-all,--no-gc-sections
else
	LDFLAGS += -Wl,--strip-all,--gc-sections,--lto-O3 -Oz
endif

OBJECTS = $(patsubst src/%.c, build/%.o, $(wildcard src/*.c))
OBJECTS += $(patsubst src/%.cpp, build/%.o, $(wildcard src/*.cpp))
DEPS = $(OBJECTS:.o=.d)

ifeq '$(findstring ;,$(PATH))' ';'
    DETECTED_OS := Windows
else
    DETECTED_OS := $(shell uname 2>/dev/null || echo Unknown)
    DETECTED_OS := $(patsubst CYGWIN%,Cygwin,$(DETECTED_OS))
    DETECTED_OS := $(patsubst MSYS%,MSYS,$(DETECTED_OS))
    DETECTED_OS := $(patsubst MINGW%,MSYS,$(DETECTED_OS))
endif

ifeq ($(DETECTED_OS), Windows)
	MKDIR_BUILD = if not exist build md build
	RMDIR = rd /s /q
else
	MKDIR_BUILD = mkdir -p build
	RMDIR = rm -rf
endif

all: build/cart.wasm

# Link cart.wasm from all object files and run wasm-opt
build/cart.wasm: $(OBJECTS)
	$(CXX) -o $@ $(OBJECTS) $(LDFLAGS)
ifneq ($(DEBUG), 1)
#ifeq (, $(shell command -v $(WASM_OPT)))
#	@echo Tip: $(WASM_OPT) was not found. Install it from binaryen for smaller builds!
#else
	$(WASM_OPT) $(WASM_OPT_FLAGS) $@ -o $@
#endif
endif

# Compile C sources
build/%.o: src/%.c
	@$(MKDIR_BUILD)
	$(CC) -c $< -o $@ $(CFLAGS)

# Compile C++ sources
build/%.o: src/%.cpp
	@$(MKDIR_BUILD)
	$(CXX) -c $< -o $@ $(CFLAGS)

.PHONY: clean
clean:
	$(RMDIR) build

-include $(DEPS)
