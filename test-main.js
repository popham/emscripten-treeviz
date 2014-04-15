var allTestFiles = [];
var TEST_REGEXP = /src\/.*?\.spec\.js$/i;

var pathToModule = function(path) {
  return path.replace(/^\/base\//, '').replace(/\.js$/, '');
};

Object.keys(window.__karma__.files).forEach(function(file) {
  if (TEST_REGEXP.test(file)) {
    // Normalize paths to AMD paths.
    allTestFiles.push(pathToModule(file));
  }
});

curl.config({
    baseUrl : 'base',
    paths : {
        chai : 'node_modules/chai/chai',
        curl : 'node_modules/curl-amd/src/curl',
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
        },
        {
            name : 'src',
            location : 'src/',
            config: { loader: 'karma-cache', 'lookup-prefix': '/' } // lookup prefix \equiv path from config to base when path contains base (?)
        }
    ],
    plugins : {
        js :  { prefetch : false },
        css : { nowait   : true }
    }
});

curl(allTestFiles)
    .then(
        window.__karma__.start,
        function (ng) { throw new Error(ng.message); } );
