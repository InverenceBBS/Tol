#include "cs.h"
/* drop entries for which fkeep(A(i,j)) is false; return nz if OK, else -1 */
int cs_fkeep (cs *A, int (*fkeep) (int, int, double, void *), void *other)
{
    int j, p, nz = 0, n, *Ap, *Ai ;
    double *Ax ;
    if (!A || !fkeep) return (-1) ;	    /* check inputs */
    n = A->n ; Ap = A->p ; Ai = A->i ; Ax = A->x ;
    for (j = 0 ; j < n ; j++)
    {
	p = Ap [j] ;			    /* get current location of col j */
	Ap [j] = nz ;			    /* record new location of col j */
	for ( ; p < Ap [j+1] ; p++)
	{
	    if (fkeep (Ai [p], j, Ax ? Ax [p] : 1, other))
	    {
		if (Ax) Ax [nz] = Ax [p] ;  /* keep A(i,j) */
		Ai [nz++] = Ai [p] ;
	    }
	}
    }
    return (Ap [n] = nz) ;		    /* finalize A and return nnz(A) */
}
