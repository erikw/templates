
BINDIR=/usr/local/bin
MANEXT=1
MANDIR=/usr/local/man/man$(MANEXT)
CFLAGS=-O

untex: untex.c
	$(CC) $(CFLAGS) -o untex untex.c

install: untex
	cp untex $(BINDIR)
	chmod 755 $(BINDIR)/untex

install.man: untex.man
	cp untex.man $(MANDIR)/untex.$(MANEXT) 
	chmod 644 $(MANDIR)/untex.$(MANEXT) 

tarfile: untex.c untex.man Makefile
	tar cvf untex-1.2.tar untex.c untex.man Makefile
	gzip -f untex-1.2.tar
	/bin/cp untex-1.2.tar.gz /nfs/sahara/ftp/pub/source
