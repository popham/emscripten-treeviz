ROOT = /home/popham/linode/emscripten-treeviz
include $(ROOT)/Makefile.inc

test: treeish flat deep test_subdirs

treeish: treeish.cpp | build_libs
	$(CPP) -L $(LIBS) treeish.cpp -l worker -l owner -o treeish

flat: sax/flat.cpp sax.cpp | build_libs
	$(CPP) -L $(LIBS) $^ -l worker -l owner -o flat

deep: sax/deep.cpp sax.cpp | build_libs
	$(CPP) -L $(LIBS) $^ -l worker -l owner -o deep

clean: clean_subdirs
	rm -f treeish flat deep
