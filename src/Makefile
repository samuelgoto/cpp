CC=g++
CPPFLAGS=-fno-elide-constructors

TARGETS= \
  hello \
  constructor \
  delete \
  destructor \
  fields \
  fields_dtr \
  unique_ptr \
  overload \
  copy \
  copyctr \
  deepctr \
  movectr \
  parameters \
  templates \
  userland

.SILENT: all

%: %.o
	$(CC) $(CFLAGS) $(CPPFLAGS) $< -o bin/$@

%.o: %.c 
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $<

all: $(TARGETS)
	cat HEADER.md > README.md
	for bin in $(TARGETS); do \
		echo $$bin; \
		echo ""; \
		echo "# [$ssrc/$$bin.cc]($ssrc/$$bin.cc)" >> README.md; \
		echo "\`\`\`c++" >> README.md; \
		cat $$bin.cc >> README.md; \
		echo "\`\`\`" >> README.md; \
		echo "Result: " >> README.md; \
		echo "\`\`\`bash" >> README.md; \
		./$$bin; \
		./$$bin > $$bin.out; \
		cat $$bin.out >> README.md; \
		echo "\`\`\`" >> README.md; \
		echo ""; \
	done
	cat FOOTER.md >> README.md

clean:
	rm -df $(TARGETS) *~
