CC=gcc
CFLAGS=-lm
DEBUG=-DDEBUG
.PHONY: default build clean test
default:
	$(info <make build> to create the binaries at bin/)
	$(info )
build:
	mkdir -p bin
	$(CC) src/lp/lp-bigm.c -o bin/lpbigm $(CFLAGS)
debug:
	mkdir -p bin
	$(CC) src/lp/lp-bigm.c -o bin/lpbigm $(CFLAGS) $(DEBUG)
clean:
	rm -f bin/lpbigm
	rm -rf bin/
