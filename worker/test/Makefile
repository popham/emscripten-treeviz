ROOT = /home/popham/linode/emscripten-treeviz
include $(ROOT)/Makefile.inc

test: treeish test_subdirs

treeish: treeish.cpp | build_libs
	$(CPP) -L $(LIBS) treeish.cpp -l worker -l owner -o treeish

clean: clean_subdirs
	rm -f treeish

