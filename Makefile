CFLAGS=-Wall -g

.PHONY: clean all

all: server client

server: serverr.c
	${CC} ${CFLAGS} -o $@ serverr.c 

client: client.c
	${CC} ${CFLAGS} -o $@ client.c 

clean: 
	@rm -f server client *.core *.c~


