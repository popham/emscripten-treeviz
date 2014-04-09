ROOT = /home/popham/linode/emscripten-treeviz
include $(ROOT)/Makefile.inc

LIB_MEMBERS = accept bound_buffer builder command matching response treeish

lib: $(LIBS)/libworker.a

$(LIBS)/libworker.a: $(addsuffix .o,$(LIB_MEMBERS)) | $(LIBS)
	$(ARCHIVE) $(LIBS)/libworker.a $^

worker:
	$(EMCC_WORKER) $(addsuffix .cpp,$(LIB_MEMBERS)) -s EXPORTED_FUNCTIONS="['_accept']" --js-library request.js -o main.js 

test: test_subdirs

clean: clean_subdirs
	rm -f $(LIBS)/libworker.a main.js
