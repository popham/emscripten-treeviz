ROOT = /home/popham/linode/emscripten-treeviz
include $(ROOT)/Makefile.inc

LIB_MEMBERS = inject iterate load render_svg scale set_physics stop

lib: $(LIBS)/libcommand.a

$(LIBS)/libcommand.a: $(addsuffix .o,$(LIB_MEMBERS)) | $(LIBS)
	$(ARCHIVE) $(LIBS)/libcommand.a $^

test: test_subdirs

clean: clean_subdirs
	rm -f $(LIBS)/libcommand.a
