.PHONY: all clean run

# Define required environment variables
#------------------------------------------------------------------------------------------------
# Define target platform: PLATFORM_DESKTOP, PLATFORM_RPI, PLATFORM_DRM, PLATFORM_ANDROID, PLATFORM_WEB
PLATFORM              ?= PLATFORM_DESKTOP

# Define project variables
PROJECT_NAME          ?= r6_no_recoil
PROJECT_VERSION       ?= 1.0
PROJECT_BUILD_PATH    ?= .

RAYLIB_PATH           ?= ../../raylib

# Locations of raylib.h and libraylib.a/libraylib.so
# NOTE: Those variables are only used for PLATFORM_OS: LINUX, BSD
RAYLIB_INCLUDE_PATH   ?= /usr/local/include
RAYLIB_LIB_PATH       ?= /usr/local/lib

# Library type compilation: STATIC (.a) or SHARED (.so/.dll)
RAYLIB_LIBTYPE        ?= STATIC

# Build mode for project: DEBUG or RELEASE
BUILD_MODE            ?= RELEASE

PLATFORM_OS = WINDOWS
ifndef PLATFORM_SHELL
    PLATFORM_SHELL = cmd
endif

# Define raylib release directory for compiled library
RAYLIB_RELEASE_PATH 	?= $(RAYLIB_PATH)/src

# Define default C compiler: CC
#------------------------------------------------------------------------------------------------
CC = g++

# Define default make program: MAKE
#------------------------------------------------------------------------------------------------
MAKE = make

# Define compiler flags: CFLAGS
#------------------------------------------------------------------------------------------------
#  -O1                  defines optimization level
#  -g                   include debug information on compilation
#  -s                   strip unnecessary data from build
#  -Wall                turns on most, but not all, compiler warnings
#  -std=c99             defines C language mode (standard C from 1999 revision)
#  -std=gnu99           defines C language mode (GNU C from 1999 revision)
#  -Wno-missing-braces  ignore invalid warning (GCC bug 53119)
#  -Wno-unused-value    ignore unused return values of some functions (i.e. fread())
#  -D_DEFAULT_SOURCE    use with -std=c99 on Linux and PLATFORM_WEB, required for timespec
#  -mwindows            hide the console that pops-up when the game is launched
CFLAGS = -std=c++20 -Wall -lraylib -lgdi32 -lwinmm -mwindows

ifeq ($(BUILD_MODE),DEBUG)
    CFLAGS += -g -D_DEBUG
else
    CFLAGS += -s -O2
endif

# Define include paths for required headers: INCLUDE_PATHS
# NOTE: Some external/extras libraries could be required (stb, physac, easings...)
#------------------------------------------------------------------------------------------------
INCLUDE_PATHS = -I.

# Define library paths containing required libs: LDFLAGS
#------------------------------------------------------------------------------------------------
LDFLAGS = -L. -L$(RAYLIB_RELEASE_PATH) -L$(RAYLIB_PATH)/src -L$(RAYLIB_LIB_PATH)

# Define libraries required on linking: LDLIBS
# NOTE: To link libraries (lib<name>.so or lib<name>.a), use -l<name>
#------------------------------------------------------------------------------------------------
LDLIBS = -lraylib -lopengl32 -lgdi32 -lwinmm
# Required for physac examples
LDLIBS += -static -lpthread

# Define source code object files required
#------------------------------------------------------------------------------------------------
PROJECT_SOURCE_FILES ?= \
    App.cpp \
    main.cpp

# Define all object files from source files
OBJS = $(patsubst %.c, %.o, $(PROJECT_SOURCE_FILES))


# Define processes to execute
#------------------------------------------------------------------------------------------------
MAKEFILE_PARAMS = $(PROJECT_NAME)

# Default target entry
# NOTE: We call this Makefile target or Makefile.Android target
all:
	$(MAKE) $(MAKEFILE_PARAMS)

# Project target defined by PROJECT_NAME
$(PROJECT_NAME): $(OBJS)
	$(CC) -o ../build/$(PROJECT_NAME)$(EXT) $(OBJS) $(CFLAGS) $(INCLUDE_PATHS) $(LDFLAGS) $(LDLIBS) -D$(PLATFORM)

# Compile source files
# NOTE: This pattern will compile every module defined on $(OBJS)
%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS) $(INCLUDE_PATHS) -D$(PLATFORM)

run:
	$(MAKE) $(MAKEFILE_PARAMS)

ifeq ($(PLATFORM),PLATFORM_DESKTOP)
    ifeq ($(PLATFORM_OS),WINDOWS)
		$(PROJECT_NAME)
    endif
    ifeq ($(PLATFORM_OS),LINUX)
		./$(PROJECT_NAME)
    endif
    ifeq ($(PLATFORM_OS),OSX)
		./$(PROJECT_NAME)
    endif
endif

# Set specific target variable
clean_shell_cmd: SHELL=cmd
clean_shell_cmd:
	del *.o *.exe $(PROJECT_NAME).data $(PROJECT_NAME).html $(PROJECT_NAME).js $(PROJECT_NAME).wasm /s
