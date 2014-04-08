INCLUDES = -I /home/popham/include/boost_1_55_0/ -I $(ROOT) -I $(ROOT)/rapidjson/include/ -I $(ROOT)/rapidxml/include/ -I $(ROOT)/lest/include/
LIBS = $(ROOT)/include
SUBDIRS := $(wildcard */.)

ARCHIVE = ar rvs
CPP = clang++ -std=c++11 $(INCLUDES)

build_libs: | $(LIBS)
	make -C $(ROOT) lib

$(LIBS):
	mkdir $(LIBS)

clean_subdirs: $(SUBDIRS)
	$(foreach dir, $^, make -C $(dir) clean; rm -f $(dir)/*.o $(dir)/*.a;)

test_subdirs: $(SUBDIRS)
	$(foreach dir, $^, make -C $(dir) test;)

%.o: %.cpp
	$(CPP) $< -c -o $@

%.cpp: %.hpp
	touch $@
