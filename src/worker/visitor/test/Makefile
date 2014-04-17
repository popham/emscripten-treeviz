ROOT = /home/popham/linode/emscripten-treeviz
include $(ROOT)/Makefile.inc

VISITOR_TEST = visitor.o ../properties.o ../../graph.o
TEST_TARGETS = mess tree forward1 forward2 cross

test: $(TEST_TARGETS) test_subdirs

mess: mess.o $(VISITOR_TEST)
	$(CPP) $^ -o $@
tree: tree.o $(VISITOR_TEST)
	$(CPP) $^ -o $@
forward1: forward1.o $(VISITOR_TEST)
	$(CPP) $^ -o $@
forward2: forward2.o $(VISITOR_TEST)
	$(CPP) $^ -o $@
cross: cross.o $(VISITOR_TEST)
	$(CPP) $^ -o $@

visitor.o: visitor.cpp ../grid.hpp

clean: clean_subdirs
	rm -f $(TEST_TARGETS)
	rm -f *.o
