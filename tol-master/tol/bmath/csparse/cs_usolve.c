#include "cs.h"
/* solve Ux=b where x and b are dense.  x=b on input, solution on output. */
int cs_usolve (cs *U, double *x)
{
    int p, j, n, *Up, *Ui ;
    double *Ux ;
    if (!U || !x) return (0) ;				    /* check inputs */
    n = U->n ; Up = U->p ; Ui = U->i ; Ux = U->x ;
    for (j = n-1 ; j >= 0 ; j--)
    {
	x [j] /= Ux [Up [j+1]-1] ;
	for (p = Up [j] ; p < Up [j+1]-1 ; p++)
	{
	    x [Ui [p]] -= Ux [p] * x [j] ;
	}
    }
    return (1) ;
}
