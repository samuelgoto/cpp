CC=g++
CPPFLAGS=-fno-elide-constructors

TARGETS= \
  hello \
  constructor \
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

%: src/%.o
	$(CC) $(CFLAGS) $(CPPFLAGS) $< -o bin/$@

src/%.o: src/%.c 
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $<

all: $(TARGETS)
	cat HEADER.md > README.md
	for bin in $(TARGETS); do \
		echo $$bin; \
		echo ""; \
		echo "# [$ssrc/$$bin.cc]($ssrc/$$bin.cc)" >> README.md; \
		echo "\`\`\`c++" >> README.md; \
		cat src/$$bin.cc >> README.md; \
		echo "\`\`\`" >> README.md; \
		echo "Result: " >> README.md; \
		echo "\`\`\`bash" >> README.md; \
		cat src/$$bin.out >> README.md; \
		echo "\`\`\`" >> README.md; \
		./bin/$$bin; \
		./bin/$$bin > src/$$bin.out; \
		echo ""; \
	done
	cat FOOTER.md >> README.md

clean:
	rm -df $(TARGETS) *~
