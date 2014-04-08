define(['cujo/when', './wire'], function (when, wire) {
    var exports = {};

    // Load from (compile -> js!...) to avoid repetition?
    var Command = {
        LOAD : 1,
        SCALE : 2,
        SET_PHYSICS : 3,
        ITERATE : 4,
        STOP : 5,
        RENDER_SVG : 20
    };

    var Response = {
        VOID : 1,
        CLEAN : 2,
        SVG : 20
    };

    function vacuousResolver(deferred, okValue) {
        return function (message) {
            message = JSON.parse(message);
            if (message['error']) {
                deferred.resolver.reject(message.error);
            } else {
                deferred.resolver.resolve(okValue);
            }
        }
    }

    exports.load = function (url) {
        return function (layout) {
            var deferred = when.defer();

            layout.setResolver(vacuousResolver(deferred, layout));
            layout.do(loadMessage(url));

            return deferred.promise;
        };
    };

    function loadMessage(resourceUrl) {
        return wire.serialize({
            command : Command.LOAD,
            dataSource : resourceUrl
        });
    };

    exports.setPhysics = function () {
        return function (layout) {
            var deferred = when.defer();

            layout.setResolver(vacuousResolver(deferred, layout));
            layout.do(setPhysicsMessage());

            return deferred.promise;
        };
    };

    function setPhysicsMessage() {
        return wire.serialize({
            command : Command.SET_PHYSICS
        });
    };

    exports.scale = function (depth, breadth) {
        return function (layout) {
            var deferred = when.defer();

            layout.setResolver(vacuousResolver(deferred, layout));
            layout.do(scaleMessage(depth, breadth));

            return deferred.promise;
        };
    };

    function scaleMessage(depth, breadth) {
        return wire.serialize({
            command : Command.SCALE,
            depth : depth,
            breadth : breadth
        });
    };

    exports.iterate = function (count) {
        return function (layout) {
            var deferred = when.defer();

            layout.setResolver(vacuousResolver(deferred, layout));
            layout.do(iterateMessage(count));

            return deferred.promise;
        };
    };

    function iterateMessage(count) {
        return wire.serialize({
            command : Command.ITERATE,
            count : count
        });
    };

    exports.stop = function () {
        return function (layout) {
            var deferred = when.defer();

            layout.setResolver(vacuousResolver(deferred, layout));
            layout.do(iterateMessage(count));

            return deferred.promise;
        }
    };

    function stopMessage() {
        return wire.serialize({
            command : Command.STOP
        });
    };

    exports.installSvg = function (parent) {
        return function (layout) {
            var deferred = when.defer();

            layout.setResolver(function (message) {
                if (message['error']) {
                    deferred.resolver.reject(message.error);
                } else {
                    parent.innerHTML = message.fragment;
                    deferred.resolver.resolve(layout);
                }
            });
            layout.do(renderSvgMessage());

            return deferred.promise;
        };
    };

    function renderSvgMessage() {
        return wire.serialize({
            command : Command.RENDER_SVG
        });
    }

    exports.Layout = function (scriptUrl) {
        this.worker = new Worker(scriptUrl);
        this.resolverRegister = undefined;

        this.worker.onmessage = function (event) {
            var message = wire.unserialize(event.message);
            this.resolverRegister(message);
        };
    };

    exports.Layout.prototype.setResolver = function (resolver) {
        this.resolverRegister = resolver;
    };

    exports.Layout.prototype.do = function (command) {
        this.worker.postMessage(command);
    };

    exports.Layout.prototype.load = function (url) {
        return exports.load(url)(this);
    };

    return exports;
});
