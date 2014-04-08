ROOT = /home/popham/linode/emscripten-treeviz
include $(ROOT)/Makefile.inc

lib: $(LIBS)/libowner.a

$(LIBS)/libowner.a: protocol.o json.o | $(LIBS)
	$(ARCHIVE) $(LIBS)/libowner.a $^

test: test_subdirs

clean: clean_subdirs
	rm -f $(LIBS)/libowner.a
