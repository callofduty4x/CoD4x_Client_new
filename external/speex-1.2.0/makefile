CC=gcc
CPP=g++
TARGET=libspeex
TARGETDIR=.

ifeq ($(OS),Windows_NT)
CFLAGS=-m32 -Wall -DHAVE_CONFIG_H -I. -Iinclude -Iinclude/speex -g -O2 -fvisibility=hidden -O3 -msse -Wall
else
CFLAGS=-m32 -Wall -O1 -g -fvisibility=hidden -mtune=core2
endif

SRC_DIR=libspeex
C_SOURCES=$(wildcard $(SRC_DIR)/*.c)
C_OBJ=$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(C_SOURCES))


all: notify $(TARGET)
	@echo libspeex done

notify:
	@echo libspeex start


$(TARGET): $(C_OBJ) $(TARGETDIR)/$(TARGET).a
	@echo   $(CC) $(TARGET)
	

#####################################
# A rule to build common server code.
# -march=nocona
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@echo   $(CC)  $@
	@$(CC) -c $(CFLAGS) $(DCFLAGS) $(C_DEFINES) -o $@ $<

$(TARGETDIR)/$(TARGET).a: $(C_OBJ)
	echo   $(AR)  $@
	$(AR) rcs $@ $(C_OBJ)


