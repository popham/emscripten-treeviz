define(['graph/tree'], function (tree) {
    var exports = {};

    var dag = [{
        "_id" : "rev1",
        "created" : 0,
        "modified" : 0
    }, {
        "_id" : "rev2",
        "parent_id" : "rev1",
        "created" : 5,
        "modified" : 5
    }, {
        "_id" : "rev3",
        "parent_id" : "rev1",
        "created" : 7,
        "modified" : 20
    }, {
        "_id" : "rev4",
        "parent_id" : "rev1",
        "created" : 24,
        "modified" : 30
    }, {
        "_id" : "rev5",
        "parent_id" : "rev1",
        "created" : 40,
        "modified" : 50
    }, {
        "_id" : "rev6",
        "parent_id" : "rev2",
        "created" : 10,
        "modified" : 20
    }, {
        "_id" : "rev7",
        "parent_id" : "rev2",
        "created" : 8,
        "modified" : 11
    }, {
        "_id" : "rev8",
        "parent_id" : "rev2",
        "created" : 10,
        "modified" : 10
    }, {
        "_id" : "rev9",
        "parent_id" : "rev2",
        "created" : 6,
        "modified" : 7
    }, {
        "_id" : "rev10",
        "parent_id" : "rev3",
        "created" : 28,
        "modified" : 50
    }, {
        "_id" : "rev11",
        "parent_id" : "rev3",
        "created" : 22,
        "modified" : 22
    }, {
        "_id" : "rev12",
        "parent_id" : "rev3",
        "created" : 80,
        "modified" : 90
    }, {
        "_id" : "rev13",
        "parent_id" : "rev11",
        "created" : 40,
        "modified" : 45
    }, {
        "_id" : "rev14",
        "parent_id" : "rev11",
        "created" : 25,
        "modified" : 30
    }, {
        "_id" : "rev15",
        "parent_id" : "rev14",
        "created" : 40,
        "modified" : 40
    }, {
        "_id" : "rev16",
        "parent_id" : "rev12",
        "created" : 109,
        "modified" : 200
    }];

    var root;
    var dagChildren = _.object(_.map(dag, function (v) { return [v._id, []]; }));
    _.each(dag, function (v) {
        if ('parent_id' in v) { dagChildren[v.parent_id].push(v); }
        else { root = v; }
    });
    function children (v) { return v in dagChildren ? dagChildren[v] : []; }

    exports.cardinal = tree.Graph.cardinal(
        root,
        children,
        function (vLhs, vRhs) { return vLhs.created - vRhs.created; }
    );

    exports.distance = tree.Graph.distance(
        root,
        children,
        function (v) { return v.created - root.created; }
    );

    exports.tree = tree.Graph.tiered(root, children);

    return exports;
});
