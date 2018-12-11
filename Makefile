src = $(wildcard *.cc)
obj = $(src:.cc=.o)

# LDFLAGS = -lGL -lglut -lpng -lz -lm

CC=g++

hello: $(obj)
	mkdir bin
	$(CC) -o bin/$@ $^ $(LDFLAGS)

.PHONY: clean

clean:
	rm -df $(obj) hello bin/* bin *~
