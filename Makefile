CC=g++
CPPFLAGS=-fno-elide-constructors

TARGETS=hello constructor destructor fields fields_dtr unique_ptr overload copy copyctr deepctr movectr parameters templates userland

.SILENT: all

%: src/%.o
	$(CC) $(CFLAGS) $(CPPFLAGS) $< -o bin/$@

src/%.o: src/%.c 
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $<

all: $(TARGETS)
	for bin in $(TARGETS); do \
		echo $$bin; \
		echo ""; \
		./bin/$$bin; \
		echo ""; \
	done


clean:
	rm -df $(TARGETS) *~
