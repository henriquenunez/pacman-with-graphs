CC=gcc
CFLAGS=-g
LDFLAGS=-fsanitize=address

ROOT_DIR=.
BIN_DIR=${ROOT_DIR}/bin

NC_ROOT_DIR=${BIN_DIR}/ncurses-6.2
NC_LIB_DIR=${NC_ROOT_DIR}/lib 		#For statically linking with ncurses.

all:

clean:
	rm -rf ${BIN_DIR} || true

build:
	#gcc ${CFLAGS} *.c ${LDFLAGS} -L ${NC_LIB_DIR}

ncurses: bin_dir nc_dl nc_build

nc_dl:
	#mkdir ${NC_DIR}
	wget http://gnu.c3sl.ufpr.br/ftp/ncurses/ncurses-6.2.tar.gz -O ${BIN_DIR}/ncurses.tar.gz
	tar -C ${BIN_DIR} -zxvf ${BIN_DIR}/ncurses.tar.gz
	rm ${BIN_DIR}/ncurses.tar.gz

nc_build:
	${NC_ROOT_DIR}/configure
	make -C ${NC_ROOT_DIR}

bin_dir:
	mkdir ${BIN_DIR}

