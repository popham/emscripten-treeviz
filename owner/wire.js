define(['lodash'], function (_) {
    var exports = {};

    // Match emscripten's worker interface
    // Emscripten uses array indices for `callbackId`, so negative values will
    // avoid name collisions.
    var stub = {
        funcName : 'listen',
        callbackId : -1 
    };

    // use stringify instead <del>Simulate a read from the HEAPU8.  Verbatim of the `processJSString`
    // implementation from `runtime.js`.
    exports.serialize = function (payload) {
        payload = _.merge({ data : payload }, stub);

        return JSON.stringify(payload);
    };

    exports.unserialize = function(message) {
        // Remove Emscripten wire protocol additions from message.
        message = JSON.parse(message).data;
        message.command = parseInt(message.command);

        return message;
    };
});
