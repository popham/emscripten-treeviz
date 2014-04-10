INCLUDES = -I /home/popham/include/boost_1_55_0/ -I $(ROOT) -I $(ROOT)/rapidjson/include/ -I $(ROOT)/rapidxml/include/ -I $(ROOT)/lest/include/
EROOT = /home/popham/emscripten
LIBS = $(ROOT)/include
SUBDIRS := $(wildcard */.)

ifdef DEBUG
CPP = g++ -g -std=c++11 $(INCLUDES)
else
CPP = clang++ -std=c++11 $(INCLUDES)
endif

ifdef DEBUG
EMCC_WORKER = /home/popham/emscripten/emcc -O0 -std=c++11 -s BUILD_AS_WORKER=1 $(INCLUDES) -I $(EROOT)/include
else
EMCC_WORKER = /home/popham/emscripten/emcc -O3 --closure 1 -std=c++11 -s BUILD_AS_WORKER=1 $(INCLUDES) -I $(EROOT)/include
endif

ARCHIVE = ar rvs

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
