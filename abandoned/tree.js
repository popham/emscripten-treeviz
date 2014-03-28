/**
 * @module
 */
define(['lodash'], function (_) {
    var exports = {};

    /**
     * Vertex layout data structure.  The `toString` method admits the use of
     * `Position` instances as object keys.
     */
    exports.Location = function (i, j) {
        this.i = i;
        this.j = j;
    }
    exports.Location.prototype.toString = function () {
        return '(' + this.i + ',' + this.j + ')';
    }

    /**
     * Vertex data structure.  The `toString` method admits the use of `Vertex`
     * instances as object keys.
     */
    function Vertex(data, location) {
        this.location = location;
        this.targets = [];
        this.parent = undefined;
        this.data = data;
    }
    Vertex.prototype.appendTarget = function (target) {
        this.targets.push(target);
    }
    Vertex.prototype.toString = function () { return String(this.location); };

    /**
     * @classdesc Directed Acyclic Graph data structure--vertices and edges.  A
     * source and a target vertex can be linked by one and only one edge.  The
     * graph includes data with two parents twice, three parents thrice, etc.
     *
     * @class
     * @desc Produce depth ranked graph representation.
     *
     * @param {object} root - Data structure containing vertex data.
     * @param {Function(object)} children - Extract the children of `root`.
     * This same function must extract children from any of `root`'s
     * descendants.
     */
    exports.Dag = function (root, children) {
        this._children = children;
        this.vertices = this._buildBranch(root, new exports.Location(0, 0));
    };

    exports.Dag.depthFirstOrder = function (lhs, rhs) {
        lhs = lhs.location;
        rhs = rhs.location;

        return lhs.j === rhs.j ? lhs.i - rhs.i : lhs.j - rhs.j;
    };

    exports.Dag.breadthFirstOrder = function (lhs, rhs) {
        lhs = lhs.location;
        rhs = rhs.location;

        return lhs.i === rhs.i ? lhs.j - rhs.j : lhs.i - rhs.i;
    };

    /**
     * Add a vertex and its connectivity to the graph's `vertices` and `edges`.
     * A canonical layout is populated for the graph's vertices.  All children
     * have identical `i` locations, one larger than that of their parent.
     * Vertex `j` values are monitonic nondecreasing during depth first
     * traversal.  Vertices with multiple parents have more than one location
     * under the `Dag` data structure.  If a post processor chooses one of
     * these locations and ignores the other, then the layout will still include
     * space for the ignored other.
     *
     * @param {object} parent - Vertex data to add to graph.  The term `parent`
     * has been chosen, since its children are added recursively by this
     * function.
     * @param {Location} location - Grid position of the branch's root.
     *
     * @returns {Vertex[]} `Vertex` representation of `parent` and its
     * descendants.
     */
    exports.Dag.prototype._buildBranch = function (parent, location) {
        var vertex = new Vertex(location, parent);
        var branch = [vertex];

        // Build canonical structure where a branch and all of its descendants
        // have distinct `j` values from the branch's sibling branches.  Leaf
        // detection implies that the next node should have an incremented `j`
        // value (logically equivalent to the start of backtracking).
        location = new exports.Location(location.i+1, location.j);
        _.forEach(
            this._children(parent),
            function (child) {
                var descendants = this._buildBranch(child, location);
                var childVertex = descendants[0];
                branch = concat(branch, descendants);
                childVertex.parent = vertex;
                vertex.appendTarget(childVertex);

                // Prepare `location` for a sibling of `child`.
                var lastJ = descendants[descendants.length-1].location.j;
                location = new exports.Location(i, lastJ + 1);
            },
            this
        );

        return branch;
    };

    function Bracket(begin, end) {
        this.begin = begin;
        this.end = end;
    }
    Bracket.prototype.contains(value) {
        return this.begin <= value && value < this.end;
    }

    exports.Dag.bracket = function (vertex) {
        var bracket = new Bracket(vertex.location.j, vertex.location.j);
        do {
            var n = vertex.targets.length;
            vertex = vertex.targets[n-1];
        } while (n > 0);

        bracket.end = vertex.location.j + 1;
        return bracket;
    };

    function KeySet(key) {
        this.key = key;
        this.best = undefined;
        this.prunes = [];
    }

    exports.Dag.prototype.removeBranch = function (root) {
        var memberI = _.indexOf(this.vertices, root);
        var member = this.vertices[memberI];
        do {
            delete member.parent;
            delete member;
            memberI += 1;
            member = this.vertices[memberI];
        } while (member.location.i > root.location.i);

        // Remove empty slots from array.
        this.vertices = _.compact(this.vertices);
    }

    /**
     * @param {Bracket} domain
     * @param {Integer} delta
     */
    function Translation(domain, delta) {
        this.domain = domain;
        this.delta = delta;
    }

    /**
     * There must exist a vertex on every subinterval of the intersection of the
     * nonnegative orthant with the union of `empties`.
     * `begin` of brackets contained in `empties` must be monotonic
     * nondecreasing.
     *
     * @param {Bracket[]} empties
     */
    exports.Dag.prototype._densify = function (empties) {
        // Prepend a vacuous bracket at the very beginning to reduce algorithm
        // complexity later.  Additional cost:
        //   * this evaluation, and
        //   * translation of vertices by a delta of 0 for the first subinterval
        //     (worst case, there exists one interval, and a no-op becomes a
        //     translation for the entire graph).
        empties = [new Bracket(0,0)].concat(empties);

        // Compute the union of the empty subintervals.
        empties = _.foldl(
            empties,
            function (brackets, next) {
                if (brackets.length > 0) {
                    // Hypothesize overlap
                    var previous = brackets.pop();

                    if (previous.end > next.begin) {
                        next = new Bracket(previous.begin, next.end);
                    } else {
                        // Invalid hypothesis, so restore and augment.
                        brackets.push(previous);
                    }
                }

                brackets.push(next);

                return brackets;
            },
            []
        );

        // Build translation domains for each subinterval between the empty
        // subintervals.
        var translations = [];
        var sumGaps = 0;
        _.forEach(
            empties,
            function (bracket) {
                if (translations.length > 0) {
                    // Hypothesis failed--complete previous iterant.
                    var partial = translations[translations.length-1];
                    partial.domain.end = bracket.begin;
                }

                // Hypothesize that this is the last iterant.
                sumGaps += bracket.end - bracket.begin;
                translations.push(new Translation(
                    new Bracket(bracket.begin, Infinity),
                    -sumGaps
                ));
            },
            []
        );

        // Translate vertices with the constructed transforms.  Preconditions
        // guarantee that the translations apply in sequence.
        var translationI = 0;
        _.forEach(
            this.vertices,
            function (vertex) {
                var translation = translations[translationI];
                if (translation.domain.contains(vertex.location.j)) {
                    vertex.location.j += translation.delta;
                } else {
                    // Initial membership in a domain is guaranteed by the empty
                    // prepended `Bracket`, so we've left the current
                    // translation's domain.
                    active = false;
                    translationI += 1;
                }
            }
        );
    };

    /**
     * Alter graph topology to include the deepest `j` when there exists more
     * than one location.
     */
    exports.Dag.prototype.pruneShallows = function (key) {
        // Sort vertex data by key so that repeats are array-adjacent.
        var vertices = _.sortBy(
            this.vertices,
            function (vertex) { return key(vertex.data); }
        );

        var set = new KeySet();
        var brackets = [];
        _.forEach(
            vertices,
            function (vertex) {
                if (key(vertex) === set.key) {
                    if (exports.Dag.breadthFirstOrder(best, vertex)) {
                        // New best candidate.
                        set.prunes.push(set.best);
                        set.best = vertex;
                    } else {
                        // Same best candidate
                        set.prunes.push(vertex);
                    }
                } else {
                    _.forEach(
                        set.prunes,
                        function (prune) {
                            // Store evacuated bracket for grid repair.
                            var bracket = exports.Dag.bracket(prune);
                            if (prune.parent.targets[0] === prune) {
                                // First child of some parent, so the bracket's
                                // beginning is still occupied.
                                bracket.begin += 1;
                            }
                            brackets.push(bracket);

                            // Reroute parent of `prune` to `best`.
                            var pruneI = _.indexOf(prune.parent.targets, prune);
                            prune.parent.targets[pruneI] = best;

                            this.removeBranch(prune);
                        }
                    );
                    set = new KeySet(vertex);
                }
            }
        );

        if (brackets.length > 0) { this._densify(brackets); }
    };

        

    return exports;
});
