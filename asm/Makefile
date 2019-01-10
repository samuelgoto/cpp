CC=g++
CPPFLAGS=-fno-elide-constructors -g -O0 -c

TARGETS= main.s constructor.s copyctr.s

.SILENT: all

%.o: %.cc
	$(CC) $(CFLAGS) $(CPPFLAGS) $< -o $@

%.ss: %.o
	objdump -d -M intel -S $< > $@

%.s: %.cc
	cce compile g82 $< > $@

foo := $(subst ".s", ".cc", $$bin)

all: $(TARGETS)
	cat HEADER.md > README.md
	for bin in $(TARGETS); do \
		echo `basename -s .s $$bin`.cc; \
		echo "# [`basename -s .s $$bin`.cc](`basename -s .s $$bin`.cc)" >> README.md; \
		echo "" >> README.md; \
		echo "\`\`\`c++" >> README.md; \
		cat `basename -s .s $$bin`.cc >> README.md; \
		echo "\`\`\`" >> README.md; \
		echo "" >> README.md; \
		echo "Machine code: " >> README.md; \
		echo "" >> README.md; \
		echo "\`\`\`assembly" >> README.md; \
		cat $$bin >> README.md; \
		echo "\`\`\`" >> README.md; \
	done
	cat FOOTER.md >> README.md

clean:
	rm -df $(TARGETS) *~ *.o
