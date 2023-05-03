CC=gcc
CPP=g++
TARGET=libspeex

ifeq ($(OS),Windows_NT)
CFLAGS=-m32 -Wall -DFLOATING_POINT -I. -I..  -I../include -I../include/speex -I.. -g -O2 -fvisibility=hidden -O3 -msse -Wall
else
CFLAGS=-m32 -Wall -O1 -g -fvisibility=hidden -mtune=core2
endif

SRC_DIR=.
C_SOURCES=$(wildcard $(SRC_DIR)/*.c)
C_OBJ=$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(C_SOURCES))


all: notify $(TARGET)
	@echo Server done

notify:
	@echo Server start


$(TARGET): $(C_OBJ)
	@echo   $(CC) $(TARGET)

#####################################
# A rule to build common server code.
# -march=nocona
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@echo   $(CC)  $@
	@$(CC) -c $(CFLAGS) $(DCFLAGS) $(C_DEFINES) -o $@ $<


