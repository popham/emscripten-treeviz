//"use strict";
mergeInto(LibraryManager.library, {
    /**
     * Synchronously grab data and leak it to the heap.  The caller is
     * responsible for deallocating the buffer, e.g. `dealloc_bound_buffer`.
     */
    get : function (target, url) {
        _log_message("PEEP");
        function dump(response) {
            var length = response.length;
            var buffer = _malloc(length);
            writeStringToMemory(response, buffer);
            _init_bound_buffer(target, buffer, length);
        }

        var url_ = Pointer_stringify(url);
        var http = new XMLHttpRequest();
        http.open("GET", url_, false);
        http.responseType = "arraybuffer";

        // Null terminated string response.
        var byteArray;

        http.onload = function (e) {
            if (http.status == 200 || url_.substr(0,4).toLowerCase() != "http") {
                dump(http.response);
            } else {
                // Vacuous on errors
                dump("");
            }
        };

        http.onerror = function (e) {
            dump("");
        };

        http.send(null);
    }
});
