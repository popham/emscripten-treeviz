define(['lodash'], function (_) {
    var exports = {};

    var controls = function (knots) {
        var control = [[], []];
        var n = knots.length - 1;

        var a = [0];
        var b = [2];
        var c = [1];
        var r = [ knots[0] + 2*knots[1] ];

        for (i = 1; i < n - 1; i++) {
            a[i] = 1;
            b[i] = 4;
            c[i] = 1;
            r[i] = 4*knots[i] + 2*knots[i+1];
        }

        a[n-1] = 2;
        b[n-1] = 7;
        c[n-1] = 0;
        r[n-1] = 8*knots[n-1] + knots[n];

        for (i = 1; i < n; i++) {
            m = a[i] / b[i-1];
            b[i] = b[i] - m * c[i-1];
            r[i] = r[i] - m*r[i-1];
        }

        control[0][n-1] = r[n-1]/b[n-1];
        for (i = n - 2; i >= 0; i--) {
            control[0][i] = (r[i] - c[i] * control[0][i+1]) / b[i];
        }

        for (i=0;i<n-1;i++) { control[1][i] = 2*knots[i+1] - control[0][i+1]; }
        control[1][n-1] = 0.5*(knots[n] + control[0][n-1]);

        return control;
    }

    exports.Spline = function (knots) {
        this.knots = knots;
    }

    exports.Spline.prototype.svg = function () {
        var xControl = controls(_.map(knots, function (knot) { return knot.x; }));
        var yControl = controls(_.map(knots, function (knot) { return knot.y; }));

        
    };

    return exports;
});
