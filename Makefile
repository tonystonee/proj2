CFLAGS=-I.
all: server client

client: client.o
	g++ -o client client.o;

server: server.o
	g++ -o server server.o;

%.o: %.cpp
		g++ -O -c -o $@ $< $(CFLAGS)

clean:
	rm -rf *o
