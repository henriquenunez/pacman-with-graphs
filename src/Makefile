CC=gcc
CFLAGS=-g

LDFLAGS=-fsanitize=address -lcurses #-l:libncurses.a -L${NC_ROOT_DIR}/lib

ROOT_DIR=$(shell pwd)
BIN_DIR=${ROOT_DIR}/bin
OBJ_DIR=${ROOT_DIR}/obj

NC_ROOT_DIR=${OBJ_DIR}/ncurses-6.2

#GENERAL TARGETS
all: bin_dir build

clean:
	rm -rf ${NC_ROOT_DIR} || true
	rm -rf ${BIN_DIR} || true
	rm -rf ${OBJ_DIR} || true

build: graph.o main
	#gcc ${CFLAGS} *.c ${LDFLAGS} -L ${NC_LIB_DIR}

bin_dir:
	mkdir ${BIN_DIR} || true
	mkdir ${OBJ_DIR} || true
	mkdir ${NC_ROOT_DIR} || true

#ENTRY POINT

main:
	$(CC) ${CFLAGS} main.c ${OBJ_DIR}/dstructures.o ${OBJ_DIR}/graph.o -o ${BIN_DIR}/pacman ${LDFLAGS}

run:
	${BIN_DIR}/pacman

#SPECIFIC TARGETS

dstructures.o:
	$(CC) -c ${CFLAGS} dstructures.c -o ${OBJ_DIR}/dstructures.o ${LDFLAGS}

graph.o: dstructures.o
	$(CC) -c ${CFLAGS} graph.c -o ${OBJ_DIR}/graph.o ${LDFLAGS}

#UTILITY FOR DOWNLOADING AND COMPILING NCURSES. STATICALLY LINKED.
#ncurses: bin_dir nc_dl nc_build
#
#nc_dl:
#	wget http://gnu.c3sl.ufpr.br/ftp/ncurses/ncurses-6.2.tar.gz -O ./ncurses.tar.gz
#	tar -C ${OBJ_DIR} -zxvf ./ncurses.tar.gz
#	rm ./ncurses.tar.gz
#
#nc_build:
#	(cd ${NC_ROOT_DIR} && ./configure && make)
#
