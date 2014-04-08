ROOT = /home/popham/linode/emscripten-treeviz
include $(ROOT)/Makefile.inc

lib: $(LIBS)/libworker.a

$(LIBS)/libworker.a: accept.o bound_buffer.o builder.o command.o matching.o response.o treeish.o | $(LIBS)
	$(ARCHIVE) $(LIBS)/libworker.a $^

js3:
	~/emscripten/emcc -O3 accept.cpp builder.cpp command.cpp treeish.cpp response.cpp -o main.js -std=c++11 -s BUILD_AS_WORKER=1 -s EXPORTED_FUNCTIONS="['_accept']" --closure 1 --js-library request.js

test: test_subdirs

clean: clean_subdirs
	rm -f $(LIBS)/libworker.a main.js
