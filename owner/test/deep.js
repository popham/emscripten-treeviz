(function () {
    curl.config({
        baseUrl: '..',
        paths : {
            curl : 'node_modules/curl/src/curl',
            when : 'node_modules/when/when.js'
        },
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
        var layout = new treeish.Layout('/worker/test/deep.js');
        layout.load('/worker/test/deep.json')
            .then(treeish.scale(30,50))
            .then(treeish.setPhysics())
            .then(treeish.iterate(5))
            .then(treeish.installSvg(node))
            .then(treeish.iterate(5))
            .then(treeish.installSvg(node))
            .then(treeish.stop())
            .done(function () {console.log('ok')},
                  function () {console.log('ng')});
    }

    function fail(ex) {
        alert('Migrate to AJAXy webservice during production (include user and session to avoid expoiters)\n\nError: ' + ex);
    }
}());
