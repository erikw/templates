# Makefile for C projects.

# Not file targets.
.PHONY: clean help list tar tar-src

### Macros ###
MAIN		= polymul
SRC		= src
SRCS		= $(wildcard $(SRC)/*.c)
HDR		= include
DEST		= bin
LIB		= lib
#SLIBS		= $(wildcard $(LIB)/*.a)
OBJS		= $(patsubst $(SRC)/%.c,$(DEST)/%.o,$(SRCS))
TESTDIR		= testfiles
TESTOUTS	= $(wildcard $(TESTDIR)/*.out)
THISDIR		= $(shell basename `pwd`)

CC		=  $(shell hash clang 2>/dev/null && echo clang || echo gcc)
#DEBUG		= -g
STD		= c99
OPTLVL		= 3
#OPTLVL		= 0
ERRFLAGS	= -Wall -Wextra -Werror
INCLUDES	= -I$(HDR)
#LFLAGS		= -L$(LIB)
#LIBS		= -lm -lpcre
CFLAGS		= $(ERRFLAGS) -O$(OPTLVL) $(DEBUG) -std=$(STD) -fstack-protector-all
ifeq ($(CXX), gcc)
	CFLAGS +=  -z noexecstack
endif
CFLAGS		+= $(INCLUDES) $(LFLAGS) $(LIBS)
DFLAGS		= -q
#DFLAGS		= -y

### Targets ###
# target: all - Default target. Clean and compile.
all : clean compile symlink

# target: clean - Deletes all compiled and generated files.
clean :
	$(RM) $(wildcard $(DEST)/*)
	$(RM) $(MAIN)

# target: compile - Compile everything.
compile :
	$(CC) $(CFLAGS) -o $(DEST)/$(MAIN) $(SRCS) $(SLIBS)

# target: symlink - Make symbolic link to the main program.
symlink : compile
	ln -s $(DEST)/$(MAIN) .

# target: help - Display all targets.
help :
	@egrep "#\starget:" [Mm]akefile  | sed 's/\s-\s/\t\t\t/' | cut -d " " -f3- | sort -d

# target: list - List all source files.
list :
	@ls -l $(SRC)/*.[ch]

# target: tar - Pack all the files to a gzip'd tarball.
tar :
	tar pvczf ../$(MAIN).tar.gz -C .. $(THISDIR)

# target: tar_src - Pack the source files only.
tar-src :
	tar pvczf ../$(MAIN).src.tar.gz $(SRC) $(HDR)

# target: tags - Generate tags with ctags for all files.
tags :
	ctags -R *

# target: doc - Generate documentation.
doc :
	#doxygen

# target: test - Test all files found in the testfile directory.
test :  $(TESTOUTS:.out=.test)

%.test : %.in
	$(DEST)/$(MAIN) < $< 2>&1 | diff $(DFLAGS) $*.out -
