CC=gcc
CFLAGS=-c -Wall -I$(HEADERDIR)
LFLAGS=

SOURCEDIR=source/
HEADERDIR=header/
OUTPUTDIR=out/

SOURCEFILES=$(SOURCEDIR)hello.c $(SOURCEDIR)mathlib.c
HEADERFILES=$(HEADERDIR)hello.h $(HEADERDIR)mathlib.h
OBJS=$(SOURCEFILES:.c=.o)
EXE=$(OUTPUTDIR)test

all: $(EXE)

$(EXE): $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o $@

$(OBJS): $(SOURCEFILES) $(HEADERFILES)
	$(CC) $(CFLAGS) $< -o $@

.PHONY: clean

clean:
	rm -f source/*.o out/*.exe