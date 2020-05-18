CC=gcc
CFLAGS=-g
LDFLAGS=-fsanitize=address

ROOT_DIR=.
BIN_DIR=${ROOT_DIR}/bin

NC_ROOT_DIR=${BIN_DIR}/ncurses-6.2
NC_LIB_DIR=${NC_ROOT_DIR}/lib 		#For statically linking with ncurses.

#GENERAL TARGETS
all: clean bin_dir build

clean:
	rm -rf ${BIN_DIR} || true

build: graph.o
	#gcc ${CFLAGS} *.c ${LDFLAGS} -L ${NC_LIB_DIR}

bin_dir:
	mkdir ${BIN_DIR}

#SPECIFIC TARGETS

dstructures.o:
	gcc -c ${CFLAGS} dstructures.c -o ${BIN_DIR}/dstructures.o ${LDFLAGS}

graph.o: dstructures.o
	gcc -c ${CFLAGS} graph.c -o ${BIN_DIR}/graph.o ${LDFLAGS}

#UTILITY FOR DOWNLOADING AND COMPILING NCURSES. STATICALLY LINKED.
ncurses: bin_dir nc_dl nc_build

nc_dl:
	#mkdir ${NC_DIR}
	wget http://gnu.c3sl.ufpr.br/ftp/ncurses/ncurses-6.2.tar.gz -O ${BIN_DIR}/ncurses.tar.gz
	tar -C ${BIN_DIR} -zxvf ${BIN_DIR}/ncurses.tar.gz
	rm ${BIN_DIR}/ncurses.tar.gz

nc_build:
	pushd ${NC_ROOT_DIR} && ./configure && make && popd

