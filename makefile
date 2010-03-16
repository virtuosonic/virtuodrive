CC=gcc
LD=ld
PREFIX=/usr

all: virtuodrive-ladspa.so

install: all
	cp virtuodrive-ladspa.so $(PREFIX)/lib/ladspa/

clean:
	rm virtuodrive-ladspa.so virtuodrive-ladspa.o

virtuodrive-ladspa.so: virtuodrive-ladspa.o
	$(LD) -shared -o virtuodrive-ladspa.so virtuodrive-ladspa.o

virtuodrive-ladspa.o: virtuodrive-ladspa.c
	$(CC) -fPIC -DPIC -c -o virtuodrive-ladspa.o virtuodrive-ladspa.c

