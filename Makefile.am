include Makefile.rules
EXTRA_DIST = ChangeLog README
SUBDIRS = src

install-dev: install
	$(MKDIR_P) "$(DESTDIR)$(includedir)" || exit $?
	cp -av $(top_srcdir)/$(ycc_includedir)/ycc "$(DESTDIR)$(includedir)" \
		|| exit $?
uninstall-dev: uninstall
	rm -fr $(DESTDIR)$(includedir)/ycc
