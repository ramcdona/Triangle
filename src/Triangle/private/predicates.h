#ifndef PREDICATES_H
#define PREDICATES_H

#include "../triangle.h"

void tri_exactinit();

REAL tri_counterclockwise( mesh *m, behavior *b,
                           vertex pa, vertex pb, vertex pc);

REAL tri_incircle( mesh *m, behavior *b,
                   vertex pa, vertex pb, vertex pc, vertex pd);

REAL tri_nonregular( mesh *m, behavior *b,
                     vertex pa, vertex pb, vertex pc, vertex pd);

void tri_findcircumcenter( mesh *m, behavior *b,
                           vertex torg, vertex tdest, vertex tapex,
                           vertex circumcenter, REAL *xi, REAL *eta, int offcenter);

/********* Private methods *********/

int tri_fast_expansion_sum_zeroelim( int elen, REAL *e, int flen, REAL *f, REAL *h);

int tri_scale_expansion_zeroelim( int elen, REAL *e, REAL b, REAL *h);

REAL tri_estimate( int elen, REAL *e);

REAL tri_counterclockwiseadapt( vertex pa, vertex pb, vertex pc, REAL detsum);

REAL tri_incircleadapt( vertex pa, vertex pb, vertex pc, vertex pd, REAL permanent);

REAL tri_orient3dadapt( vertex pa, vertex pb, vertex pc, vertex pd,
                        REAL aheight, REAL bheight, REAL cheight, REAL dheight,
                        REAL permanent);

REAL tri_orient3d( mesh *m, behavior *b,
                   vertex pa, vertex pb, vertex pc, vertex pd,
                   REAL aheight, REAL bheight, REAL cheight, REAL dheight);


#endif /* PREDICATES_H */
