ROOT = /home/popham/linode/emscripten-treeviz
include $(ROOT)/Makefile.inc

test: forward1 test_subdirs

forward1: forward1.o visitor.o ../../graph.o | build_libs
	$(CPP) $^ -o $@

clean: clean_subdirs
	rm -f forward1
