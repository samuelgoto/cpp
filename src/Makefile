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

ERRORS= \
  no-copyctr.err \
  no-assign.err \

# FAILS = $(ERRORS:.cc=)

%.err : %.cc
	-$(CC) $(CFLAGS) $(CPPFLAGS) $< -o /tmp/$@ 2> bin/$@ || true

%: %.o
	$(CC) $(CFLAGS) $(CPPFLAGS) $< -o bin/$@

%.o: %.cc
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $<

all: $(TARGETS) $(ERRORS)
	cat HEADER.md > README.md
	for bin in $(TARGETS); do \
		echo $$bin; \
		echo ""; \
		echo "# [$ssrc/$$bin.cc]($ssrc/$$bin.cc)" >> README.md; \
		echo "\`\`\`c++" >> README.md; \
		cat $$bin.cc >> README.md; \
		echo "\`\`\`" >> README.md; \
		echo "Result:" >> README.md; \
		echo "\`\`\`bash" >> README.md; \
		./$$bin; \
		./$$bin > $$bin.out; \
		cat $$bin.out >> README.md; \
		echo "\`\`\`" >> README.md; \
		echo ""; \
	done

	@echo $(ERRORS)
	for bin in $(ERRORS:.err=); do \
		echo $$bin; \
		echo ""; \
		echo "# [$ssrc/$$bin.cc]($ssrc/$$bin.cc)" >> README.md; \
		echo "\`\`\`c++" >> README.md; \
		cat $$bin.cc >> README.md; \
		echo "\`\`\`" >> README.md; \
		echo "Result:" >> README.md; \
		echo "\`\`\`bash" >> README.md; \
		cat bin/$$bin.err >> README.md; \
		echo "\`\`\`" >> README.md; \
		echo ""; \
	done

	cat FOOTER.md >> README.md

clean:
	rm -df $(TARGETS) *~ bin/*
