################################################################################
#	Name       : Makefile
#	Author     : Didier Barvaux <didier.barvaux@toulouse.viveris.com>
#	Description: create the GSE library and the test application
################################################################################

SUBDIRS = \
	src \
	test \
	app

dist_doc_DATA = \
	AUTHORS \
	ChangeLog \
	COPYING.LESSER \
	COPYING.BSD \
	INSTALL \
	NEWS \
	README.md
	
EXTRA_DIST = \
	.clang-format \
	doc/doxygen \
	debian/changelog \
	debian/compat \
	debian/control \
	debian/copyright \
	debian/docs \
	debian/libgse-dev.dirs \
	debian/libgse-dev.install \
	debian/libgse.dirs \
	debian/libgse.install \
	debian/postinst \
	debian/postrm \
	debian/preinst \
	debian/prerm \
	debian/rules

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = gse.pc

.PHONY: doc format

doc:
	doxygen doc/doxygen

format:
	find src test app \( -name '*.[ch]' -o -name '*.cc' \) -print | xargs clang-format -i

clean-doc:
	$(RM) -r doc/html

