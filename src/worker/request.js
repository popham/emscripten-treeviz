//"use strict";
mergeInto(LibraryManager.library, {
    /**
     * Synchronously grab data and leak it to the heap.  The caller is
     * responsible for deallocating the buffer, e.g. `dealloc_bound_buffer`.
     */
    get : function (target, url) {
        var url_ = Pointer_stringify(url);
        var http = new XMLHttpRequest();
        http.open("GET", url_, false);
        http.responseType = "arraybuffer";

        var byteArray;

        http.onload = function (e) {
            if (http.status == 200 || url_.substr(0,4).toLowerCase() != "http") {
                byteArray = new Uint8Array(http.response);
            } else {
                // Vacuous on errors
                byteArray = new Uint8Array("");
            }
        };

        http.onerror = function (e) {
            byteArray = new Uint8Array("");
        };

        http.send(null);
        var length = byteArray.length;
        var buffer = _malloc(length);
        HEAPU8.set(byteArray, buffer);
        _init_bound_buffer(target, buffer, length);
    }
});
