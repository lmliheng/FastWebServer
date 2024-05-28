CC=gcc
CFLAGS=-Wall

all: web_server

web_server: src/main.o src/server.o src/response.o
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o web_server