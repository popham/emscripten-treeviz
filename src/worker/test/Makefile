ROOT = /home/popham/linode/emscripten-treeviz
include $(ROOT)/Makefile.inc

WORKER_LIB = $(addprefix ../,$(addsuffix .cpp,accept bound_buffer builder command matching response treeish))

test: treeish flat deep test_subdirs

all: deep.js

treeish: treeish.cpp | build_libs
	$(CPP) -L $(LIBS) treeish.cpp -l worker -l owner -o treeish

flat: sax/flat.cpp sax/flat_path.cpp sax.cpp | build_libs
	$(CPP) -L $(LIBS) $^ -l worker -l owner -o flat

flat.js: sax/flat.cpp sax/flat_path.cpp sax.cpp | build_libs
	$(shell ./flat > ./flat.json)
	$(EMCC_WORKER) $(addprefix ../,$(WORKER_LIB)) sax/flat_path.cpp -s EXPORTED_FUNCTIONS="['_accept']" --js-library ../request.js -o flat.js

deep: sax/deep.cpp sax/deep_path.cpp sax.cpp | build_libs
	$(CPP) -L $(LIBS) $^ -l worker -l owner -o deep

deep.js: deep $(WORKER_LIB)
	$(shell ./deep > ./deep.json)
	$(EMCC_WORKER) $(WORKER_LIB) sax/deep_path.cpp -s EXPORTED_FUNCTIONS="['_accept','_init_bound_buffer']" --js-library ../request.js -o deep.js

clean: clean_subdirs
	rm -f treeish
	rm -f flat flat.js flat.js.map flat.json
	rm -f deep deep.js deep.js.map deep.json
