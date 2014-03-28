Client Side Tree Layout by [Emscripten](https://github.com/kripken/emscripten)
==============================================================================
This project demonstrates how to leverage C++ assets to build an SVG tree visualization on a client's web browser.
The following assets are used:
* Data structures by [Boost Graph Library](http://www.boost.org/doc/libs/release/libs/graph/).
* Optimization algorithms by [DLib](http://dlib.net).
* Splines by [John Burkardt](http://people.sc.fsu.edu/~jburkardt/cpp_src/spline/spline.html).

The code does the following:
* Initialize a treeish directed acyclic graph data structure.
* Generate a canonical spatial representation of the data structure from a vertex ranking metric.
* Attach springs within the spatial representation and impose a central force to the system.
* Iterate the system toward equilibrium a few times.

Extra credit:
* Edge targets with multiple parents degenerate the perfectly handled tree to a treeish thing.
  An edge could be routed efficiently by building a Voronoi graph from the vertex spatial layout, and
  then constraining the edge's interior Bezier points to a shortest path in the Voronoi graph.
  [CGAL](http://doc.cgal.org) seems like the path of least resistence--check out [this repo](https://github.com/marcosscriven/cgaljs) for a jump start.
  Maybe there's a better way?
* [Mori](https://github.com/swannodette/mori) provides immutable data structures for Javascript.
  How difficult would it be to get BGL or DLib to use these data structure?
  How does Mori benchmark against BGL's best practice?
  How does DLib benchmark against DLib's best practice?

Rationale
---------
This code resulted from an abandoned attempt under pure Javascript, included in this repository for posterity (I sure don't want it cluttering my computer).
When I decided that I needed a segment tree, I tired of the one-off effort.
The central focus of this repository is bending [Emscripten](https://github.com/kripken/emscripten) to the problem.

I anticipated the following hurdles from the get-go:
* Marshalling data in and out of the resulting javascript code (in an acceptably literate manner).
* Size of the glue code needed to bring together multiple codebases.
  Both BGL and Dlib heavily templated, which I hope constitutes a virtue under Emscripten.
* AMDifying the resulting code.
  I see no value in covering the whole gamut of Javascript imports, since I expect very little glue code required to get things rolling.
  I'm using AMD alone until a need for some other arises.

Elaboration on these hurdles and additional problems will be documented as encountered.

Marshalling Data Between Languages
----------------------------------
There's a bunch of example invocations found in some [QCon talk](http://kripken.github.io/mloc_emscripten_talk/qcon.html).
I'm targeting an AMD module that exposes:
* A constructor method that takes graph topology to a coarse visualization.
* An iteration interface that maps the coarse visualization toward a better visualization.
* Rendering alternatives (the non-used alternative should get optimized out of existence):
  * React SVG.
  * Handlebars SVG.

Speaking of optimization out of existence....
I don't want to be specifying that some construct within a C++ file gets exported to have it included in the module.
Any export from a C++ file should be rebound in a Javascript file (my AMD exports are very semantic).
