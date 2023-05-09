############################################
# A test makefile for incremental building.#
############################################
############################################################################
# By default, building non-OFFICIAL, non-DEBUG version.                    #
# If you want to get a debug version, use                                  #
# `make DEBUG=true`                                                        #
# If you want to get a official version, which does always autoupdate, use #
# `make release`                                                     #
############################################################################

##############################
# A name of server executable.


TARGETNAME=cod4x_game

###################################################################
# Build system specific information.
# In git not exist there will be some errors, but nothing critical.
#BUILD_NUMBER=$(shell git rev-list --count HEAD)
#BUILD_BRANCH=$(shell git rev-parse --abbrev-ref HEAD)
#BUILD_REVISION=$(shell git rev-parse HEAD)

ifneq ($(OS),Windows_NT)
VERSION=$(shell grep '\#define SYS_COMMONVERSION' src/version/version.c | cut -d' ' -f3)
$(info You build CoD4 version: $(VERSION))
endif

ifeq ($(BUILD_NUMBER), )
BUILD_NUMBER:=0
endif

ifeq ($(BUILD_BRANCH), )
BUILD_BRANCH:=no-branch
endif

ifeq ($(BUILD_REVISION), )
BUILD_REVISION:=no-revision
endif

EXTERNAL_INCLUDES=-Iexternal/fmt/include -Iexternal/mingw_ext

FMTLIB=external/fmt/build/libfmt.a


###################
# Compiler options.
CC=gcc
CPP=g++
WIN_DEFINES=WINVER=0x501
LINUX_DEFINES=_GNU_SOURCE
CFLAGS=-m32 -fno-common -msse2 -mfpmath=sse -Wall -fno-omit-frame-pointer -fmax-errors=15 -Isrc/

ifeq ($(DEBUG), true)
DCFLAGS=-fno-pie -Og -g3 -fno-eliminate-unused-debug-types -fno-eliminate-unused-debug-symbols -femit-class-debug-always $(EXTERNAL_INCLUDES)
else
#DCFLAGS=-fno-pie -O1 -DNDEBUG
DCFLAGS=-fno-pie -O0 -g $(EXTERNAL_INCLUDES)
endif

WIN_LFLAGS=-m32 -g -fno-common -Wl,--nxcompat,--stack,0x800000,--subsystem,windows -mwindows -static-libgcc -static -lm -Lexternal/fmt/build
WIN_LLIBS=tomcrypt mbedtls mbedcrypto mbedx509 jpeg speex mss32 binkw32 ws2_32 wsock32 wininet iphlpapi gdi32 kernel32 winmm d3d9 d3dx9 ddraw dsound crypt32 fmt stdc++
LINUX_LFLAGS=-m32 -g -static-libgcc -rdynamic -Wl,-rpath=./ -Lexternal/fmt/build
LINUX_LLIBS=tomcrypt mbedtls mbedcrypto mbedx509 dl pthread m fmt stdc++
BSD_LLIBS=tomcrypt mbedtls mbedcrypto mbedx509 pthread m execinfo fmt stdc++
COD4X_DEFINES=COD4X18UPDATE BUILD_NUMBER=$(BUILD_NUMBER) BUILD_BRANCH=$(BUILD_BRANCH) BUILD_REVISION=$(BUILD_REVISION)

########################
# Setup directory names.
SRC_DIR=src
PLUGIN_DIR=plugins
BIN_DIR=bin
LIB_DIR=lib
OBJ_DIR=obj
PLUGINS_DIR=plugins
ZLIB_DIR=$(SRC_DIR)/zlib
WIN_DIR=$(SRC_DIR)/win32
LINUX_DIR=$(SRC_DIR)/unix
ASSETS_DIR=$(SRC_DIR)/xassets
RENDERER_DIR=$(SRC_DIR)/gfx_d3d
DATABASE_DIR=$(SRC_DIR)/database
SCRIPT_DIR=$(SRC_DIR)/script
COMMON_DIR=$(SRC_DIR)/common
XANIM_DIR=$(SRC_DIR)/xanim
GAME_DIR=$(SRC_DIR)/game
GAMEMP_DIR=$(SRC_DIR)/game_mp
BG_DIR=$(SRC_DIR)/bgame
CLIENT_DIR=$(SRC_DIR)/client
SERVER_DIR=$(SRC_DIR)/server
UI_DIR=$(SRC_DIR)/ui
CGAME_DIR=$(SRC_DIR)/cgame
RAGDOLL_DIR=$(SRC_DIR)/ragdoll
PHYSICS_DIR=$(SRC_DIR)/physics
SND_DIR=$(SRC_DIR)/sound
SND_DRIVERDIR=$(SRC_DIR)/sound/drivers
FX_DIR=$(SRC_DIR)/effectscore
DYNENT_DIR=$(SRC_DIR)/dynentity
AIMASSIST_DIR=$(SRC_DIR)/aim_assist
PB_DIR=$(SRC_DIR)/pb
GROUPVOICE_DIR=$(SRC_DIR)/groupvoice
ODE_DIR=$(SRC_DIR)/physics/ode
EXTERNAL=mbedtls tomcrypt $(FMTLIB)

##############################
# Setup external applications.
NASM=nasm

###########################################################
# Setup OS-specific variables (All the garbage goes there).
ifeq ($(OS),Windows_NT)
####################
# Windows variables.
BIN_EXT=.exe
NASMFLAGS=-g -f win -dWin32 --prefix _
OS_SOURCES=$(wildcard $(WIN_DIR)/*.asm $(WIN_DIR)/*.c $(WIN_DIR)/*.cpp)
OS_OBJ=$(patsubst $(WIN_DIR)/%.asm,$(OBJ_DIR)/%.o,$(filter %.asm, $(OS_SOURCES)))
OS_OBJ+=$(patsubst $(WIN_DIR)/%.c,$(OBJ_DIR)/%.o,$(filter %.c, $(OS_SOURCES)))
OS_OBJ+=$(patsubst $(WIN_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(filter %.cpp, $(OS_SOURCES)))
C_DEFINES=$(addprefix -D,$(COD4X_DEFINES) $(WIN_DEFINES))
LFLAGS=$(WIN_LFLAGS)
LLIBS=-L$(LIB_DIR)/ $(addprefix -l,$(WIN_LLIBS))
RESOURCE_FILE=src/win32/win_cod4.res
ADDITIONAL_OBJ=

CLEAN=del $(OBJ_DIR)\*.o

else
#################
# LINUX variables.
BIN_EXT=
NASMFLAGS=-f elf
OS_SOURCES=$(wildcard $(LINUX_DIR)/*.c)
OS_OBJ=$(patsubst $(LINUX_DIR)/%.c,$(OBJ_DIR)/%.o,$(OS_SOURCES))
C_DEFINES=$(addprefix -D,$(COD4X_DEFINES) $(LINUX_DEFINES))
LFLAGS=$(LINUX_LFLAGS)

UNAME := $(shell uname)
ifeq ($(UNAME),FreeBSD)
LLIBS=-L./$(LIB_DIR) $(addprefix -l,$(BSD_LLIBS))
else
LLIBS=-L./$(LIB_DIR) $(addprefix -l,$(LINUX_LLIBS))
endif

RESOURCE_FILE=
ADDITIONAL_OBJ=
CLEAN=-rm $(OBJ_DIR)/*.o

endif

ifeq ($(snd_driver), xaudio)
SND_DRIVER=xaudio2
else
SND_DRIVER=ail
endif

#####################
# Source files lists.
TARGET=$(addprefix $(BIN_DIR)/,$(TARGETNAME)$(BIN_EXT))
ASM_SOURCES=$(wildcard $(SRC_DIR)/asmsource/*.asm)
C_SOURCES=$(wildcard $(SRC_DIR)/*.c)
CPP_SOURCES=$(wildcard $(SRC_DIR)/*.cpp)
ZLIB_SOURCES=$(wildcard $(ZLIB_DIR)/*.c)
ASSETS_SOURCES=$(wildcard $(ASSETS_DIR)/*.c)
RENDERER_SOURCES=$(wildcard $(RENDERER_DIR)/*.asm $(RENDERER_DIR)/*.c $(RENDERER_DIR)/*.cpp $(RENDERER_DIR)/dxerr/*.cpp)
COMMON_SOURCES=$(wildcard $(COMMON_DIR)/*.asm $(COMMON_DIR)/*.c $(COMMON_DIR)/*.cpp)
DATABASE_SOURCES=$(wildcard $(DATABASE_DIR)/*.asm $(DATABASE_DIR)/*.cpp $(DATABASE_DIR)/*.c)
SCRIPT_SOURCES=$(wildcard $(SCRIPT_DIR)/*.asm $(SCRIPT_DIR)/*.c $(SCRIPT_DIR)/*.cpp)
XANIM_SOURCES=$(wildcard $(XANIM_DIR)/*.asm $(XANIM_DIR)/*.c)
GAMEMP_SOURCES=$(wildcard $(GAMEMP_DIR)/*.asm $(GAMEMP_DIR)/*.cpp)
GAME_SOURCES=$(wildcard $(GAME_DIR)/*.asm $(GAME_DIR)/*.cpp)
BG_SOURCES=$(wildcard $(BG_DIR)/*.asm $(BG_DIR)/*.cpp)
CLIENT_SOURCES=$(wildcard $(CLIENT_DIR)/*.asm $(CLIENT_DIR)/*.c $(CLIENT_DIR)/*.cpp)
SERVER_SOURCES=$(wildcard $(SERVER_DIR)/*.asm $(SERVER_DIR)/*.cpp)
UI_SOURCES=$(wildcard $(UI_DIR)/*.asm $(UI_DIR)/*.cpp)
CGAME_SOURCES=$(wildcard $(CGAME_DIR)/*.asm $(CGAME_DIR)/*.cpp)
RAGDOLL_SOURCES=$(wildcard $(RAGDOLL_DIR)/*.asm $(RAGDOLL_DIR)/*.cpp)
PHYSICS_SOURCES=$(wildcard $(PHYSICS_DIR)/*.asm $(PHYSICS_DIR)/*.cpp)
SND_SOURCES=$(wildcard $(SND_DIR)/*.asm $(SND_DIR)/*.cpp $(SND_DRIVERDIR)/$(SND_DRIVER)/*.cpp $(SND_DRIVERDIR)/$(SND_DRIVER)/*.asm)
FX_SOURCES=$(wildcard $(FX_DIR)/*.asm $(FX_DIR)/*.c)
DYNENT_SOURCES=$(wildcard $(DYNENT_DIR)/*.asm $(DYNENT_DIR)/*.c)
AIMASSIST_SOURCES=$(wildcard $(AIMASSIST_DIR)/*.asm $(AIMASSIST_DIR)/*.c) 
PB_SOURCES=$(wildcard $(PB_DIR)/*.asm $(PB_DIR)/*.c $(PB_DIR)/*.cpp) 
GROUPVOICE_SOURCES=$(wildcard $(GROUPVOICE_DIR)/*.cpp)
ODE_SOURCES=$(wildcard $(ODE_DIR)/src/*.cpp)
 


#################################################################
# Object files lists. (prefixes for rules may be required later).
ASM_OBJ=$(patsubst $(SRC_DIR)/asmsource/%.asm,$(OBJ_DIR)/%.o,$(ASM_SOURCES))
C_OBJ=$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(C_SOURCES))
CPP_OBJ=$(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(CPP_SOURCES))
ZLIB_OBJ=$(patsubst $(ZLIB_DIR)/%.c,$(OBJ_DIR)/%.o,$(ZLIB_SOURCES))
ASSETS_OBJ=$(patsubst $(ASSETS_DIR)/%.c,$(OBJ_DIR)/%.o,$(ASSETS_SOURCES))
RENDERER_OBJ=$(patsubst $(RENDERER_DIR)/%.asm,$(OBJ_DIR)/%.o,$(filter %.asm, $(RENDERER_SOURCES)))
RENDERER_OBJ+=$(patsubst $(RENDERER_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(filter %.cpp, $(RENDERER_SOURCES))) 
RENDERER_OBJ+=$(patsubst $(RENDERER_DIR)/%.c,$(OBJ_DIR)/%.o,$(filter %.c, $(RENDERER_SOURCES))) 
COMMON_OBJ=$(patsubst $(COMMON_DIR)/%.asm,$(OBJ_DIR)/%.o,$(filter %.asm, $(COMMON_SOURCES)))
COMMON_OBJ+=$(patsubst $(COMMON_DIR)/%.c,$(OBJ_DIR)/%.o,$(filter %.c, $(COMMON_SOURCES))) 
COMMON_OBJ+=$(patsubst $(COMMON_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(filter %.cpp, $(COMMON_SOURCES))) 
DATABASE_OBJ=$(patsubst $(DATABASE_DIR)/%.asm,$(OBJ_DIR)/%.o,$(filter %.asm, $(DATABASE_SOURCES)))
DATABASE_OBJ+=$(patsubst $(DATABASE_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(filter %.cpp, $(DATABASE_SOURCES)))
SCRIPT_OBJ=$(patsubst $(SCRIPT_DIR)/%.asm,$(OBJ_DIR)/%.o,$(filter %.asm, $(SCRIPT_SOURCES)))
SCRIPT_OBJ+=$(patsubst $(SCRIPT_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(filter %.cpp, $(SCRIPT_SOURCES)))
XANIM_OBJ=$(patsubst $(XANIM_DIR)/%.asm,$(OBJ_DIR)/%.o,$(filter %.asm, $(XANIM_SOURCES)))
GAMEMP_OBJ=$(patsubst $(GAMEMP_DIR)/%.asm,$(OBJ_DIR)/%.o,$(filter %.asm, $(GAMEMP_SOURCES)))
GAMEMP_OBJ+=$(patsubst $(GAMEMP_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(filter %.cpp, $(GAMEMP_SOURCES)))
GAME_OBJ=$(patsubst $(GAME_DIR)/%.asm,$(OBJ_DIR)/%.o,$(filter %.asm, $(GAME_SOURCES)))
GAME_OBJ+=$(patsubst $(GAME_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(filter %.cpp, $(GAME_SOURCES)))
BG_OBJ=$(patsubst $(BG_DIR)/%.asm,$(OBJ_DIR)/%.o,$(filter %.asm, $(BG_SOURCES)))
BG_OBJ+=$(patsubst $(BG_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(filter %.cpp, $(BG_SOURCES)))
CLIENT_OBJ=$(patsubst $(CLIENT_DIR)/%.asm,$(OBJ_DIR)/%.o,$(filter %.asm, $(CLIENT_SOURCES)))
CLIENT_OBJ+=$(patsubst $(CLIENT_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(filter %.cpp, $(CLIENT_SOURCES)))
SERVER_OBJ=$(patsubst $(SERVER_DIR)/%.asm,$(OBJ_DIR)/%.o,$(filter %.asm, $(SERVER_SOURCES)))
SERVER_OBJ+=$(patsubst $(SERVER_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(filter %.cpp, $(SERVER_SOURCES)))
UI_OBJ=$(patsubst $(UI_DIR)/%.asm,$(OBJ_DIR)/%.o,$(filter %.asm, $(UI_SOURCES)))
UI_OBJ+=$(patsubst $(UI_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(filter %.cpp, $(UI_SOURCES)))
CGAME_OBJ=$(patsubst $(CGAME_DIR)/%.asm,$(OBJ_DIR)/%.o,$(filter %.asm, $(CGAME_SOURCES)))
CGAME_OBJ+=$(patsubst $(CGAME_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(filter %.cpp, $(CGAME_SOURCES)))
RAGDOLL_OBJ=$(patsubst $(RAGDOLL_DIR)/%.asm,$(OBJ_DIR)/%.o,$(filter %.asm, $(RAGDOLL_SOURCES)))
RAGDOLL_OBJ+=$(patsubst $(RAGDOLL_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(filter %.cpp, $(RAGDOLL_SOURCES)))
PHYSICS_OBJ=$(patsubst $(PHYSICS_DIR)/%.asm,$(OBJ_DIR)/%.o,$(filter %.asm, $(PHYSICS_SOURCES)))
PHYSICS_OBJ+=$(patsubst $(PHYSICS_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(filter %.cpp, $(PHYSICS_SOURCES)))
SND_OBJ=$(patsubst $(SND_DIR)/%.asm,$(OBJ_DIR)/%.o,$(filter %.asm, $(SND_SOURCES)))
SND_OBJ+=$(patsubst $(SND_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(filter %.cpp, $(SND_SOURCES)))
FX_OBJ=$(patsubst $(FX_DIR)/%.asm,$(OBJ_DIR)/%.o,$(filter %.asm, $(FX_SOURCES)))
DYNENT_OBJ=$(patsubst $(DYNENT_DIR)/%.asm,$(OBJ_DIR)/%.o,$(filter %.asm, $(DYNENT_SOURCES)))
AIMASSIST_OBJ=$(patsubst $(AIMASSIST_DIR)/%.asm,$(OBJ_DIR)/%.o,$(filter %.asm, $(AIMASSIST_SOURCES)))
PB_OBJ=$(patsubst $(PB_DIR)/%.asm,$(OBJ_DIR)/%.o,$(filter %.asm, $(PB_SOURCES)))
PB_OBJ+=$(patsubst $(PB_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(filter %.cpp, $(PB_SOURCES)))
GROUPVOICE_OBJ=$(patsubst $(GROUPVOICE_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(filter %.cpp, $(GROUPVOICE_SOURCES)))
ODE_OBJ=$(patsubst $(ODE_DIR)/src/%.cpp,$(OBJ_DIR)/%.o,$(filter %.cpp, $(ODE_SOURCES)))

#############################################################
#############################################################
#############################################################
#############################################################
#############################################################


###############################
# Default rule: rebuild server.
all: notify $(EXTERNAL) $(TARGET) $(ADDITIONAL_OBJ)
	@echo Game done

notify:
	@echo Game start

# defines this new target for tagging and releasing
.PHONY: release
release: C_DEFINES+=$(addprefix -D,OFFICIAL)
release: clean all


$(FMTLIB): external/fmt/CMakeLists.txt
	cmake -G "MinGW Makefiles" -DFMT_TEST=False -DCMAKE_BUILD_TYPE=Release -S external/fmt -B external/fmt/build
	cmake --build external/fmt/build
#################################
# A rule to make mbedtls library.
mbedtls:
	@echo   $(MAKE)  $@
	@$(MAKE) -C $(SRC_DIR)/$@

##################################
# A rule to make tomcrypt library.
tomcrypt:
	@echo   $(MAKE)  $@
	@$(MAKE) -C $(SRC_DIR)/$@

###############################
# A rule to link server binary.
$(TARGET): $(OS_OBJ) $(C_OBJ) $(CPP_OBJ) $(ZLIB_OBJ) $(ASSETS_OBJ) $(RENDERER_OBJ) $(COMMON_OBJ) $(DATABASE_OBJ) $(SCRIPT_OBJ) $(GAMEMP_OBJ) $(GAME_OBJ) $(BG_OBJ) $(CLIENT_OBJ) $(SERVER_OBJ) $(UI_OBJ) $(CGAME_OBJ) $(RAGDOLL_OBJ) $(PHYSICS_OBJ) $(XANIM_OBJ) $(SND_OBJ) $(FX_OBJ) $(DYNENT_OBJ) $(AIMASSIST_OBJ) $(GROUPVOICE_OBJ) $(ODE_OBJ) $(PB_OBJ) obj/version.o
	@echo   $(CC) $(TARGET)
# CFLAGS for compiler, LFLAGS for linker.
	@$(CC) $(LFLAGS) -o $@ $^ $(RESOURCE_FILE) $(LLIBS)

################################
# A rule to make version module.
obj/version.o: src/version/version.c FORCE
	@echo   $(CC)  $@ $(C_DEFINES)
	@$(CC) -c $(CFLAGS) $(DCFLAGS) $(C_DEFINES) -o $@ $<

############################################
# An empty rule to force rebuild other rule.
FORCE:

#####################################
# A rule to build common server code.
# -march=nocona
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@echo   $(CC)  $@
	@$(CC) -c $(CFLAGS) $(DCFLAGS) $(C_DEFINES) -o $@ $<

#####################################
# A rule to build common c++ server code.
# -march=nocona
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@echo   $(CPP)  $@
	@$(CPP) -c $(CFLAGS) $(DCFLAGS) $(C_DEFINES) -o $@ $<

###################################
# A rule to build zlib source code.
$(OBJ_DIR)/%.o: $(ZLIB_DIR)/%.c
	@echo   $(CC)  $@
	@$(CC) -c $(CFLAGS) $(DCFLAGS) $(C_DEFINES) -o $@ $<

######################################
# A rule to build renderer source code.
$(OBJ_DIR)/%.o: $(RENDERER_DIR)/%.asm
	@echo   $(NASM)  $@
	@$(NASM) $(NASMFLAGS) $< -o $@

$(OBJ_DIR)/%.o: $(RENDERER_DIR)/%.c
	@echo   $(CC)  $@
	@$(CC) -c $(CFLAGS) $(DCFLAGS) $(C_DEFINES) -o $@ $<

$(OBJ_DIR)/%.o: $(RENDERER_DIR)/%.cpp
	@echo   $(CPP)  $@
	@$(CPP) -c $(CFLAGS) $(DCFLAGS) $(C_DEFINES) -o $@ $<

######################################
# A rule to build common source code.
$(OBJ_DIR)/%.o: $(COMMON_DIR)/%.asm
	@echo   $(NASM)  $@
	@$(NASM) $(NASMFLAGS) $< -o $@

$(OBJ_DIR)/%.o: $(COMMON_DIR)/%.c
	@echo   $(CC)  $@
	@$(CC) -c $(CFLAGS) $(DCFLAGS) $(C_DEFINES) -o $@ $<

$(OBJ_DIR)/%.o: $(COMMON_DIR)/%.cpp
	@echo   $(CPP)  $@
	@$(CPP) -c $(CFLAGS) $(DCFLAGS) $(C_DEFINES) -o $@ $<

######################################
# A rule to build database source code.
$(OBJ_DIR)/%.o: $(DATABASE_DIR)/%.asm
	@echo   $(NASM)  $@
	@$(NASM) $(NASMFLAGS) $< -o $@

$(OBJ_DIR)/%.o: $(DATABASE_DIR)/%.cpp
	@echo   $(CPP)  $@
	@$(CPP) -c $(CFLAGS) $(DCFLAGS) $(C_DEFINES) -o $@ $<

######################################
# A rule to build xassets source code.
$(OBJ_DIR)/%.o: $(ASSETS_DIR)/%.c
	@echo   $(CC)  $@
	@$(CC) -c $(CFLAGS) $(DCFLAGS) $(C_DEFINES) -o $@ $<

######################################
# A rule to build scriptengine source code.
$(OBJ_DIR)/%.o: $(SCRIPT_DIR)/%.cpp
	@echo   $(CC)  $@
	@$(CC) -c $(CFLAGS) $(DCFLAGS) $(C_DEFINES) -o $@ $<

$(OBJ_DIR)/%.o: $(SCRIPT_DIR)/%.asm
	@echo   $(NASM)  $@
	@$(NASM) $(NASMFLAGS) $< -o $@

########################################
# A rule to build xanim code.
$(OBJ_DIR)/%.o: $(XANIM_DIR)/%.asm
	@echo   $(NASM)  $@
	@$(NASM) $(NASMFLAGS) $< -o $@

########################################
# A rule to build game_mp code.
$(OBJ_DIR)/%.o: $(GAMEMP_DIR)/%.asm
	@echo   $(NASM)  $@
	@$(NASM) $(NASMFLAGS) $< -o $@

$(OBJ_DIR)/%.o: $(GAMEMP_DIR)/%.cpp
	@echo   $(CC)  $@
	@$(CC) -c $(CFLAGS) $(DCFLAGS) $(C_DEFINES) -o $@ $<

########################################
# A rule to build game code.
$(OBJ_DIR)/%.o: $(GAME_DIR)/%.asm
	@echo   $(NASM)  $@
	@$(NASM) $(NASMFLAGS) $< -o $@

$(OBJ_DIR)/%.o: $(GAME_DIR)/%.cpp
	@echo   $(CC)  $@
	@$(CC) -c $(CFLAGS) $(DCFLAGS) $(C_DEFINES) -o $@ $<

########################################
# A rule to build bg code.
$(OBJ_DIR)/%.o: $(BG_DIR)/%.asm
	@echo   $(NASM)  $@
	@$(NASM) $(NASMFLAGS) $< -o $@

$(OBJ_DIR)/%.o: $(BG_DIR)/%.cpp
	@echo   $(CC)  $@
	@$(CC) -c $(CFLAGS) $(DCFLAGS) $(C_DEFINES) -o $@ $<

########################################
# A rule to build client code.
$(OBJ_DIR)/%.o: $(CLIENT_DIR)/%.cpp
	@echo   $(CC)  $@
	@$(CC) -c $(CFLAGS) $(DCFLAGS) $(C_DEFINES) -o $@ $<

$(OBJ_DIR)/%.o: $(CLIENT_DIR)/%.asm
	@echo   $(NASM)  $@
	@$(NASM) $(NASMFLAGS) $< -o $@

########################################
# A rule to build server code.
$(OBJ_DIR)/%.o: $(SERVER_DIR)/%.asm
	@echo   $(NASM)  $@
	@$(NASM) $(NASMFLAGS) $< -o $@

$(OBJ_DIR)/%.o: $(SERVER_DIR)/%.cpp
	@echo   $(CC)  $@
	@$(CC) -c $(CFLAGS) $(DCFLAGS) $(C_DEFINES) -o $@ $<

########################################
# A rule to build ui code.
$(OBJ_DIR)/%.o: $(UI_DIR)/%.asm
	@echo   $(NASM)  $@
	@$(NASM) $(NASMFLAGS) $< -o $@

$(OBJ_DIR)/%.o: $(UI_DIR)/%.cpp
	@echo   $(CC)  $@
	@$(CC) -c $(CFLAGS) $(DCFLAGS) $(C_DEFINES) -o $@ $<

########################################
# A rule to build cgame code.
$(OBJ_DIR)/%.o: $(CGAME_DIR)/%.asm
	@echo   $(NASM)  $@
	@$(NASM) $(NASMFLAGS) $< -o $@

$(OBJ_DIR)/%.o: $(CGAME_DIR)/%.cpp
	@echo   $(CC)  $@
	@$(CC) -c $(CFLAGS) $(DCFLAGS) $(C_DEFINES) -o $@ $<

########################################
# A rule to build ragdoll code.
$(OBJ_DIR)/%.o: $(RAGDOLL_DIR)/%.asm
	@echo   $(NASM)  $@
	@$(NASM) $(NASMFLAGS) $< -o $@

$(OBJ_DIR)/%.o: $(RAGDOLL_DIR)/%.cpp
	@echo   $(CPP)  $@
	@$(CPP) -c $(CFLAGS) $(DCFLAGS) $(C_DEFINES) -o $@ $<

########################################
# A rule to build phys code.
$(OBJ_DIR)/%.o: $(PHYSICS_DIR)/%.asm
	@echo   $(NASM)  $@
	@$(NASM) $(NASMFLAGS) $< -o $@

$(OBJ_DIR)/%.o: $(PHYSICS_DIR)/%.cpp
	@echo   $(CPP)  $@
	@$(CPP) -c $(CFLAGS) $(DCFLAGS) $(C_DEFINES) -I$(ODE_DIR)/include -o $@ $<

########################################
# A rule to build sound code.
$(OBJ_DIR)/%.o: $(SND_DIR)/%.cpp
	@echo   $(CC)  $@
	@$(CC) -c $(CFLAGS) $(DCFLAGS) $(C_DEFINES) -o $@ $<

$(OBJ_DIR)/%.o: $(SND_DIR)/%.asm
	@echo   $(NASM)  $@
	@$(NASM) $(NASMFLAGS) $< -o $@

########################################
# A rule to build effects code.
$(OBJ_DIR)/%.o: $(FX_DIR)/%.asm
	@echo   $(NASM)  $@
	@$(NASM) $(NASMFLAGS) $< -o $@

########################################
# A rule to build DynEntity code.
$(OBJ_DIR)/%.o: $(DYNENT_DIR)/%.asm
	@echo   $(NASM)  $@
	@$(NASM) $(NASMFLAGS) $< -o $@

########################################
# A rule to build Aim assist code.
$(OBJ_DIR)/%.o: $(AIMASSIST_DIR)/%.asm
	@echo   $(NASM)  $@
	@$(NASM) $(NASMFLAGS) $< -o $@

########################################
# A rule to build Windows specific code.
$(OBJ_DIR)/%.o: $(WIN_DIR)/%.asm
	@echo   $(NASM)  $@
	@$(NASM) $(NASMFLAGS) $< -o $@

$(OBJ_DIR)/%.o: $(WIN_DIR)/%.c
	@echo   $(CC)  $@
	@$(CC) -c $(CFLAGS) $(DCFLAGS) $(C_DEFINES) -o $@ $<

$(OBJ_DIR)/%.o: $(WIN_DIR)/%.cpp
	@echo   $(CPP)  $@
	@$(CPP) -c $(CFLAGS) $(DCFLAGS) $(C_DEFINES) -o $@ $<
########################################
# A rule to build Linux specific code.
$(OBJ_DIR)/%.o: $(LINUX_DIR)/%.c
	@echo   $(CC)  $@
	@$(CC) -c $(CFLAGS) $(DCFLAGS) $(C_DEFINES) -o $@ $<

########################################
# A rule to build voicechat specific code.
$(OBJ_DIR)/%.o: $(GROUPVOICE_DIR)/%.cpp
	@echo   $(CPP)  $@
	@$(CPP) -c $(CFLAGS) $(DCFLAGS) $(C_DEFINES) -Iexternal/speex-1.2.0/include -o $@ $<

########################################
# A rule to build ODE code.
$(OBJ_DIR)/%.o: $(ODE_DIR)/src/%.cpp
	@echo   $(CPP)  $@
	@$(CPP) -c $(CFLAGS) $(DCFLAGS) $(C_DEFINES) -I$(ODE_DIR)/include -o $@ $<

########################################
# A rule to build punkbuster specific code.
$(OBJ_DIR)/%.o: $(PB_DIR)/%.asm
	@echo   $(NASM)  $@
	@$(NASM) $(NASMFLAGS) $< -o $@

$(OBJ_DIR)/%.o: $(PB_DIR)/%.cpp
	@echo   $(CC)  $@
	@$(CC) -c $(CFLAGS) $(DCFLAGS) $(C_DEFINES) -o $@ $<

############################
# Delete built object files. (Server only)
clean:
	@echo   clean Client
	@$(CLEAN)

############################
# Delete built object files. (Server only)
clean_all:
	@echo   clean Server
	@$(CLEAN)
	@echo   clean Mbedtls
	@$(MAKE) -C $(SRC_DIR)/mbedtls clean
	@echo   clean Tomcrypt
	@$(MAKE) -C $(SRC_DIR)/tomcrypt clean

