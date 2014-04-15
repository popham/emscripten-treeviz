// Karma configuration
// Generated on Fri Apr 11 2014 09:52:03 GMT-0700 (PDT)

module.exports = function(config) {
    config.set({
        // base path that will be used to resolve all patterns (eg. files, exclude)
        basePath: '',
        frameworks: ['mocha', 'curl-amd'],
        files: [
            { pattern: 'node_modules/**/*.js', watched: false, included: false, served: true },
            { pattern: 'src/**/*', watched: true, included: false, served: true },
            { pattern: 'src/**/*.spec.js', watched:true, included: false, served: true },
            'test-main.js'
        ],
        exclude: [
            'src/**/*.hpp',
            'src/**/*.cpp'
        ],

        // preprocess matching files before serving them to the browser
        // available preprocessors: https://npmjs.org/browse/keyword/karma-preprocessor
        preprocessors: {},

        reporters: ['spec'],

        //browsers: ['Chrome', 'PhantomJS', 'Firefox'],
        browsers: ['Chrome'],
        singleRun: false,
        client: {
            mocha: {
                ui: 'bdd'
            }
        },

        // web server port
        port: 9876,
        colors: true,

        // level of logging
        // possible values: config.LOG_DISABLE || config.LOG_ERROR || config.LOG_WARN || config.LOG_INFO || config.LOG_DEBUG
        logLevel: config.LOG_WARN,

        // enable / disable watching file and executing tests whenever any file changes
        autoWatch: true
    });
};
