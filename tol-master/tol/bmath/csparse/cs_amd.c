#include "cs.h"
/* clear w */
static int cs_wclear (int mark, int lemax, int *w, int n)
{
    int k ;
    if (mark < 2 || (mark + lemax < 0))
    {
	for (k = 0 ; k < n ; k++) if (w [k] != 0) w [k] = 1 ;
	mark = 2 ;
    }
    return (mark) ;	/* at this point, w [0..n-1] < mark holds */
}

/* keep off-diagonal entries; drop diagonal entries */
static int cs_diag (int i, int j, double aij, void *other) { return (i != j) ; }

/* p = amd(A+A') if symmetric is true, or amd(A'A) otherwise */
int *cs_amd (cs *A, int order)	/* order -1:natural, 0:Cholesky, 1:LU, 2:QR */
{
    cs *C, *A2, *AT ;
    int *Cp, *Ci, *last, *ww, *len, *nv, *next, *P, *head, *elen, *degree, *w,
	*hhead, *ATp, *ATi, d, dk, dext, lemax = 0, e, elenk, eln, i, j, k, k1,
	k2, k3, jlast, ln, dense, nzmax, mindeg = 0, nvi, nvj, nvk, mark, wnvi,
	ok, cnz, nel = 0, p, p1, p2, p3, p4, pj, pk, pk1, pk2, pn, q, n, m ;
    unsigned int h ;
    if (!A || order < 0) return (NULL) ;    /* check inputs; quick return */
    AT = cs_transpose (A, 0) ;		    /* compute A' */
    if (!AT) return (NULL) ;
    m = A->m ; n = A->n ;
    dense = CS_MAX (16, 10 * sqrt ((double) n)) ;   /* find dense threshold */
    dense = CS_MIN (n-2, dense) ;
    if (order == 0 && n == m)
    {
	C = cs_add (A, AT, 0, 0) ;	    /* C = A+A' */
    }
    else if (order == 1)
    {
	ATp = AT->p ;			    /* drop dense columns from AT */
	ATi = AT->i ;
	for (p2 = 0, j = 0 ; j < m ; j++)
	{
	    p = ATp [j] ;		    /* column j of AT starts here */
	    ATp [j] = p2 ;		    /* new column j starts here */
	    if (ATp [j+1] - p > dense) continue ;   /* skip dense col j */
	    for ( ; p < ATp [j+1] ; p++) ATi [p2++] = ATi [p] ;
	}
	ATp [m] = p2 ;			    /* finalize AT */
	A2 = cs_transpose (AT, 0) ;	    /* A2 = AT' */
	C = A2 ? cs_multiply (AT, A2) : NULL ;	/* C=A'*A with no dense rows */
	cs_spfree (A2) ;
    }
    else
    {
	C = cs_multiply (AT, A) ;	    /* C=A'*A */
    }
    cs_spfree (AT) ;
    if (!C) return (NULL) ;
    P = cs_malloc (n+1, sizeof (int)) ;	    /* allocate result */
    ww = cs_malloc (8*(n+1), sizeof (int)) ;/* get workspace */
    len  = ww           ; nv     = ww +   (n+1) ; next   = ww + 2*(n+1) ;
    head = ww + 3*(n+1) ; elen   = ww + 4*(n+1) ; degree = ww + 5*(n+1) ;
    w    = ww + 6*(n+1) ; hhead  = ww + 7*(n+1) ;
    last = P ;				    /* use P as workspace for last */
    cs_fkeep (C, &cs_diag, NULL) ;	    /* drop diagonal entries */
    Cp = C->p ;
    cnz = Cp [n] ;
    if (!cs_sprealloc (C, cnz+cnz/5+2*n)) return (cs_idone (P, C, ww, 0)) ;
    for (k = 0 ; k < n ; k++) len [k] = Cp [k+1] - Cp [k] ;
    len [n] = 0 ;
    nzmax = C->nzmax ;
    Ci = C->i ;
    for (i = 0 ; i <= n ; i++)
    {
	head [i] = -1 ;			    /* degree list i is empty */
	last [i] = -1 ;
	next [i] = -1 ;
	hhead [i] = -1 ;		    /* hash list i is empty */
	nv [i] = 1 ;			    /* node i is just one node */
	w [i] = 1 ;			    /* node i is alive */
	elen [i] = 0 ;			    /* Ek of node i is empty */
	degree [i] = len [i] ;		    /* degree of node i */
    }
    mark = cs_wclear (0, 0, w, n) ;	    /* clear w */
    elen [n] = -2 ;			    /* n is a dead element */
    Cp [n] = -1 ;			    /* n is a root of assembly tree */
    w [n] = 0 ;				    /* n is a dead element */
    for (i = 0 ; i < n ; i++)		    /* initialize degree lists */
    {
	d = degree [i] ;
	if (d == 0)			    /* node i is empty */
	{
	    elen [i] = -2 ;		    /* element i is dead */
	    nel++ ;
	    Cp [i] = -1 ;		    /* i is a root of assemby tree */
	    w [i] = 0 ;
	}
	else if (d > dense)		    /* node i is dense */
	{
	    nv [i] = 0 ;		    /* absorb i into element n */
	    elen [i] = -1 ;		    /* node i is dead */
	    nel++ ;
	    Cp [i] = CS_FLIP (n) ;
	    nv [n]++ ;
	}
	else
	{
	    if (head [d] != -1) last [head [d]] = i ;
	    next [i] = head [d] ;	    /* put node i in degree list d */
	    head [d] = i ;
	}
    } 
    while (nel < n)			    /* while (selecting pivots) do */
    {
	for (k = -1 ; mindeg < n && (k = head [mindeg]) == -1 ; mindeg++) ;
	if (next [k] != -1) last [next [k]] = -1 ;
	head [mindeg] = next [k] ;	    /* remove k from degree list */
	elenk = elen [k] ;		    /* elenk = |Ek| */
	nvk = nv [k] ;			    /* # of nodes k represents */
	nel += nvk ;			    /* nv[k] nodes of A eliminated */
	if (elenk > 0 && cnz + mindeg >= nzmax)  /* garbage collection */
	{
	    for (j = 0 ; j < n ; j++)
	    {
		if ((p = Cp [j]) >= 0)	    /* j is a live node or element */
		{
		    Cp [j] = Ci [p] ;	    /* save first entry of object */
		    Ci [p] = CS_FLIP (j) ;  /* first entry is now CS_FLIP(j) */
		}
	    }
	    for (q = 0, p = 0 ; p < cnz ; ) /* scan all of memory */
	    {
		if ((j = CS_FLIP (Ci [p++])) >= 0)  /* found object j */
		{
		    Ci [q] = Cp [j] ;	    /* restore first entry of object */
		    Cp [j] = q++ ;	    /* new pointer to object j */
		    for (k3 = 0 ; k3 < len [j]-1 ; k3++) Ci [q++] = Ci [p++] ;
		}
	    }
	    cnz = q ;			    /* Ci [cnz...nzmax-1] now free */
	} 
	dk = 0 ;			    /* construct the new element */
	nv [k] = -nvk ;			    /* flag k as in Lk */
	p = Cp [k] ;
	pk1 = (elenk == 0) ? p : cnz ;	    /* do in place if elen[k] == 0 */
	pk2 = pk1 ;
	for (k1 = 1 ; k1 <= elenk + 1 ; k1++)
	{
	    if (k1 > elenk)
	    {
		e = k ;			    /* search the nodes in k */
		pj = p ;		    /* list of nodes starts at Ci[pj]*/
		ln = len [k] - elenk ;	    /* length of list of nodes in k */
	    }
	    else
	    {
		e = Ci [p++] ;		    /* search the nodes in e */
		pj = Cp [e] ;
		ln = len [e] ;		    /* length of list of nodes in e */
	    }
	    for (k2 = 1 ; k2 <= ln ; k2++)
	    {
		i = Ci [pj++] ;
		if ((nvi = nv [i]) <= 0) continue ; /* node i dead, or seen */
		dk += nvi ;		    /* degree[Lk] += size of node i */
		nv [i] = -nvi ;		    /* negate nv[i] to denote i in Lk*/
		Ci [pk2++] = i ;	    /* place i in Lk */
		if (next [i] != -1) last [next [i]] = last [i] ;
		if (last [i] != -1)	    /* remove i from degree list */
		{
		    next [last [i]] = next [i] ;
		}
		else
		{
		    head [degree [i]] = next [i] ;
		}
	    }
	    if (e != k)
	    {
		Cp [e] = CS_FLIP (k) ;	    /* absorb e into k */
		w [e] = 0 ;		    /* e is now a dead element */
	    }
	}
	if (elenk != 0) cnz = pk2 ;	    /* Ci [cnz...nzmax] is free */
	degree [k] = dk ;		    /* external degree of k - |Lk\i| */
	Cp [k] = pk1 ;			    /* element k is in Ci[pk1..pk2-1] */
	len [k] = pk2 - pk1 ;
	elen [k] = -2 ;			    /* k is now an element */
	mark = cs_wclear (mark, lemax, w, n) ;	/* clear w if necessary */
	for (pk = pk1 ; pk < pk2 ; pk++)    /* scan 1: find |Le\Lk| */
	{
	    i = Ci [pk] ;
	    if ((eln = elen [i]) <= 0) continue ;/* skip if elen[i] empty */
	    nvi = -nv [i] ;			 /* nv [i] was negated */
	    wnvi = mark - nvi ;
	    for (p = Cp [i] ; p <= Cp [i] + eln - 1 ; p++)  /* scan Ei */
	    {
		e = Ci [p] ;
		if (w [e] >= mark)
		{
		    w [e] -= nvi ;	    /* decrement |Le\Lk| */
		}
		else if (w [e] != 0)	    /* ensure e is a live element */
		{
		    w [e] = degree [e] + wnvi ;	/* 1st time e seen in scan 1 */
		}
	    }
	} 
	for (pk = pk1 ; pk < pk2 ; pk++)    /* scan2: degree update */
	{
	    i = Ci [pk] ;		    /* consider node i in Lk */
	    p1 = Cp [i] ;
	    p2 = p1 + elen [i] - 1 ;
	    pn = p1 ;
	    for (h = 0, d = 0, p = p1 ; p <= p2 ; p++)    /* scan Ei */
	    {
		e = Ci [p] ;
		if (w [e] != 0)		    /* e is an unabsorbed element */
		{
		    dext = w [e] - mark ;   /* dext = |Le\Lk| */
		    if (dext > 0)
		    {
			d += dext ;	    /* sum up the set differences */
			Ci [pn++] = e ;	    /* keep e in Ei */
			h += e ;	    /* compute the hash of node i */
		    }
		    else
		    {
			Cp [e] = CS_FLIP (k) ;	/* aggressive absorb. e->k */
			w [e] = 0 ;		/* e is a dead element */
		    }
		}
	    }
	    elen [i] = pn - p1 + 1 ;	    /* elen[i] = |Ei| */
	    p3 = pn ;
	    p4 = p1 + len [i] ;
	    for (p = p2 + 1 ; p < p4 ; p++) /* prune edges in Ai */
	    {
		j = Ci [p] ;
		if ((nvj = nv [j]) <= 0) continue ; /* node j dead or in Lk */
		d += nvj ;		    /* degree(i) += |j| */
		Ci [pn++] = j ;		    /* place j in node list of i */
		h += j ;		    /* compute hash for node i */
	    }
	    if (d == 0)			    /* check for mass elimination */
	    {
		Cp [i] = CS_FLIP (k) ;	    /* absorb i into k */
		nvi = -nv [i] ;
		dk -= nvi ;		    /* |Lk| -= |i| */
		nvk += nvi ;		    /* |k| += nv[i] */
		nel += nvi ;
		nv [i] = 0 ;
		elen [i] = -1 ;		    /* node i is dead */
	    }
	    else
	    {
		degree [i] = CS_MIN (degree [i], d) ;	/* update degree(i) */
		Ci [pn] = Ci [p3] ;	    /* move first node to end */
		Ci [p3] = Ci [p1] ;	    /* move 1st el. to end of Ei */
		Ci [p1] = k ;		    /* add k as 1st element in of Ei */
		len [i] = pn - p1 + 1 ;	    /* new len of adj. list of node i */
		h %= n ;		    /* finalize hash of i */
		next [i] = hhead [h] ;	    /* place i in hash bucket */
		hhead [h] = i ;
		last [i] = h ;		    /* save hash of i in last[i] */
	    }
	}				    /* scan2 is done */
	degree [k] = dk ;		    /* finalize |Lk| */
	lemax = CS_MAX (lemax, dk) ;
	mark = cs_wclear (mark+lemax, lemax, w, n) ;	/* clear w */
	for (pk = pk1 ; pk < pk2 ; pk++)    /* supernode detection */
	{
	    i = Ci [pk] ;
	    if (nv [i] >= 0) continue ;		/* skip if i is dead */
	    h = last [i] ;			/* scan hash bucket of node i */
	    i = hhead [h] ;
	    hhead [h] = -1 ;			/* hash bucket will be empty */
	    for ( ; i != -1 && next [i] != -1 ; i = next [i], mark++)
	    {
		ln = len [i] ;
		eln = elen [i] ;
		for (p = Cp[i]+1 ; p <= Cp[i]+ln-1 ; p++) w [Ci [p]] = mark ;
		jlast = i ;
		for (j = next [i] ; j != -1 ; )	/* compare i with all j */
		{
		    ok = (len [j] == ln) && (elen [j] == eln) ;
		    for (p = Cp [j] + 1 ; ok && p <= Cp [j] + ln - 1 ; p++)
		    {
			if (w [Ci [p]] != mark) ok = 0 ;    /* compare i and j*/
		    }
		    if (ok)			/* i and j are identical */
		    {
			Cp [j] = CS_FLIP (i) ;	/* absorb j into i */
			nv [i] += nv [j] ;
			nv [j] = 0 ;
			elen [j] = -1 ;		/* node j is dead */
			j = next [j] ;		/* delete j from hash bucket */
			next [jlast] = j ;
		    }
		    else
		    {
			jlast = j ;		/* j and i are different */
			j = next [j] ;
		    }
		}
	    }
	} 
	for (p = pk1, pk = pk1 ; pk < pk2 ; pk++)   /* finalize Lk */
	{
	    i = Ci [pk] ;
	    if ((nvi = -nv [i]) <= 0) continue ;/* skip if i is dead */
	    nv [i] = nvi ;			/* restore nv[i] */
	    d = degree [i] + dk - nvi ;		/* compute external degree(i) */
	    d = CS_MIN (d, n - nel - nvi) ;
	    if (head [d] != -1) last [head [d]] = i ;
	    next [i] = head [d] ;		/* put i back in degree list */
	    last [i] = -1 ;
	    head [d] = i ;
	    mindeg = CS_MIN (mindeg, d) ;	/* find new minimum degree */
	    degree [i] = d ;
	    Ci [p++] = i ;			/* place i in Lk */
	}
	nv [k] = nvk ;			    /* # nodes absorbed into k */
	if ((len [k] = p - pk1) == 0)	    /* length of adj. list of k */
	{
	    Cp [k] = -1 ;		    /* k is a root of the tree */
	    w [k] = 0 ;			    /* k is now a dead element */
	}
	if (elenk != 0) cnz = p ;	    /* free unused space in Lk */
    } 
    for (i = 0 ; i < n ; i++) Cp [i] = CS_FLIP (Cp [i]) ;/* fix assembly tree */
    for (j = 0 ; j <= n ; j++) head [j] = -1 ;
    for (j = n ; j >= 0 ; j--)		    /* place unordered nodes in lists */
    {
	if (nv [j] > 0) continue ;	    /* skip if j is an element */
	next [j] = head [Cp [j]] ;	    /* place j in list of its parent */
	head [Cp [j]] = j ;
    }
    for (e = n ; e >= 0 ; e--)		    /* place elements in lists */
    {
	if (nv [e] <= 0) continue ;	    /* skip unless e is an element */
	if (Cp [e] != -1)
	{
	    next [e] = head [Cp [e]] ;	    /* place e in list of its parent */
	    head [Cp [e]] = e ;
	}
    }
    for (k = 0, i = 0 ; i <= n ; i++)	    /* postorder the assembly tree */
    {
	if (Cp [i] == -1) k = cs_tdfs (i, k, head, next, P, w) ;
    }
    return (cs_idone (P, C, ww, 1)) ;
}
