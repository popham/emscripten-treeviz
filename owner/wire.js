define(['lodash', 'js!text_encoding/encoding.js'], function (_) {
    var exports = {};

    // Match emscripten's worker interface
    // Emscripten uses array indices for `callbackId`, so negative values will
    // avoid name collisions.
    var stub = {
        funcName : 'accept',
        callbackId : -1 
    };

    // use stringify instead <del>Simulate a read from the HEAPU8.  Verbatim of the `processJSString`
    // implementation from `runtime.js`.
    exports.serialize = function (payload) {
        payload = _.merge({ data : payload }, stub);

        return payload;
    };

    exports.unserialize = function(message) {
        // Remove Emscripten wire protocol additions from message.
        message = TextDecoder('utf-8').decode(message.data);
        message = JSON.parse(message);

        return message;
    };

    return exports;
});
