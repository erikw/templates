# Generate a mood graph.
IN=something
OUT=$(IN).png


.PHONY: all clean help

# target: all - Default target. Cleans and compiles.
all: $(OUT)

# target: help - Display all targets.
help:
	@egrep "#\starget:" [Mm]akefile  | cut -d " " -f3-

# target: clean - Deletes all generated files.
clean:
	$(RM) $(OUT)

# target open - open the produced png file.
open: $(OUT)
	open $<

%.png : %.dat %.pg
	./$(subst dat,pg,$<) > $@
