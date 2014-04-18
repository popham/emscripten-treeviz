ROOT = /home/popham/linode/emscripten-treeviz
include $(ROOT)/Makefile.inc

LIB_MEMBERS = hypothetical

lib: $(LIBS)/librender.a

$(LIBS)/librender.a: $(addsuffix .o,$(LIB_MEMBERS)) | $(LIBS)
	$(ARCHIVE) $(LIBS)/librender.a $^

test: test_subdirs

clean: clean_subdirs
	rm -f $(LIBS)/librender.a
