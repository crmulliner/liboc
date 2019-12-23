all: build

build:
	gcc -shared -fPIC -o liboc.so count.c -ldl

test: build
	./test/test.sh

