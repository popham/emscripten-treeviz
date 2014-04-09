Client Side Tree Layout by [Emscripten](https://github.com/kripken/emscripten)
==============================================================================
This project demonstrates how to leverage C++ assets to build an SVG tree visualization on a client's web browser.
The following assets are used:
* Data structures by [Boost Graph Library](http://www.boost.org/doc/libs/release/libs/graph/).
* Interval tree by [Boost ICL](http://www.boost.org/doc/libs/release/libs/icl/doc/html/index.html).
* Optimization algorithms by [DLib](http://dlib.net).
* Splines by [John Burkardt](http://people.sc.fsu.edu/~jburkardt/cpp_src/spline/spline.html).

The code provides a worker that does the following:
* Initializes a treeish directed acyclic graph data structure.
* Generates a canonical spatial representation of the data structure from a vertex ranking metric.
* Attaches springs within the spatial representation and imposes a central force to the system.
* Iterates the system toward equilibrium.

The worker provides AMD bindings to control the worker from its owner.
These bindings have been built with an eye toward generic RPC.

Extra credit:
* Edge targets with multiple parents degenerate the perfectly handled tree to a treeish thing.
  An edge could be routed efficiently by building a Voronoi diagram from the vertex spatial layout, and
  then constraining the edge's interior Bezier points to a shortest path in the Voronoi graph.
  [CGAL](http://doc.cgal.org) seems like the path of least resistence--check out [this repo](https://github.com/marcosscriven/cgaljs) for a jump start.
  Maybe there's a better way?

Rationale
---------
This code resulted from an abandoned attempt under pure Javascript, included in this repository for posterity (I sure don't want it cluttering my computer).
When I decided that I needed a segment tree, I tired of the one-off effort.
The central focus of this repository is bending [Emscripten](https://github.com/kripken/emscripten) to the problem.

The following hurdles affected the final solution (expected hurdles that were nonissues have been struck through):
* <del>Marshalling data in and out of the resulting javascript code (in an acceptably literate manner).</del>
  Workers provide a natural separation.
* Size of the glue code needed to bring together multiple codebases.
  Both BGL and Dlib are heavily templated, which I hope constitutes a virtue under Emscripten.
* <del>
  AMDifying the resulting code.
  I see no value in covering the whole gamut of Javascript imports, since I expect very little glue code required to get things rolling.
  I'm using AMD alone until a need for some other arises.
  </del>
  I've built a Promises interface to access the worker.
  While it's more code than I care for, a custom DSL could generate the C++ bindings and the AMD boilerplate as a build step--I'm thinking Python's [PLY](http://www.dabeaz.com/ply/ply.html).
