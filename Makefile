all: c_build

c_build:
	gcc -fPIC -shared -o $(CURDIR)/bk_field.so bk_field.c

install:
	mkdir -p /usr/local/sphinx/lib && cp bk_field.so /usr/local/sphinx/lib/
