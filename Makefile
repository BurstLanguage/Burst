#
# Burst/Makefile
#
NAME := burstc
ROOT := ${CURDIR}
TEST := ${CURDIR}/Test

_SRC := ${ROOT}/Source
_INC := ${ROOT}/Include

_OUT := ${ROOT}/Build
_OBJ := ${_OUT}/obj
_BIN := ${_OUT}/bin

TARGET := ${_BIN}/${NAME}
T_ARGS := $(shell find ${TEST} -type f -name "*.burst")

SOURCES := $(shell find ${_SRC} -type f -name "*.c")
OBJECTS := $(patsubst ${_SRC}/%.c, ${_OBJ}/%.o, ${SOURCES})

CC := gcc
CC_FLAGS := -Wall -Werror -ggdb
LD_FLAGS := -std=gnu99 -I${_INC}

VAL := valgrind
VAL_FLAGS := --leak-check=yes --track-origins=yes

.PHONY: all
all: clean prepare objects binary

clean:
	rm -rf ${_OUT}

prepare:
	if [ ! -d ${_OUT} ]; then mkdir ${_OUT}; fi
	if [ ! -d ${_OBJ} ]; then mkdir ${_OBJ}; fi
	if [ ! -d ${_BIN} ]; then mkdir ${_BIN}; fi

objects: ${OBJECTS}
binary:
	${CC} ${CC_FLAGS} ${LD_FLAGS} -o ${TARGET} ${OBJECTS}
	chmod +x ${TARGET}

launch:
	${TARGET} ${T_ARGS}

${VAL}:
	${VAL} ${VAL_FLAGS} ${TARGET} ${T_ARGS}

${_OBJ}/%.o: ${_SRC}/%.c
	mkdir -p $(dir $@)
	${CC} ${CC_FLAGS} ${LD_FLAGS} -c $^ -o $@