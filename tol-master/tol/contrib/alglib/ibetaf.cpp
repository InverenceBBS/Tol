/*************************************************************************
Cephes Math Library Release 2.8:  June, 2000
Copyright by Stephen L. Moshier

Contributors:
    * Sergey Bochkanov (ALGLIB project). Translation from C to
      pseudocode.

See subroutines comments for additional copyrights.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are
met:

- Redistributions of source code must retain the above copyright
  notice, this list of conditions and the following disclaimer.

- Redistributions in binary form must reproduce the above copyright
  notice, this list of conditions and the following disclaimer listed
  in this license in the documentation and/or other materials
  provided with the distribution.

- Neither the name of the copyright holders nor the names of its
  contributors may be used to endorse or promote products derived from
  this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*************************************************************************/

#include <stdafx.h>
#include "ibetaf.h"

double incompletebetafe(double a,
     double b,
     double x,
     double big,
     double biginv);
double incompletebetafe2(double a,
     double b,
     double x,
     double big,
     double biginv);
double incompletebetaps(double a, double b, double x, double maxgam);

/*************************************************************************
Incomplete beta integral

Returns incomplete beta integral of the arguments, evaluated
from zero to x.  The function is defined as

                 x
    -            -
   | (a+b)      | |  a-1     b-1
 -----------    |   t   (1-t)   dt.
  -     -     | |
 | (a) | (b)   -
                0

The domain of definition is 0 <= x <= 1.  In this
implementation a and b are restricted to positive values.
The integral from x to 1 may be obtained by the symmetry
relation

   1 - incbet( a, b, x )  =  incbet( b, a, 1-x ).

The integral is evaluated by a continued fraction expansion
or, when b*x is small, by a power series.

ACCURACY:

Tested at uniformly distributed random points (a,b,x) with a and b
in "domain" and x between 0 and 1.
                                       Relative error
arithmetic   domain     # trials      peak         rms
   IEEE      0,5         10000       6.9e-15     4.5e-16
   IEEE      0,85       250000       2.2e-13     1.7e-14
   IEEE      0,1000      30000       5.3e-12     6.3e-13
   IEEE      0,10000    250000       9.3e-11     7.1e-12
   IEEE      0,100000    10000       8.7e-10     4.8e-11
Outputs smaller than the IEEE gradual underflow threshold
were excluded from these statistics.

Cephes Math Library, Release 2.8:  June, 2000
Copyright 1984, 1995, 2000 by Stephen L. Moshier
*************************************************************************/
double incompletebeta(double a, double b, double x)
{
    double result;
    double t;
    double xc;
    double w;
    double y;
    int flag;
    double sg;
    double big;
    double biginv;
    double maxgam;
    double minlog;
    double maxlog;

    big = 4.503599627370496e15;
    biginv = 2.22044604925031308085e-16;
    maxgam = 171.624376956302725;
    minlog = log(ap::minrealnumber);
    maxlog = log(ap::maxrealnumber);
    ap::ap_error::make_assertion(a>0&&b>0);
    ap::ap_error::make_assertion(x>=0&&x<=1);
    if( x==0 )
    {
        result = 0;
        return result;
    }
    if( x==1 )
    {
        result = 1;
        return result;
    }
    flag = 0;
    if( b*x<=1.0&&x<=0.95 )
    {
        result = incompletebetaps(a, b, x, maxgam);
        return result;
    }
    w = 1.0-x;
    if( x>a/(a+b) )
    {
        flag = 1;
        t = a;
        a = b;
        b = t;
        xc = x;
        x = w;
    }
    else
    {
        xc = w;
    }
    if( flag==1&&b*x<=1.0&&x<=0.95 )
    {
        t = incompletebetaps(a, b, x, maxgam);
        if( t<=ap::machineepsilon )
        {
            result = 1.0-ap::machineepsilon;
        }
        else
        {
            result = 1.0-t;
        }
        return result;
    }
    y = x*(a+b-2.0)-(a-1.0);
    if( y<0.0 )
    {
        w = incompletebetafe(a, b, x, big, biginv);
    }
    else
    {
        w = incompletebetafe2(a, b, x, big, biginv)/xc;
    }
    y = a*log(x);
    t = b*log(xc);
    if( a+b<maxgam&&fabs(y)<maxlog&&fabs(t)<maxlog )
    {
        t = pow(xc, b);
        t = t*pow(x, a);
        t = t/a;
        t = t*w;
        t = t*(gamma(a+b)/(gamma(a)*gamma(b)));
        if( flag==1 )
        {
            if( t<=ap::machineepsilon )
            {
                result = 1.0-ap::machineepsilon;
            }
            else
            {
                result = 1.0-t;
            }
        }
        else
        {
            result = t;
        }
        return result;
    }
    y = y+t+lngamma(a+b, sg)-lngamma(a, sg)-lngamma(b, sg);
    y = y+log(w/a);
    if( y<minlog )
    {
        t = 0.0;
    }
    else
    {
        t = exp(y);
    }
    if( flag==1 )
    {
        if( t<=ap::machineepsilon )
        {
            t = 1.0-ap::machineepsilon;
        }
        else
        {
            t = 1.0-t;
        }
    }
    result = t;
    return result;
}


/*************************************************************************
Inverse of imcomplete beta integral

Given y, the function finds x such that

 incbet( a, b, x ) = y .

The routine performs interval halving or Newton iterations to find the
root of incbet(a,b,x) - y = 0.


ACCURACY:

                     Relative error:
               x     a,b
arithmetic   domain  domain  # trials    peak       rms
   IEEE      0,1    .5,10000   50000    5.8e-12   1.3e-13
   IEEE      0,1   .25,100    100000    1.8e-13   3.9e-15
   IEEE      0,1     0,5       50000    1.1e-12   5.5e-15
With a and b constrained to half-integer or integer values:
   IEEE      0,1    .5,10000   50000    5.8e-12   1.1e-13
   IEEE      0,1    .5,100    100000    1.7e-14   7.9e-16
With a = .5, b constrained to half-integer or integer values:
   IEEE      0,1    .5,10000   10000    8.3e-11   1.0e-11

Cephes Math Library Release 2.8:  June, 2000
Copyright 1984, 1996, 2000 by Stephen L. Moshier
*************************************************************************/
double invincompletebeta(double a, double b, double y)
{
    double result;
    double aaa;
    double bbb;
    double y0;
    double d;
    double yyy;
    double x;
    double x0;
    double x1;
    double lgm;
    double yp;
    double di;
    double dithresh;
    double yl;
    double yh;
    double xt;
    int i;
    int rflg;
    int dir;
    int nflg;
    double s;
    int mainlooppos;
    int ihalve;
    int ihalvecycle;
    int newt;
    int newtcycle;
    int breaknewtcycle;
    int breakihalvecycle;

    i = 0;
    ap::ap_error::make_assertion(y>=0&&y<=1);
    if( y==0 )
    {
        result = 0;
        return result;
    }
    if( y==1.0 )
    {
        result = 1;
        return result;
    }
    x0 = 0.0;
    yl = 0.0;
    x1 = 1.0;
    yh = 1.0;
    nflg = 0;
    mainlooppos = 0;
    ihalve = 1;
    ihalvecycle = 2;
    newt = 3;
    newtcycle = 4;
    breaknewtcycle = 5;
    breakihalvecycle = 6;
    while(true)
    {
        
        //
        // start
        //
        if( mainlooppos==0 )
        {
            if( a<=1.0||b<=1.0 )
            {
                dithresh = 1.0e-6;
                rflg = 0;
                aaa = a;
                bbb = b;
                y0 = y;
                x = aaa/(aaa+bbb);
                yyy = incompletebeta(aaa, bbb, x);
                mainlooppos = ihalve;
                continue;
            }
            else
            {
                dithresh = 1.0e-4;
            }
            yp = -invnormaldistribution(y);
            if( y>0.5 )
            {
                rflg = 1;
                aaa = b;
                bbb = a;
                y0 = 1.0-y;
                yp = -yp;
            }
            else
            {
                rflg = 0;
                aaa = a;
                bbb = b;
                y0 = y;
            }
            lgm = (yp*yp-3.0)/6.0;
            x = 2.0/(1.0/(2.0*aaa-1.0)+1.0/(2.0*bbb-1.0));
            d = yp*sqrt(x+lgm)/x-(1.0/(2.0*bbb-1.0)-1.0/(2.0*aaa-1.0))*(lgm+5.0/6.0-2.0/(3.0*x));
            d = 2.0*d;
            if( d<log(ap::minrealnumber) )
            {
                x = 0;
                break;
            }
            x = aaa/(aaa+bbb*exp(d));
            yyy = incompletebeta(aaa, bbb, x);
            yp = (yyy-y0)/y0;
            if( fabs(yp)<0.2 )
            {
                mainlooppos = newt;
                continue;
            }
            mainlooppos = ihalve;
            continue;
        }
        
        //
        // ihalve
        //
        if( mainlooppos==ihalve )
        {
            dir = 0;
            di = 0.5;
            i = 0;
            mainlooppos = ihalvecycle;
            continue;
        }
        
        //
        // ihalvecycle
        //
        if( mainlooppos==ihalvecycle )
        {
            if( i<=99 )
            {
                if( i!=0 )
                {
                    x = x0+di*(x1-x0);
                    if( x==1.0 )
                    {
                        x = 1.0-ap::machineepsilon;
                    }
                    if( x==0.0 )
                    {
                        di = 0.5;
                        x = x0+di*(x1-x0);
                        if( x==0.0 )
                        {
                            break;
                        }
                    }
                    yyy = incompletebeta(aaa, bbb, x);
                    yp = (x1-x0)/(x1+x0);
                    if( fabs(yp)<dithresh )
                    {
                        mainlooppos = newt;
                        continue;
                    }
                    yp = (yyy-y0)/y0;
                    if( fabs(yp)<dithresh )
                    {
                        mainlooppos = newt;
                        continue;
                    }
                }
                if( yyy<y0 )
                {
                    x0 = x;
                    yl = yyy;
                    if( dir<0 )
                    {
                        dir = 0;
                        di = 0.5;
                    }
                    else
                    {
                        if( dir>3 )
                        {
                            di = 1.0-(1.0-di)*(1.0-di);
                        }
                        else
                        {
                            if( dir>1 )
                            {
                                di = 0.5*di+0.5;
                            }
                            else
                            {
                                di = (y0-yyy)/(yh-yl);
                            }
                        }
                    }
                    dir = dir+1;
                    if( x0>0.75 )
                    {
                        if( rflg==1 )
                        {
                            rflg = 0;
                            aaa = a;
                            bbb = b;
                            y0 = y;
                        }
                        else
                        {
                            rflg = 1;
                            aaa = b;
                            bbb = a;
                            y0 = 1.0-y;
                        }
                        x = 1.0-x;
                        yyy = incompletebeta(aaa, bbb, x);
                        x0 = 0.0;
                        yl = 0.0;
                        x1 = 1.0;
                        yh = 1.0;
                        mainlooppos = ihalve;
                        continue;
                    }
                }
                else
                {
                    x1 = x;
                    if( rflg==1&&x1<ap::machineepsilon )
                    {
                        x = 0.0;
                        break;
                    }
                    yh = yyy;
                    if( dir>0 )
                    {
                        dir = 0;
                        di = 0.5;
                    }
                    else
                    {
                        if( dir<-3 )
                        {
                            di = di*di;
                        }
                        else
                        {
                            if( dir<-1 )
                            {
                                di = 0.5*di;
                            }
                            else
                            {
                                di = (yyy-y0)/(yh-yl);
                            }
                        }
                    }
                    dir = dir-1;
                }
                i = i+1;
                mainlooppos = ihalvecycle;
                continue;
            }
            else
            {
                mainlooppos = breakihalvecycle;
                continue;
            }
        }
        
        //
        // breakihalvecycle
        //
        if( mainlooppos==breakihalvecycle )
        {
            if( x0>=1.0 )
            {
                x = 1.0-ap::machineepsilon;
                break;
            }
            if( x<=0.0 )
            {
                x = 0.0;
                break;
            }
            mainlooppos = newt;
            continue;
        }
        
        //
        // newt
        //
        if( mainlooppos==newt )
        {
            if( nflg!=0 )
            {
                break;
            }
            nflg = 1;
            lgm = lngamma(aaa+bbb, s)-lngamma(aaa, s)-lngamma(bbb, s);
            i = 0;
            mainlooppos = newtcycle;
            continue;
        }
        
        //
        // newtcycle
        //
        if( mainlooppos==newtcycle )
        {
            if( i<=7 )
            {
                if( i!=0 )
                {
                    yyy = incompletebeta(aaa, bbb, x);
                }
                if( yyy<yl )
                {
                    x = x0;
                    yyy = yl;
                }
                else
                {
                    if( yyy>yh )
                    {
                        x = x1;
                        yyy = yh;
                    }
                    else
                    {
                        if( yyy<y0 )
                        {
                            x0 = x;
                            yl = yyy;
                        }
                        else
                        {
                            x1 = x;
                            yh = yyy;
                        }
                    }
                }
                if( x==1.0||x==0.0 )
                {
                    mainlooppos = breaknewtcycle;
                    continue;
                }
                d = (aaa-1.0)*log(x)+(bbb-1.0)*log(1.0-x)+lgm;
                if( d<log(ap::minrealnumber) )
                {
                    break;
                }
                if( d>log(ap::maxrealnumber) )
                {
                    mainlooppos = breaknewtcycle;
                    continue;
                }
                d = exp(d);
                d = (yyy-y0)/d;
                xt = x-d;
                if( xt<=x0 )
                {
                    yyy = (x-x0)/(x1-x0);
                    xt = x0+0.5*yyy*(x-x0);
                    if( xt<=0.0 )
                    {
                        mainlooppos = breaknewtcycle;
                        continue;
                    }
                }
                if( xt>=x1 )
                {
                    yyy = (x1-x)/(x1-x0);
                    xt = x1-0.5*yyy*(x1-x);
                    if( xt>=1.0 )
                    {
                        mainlooppos = breaknewtcycle;
                        continue;
                    }
                }
                x = xt;
                if( fabs(d/x)<128.0*ap::machineepsilon )
                {
                    break;
                }
                i = i+1;
                mainlooppos = newtcycle;
                continue;
            }
            else
            {
                mainlooppos = breaknewtcycle;
                continue;
            }
        }
        
        //
        // breaknewtcycle
        //
        if( mainlooppos==breaknewtcycle )
        {
            dithresh = 256.0*ap::machineepsilon;
            mainlooppos = ihalve;
            continue;
        }
    }
    
    //
    // done
    //
    if( rflg!=0 )
    {
        if( x<=ap::machineepsilon )
        {
            x = 1.0-ap::machineepsilon;
        }
        else
        {
            x = 1.0-x;
        }
    }
    result = x;
    return result;
}


/*************************************************************************
Continued fraction expansion #1 for incomplete beta integral

Cephes Math Library, Release 2.8:  June, 2000
Copyright 1984, 1995, 2000 by Stephen L. Moshier
*************************************************************************/
double incompletebetafe(double a,
     double b,
     double x,
     double big,
     double biginv)
{
    double result;
    double xk;
    double pk;
    double pkm1;
    double pkm2;
    double qk;
    double qkm1;
    double qkm2;
    double k1;
    double k2;
    double k3;
    double k4;
    double k5;
    double k6;
    double k7;
    double k8;
    double r;
    double t;
    double ans;
    double thresh;
    int n;

    k1 = a;
    k2 = a+b;
    k3 = a;
    k4 = a+1.0;
    k5 = 1.0;
    k6 = b-1.0;
    k7 = k4;
    k8 = a+2.0;
    pkm2 = 0.0;
    qkm2 = 1.0;
    pkm1 = 1.0;
    qkm1 = 1.0;
    ans = 1.0;
    r = 1.0;
    n = 0;
    thresh = 3.0*ap::machineepsilon;
    do
    {
        xk = -x*k1*k2/(k3*k4);
        pk = pkm1+pkm2*xk;
        qk = qkm1+qkm2*xk;
        pkm2 = pkm1;
        pkm1 = pk;
        qkm2 = qkm1;
        qkm1 = qk;
        xk = x*k5*k6/(k7*k8);
        pk = pkm1+pkm2*xk;
        qk = qkm1+qkm2*xk;
        pkm2 = pkm1;
        pkm1 = pk;
        qkm2 = qkm1;
        qkm1 = qk;
        if( qk!=0 )
        {
            r = pk/qk;
        }
        if( r!=0 )
        {
            t = fabs((ans-r)/r);
            ans = r;
        }
        else
        {
            t = 1.0;
        }
        if( t<thresh )
        {
            break;
        }
        k1 = k1+1.0;
        k2 = k2+1.0;
        k3 = k3+2.0;
        k4 = k4+2.0;
        k5 = k5+1.0;
        k6 = k6-1.0;
        k7 = k7+2.0;
        k8 = k8+2.0;
        if( fabs(qk)+fabs(pk)>big )
        {
            pkm2 = pkm2*biginv;
            pkm1 = pkm1*biginv;
            qkm2 = qkm2*biginv;
            qkm1 = qkm1*biginv;
        }
        if( fabs(qk)<biginv||fabs(pk)<biginv )
        {
            pkm2 = pkm2*big;
            pkm1 = pkm1*big;
            qkm2 = qkm2*big;
            qkm1 = qkm1*big;
        }
        n = n+1;
    }
    while(n!=300);
    result = ans;
    return result;
}


/*************************************************************************
Continued fraction expansion #2
for incomplete beta integral

Cephes Math Library, Release 2.8:  June, 2000
Copyright 1984, 1995, 2000 by Stephen L. Moshier
*************************************************************************/
double incompletebetafe2(double a,
     double b,
     double x,
     double big,
     double biginv)
{
    double result;
    double xk;
    double pk;
    double pkm1;
    double pkm2;
    double qk;
    double qkm1;
    double qkm2;
    double k1;
    double k2;
    double k3;
    double k4;
    double k5;
    double k6;
    double k7;
    double k8;
    double r;
    double t;
    double ans;
    double z;
    double thresh;
    int n;

    k1 = a;
    k2 = b-1.0;
    k3 = a;
    k4 = a+1.0;
    k5 = 1.0;
    k6 = a+b;
    k7 = a+1.0;
    k8 = a+2.0;
    pkm2 = 0.0;
    qkm2 = 1.0;
    pkm1 = 1.0;
    qkm1 = 1.0;
    z = x/(1.0-x);
    ans = 1.0;
    r = 1.0;
    n = 0;
    thresh = 3.0*ap::machineepsilon;
    do
    {
        xk = -z*k1*k2/(k3*k4);
        pk = pkm1+pkm2*xk;
        qk = qkm1+qkm2*xk;
        pkm2 = pkm1;
        pkm1 = pk;
        qkm2 = qkm1;
        qkm1 = qk;
        xk = z*k5*k6/(k7*k8);
        pk = pkm1+pkm2*xk;
        qk = qkm1+qkm2*xk;
        pkm2 = pkm1;
        pkm1 = pk;
        qkm2 = qkm1;
        qkm1 = qk;
        if( qk!=0 )
        {
            r = pk/qk;
        }
        if( r!=0 )
        {
            t = fabs((ans-r)/r);
            ans = r;
        }
        else
        {
            t = 1.0;
        }
        if( t<thresh )
        {
            break;
        }
        k1 = k1+1.0;
        k2 = k2-1.0;
        k3 = k3+2.0;
        k4 = k4+2.0;
        k5 = k5+1.0;
        k6 = k6+1.0;
        k7 = k7+2.0;
        k8 = k8+2.0;
        if( fabs(qk)+fabs(pk)>big )
        {
            pkm2 = pkm2*biginv;
            pkm1 = pkm1*biginv;
            qkm2 = qkm2*biginv;
            qkm1 = qkm1*biginv;
        }
        if( fabs(qk)<biginv||fabs(pk)<biginv )
        {
            pkm2 = pkm2*big;
            pkm1 = pkm1*big;
            qkm2 = qkm2*big;
            qkm1 = qkm1*big;
        }
        n = n+1;
    }
    while(n!=300);
    result = ans;
    return result;
}


/*************************************************************************
Power series for incomplete beta integral.
Use when b*x is small and x not too close to 1.

Cephes Math Library, Release 2.8:  June, 2000
Copyright 1984, 1995, 2000 by Stephen L. Moshier
*************************************************************************/
double incompletebetaps(double a, double b, double x, double maxgam)
{
    double result;
    double s;
    double t;
    double u;
    double v;
    double n;
    double t1;
    double z;
    double ai;
    double sg;

    ai = 1.0/a;
    u = (1.0-b)*x;
    v = u/(a+1.0);
    t1 = v;
    t = u;
    n = 2.0;
    s = 0.0;
    z = ap::machineepsilon*ai;
    while(fabs(v)>z)
    {
        u = (n-b)*x/n;
        t = t*u;
        v = t/(a+n);
        s = s+v;
        n = n+1.0;
    }
    s = s+t1;
    s = s+ai;
    u = a*log(x);
    if( a+b<maxgam&&fabs(u)<log(ap::maxrealnumber) )
    {
        t = gamma(a+b)/(gamma(a)*gamma(b));
        s = s*t*pow(x, a);
    }
    else
    {
        t = lngamma(a+b, sg)-lngamma(a, sg)-lngamma(b, sg)+u+log(s);
        if( t<log(ap::minrealnumber) )
        {
            s = 0.0;
        }
        else
        {
            s = exp(t);
        }
    }
    result = s;
    return result;
}



