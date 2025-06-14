#include "cs.h"
/* solve Lx=b where x and b are dense.  x=b on input, solution on output. */
int cs_lsolve (cs *L, double *x)
{
    int p, j, n, *Lp, *Li ;
    double *Lx ;
    if (!L || !x) return (0) ;				    /* check inputs */
    n = L->n ; Lp = L->p ; Li = L->i ; Lx = L->x ;
    for (j = 0 ; j < n ; j++)
    {
	x [j] /= Lx [Lp [j]] ;
	for (p = Lp [j]+1 ; p < Lp [j+1] ; p++)
	{
	    x [Li [p]] -= Lx [p] * x [j] ;
	}
    }
    return (1) ;
}
