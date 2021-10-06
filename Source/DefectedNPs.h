#pragma once
extern class Group;

Group icosahedral(float lattice_constant, int noshells);

Group decahedron(int p, int q, int r, float lattice_constant);
//p: Number of atoms on the (100) facets perpendicular to the five fold axis
//q: Number of atoms on the (100) facets parallel to the five fold axis.q = 1 corresponds to no visible(100) facets.
//r: Depth of the Marks re-entrence at the pentagon corners. r = 0 corresponds to no re - entrence.

