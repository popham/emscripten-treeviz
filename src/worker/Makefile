ROOT = /home/popham/linode/emscripten-treeviz
include $(ROOT)/Makefile.inc

LIB_MEMBERS = accept bound_buffer builder command graph matching response treeish

lib: $(LIBS)/libworker.a

$(LIBS)/libworker.a: $(addsuffix .o,$(LIB_MEMBERS)) | $(LIBS)
	$(ARCHIVE) $(LIBS)/libworker.a $^

test: test_subdirs

clean: clean_subdirs
	rm -f $(LIBS)/libworker.a
