(function () {
    curl.config({
        baseUrl: '..',
        paths : {
            curl : 'node_modules/curl/src/curl'
        },
        plugins: {
            js :  { prefetch : false },
            css : { nowait   : true }
        }
    });

    curl(['parent/command']).then(start, fail);

    function start(command) {
        var worker = new Worker('/child/dag.js');
        worker.onmessage = function (event) {
            var svg = event.data;

            if (svg.length === 0) {
                var parser = new DOMParser();
                var fragment = parser.parseFromString(svg, 'application/xml');
                var body = window.document.getElementsByTagName('body').item(0);
                body.appendChild(fragment.documentElement);
            } else {
                worker.terminate();
            }
        };
        worker.postMessage(command.load('tree1.js'));
        worker.postMessage(command.scale(30,45));
        worker.postMessage(command.set_physics());
        worker.postMessage(command.iterate(5));
        worker.postMessage(command.stop());
    }

    function fail(ex) {
        alert('Migrate to AJAXy webservice during production (include user and session to avoid expoiters)\n\nError: ' + ex);
    }
}());
