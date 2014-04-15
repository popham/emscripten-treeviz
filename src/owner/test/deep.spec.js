define(['chai'], function (chai) {
var assert = chai.assert;

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

    describe("Deep tree worker", function () {
        var stub = {};
        stub.innerHTML = "";
        var layout;
        var promise;

        it("should instantiate", function () {
            layout = new treeish.Layout('/base/worker/test/deep.js');
            assert.ok(layout);
        });

        it("should load", function () {
            promise = layout.load('/base/worker/test/deep.json');
            assert.equal(true, false);
            // interrogate
        });

        it("should scale", function () {
            promise.then(treeish.scale(30,50));
            assert.equal(true, false);
        });

        it("should take new physical parameters", function () {
            promise.then(treeish.setPhysics());
            assert.equal(true, false);
        });

        it("should iterate to a better configuration", function () {
            promise.then(treeish.iterate(5));
            assert.equal(true, false);
        });

        it("should retrieve an SVG representation and install it to a node's innerHTML", function () {
            promise.then(treeish.installSvg(stub));
            assert.equal(true, false);
        });

        it("should iterate to a still better configuration", function () {
            promise.then(treeish.iterate(5));
            assert.equal(true, false);
        });

        it("should retrieve a new SVG representation and install it to a node's innerHTML", function () {
            promise.then(treeish.installSvg(stub));
            assert.equal(true, false);
        })

        it("should terminate", function () {
            promise.then(treeish.stop());
            assert.equal(true, false);
        });

        it("should retrieve a vacuous SVG representatino after stopping", function () {
            promise.then(treeish.installSvg(stub));
            assert.equal(true, false);
        });

        it("should be in a non-error state after the preceding sequence", function () {
            // Spies promise library for cases like this?
            promise.done(function () {console.log('huzzah');},
                         function (e) {console.log(e);});
            assert.equal(true, false);
        });;
    });
});
