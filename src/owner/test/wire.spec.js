define(['chai', '../wire'], function (chai, wire) {
    var assert = chai.assert;

    function roundTrip(obj, message) {
        assert.deepEqual(
            obj,
            wire.unserialize(wire.serialize(obj)),
            message
        );
    }

    describe("Wire protocol", function () {
        it("should roundtrip string data without altering it", function () {
            roundTrip("`1234567890-=qwertyuiop[]asdfghjkl;'zxcvbnm,./~!@#$%^&*()_+QERTYUIOP{}|ASDFGHJKL:\"ZXCVBNM<>?", "Any old character should roundtrip to the same character.");
            roundTrip({a:'1'}, "Singleton objects with string values should roundtrip to the same data structure.");
            roundTrip({a:'asdf', b:{c:['qwerty']}}, "Nontrivial objects with string values should roundtrip to the same data structure.");
        });

        it("should roundtrip integral data without altering it", function () {
            roundTrip({a:5}, "Singleton objects with integral values should roundtrip to the same data structure.");
            roundTrip({a:56, b:93, c:-12, d:{e:0}}, "Nontrivial objects with integral values should roundtrip to the same data structure.");
        });

        it("should roundtrip floating point data without altering it", function () {
            roundTrip({a:3.292e+8}, "Singleton objects with floating point values should round trip to the same data structure.");
            roundTrip({a:2.4e-9, b:{c:4.32, d:[-5.6]}}, "Nontrivial objects with floating point values should roundtrip to the same data structure");
        });

        it("should roundtrip arbitrary data without altering it", function () {
            roundTrip({a:"844", b:832, c:[12, "a", "34"], d:{e:"qwe45", f:[12]}}, "Big old messy objects should roundtrip to the same data structure");
        });
    });
});
