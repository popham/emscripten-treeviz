ROOT = /home/popham/linode/emscripten-treeviz
include $(ROOT)/Makefile.inc

WORKER_LIB = $(addprefix ../,$(addsuffix .cpp,accept bound_buffer builder command graph matching response treeish))
RENDER_LIB = $(addprefix ../render/,$(addsuffix .cpp,hypothetical))

test: treeish flat deep flat.js deep.js test_subdirs

treeish: render.cpp treeish.cpp $(WORKER_LIB) $(RENDER_LIB) | build_libs
	$(CPP) -L $(LIBS) $^ -l worker -l owner -o treeish

flat: render.cpp sax/flat.cpp sax/flat_path.cpp sax.cpp | build_libs
	$(CPP) -L $(LIBS) $^ -l render -l worker -l owner -o flat

flat.js: flat $(WORKER_LIB) $(RENDER_LIB) ../request.js
	$(shell ./flat > ./flat.json)
	$(EMCC_WORKER) $(WORKER_LIB) $(RENDER_LIB) render.cpp sax/flat_path.cpp -s EXPORTED_FUNCTIONS="['_accept']" --js-library ../request.js -o flat.js

deep: render.cpp sax/deep.cpp sax/deep_path.cpp sax.cpp | build_libs
	$(CPP) -L $(LIBS) $^ -l render -l worker -l owner -o deep

deep.js: deep $(WORKER_LIB) ../request.js
	$(shell ./deep > ./deep.json)
	$(EMCC_WORKER) $(WORKER_LIB) $(RENDER_LIB) render.cpp sax/deep_path.cpp -s EXPORTED_FUNCTIONS="['_accept','_init_bound_buffer']" --js-library ../request.js -o deep.js

$(RENDER_LIB): ../visitor/grid.hpp
	touch $(RENDER_LIB)

clean: clean_subdirs
	rm -f treeish
	rm -f flat flat.js flat.js.map flat.json
	rm -f deep deep.js deep.js.map deep.json
