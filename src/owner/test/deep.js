(function () {
    curl.config({
        baseUrl: '../..',
        paths : {
            curl : 'node_modules/curl/src/curl',
            'text-encoding' : 'node_modules/text-encoding/lib/encoding'
        },
        packages : [
            {
                name : 'lodash',
                location : 'node_modules/lodash-amd',
                main : 'main'
            },
            {
                name : 'when',
                location : 'node_modules/when',
                main : 'when'
            }
        ],
        plugins: {
            js :  { prefetch : false },
            css : { nowait   : true }
        }
    });

    curl(['owner/treeish']).then(start, fail);

    function start(treeish) {
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

        var target = document.getElementById('target');
        var layout = new treeish.Layout('/worker/test/deep.js');
        layout.load('/worker/test/deep.json')
            .then(treeish.scale(30,50))
            .then(treeish.setPhysics())
            .then(treeish.iterate(5))
            .then(treeish.installSvg(target))
            .then(treeish.iterate(5))
            .then(treeish.installSvg(target))
            .then(treeish.stop())
            .done(function () {console.log('huzzah');},
                  function (e) {console.log(e);});
    }

    function fail(ex) {
        alert('Migrate to AJAXy webservice during production (include user and session to avoid expoiters)\n\nError: ' + ex);
    }
}());
