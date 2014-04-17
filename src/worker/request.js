//"use strict";
mergeInto(LibraryManager.library, {
    /**
     * Synchronously grab data and leak it to the heap.  The caller is
     * responsible for deallocating the buffer, e.g. `dealloc_bound_buffer`.
     */
    getJson : function (target, url) {
        var url = Pointer_stringify(url);

        function dump(bb, string) {
            var utf8 = new Runtime.UTF8Processor();
            var buffer = utf8.processJSString(string);
            buffer.push(0); // terminal null
            var data = new Uint8Array(buffer);
            var size = data.length;
            var first = Module._malloc(size);
            Module.HEAPU8.set(data, first); // copy without offset
            _init_bound_buffer(bb, first, size-1); // ignore null terminator
        }

        var http = new XMLHttpRequest();
        http.onload = function (e) {
            if (http.status == 200 || url.substr(0,4).toLowerCase() != "http") {
                dump(target, http.response);
            } else {
                // Vacuous on errors
                dump(target, "");
            }
        };

        http.onerror = function (e) {
            dump(target, "");
        };

        http.open("GET", url, false);
        http.setRequestHeader("Accept", "application/json");
        http.send(null);
    }
});
