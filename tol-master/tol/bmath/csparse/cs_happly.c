#include "cs.h"
/* apply the ith Householder vector to x */
int cs_happly (cs *V, int i, double beta, double *x)
{
    int p, *Vp, *Vi ;
    double *Vx, tau = 0 ;
    if (!V || !x) return (0) ;		    /* check inputs */
    Vp = V->p ; Vi = V->i ; Vx = V->x ;
    for (p = Vp [i] ; p < Vp [i+1] ; p++)   /* tau = v'*x */
    {
	tau += Vx [p] * x [Vi [p]] ;
    }
    tau *= beta ;			    /* tau = beta*(v'*x) */
    for (p = Vp [i] ; p < Vp [i+1] ; p++)   /* x = x - v*tau */
    {
	x [Vi [p]] -= Vx [p] * tau ;
    }
    return (1) ;
}
