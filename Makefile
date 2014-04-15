ROOT = /home/popham/linode/emscripten-treeviz
include $(ROOT)/Makefile.inc

lib:
	make -C src/owner/ lib
	make -C src/worker/ lib

.PHONY: lib

test: test_subdirs

clean: clean_subdirs
	rm -rf lib/
	rm -f *.o *.a #clean_subdirs handles this for descendants
