#src = $(wildcard *.cc)
#obj = $(src:.cc=.o)

# LDFLAGS = -lGL -lglut -lpng -lz -lm

CC=g++

TARGETS=hello constructor destructor fields fields_dtr unique_ptr overload copy copyctr move

.SILENT: all

all: $(TARGETS)
	for bin in $(TARGETS); do \
		echo $$bin; \
		echo ""; \
		./$$bin; \
		echo ""; \
	done

%: %.o
	$(CC) $< -o $@

clean:
	rm -df $(TARGETS) *~
