#include "cs.h"
/* C = A' */
cs *cs_transpose (cs *A, int values)
{
    int p, q, j, *Cp, *Ci, n, m, *Ap, *Ai, *w ;
    double *Cx, *Ax ;
    cs *C ;
    if (!A) return (NULL) ;
    m = A->m ; n = A->n ; Ap = A->p ; Ai = A->i ; Ax = A->x ;
    C = cs_spalloc (n, m, Ap [n], values && Ax, 0) ;	   /* allocate result */
    w = cs_calloc (m, sizeof (int)) ;
    if (!C || !w) return (cs_done (C, w, NULL, 0)) ;	   /* out of memory */
    Cp = C->p ; Ci = C->i ; Cx = C->x ;
    for (p = 0 ; p < Ap [n] ; p++) w [Ai [p]]++ ;	   /* row counts */
    cs_cumsum (Cp, w, m) ;				   /* row pointers */
    for (j = 0 ; j < n ; j++)
    {
	for (p = Ap [j] ; p < Ap [j+1] ; p++)
	{
	    Ci [q = w [Ai [p]]++] = j ;	/* place A(i,j) as entry C(j,i) */
	    if (Cx) Cx [q] = Ax [p] ;
	}
    }
    return (cs_done (C, w, NULL, 1)) ;	/* success; free w and return C */
}
