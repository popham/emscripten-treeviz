define(['chai', '../treeish'], function (chai, treeish) {
/*
            if (svg.length === 0) {
                var parser = new DOMParser();
                var fragment = parser.parseFromString(svg, 'application/xml');
                var body = window.document.getElementsByTagName('body').item(0);
                body.appendChild(fragment.documentElement);
            } else {
                worker.terminate();
            }
        };
*/
    var assert = chai.assert;

    describe("Deep tree", function () {
        var layout;

        it("should instantiate", function () {
            layout = new treeish.Layout('/base/src/worker/test/deep.js');
            assert.ok(layout);
        });

        function bfStub() {
            return {
                before: { innerHTML: "" },
                after:  { innerHTML: "" }
            };
        }

        function assertNoOp(stub) {
            assert.deepEqual(stub.before, stub.after);
        }

        function assertOp(stub) {
            assert.notDeepEqual(stub.before, stub.after);
        }

        it("should load JSON data", function (done) {
            var states = bfStub();

            layout.injectSvg(states.before)
                .tap(treeish.load('/base/src/worker/test/deep.json'))
                .tap(treeish.injectSvg(states.after))
                .done(
                    function () {
                        assertOp(states);
                        done();
                    },
                    function (e) { throw new Error(e); });
        });

        it("should scale", function (done) {
            var states = bfStub();

            layout.injectSvg(states.before)
                .tap(treeish.scale(30,50))
                .tap(treeish.injectSvg(states.after))
                .done(
                    function () {
                        assertOp(states);
                        done();
                    },
                    function (e) { throw new Error(e); });
        });

        it("should take new physical parameters without changing state", function (done) {
            var states = bfStub();

            layout.injectSvg(states.before)
                .tap(treeish.setPhysics())
                .tap(treeish.injectSvg(states.after))
                .done(
                    function () {
                        assertNoOp(states);
                        done();
                    },
                    function (e) { throw new Error(e); });
        });

        it("should iterate to another configuration", function (done) {
            var states = bfStub();

            layout.injectSvg(states.before)
                .tap(treeish.iterate(5))
                .tap(treeish.injectSvg(states.after))
                .done(
                    function () {
                        assertOp(states);
                        done();
                    },
                    function (e) { throw new Error(e) });
        });

        it("should retrieve an SVG representation and install it to a node's innerHTML", function (done) {
            var stub = {};
            stub.innerHTML = "";

            layout.injectSvg(stub)
                .done(
                    function () {
                        assert.notEqual(stub.innerHTML, "");
                        done();
                    },
                    function (e) { throw new Error(e); })
        });

        it("should iterate to a yet another configuration", function (done) {
            var states = bfStub();

            layout.injectSvg(states.before)
                .tap(treeish.iterate(5))
                .tap(treeish.injectSvg(states.after))
                .done(
                    function () {
                        assertOp(states);
                        done();
                    },
                    function (e) { throw new Error(e) });
        });

        it("should become vacuous upon receiving a stop command", function (done) {
            var states = bfStub();

            layout.injectSvg(states.before)
                .tap(treeish.stop())
                .tap(treeish.injectSvg(states.after))
                .done(
                    function () {
                        assertOp(states);
                        assert.equal(states.after.innerHTML, "");
                        done();
                    },
                    function (e) { throw new Error(e) });
        });
    });
});
