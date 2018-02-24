include VERSION
include Makefile.inc

.PHONY: all doc clean_doc clean test slibc tests_slibc tests_ow

all: slibc

ARCHIVE_NAME = slibc-$(VER_MAJOR).$(VER_MINOR).$(VER_RELEASE)
archive:
	rm -rf ./gen/
	mkdir ./gen/
	svn export ./ ./gen/$(ARCHIVE_NAME)
	cd ./gen/ && tar czf $(ARCHIVE_NAME).tar.gz $(ARCHIVE_NAME)/
	rm -rf ./gen/$(ARCHIVE_NAME)

install_devel:
	install -d $(DESTDIR)/$(includedir)/slibc/
	install -D include/slibc/* $(DESTDIR)/$(includedir)/slibc/

install_doc: doc
	install -d $(DESTDIR)/$(mandir)/man3/
	install -m 444 -D doc/man/man3/* $(DESTDIR)/$(mandir)/man3/

install: test install_devel install_doc
	install -d $(DESTDIR)/$(libdir)/
	install -D src/$(SLIBC_LIB_SO) $(DESTDIR)/$(libdir)/$(SLIBC_LIB_SO)

# build targets
tests_slibc: slibc
	$(MAKE) -C tests_slibc/

tests_ow: slibc
	$(MAKE) -C tests_ow/

slibc:
	$(MAKE) -C src/

test: slibc
	-$(MAKE) -C src/ prepare_test
	-$(MAKE) -C tests_slibc/ test
	-$(MAKE) -C tests_ow/ test

doc: clean_doc
	doxygen ./slibc.doxy

clean_doc:
	rm -rf doc/html doc/latex doc/man

clean: clean_doc
	$(MAKE) -C src/ clean
	$(MAKE) -C tests_slibc/ clean
	$(MAKE) -C tests_ow/ clean
