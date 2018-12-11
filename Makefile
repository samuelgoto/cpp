#src = $(wildcard *.cc)
#obj = $(src:.cc=.o)

# LDFLAGS = -lGL -lglut -lpng -lz -lm

CC=g++

TARGETS=hello scopes

all: $(TARGETS)

%: %.o
	$(CC) $< -o $@

clean:
	rm -df $(TARGETS)
