[Boost Graph Library](http://www.boost.org/doc/libs/release/libs/graph/) and [DLib Optimization](http://dlib.net/optimization.html) for Client-Side Tree Layout
===============================================================================================================================================================

This repository demonstrates how to leverage c++ assets to build an SVG tree visualization on a client's web browser.
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


But Boost Dlib are c++ libraries
--------------------------------

This code resulted from an abandoned attempt under pure Javascript, included in this repository for posterity (I sure don't want it cluttering my computer).
When I decided that I needed a segment tree, I tired of the one-off effort.
The central focus of this repository is bending [Emscripten](https://github.com/kripken/emscripten) to the problem.

I anticipated the following hurdles from the get-go:
* Marshalling data in and out of the resulting javascript code (in an acceptably literate manner).
* Size of the glue code needed to bring together multiple codebases.
  Both BGL and Dlib heavily templated, which I hope constitutes a virtue under Emscripten.
* AMDifying the resulting code.
  I see no value in covering the whole gamut of Javascript includes, since I expect very little glue code required to get things rolling.

Elaboration on these hurdles and additional problems will be documented as encountered.
