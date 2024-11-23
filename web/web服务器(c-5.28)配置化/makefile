CC = gcc
CFLAGS = -Wall -I./includes

all: web_server

web_server: src/main.o src/server.o src/request.o src/response.o src/config.o
	$(CC) $(CFLAGS) -o web_server src/main.o src/server.o src/request.o src/response.o src/config.o

src/main.o: src/main.c
	$(CC) $(CFLAGS) -c src/main.c -o src/main.o

src/server.o: src/server.c
	$(CC) $(CFLAGS) -c src/server.c -o src/server.o

src/request.o: src/request.c
	$(CC) $(CFLAGS) -c src/request.c -o src/request.o

src/response.o: src/response.c
	$(CC) $(CFLAGS) -c src/response.c -o src/response.o

src/config.o: src/config.c
	$(CC) $(CFLAGS) -c src/config.c -o src/config.o

clean:
	rm -f src/*.o web_server