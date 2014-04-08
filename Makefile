ROOT = /home/popham/linode/emscripten-treeviz
include $(ROOT)/Makefile.inc

lib:
	make -C owner/ lib
	make -C worker/ lib

test: test_subdirs

clean: clean_subdirs
	rm -rf lib/
	rm -f *.o *.a #clean_subdirs handles this for descendants
