/* vmat_convert.cpp: BVMat conversion methods
               GNU/TOL Language.

   Copyright (C) 2003-2005, Bayes Decision, SL (Spain [EU])

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307,
   USA.
 */

#if defined(_MSC_VER)
#include <win_tolinc.h>
#endif

#include <tol/tol_bvmat_impl.h>
#include <tol/tol_bsetgra.h>
#include <tol/tol_bdatgra.h>
#include <tol/tol_bpolyn.h>


  
////////////////////////////////////////////////////////////////////////////////
//Matrix conversions
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
  void BVMat::cRs_ensure_packed(cholmod_sparse_struct* sp)
////////////////////////////////////////////////////////////////////////////////
{
  if(!sp->sorted || !sp->packed) 
  {
    CholmodSort(sp,common_);
  }
};

////////////////////////////////////////////////////////////////////////////////
int BVMat::bRd2cRt(BVMat& left, const BVMat& right)
////////////////////////////////////////////////////////////////////////////////
{
  BVMat aux; 
  int result = bRd2cRs(aux, right);
  if(result==0)
  {
    result = cRs2cRt(left, aux);
  }
  return(result);
};

////////////////////////////////////////////////////////////////////////////////
int BVMat::cRt2bRd(BVMat& left, const BVMat& right)
////////////////////////////////////////////////////////////////////////////////
{
  BVMat aux; 
  int result = cRt2cRs(aux, right);
  if(result==0)
  {
    result = cRs2bRd(left, aux);
  }
  return(result);
};

////////////////////////////////////////////////////////////////////////////////
int BVMat::bRd2cRs(BVMat& left, const BVMat& right)
////////////////////////////////////////////////////////////////////////////////
{
  left.code_ = ESC_chlmRsparse;
  left.s_.chlmRsparse_ = 
    CholmodDenseToSparse(right.s_.blasRdense_, 1, common_);
  if(!left.s_.undefined_) { left.code_ = ESC_undefined; }
  else { cRs_ensure_packed(left.s_.chlmRsparse_); }
  return(0);
};

////////////////////////////////////////////////////////////////////////////////
cholmod_sparse* BVMat::cRf2cRs(cholmod_factor* factor)
////////////////////////////////////////////////////////////////////////////////
{
//WARNING: Copying factor due to CholmodFactorToSparse can reuse memory
  cholmod_factor* f = CholmodCopy_factor(factor, common_);
  cholmod_sparse* sp = CholmodFactorToSparse(f, common_);
  CholmodFree_factor(&f,common_);
  return(sp);
};

////////////////////////////////////////////////////////////////////////////////
int BVMat::cRf2cRs(BVMat& left, const BVMat& right)
////////////////////////////////////////////////////////////////////////////////
{
  left.code_ = ESC_chlmRsparse;
  left.s_.chlmRsparse_ = cRf2cRs(right.s_.chlmRfactor_);
  if(!left.s_.undefined_) { left.code_ = ESC_undefined; }
  else { cRs_ensure_packed(left.s_.chlmRsparse_); }
  return(0);
};
////////////////////////////////////////////////////////////////////////////////
int BVMat::cRt2cRs(BVMat& left, const BVMat& right)
////////////////////////////////////////////////////////////////////////////////
{
  left.code_ = ESC_chlmRsparse;
  left.s_.chlmRsparse_ = CholmodTripletToSparse
    (right.s_.chlmRtriplet_, right.s_.chlmRtriplet_->nnz, common_);
  if(!left.s_.undefined_) { left.code_ = ESC_undefined; }
  else { cRs_ensure_packed(left.s_.chlmRsparse_); }
  return(0);
};
////////////////////////////////////////////////////////////////////////////////
int BVMat::cRs2cRt(BVMat& left, const BVMat& right)
////////////////////////////////////////////////////////////////////////////////
{
  left.code_ = ESC_chlmRtriplet;
  cholmod_R_sparse* unsym = CholmodCopy(right.s_.chlmRsparse_, 0, 1, common_);
  left.s_.chlmRtriplet_ = 
    CholmodSparseToTriplet(unsym, common_);
  CholmodFree_sparse(&unsym, common_); 
  if(!left.s_.undefined_) { left.code_ = ESC_undefined; }
  return(0);
};
////////////////////////////////////////////////////////////////////////////////
int BVMat::cRs2bRd(BVMat& left, const BVMat& right)
////////////////////////////////////////////////////////////////////////////////
{
  left.code_ = ESC_blasRdense;
  left.s_.blasRdense_ = 
    CholmodSparseToDense(right.s_.chlmRsparse_, common_);
  if(!left.s_.undefined_) { left.code_ = ESC_undefined; }
  return(0);
};

////////////////////////////////////////////////////////////////////////////////
  int BVMat::convertIfNeeded_cRt2cRs(const BVMat&  A,  const BVMat&  B, 
                                           BVMat*& A_,       BVMat*& B_,
                                     const char* fName, bool forze)
//Matrix instances
////////////////////////////////////////////////////////////////////////////////
{
  if(!autoConvert_) { return(-1); }
  A_ = (BVMat*)&A;
  B_ = (BVMat*)&B;
  int result = 0;
  if((A.code_==ESC_chlmRsparse) && (B.code_==ESC_chlmRtriplet)) 
  { 
    warn_convert2cRs(fName,B);
    B_ = new BVMat(B,ESC_chlmRsparse); 
    result = 1;
  }
  else if((B.code_==ESC_chlmRsparse) && (A.code_==ESC_chlmRtriplet)) 
  { 
    warn_convert2cRs(fName,A);
    A_ = new BVMat(A,ESC_chlmRsparse); 
    result = 1;
  }
  else
  {
    if(forze && (A.code_!=ESC_chlmRsparse)) 
    { 
      A_=new BVMat(A,ESC_chlmRsparse); 
      result = 1;
    }
    if(forze && (B.code_!=ESC_chlmRsparse)) 
    { 
      B_=new BVMat(B,ESC_chlmRsparse); 
      result = 1;
    }
  }
  return(result);
}

////////////////////////////////////////////////////////////////////////////////
  int BVMat::convertIfNeeded_cRt2cRs(const BVMat&  A,  BVMat*& A_, 
                                     const char* fName)
//Matrix instances
////////////////////////////////////////////////////////////////////////////////
{
  if(!autoConvert_) { return(-1); }
  A_ = (BVMat*)&A;
  if(A.code_==ESC_chlmRtriplet)
  { 
    warn_convert2cRs(fName,A);
    A_ = new BVMat(A, ESC_chlmRsparse); 
  }
  return(0);
}
  
////////////////////////////////////////////////////////////////////////////////
  int BVMat::convertIfNeeded_all2cRs(const BVMat&  A,  const BVMat&  B, 
                                           BVMat*& A_,       BVMat*& B_,
                                     const char* fName, bool forze)
//Matrix instances
////////////////////////////////////////////////////////////////////////////////
{
  if(!autoConvert_) { return(-1); }
  A_ = (BVMat*)&A;
  B_ = (BVMat*)&B;
  int result = 0;
  if((A.code_==ESC_chlmRsparse) && (B.code_==ESC_chlmRsparse))
  {
    result = -1;
  }
  else if((A.code_==ESC_chlmRsparse) && (B.code_!=ESC_chlmRsparse))
  { 
    warn_convert2cRs(fName,B);
    B_ = new BVMat(B, ESC_chlmRsparse); 
    result = 1;
  }
  else if((B.code_==ESC_chlmRsparse) && (A.code_!=ESC_chlmRsparse))
  { 
    warn_convert2cRs(fName,B);
    A_ = new BVMat(A, ESC_chlmRsparse); 
    result = 1;
  }
  else
  {
    if(forze && (A.code_!=ESC_chlmRsparse)) 
    { 
      A_=new BVMat(A,ESC_chlmRsparse); 
      result = 1;
    }
    if(forze && (B.code_!=ESC_chlmRsparse)) 
    { 
      B_=new BVMat(B,ESC_chlmRsparse); 
      result = 1;
    }
  }
  return(result);
}
  
////////////////////////////////////////////////////////////////////////////////
  int BVMat::convertIfNeeded_all2cRs(const BVMat&  A,  BVMat*& A_, 
                                     const char* fName)
//Matrix instances
////////////////////////////////////////////////////////////////////////////////
{
  if(!autoConvert_) { return(-1); }
  A_ = (BVMat*)&A;
  if(A.code_!=ESC_chlmRsparse)
  { 
    warn_convert2cRs(fName,A);
    A_ = new BVMat(A, ESC_chlmRsparse); 
  }
  return(0);
}
  

////////////////////////////////////////////////////////////////////////////////
  int BVMat::convertIfNeeded_all2bRd(const BVMat&  A,  const BVMat&  B, 
                                           BVMat*& A_,       BVMat*& B_,
                                     const char* fName, bool forze)
//Matrix instances
////////////////////////////////////////////////////////////////////////////////
{
  if(!autoConvert_) { return(-1); }
  A_ = (BVMat*)&A;
  B_ = (BVMat*)&B;
  int result = 0;
  if((A.code_==ESC_blasRdense) && (B.code_==ESC_blasRdense))
  {
    result = -1;
  }
  else if((A.code_==ESC_blasRdense) && (B.code_!=ESC_blasRdense))
  { 
    warn_convert2bRd(fName,B);
    B_ = new BVMat(B, ESC_blasRdense); 
    result = 1;
  }
  else if((B.code_==ESC_blasRdense) && (A.code_!=ESC_blasRdense))
  { 
    warn_convert2bRd(fName,A);
    A_ = new BVMat(A, ESC_blasRdense); 
    result = 1;
  }
  else
  {
    if(forze && (A.code_!=ESC_blasRdense)) 
    { 
      A_=new BVMat(A,ESC_blasRdense); 
      result = 1;
    }
    if(forze && (B.code_!=ESC_blasRdense)) 
    { 
      B_=new BVMat(B,ESC_blasRdense); 
      result = 1;
    }
  }
  return(result);
}

////////////////////////////////////////////////////////////////////////////////
  int BVMat::convertIfNeeded_all2bRd(const BVMat&  A,  BVMat*& A_, 
                                     const char* fName)
//Matrix instances
////////////////////////////////////////////////////////////////////////////////
{
  if(!autoConvert_) { return(-1); }
  A_ = (BVMat*)&A;
  if(A.code_!=ESC_blasRdense)
  { 
    warn_convert2bRd(fName,A);
    A_ = new BVMat;
    A_->Convert(A, ESC_blasRdense); 
  }
  return(0);
}

////////////////////////////////////////////////////////////////////////////////
  void BVMat::Convert(const BVMat& v, ECode c)
//Importing method
////////////////////////////////////////////////////////////////////////////////
{
  if(&v==this) { return; }
  if(c==v.code_)
  {
    Copy(v);
    return;
  }
  Delete();
  const StrConvert* convert = FindConvert(c, v.code_);
  if(convert)
  {
    (*convert->fun)(*this, v);
  }
  else
  {
    Error(I2("Cannot convert a virtual matrix from ",
             "No es posible convertir una matriz virtual de ")+
          CodeName(v.code_)+ I2(" to "," a ")+ CodeName(c));
  }
};

////////////////////////////////////////////////////////////////////////////////
  void BVMat::Convert(const BVMat& v, const BText& codeName)
//Importing method
////////////////////////////////////////////////////////////////////////////////
{
  ECode code = FindCodeName(codeName);
  if(code!=ESC_undefined)
  {
    Convert(v, code);
  }
  else
  {
    Error(I2("Invalid subtype code for VMatrix Convert function",
             "Codigo de subtipo inv�lido para la funci�n VMatrix Convert")+
          ": "+codeName);
  }
}
  
  
////////////////////////////////////////////////////////////////////////////////
  void BVMat::DMat2dense (const BMatrix<double>& d)
//Importing method
//Converts a row major BMatrix<double> to a column major cholmod dense matrix
////////////////////////////////////////////////////////////////////////////////
{
  Delete();
  code_  = ESC_blasRdense;
  int r = d.Rows();
  int c = d.Columns();
  s_.blasRdense_ = CholmodAllocate_dense
    (r, c, r, CHOLMOD_REAL, common_);
  double * x = (double*)(s_.blasRdense_->x);
  int i, j, k;
  for (j=k=0; j<c; j++) 
  {
    for (i=0; i<r; i++, k++) 
    {
      x[k] =d(i,j);
    }
  }
};

////////////////////////////////////////////////////////////////////////////////
  void BVMat::DMat2denseT (const BMatrix<double>& d)
//Importing method
//Converts the traspose of a row major BMatrix<double> to a column major
//cholmod dense matrix
////////////////////////////////////////////////////////////////////////////////
{
  Delete();
  code_  = ESC_blasRdense;
  int r = d.Columns();
  int c = d.Rows();
  s_.blasRdense_ = CholmodAllocate_dense
    (r, c, r, CHOLMOD_REAL, common_);
  double * x = (double*)(s_.blasRdense_->x);
  memcpy(x, d.Data().Buffer(), r*c*sizeof(double));
};

////////////////////////////////////////////////////////////////////////////////
  void BVMat::DMat2sparse(const BMatrix<double>& d)
//Importing method
//Converts a row major BMatrix<double> to a column major cholmod dense matrix
////////////////////////////////////////////////////////////////////////////////
{
  Delete();
  int r = d.Columns();
  int c = d.Rows();
  code_  = ESC_chlmRsparse;
  cholmod_dense* dense=CholmodAllocate_dense
    (r, c, r, CHOLMOD_REAL, common_);
  double * x = (double*)(dense->x);
  memcpy(x, d.Data().Buffer(), r*c*sizeof(double));
  cholmod_sparse* sparse = CholmodDenseToSparse
    (dense, 1, common_);
  CholmodFree_dense (&dense, common_);
  s_.chlmRsparse_ = cholmod_transpose(sparse,1,common_);
  CholmodFree_sparse (&sparse, common_);
};

////////////////////////////////////////////////////////////////////////////////
  void BVMat::DMat2sparseT(const BMatrix<double>& d)
//Importing method
//Converts a row major BMatrix<double> to a column major cholmod dense matrix
////////////////////////////////////////////////////////////////////////////////
{
  Delete();
  code_  = ESC_chlmRsparse;
  int r = d.Columns();
  int c = d.Rows();
  cholmod_dense* dense=CholmodAllocate_dense
    (r, c, r, CHOLMOD_REAL, common_);
  double * x = (double*)(dense->x);
  memcpy(x, d.Data().Buffer(), r*c*sizeof(double));
  s_.chlmRsparse_ = CholmodDenseToSparse
    (dense, 1, common_);
  CholmodFree_dense (&dense, common_);
};

////////////////////////////////////////////////////////////////////////////////
  void BVMat::DMat2VMat(const BMatrix<double>& d_, 
                        bool traspose, double minSparse, double drop)
//Importing method
//Converts an optionally droped row major BMatrix<double> or its trapose to a 
//column major blas.R.dense matrix or a cholmod.R.sparse
////////////////////////////////////////////////////////////////////////////////
{
  Delete();
  BMatrix<double> d = d_;
  int nullCells = 0;
  int i, n = d.Data().Size();
  double* x = d.GetData().GetBuffer();
  double  a;
  for(i=0; i<n; i++)
  {
    if(drop>0.0)
    {
      a = fabs(x[i]);
      if(a<drop) { x[i]=0.0; }
    }
    nullCells += (x[i]==0.0);
  }
  double sprst = ((double)nullCells) / ((double)(d.Rows()*d.Columns())); 
  if(sprst>=minSparse)
  {
    if(traspose) { DMat2sparseT(d); }
    else         { DMat2sparse (d); }
  }
  else
  {
    if(traspose) { DMat2denseT(d); }
    else         { DMat2dense (d); }
  }
};


////////////////////////////////////////////////////////////////////////////////
  void BVMat::DMat2tripletUnique(const BMatrix<double>& ijx, int nrow, int ncol)
//Importing method
//Converts a row major BMatrix<double> to a column major cholmod dense matrix
////////////////////////////////////////////////////////////////////////////////
{
  BHashBoolByIntPair hashPairs;
  BIntPair p;
  double x;
  static BText fName = "TripletUnique";
  Delete();
  int h, k, n = ijx.Rows();
  code_  = ESC_chlmRtriplet;
  s_.chlmRtriplet_ = CholmodAllocate_triplet
    (nrow,ncol,n,0,CHOLMOD_REAL,common_);
  int*    r_ = (int*)   s_.chlmRtriplet_->i;
  int*    c_ = (int*)   s_.chlmRtriplet_->j;
  double* x_ = (double*)s_.chlmRtriplet_->x;
  bool ok = true;
  k=-1;
  for(h=0; h<n; h++)
  {
    p.r_ = (int)ijx(h,0)-1;
    p.c_ = (int)ijx(h,1)-1;
    x = ijx(h,2);
    if(x==0.0) { continue; }
    BHashBoolByIntPair::const_iterator fc = hashPairs.find(p);
    if(fc!=hashPairs.end()) { continue; }
    hashPairs[p] = true;
    k++;
    r_[k] = p.r_;
    c_[k] = p.c_;
    x_[k] = x;

    if((r_[k]<0)||(r_[k]>=nrow))
    {
      err_cannot_apply(fName, 
        BText("Row index ")+(r_[k]+1)+" out of range 1..."+(nrow+1), 
        *this);
      ok = false;
      break;
    }
    else if((c_[k]<0)||(c_[k]>=ncol))
    {
      err_cannot_apply(fName, 
        BText("Columns index ")+(c_[k]+1)+" out of range 1..."+(ncol+1), 
        *this);
      ok = false;
      break;
    }
    s_.chlmRtriplet_->nnz++; 
  }
  if(!ok) { Delete(); }
};



////////////////////////////////////////////////////////////////////////////////
  void BVMat::DMat2triplet(const BMatrix<double>& ijx, int nrow, int ncol)
//Importing method
//Converts a row major BMatrix<double> to a column major cholmod dense matrix
////////////////////////////////////////////////////////////////////////////////
{
  static BText fName = "Triplet(Matrix triplets,Real nrow,Real ncol)";
  Delete();
  int k, n = ijx.Rows();
  code_  = ESC_chlmRtriplet;
  s_.chlmRtriplet_ = CholmodAllocate_triplet
    (nrow,ncol,n,0,CHOLMOD_REAL,common_);
  int*    r_ = (int*)   s_.chlmRtriplet_->i;
  int*    c_ = (int*)   s_.chlmRtriplet_->j;
  double* x_ = (double*)s_.chlmRtriplet_->x;
  bool ok = true;
  for(k=0; k<n; k++)
  {
    r_[k] = (int)ijx(k,0)-1;
    c_[k] = (int)ijx(k,1)-1;
    x_[k] = ijx(k,2);
    if((r_[k]<0)||(r_[k]>=nrow))
    {
      err_cannot_apply(fName, 
        BText("Row index ")+(r_[k]+1)+" out of range 1..."+(nrow+1), 
        *this);
      ok = false;
      break;
    }
    else if((c_[k]<0)||(c_[k]>=ncol))
    {
      err_cannot_apply(fName, 
        BText("Columns index ")+(c_[k]+1)+" out of range 1..."+(ncol+1), 
        *this);
      ok = false;
      break;
    }
    s_.chlmRtriplet_->nnz++; 
  }
  if(!ok) { Delete(); }
};


////////////////////////////////////////////////////////////////////////////////
  void BVMat::DMat2triplet(const BMatrix<double>& ijx, int nrow, int ncol,
                           const BArray<int>& rowIdx, const BArray<int>& colIdx)
//Importing method
//Converts a row major BMatrix<double> to a column major cholmod dense matrix
////////////////////////////////////////////////////////////////////////////////
{
  static BText fName = "Triplet(Matrix triplets,Real nrow,Real ncol)";
  Delete();
  int k, n = ijx.Rows();
  code_  = ESC_chlmRtriplet;
  s_.chlmRtriplet_ = CholmodAllocate_triplet
    (nrow,ncol,n,0,CHOLMOD_REAL,common_);
  int*    r_ = (int*)   s_.chlmRtriplet_->i;
  int*    c_ = (int*)   s_.chlmRtriplet_->j;
  double* x_ = (double*)s_.chlmRtriplet_->x;
  bool ok = true;
  for(k=0; k<n; k++)
  {
    r_[k] = rowIdx[(int)ijx(k,0)-1];
    c_[k] = colIdx[(int)ijx(k,1)-1];
    x_[k] = ijx(k,2);
    if((r_[k]<0)||(r_[k]>=nrow))
    {
      err_cannot_apply(fName, 
        BText("Row index ")+(r_[k]+1)+" out of range 1..."+(nrow+1), 
        *this);
      ok = false;
      break;
    }
    else if((c_[k]<0)||(c_[k]>=ncol))
    {
      err_cannot_apply(fName, 
        BText("Columns index ")+(c_[k]+1)+" out of range 1..."+(ncol+1), 
        *this);
      ok = false;
      break;
    }
    if(x_[k]!=0.0) { s_.chlmRtriplet_->nnz++; }
  }
  if(!ok) { Delete(); }
};

////////////////////////////////////////////////////////////////////////////////
  bool BVMat::AddTriplet(const BMatrix<double>& ijx)
////////////////////////////////////////////////////////////////////////////////
{
  static BText fName = "AddTriplet(Matrix triplets)";
  Error(BText("Still not impemented function VMatrix ")+fName);
  return(false);
/*
  int k, n = ijx.Rows();
  bool ok = true;
  if(code_  != ESC_chlmRtriplet)
  {
    err_wrong_defined(fName, *this);
    ok = false;
  }
  else
  {
    int nrow; 
    int ncol;
    cholmod_triplet *all = CholmodAllocate_triplet
      (nrow,ncol,n,0,CHOLMOD_REAL,common_);
    int*    r_ = (int*)   s_.chlmRtriplet_->i;
    int*    c_ = (int*)   s_.chlmRtriplet_->j;
    double* x_ = (double*)s_.chlmRtriplet_->x;
    for(k=0; k<n; k++)
    {
      r_[k] = (int)ijx(k,0)-1;
      c_[k] = (int)ijx(k,1)-1;
      x_[k] = ijx(k,2);
      if((r_[k]<0)||(r_[k]>=nrow))
      {
        err_cannot_apply(fName, 
          BText("Row index ")+(r_[k]+1)+" out of range 1..."+(nrow+1), 
          *this);
        ok = false;
        break;
      }
      else if((c_[k]<0)||(c_[k]>=ncol))
      {
        err_cannot_apply(fName, 
          BText("Columns index ")+(c_[k]+1)+" out of range 1..."+(ncol+1), 
          *this);
        ok = false;
        break;
      }
      s_.chlmRtriplet_->nnz++; 
    }
  }
  return(false);
*/
};

////////////////////////////////////////////////////////////////////////////////
  void BVMat::GetTriplet(BMatrix<double>& ijx) const
//Exporting method
////////////////////////////////////////////////////////////////////////////////
{
  BVMat T(*this,ESC_chlmRtriplet);
  if((T.code_!=ESC_chlmRtriplet)||!T.s_.undefined_) { return; }
  int k, n = T.s_.chlmRtriplet_->nnz;
  int*    r_ = (int*)   T.s_.chlmRtriplet_->i;
  int*    c_ = (int*)   T.s_.chlmRtriplet_->j;
  double* x_ = (double*)T.s_.chlmRtriplet_->x;
  ijx.Alloc(n,3);
  for(k=0; k<n; k++)
  {
    ijx(k,0) = r_[k]+1;
    ijx(k,1) = c_[k]+1;
    ijx(k,2) = x_[k];
  }
};

////////////////////////////////////////////////////////////////////////////////
  void BVMat::BSetSparseLinReg2sparse(const BSet& sparseDef)
//Importing method
////////////////////////////////////////////////////////////////////////////////
{
  Delete();
  cholmod_sparse * sparse_create(BSet& , cholmod_common*);
  code_  = ESC_chlmRsparse;
  s_.chlmRsparse_ = sparse_create((BSet&)sparseDef, common_);
}

////////////////////////////////////////////////////////////////////////////////
  void BVMat::BSet2sparse(const BSet& sparseDef)
//Importing method
////////////////////////////////////////////////////////////////////////////////
{
  Delete();
  cholmod_sparse * sparse_create(BSet& , cholmod_common*);
  code_  = ESC_chlmRsparse;
  s_.chlmRsparse_ = sparse_create((BSet&)sparseDef, common_);
}


////////////////////////////////////////////////////////////////////////////////
  void BVMat::BPol2sparse(const BPolyn<BDat>& pol_, int nrow, int ncol)
//Importing method
////////////////////////////////////////////////////////////////////////////////
{
  if(!nrow | !ncol) { ChlmRSparse(nrow, ncol, 0); }
  Delete();
  code_  = ESC_chlmRsparse;
  int n = Minimum(nrow,ncol);
  int nnz = 0;
  int i, j, k, h, d;
  double c;
  BPolyn<BDat> pol = pol_;
  pol.Aggregate();
  int s=pol.Size();
  //const BMonome<BDat>* mon = pol.Buffer();

  for(k=0; k<s; k++)
  {
  //d = mon->Degree();
  d = pol[k].Degree();
    if(d>=0)
    {
      for(i=d; (i<nrow)&&(i-d<ncol); i++)
      {
        nnz++;
      }
    }
    else
    {
      for(j=-d; (j<ncol)&&(j+d<nrow); j++)
      {
        nnz++;
      }
    }
    //mon++;
  }
  //mon = pol.Buffer();
  cholmod_triplet* triplet = CholmodAllocate_triplet
    (nrow,ncol,nnz,0,CHOLMOD_REAL,common_);
  int*    r_ = (int*)   triplet->i;
  int*    c_ = (int*)   triplet->j;
  double* x_ = (double*)triplet->x;
  triplet->nnz = nnz;
  for(k=h=0; k<s; k++)
  {
  //d = mon->Degree();
  d = pol[k].Degree();
  //c = mon->Coef().Value();
  c = pol[k].Coef().Value();
    if(d>=0)
    {
      for(i=d; (i<nrow)&&(i-d<ncol); i++, h++)
      {
        r_[h] = i;
        c_[h] = i-d;
        x_[h] = c;
      }
    }
    else
    {
      for(j=-d; (j<ncol)&&(j+d<nrow); j++, h++)
      {
        r_[h] = j+d;
        c_[h] = j;
        x_[h] = c;
      }
    }
    //mon++;
  }

  s_.chlmRsparse_ = CholmodTripletToSparse(triplet, nnz, common_);
  CholmodFree_triplet(&triplet,common_);
}


////////////////////////////////////////////////////////////////////////////////
//Instances of trivial matrices
////////////////////////////////////////////////////////////////////////////////
  

  ////////////////////////////////////////////////////////////////////////////////
  void BVMat::GetDMatT(BMatrix<double>& d) const
//Exporting method
////////////////////////////////////////////////////////////////////////////////
{
  cholmod_dense* dense = NULL;
  cholmod_sparse* sp = NULL;
  bool mustDelete = true;
  switch(code_) {
  case(ESC_blasRdense  ) :
    mustDelete = false;
    dense = s_.blasRdense_; 
    break;
  case(ESC_chlmRsparse ) :
    dense = CholmodSparseToDense(s_.chlmRsparse_, common_); 
    break;
  case(ESC_chlmRfactor ) :
    sp = cRf2cRs(s_.chlmRfactor_); 
    dense = CholmodSparseToDense(sp, common_);
    CholmodFree_sparse(&sp, common_);
    break;
  case(ESC_chlmRtriplet) :
    sp =CholmodTripletToSparse
      (s_.chlmRtriplet_, s_.chlmRtriplet_->nnz, common_); 
    dense = CholmodSparseToDense(sp, common_);
    CholmodFree_sparse(&sp, common_);
    break;
  default: return; }
  if(dense)
  {
    d.Alloc(Columns(),Rows());
    double * x = (double*)(dense->x);  
    memcpy(d.GetData().GetBuffer(), x, d.Data().Size()*sizeof(double));  
    if(mustDelete)
    {
      CholmodFree_dense(&dense, common_);
    }
  }
};

////////////////////////////////////////////////////////////////////////////////
  void BVMat::GetDMat(BMatrix<double>& d) const
//Exporting method
////////////////////////////////////////////////////////////////////////////////
{
  BMatrix<double> t;
  GetDMatT(t);
  d = t.T();
};

////////////////////////////////////////////////////////////////////////////////
BMatrix<double> BVMat::GetTriplet() const 
////////////////////////////////////////////////////////////////////////////////
{ 
  BMatrix<double> d; 
  GetTriplet(d); 
  return(d); 
}

////////////////////////////////////////////////////////////////////////////////
BMatrix<double> BVMat::GetDMatT() const 
////////////////////////////////////////////////////////////////////////////////
{ 
  BMatrix<double> d; 
  GetDMatT(d); 
  return(d); 
}

////////////////////////////////////////////////////////////////////////////////
BMatrix<double> BVMat::GetDMat () const 
////////////////////////////////////////////////////////////////////////////////
{ 
  BMatrix<double> d; 
  GetDMat(d); 
  return(d); 
}

////////////////////////////////////////////////////////////////////////////////
//Instances of trivial matrices
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
  void BVMat::Eye(int nrow, int ncol, int diag, const BVMat& v_)
//Importing method
////////////////////////////////////////////////////////////////////////////////
{
  static BText fName = "Eye";
  Delete();
  if((nrow<0)||(ncol<0))
  {
    err_invalid_dimensions(fName,nrow,ncol);
    return;
  }
  BVMat* v__;
  convertIfNeeded_cRt2cRs(v_,v__,fName);
  BVMat &v = *v__;
  bool isCol = v.Columns()==1;
  bool isRow = v.Rows   ()==1;
  if(!isCol && !isRow)
  {
    err_cannot_apply(fName, "(is not a row nor column VMatrix)", v);
    return;
  }
  bool lower = diag<=0;
  int i, k, n = isCol?v.Rows():v.Columns();
  if(lower)
  {
    if(n>nrow+diag) { n=nrow+diag; }
    if(n>ncol)      { n=ncol; }
  }
  else
  {
    if(n>ncol-diag) { n=ncol-diag; }
    if(n>nrow)      { n=nrow; }
  }
  cholmod_triplet* triplet = CholmodAllocate_triplet
    (nrow,ncol,n,0,CHOLMOD_REAL,common_);
  int*    r_ = (int*)   triplet->i;
  int*    c_ = (int*)   triplet->j;
  double* x_ = (double*)triplet->x;

  for(i=k=0; k<n; k++)
  {
    r_[i] = lower?k-diag:k;
    c_[i] = lower?k:k+diag;
    x_[i] = isCol?v.GetCell(k,0):v.GetCell(0,k);
    if(x_[i]!=0.0) { triplet->nnz++; i++; }
  }
  code_  = ESC_chlmRsparse;
  s_.chlmRsparse_ = CholmodTripletToSparse(triplet, triplet->nnz, common_);
  CholmodFree_triplet(&triplet, common_);
  if(v__!=&v_) { delete v__; }
}

////////////////////////////////////////////////////////////////////////////////
  void BVMat::Eye(int nrow, int ncol, int diag, double x)
//Importing method
////////////////////////////////////////////////////////////////////////////////
{
  static BText fName = "Eye";
  Delete();
  if((nrow<0)||(ncol<0))
  {
    err_invalid_dimensions(fName,nrow,ncol);
    return;
  }
  bool lower = diag<=0;
  int k, n = Maximum(nrow, ncol);
  if(lower)
  {
    if(n>nrow+diag) { n=nrow+diag; }
    if(n>ncol)      { n=ncol; }
  }
  else
  {
    if(n>ncol-diag) { n=ncol-diag; }
    if(n>nrow)      { n=nrow; }
  }
  cholmod_triplet* triplet = CholmodAllocate_triplet
    (nrow,ncol,n,0,CHOLMOD_REAL,common_);
  if(x!=0.0)
  {
    int*    r_ = (int*)   triplet->i;
    int*    c_ = (int*)   triplet->j;
    double* x_ = (double*)triplet->x;
    for(k=0; k<n; k++)
    {
      r_[k] = lower?k-diag:k;
      c_[k] = lower?k:k+diag;
      x_[k] = x;
    }
    triplet->nnz = n;
  }
  code_  = ESC_chlmRsparse;
  s_.chlmRsparse_ = CholmodTripletToSparse(triplet, triplet->nnz, common_);
  CholmodFree_triplet(&triplet, common_);
}

////////////////////////////////////////////////////////////////////////////////
  void BVMat::Eye(int nrow, int ncol, ECode c)
//Matrix instances
////////////////////////////////////////////////////////////////////////////////
{
  static BText fName = "Eye";
  Delete();
  if((nrow<0)||(ncol<0))
  {
    err_invalid_dimensions(fName,nrow,ncol);
    return;
  }
  switch(c) {
  case(ESC_blasRdense  ) :
    code_  = ESC_blasRdense;
    s_.blasRdense_ = cholmod_eye(nrow, ncol, CHOLMOD_REAL, common_);
    break;
  case(ESC_chlmRsparse ) :
    code_  = ESC_chlmRsparse;         
    s_.chlmRsparse_=cholmod_speye(nrow, ncol, CHOLMOD_REAL, common_);
    break;
  default: 
    err_cannot_create(fName,c); }
};

////////////////////////////////////////////////////////////////////////////////
  void BVMat::Zeros(int nrow, int ncol, ECode c)
//Matrix instances
////////////////////////////////////////////////////////////////////////////////
{
  static BText fName = "Zeros";
  Delete();
  if((nrow<0)||(ncol<0))
  {
    err_invalid_dimensions(fName,nrow,ncol);
    return;
  }
  switch(c) {
  case(ESC_blasRdense  ) :
    code_  = ESC_blasRdense;         
    s_.blasRdense_ = cholmod_zeros(nrow, ncol, CHOLMOD_REAL, common_);
    break;
  case(ESC_chlmRsparse ) :
    code_  = ESC_chlmRsparse;         
    s_.chlmRsparse_=cholmod_spzeros(nrow, ncol, 0, CHOLMOD_REAL, common_);
    break;
  default: 
    err_cannot_create(fName,c);  }
};

////////////////////////////////////////////////////////////////////////////////
  void BVMat::Eye(int n, ECode c)
//Matrix instances
////////////////////////////////////////////////////////////////////////////////
{
  BVMat::Eye(n,n,c);
};

////////////////////////////////////////////////////////////////////////////////
  void BVMat::Zeros(int n, ECode c)
//Matrix instances
////////////////////////////////////////////////////////////////////////////////
{
  BVMat::Zeros(n,n,c);
};



////////////////////////////////////////////////////////////////////////////////
  int BVMat::CatCol(const BVMat& A_, const BVMat& B_, BVMat& C)
//Matrix instances
////////////////////////////////////////////////////////////////////////////////
{
  C.Delete();
  int r  = A_.Rows();
  int rB = B_.Rows();
  int cA = A_.Columns();
  int cB = B_.Columns();
  if(r!=rB)
  {
    err_invalid_dimensions("|",A_,B_);
    return(-1);
  }
  BVMat* A__, *B__;
  if((A_.code_!=ESC_blasRdense)||(B_.code_!=ESC_blasRdense))
  {
    convertIfNeeded_all2cRs(A_,B_,A__,B__,"|",true);
  }
  else
  {
    A__=(BVMat*)&A_;
    B__=(BVMat*)&B_;
  }
  BVMat &A = *A__,  &B = *B__;
  int cC = cA+cB;
  int nA = r*cA;
  int nB = r*cB;
  double* xA = NULL;
  double* xB = NULL;
  double* xC = NULL;
  int result = 0;
  if(A.code_!=B.code_)
  {
    err_invalid_subtypes("|",A,B);
    result = -2;
  }
  else switch(A.code_) {
  case(ESC_blasRdense  ) :
    C.code_  = ESC_blasRdense;
    C.s_.blasRdense_ = CholmodAllocate_dense
    (r, cC , r, CHOLMOD_REAL, common_);
    xA = (double*)(A.s_.blasRdense_->x);
    xB = (double*)(B.s_.blasRdense_->x);
    xC = (double*)(C.s_.blasRdense_->x);
    memcpy(xC,    xA, nA*sizeof(double));
    memcpy(xC+nA, xB, nB*sizeof(double));
    break;
  case(ESC_chlmRsparse ) :
    C.code_  = ESC_chlmRsparse;
    C.s_.chlmRsparse_= cholmod_horzcat
      (A.s_.chlmRsparse_,B.s_.chlmRsparse_,1,common_);
    TRACE_CHOLMOD_ALLOCATE("Cholmod.R.Sparse",C.s_.chlmRsparse_);
    break;
  default:
    err_invalid_subtype("|",A); 
    result = -3; }
  if(A__!=&A_) { delete A__; }
  if(B__!=&B_) { delete B__; }
  return(result);
};

////////////////////////////////////////////////////////////////////////////////
  int BVMat::CatRow(const BVMat& A_, const BVMat& B_, BVMat& C)
//Matrix algebra operator
////////////////////////////////////////////////////////////////////////////////
{
  C.Delete();
  int c  = A_.Columns();
  int cB = B_.Columns();
  int rA = A_.Rows();
  int rB = B_.Rows();
  if(c!=cB)
  {
    err_invalid_dimensions("<<",A_,B_);
    return(-2);
  }
  BVMat* A__, *B__;
  if((A_.code_!=ESC_blasRdense)||(B_.code_!=ESC_blasRdense))
  {
    convertIfNeeded_all2cRs(A_,B_,A__,B__,"<<",true);
  }
  else
  {
    A__=(BVMat*)&A_;
    B__=(BVMat*)&B_;
  }
  BVMat &A = *A__,  &B = *B__;
  int j;
  int rC = rA+rB;
  double* xA  = NULL;
  double* xB  = NULL;
  double* xC  = NULL;
  double* xAj = NULL;
  double* xBj = NULL;
  double* xCj = NULL;
  int result = 0;
  if(A.code_!=B.code_)
  {
    err_invalid_subtypes("<<",A,B);
    result = -2;
  }
  switch(A.code_) {
  case(ESC_blasRdense  ) :
    C.code_  = ESC_blasRdense;
    C.s_.blasRdense_ = CholmodAllocate_dense
    (rC, c , rC, CHOLMOD_REAL, common_);
    xA = (double*)(A.s_.blasRdense_->x);
    xB = (double*)(B.s_.blasRdense_->x);
    xC = (double*)(C.s_.blasRdense_->x);
    xAj = xA;
    xBj = xB;
    xCj = xC;
    for(j=0; j<c; j++)
    {
      memcpy(xCj, xAj, rA*sizeof(double));
      xCj += rA;
      xAj += rA;
      memcpy(xCj, xBj, rB*sizeof(double));
      xCj += rB;
      xBj += rB;
    }
    break;
  case(ESC_chlmRsparse ) :
    C.code_  = ESC_chlmRsparse;
    C.s_.chlmRsparse_= cholmod_vertcat
      (A.s_.chlmRsparse_,B.s_.chlmRsparse_,1,common_);
    TRACE_CHOLMOD_ALLOCATE("Cholmod.R.Sparse",C.s_.chlmRsparse_);
    break;
  default:
    err_invalid_subtype("<<",A); 
        result = -3; }
  if(A__!=&A_) { delete A__; }
  if(B__!=&B_) { delete B__; }
  return(result);
};

////////////////////////////////////////////////////////////////////////////////
  BVMat BVMat::operator | (const BVMat& B) const
//Matrix instances
////////////////////////////////////////////////////////////////////////////////
{
  BVMat aux;
  CatCol(*this, B, aux);
  return(aux);
};

////////////////////////////////////////////////////////////////////////////////
  BVMat BVMat::operator<<(const BVMat& B) const
//Matrix algebra operator
////////////////////////////////////////////////////////////////////////////////
{
  BVMat aux;
  CatRow(*this, B, aux);
  return(aux);
};

////////////////////////////////////////////////////////////////////////////////
  int BVMat::SubCells(const BArray<int>& rows, const BArray<int>& cols, 
                        BVMat& aux) const
//Matrix algebra operator
////////////////////////////////////////////////////////////////////////////////
{
  aux.Delete();
  int r = rows.Size();
  int c = cols.Size();
  int i, j;
  double *x, *y;
  switch(code_) {
  case(ESC_blasRdense  ) :
    aux.code_  = ESC_blasRdense;
    aux.s_.blasRdense_=CholmodAllocate_dense(r, c, r, CHOLMOD_REAL, common_);
    x = (double*)(    s_.blasRdense_->x);
    y = (double*)(aux.s_.blasRdense_->x);
    for(i=0; i<r; i++)
    {
      for(j=0; j<c; j++)
      {
        y[j*r+i] = x[ cols[j]*s_.blasRdense_->nrow+rows[i] ];
      }
    }
    break;
  case(ESC_chlmRsparse ) :
    aux.code_ = ESC_chlmRsparse;
    aux.s_.chlmRsparse_=cholmod_submatrix
    ( s_.chlmRsparse_,(int*)rows.Buffer(),r,(int*)cols.Buffer(),c,1,1,common_);
    TRACE_CHOLMOD_ALLOCATE("Cholmod.R.Sparse",aux.s_.chlmRsparse_);
    break;
  default:
    err_invalid_subtype("SubCells",*this); 
    return(-1); }
  return(0);
};

////////////////////////////////////////////////////////////////////////////////
  BVMat BVMat::SubCells(const BArray<int>& rows, const BArray<int>& cols) const
//Matrix algebra operator
////////////////////////////////////////////////////////////////////////////////
{
  BVMat aux;
  SubCells(rows,cols,aux);
  return(aux);
};


////////////////////////////////////////////////////////////////////////////////
  int BVMat::Sub(int i0, int j0, int rows, int cols, BVMat& aux) const
//Matrix algebra operator
////////////////////////////////////////////////////////////////////////////////
{
  int i, j;
  if((rows<0)||(cols<0))
  {
    err_invalid_dimensions("Sub",rows,cols);
    return(-1);
  }
  BArray<int> r(rows);
  BArray<int> c(cols);
  for(i=0; i<rows; i++) { r[i]=i0+i; }
  for(j=0; j<cols; j++) { c[j]=j0+j; }
  return(SubCells(r,c,aux));
};

////////////////////////////////////////////////////////////////////////////////
  BVMat BVMat::Sub(int i0, int j0, int rows, int cols) const
//Matrix algebra operator
////////////////////////////////////////////////////////////////////////////////
{
  BVMat aux;
  if((rows<0)||(cols<0))
  {
    err_invalid_dimensions("Sub",rows,cols);
    return(aux);
  }
  Sub(i0,j0,rows,cols,aux);
  return(aux);
};

////////////////////////////////////////////////////////////////////////////////
  int BVMat::SubRows(const BArray<int>& rows, BVMat& aux) const
//Matrix algebra operator
////////////////////////////////////////////////////////////////////////////////
{
  static BText fName = "SubRow";
  aux.Delete();
  int i, j;
  int R = Rows();
  for(i=0; i<R; i++)
  {
    if((rows[i]<0)||(rows[i]>=R))
    {
      err_cannot_apply(fName, 
        BText("Row index ")+(rows[i]+1)+" out of range 1..."+R, 
        *this);
      return(-1);
    }
  }
  int r = rows.Size();
  int c = Columns();
  double *x, *y;
  switch(code_) {
  case(ESC_blasRdense  ) :
    aux.code_  = ESC_blasRdense;
    aux.s_.blasRdense_=CholmodAllocate_dense(r, c, r, CHOLMOD_REAL, common_);
    x = (double*)(    s_.blasRdense_->x);
    y = (double*)(aux.s_.blasRdense_->x);
    for(i=0; i<r; i++)
    {
      for(j=0; j<c; j++)
      {
        y[j*r+i] = x[ j*s_.blasRdense_->nrow+rows[i] ];
      }
    }
    break;
  case(ESC_chlmRsparse ) :
    aux.code_ = ESC_chlmRsparse;
    aux.s_.chlmRsparse_=cholmod_submatrix
    ( s_.chlmRsparse_,(int*)rows.Buffer(),r,NULL,-1,1,1,common_);
    TRACE_CHOLMOD_ALLOCATE("Cholmod.R.Sparse",aux.s_.chlmRsparse_);
    break;
  default:
    err_invalid_subtype("SubRows",*this); 
    return(-1); }
  return(0);
};

////////////////////////////////////////////////////////////////////////////////
  BVMat BVMat::SubRows(const BArray<int>& rows) const
//Matrix algebra operator
////////////////////////////////////////////////////////////////////////////////
{
  BVMat aux;
  SubRows(rows, aux);
  return(aux);
};

////////////////////////////////////////////////////////////////////////////////
  int BVMat::SubCols(const BArray<int>& cols, BVMat& aux) const
//Matrix algebra operator
////////////////////////////////////////////////////////////////////////////////
{
  static BText fName = "SubCol";
  aux.Delete();
  int C = Columns();
  int i, j;
  for(j=0; j<C; j++)
  {
    if((cols[j]<0)||(cols[j]>=C))
    {
      err_cannot_apply(fName, 
        BText("Column index ")+(cols[j]+1)+" out of range 1..."+C, 
        *this);
      return(-1);
    }
  }
  int r = Rows();
  int c = cols.Size();
  double *x, *y;
  switch(code_) {
  case(ESC_blasRdense  ) :
    aux.code_  = ESC_blasRdense;
    aux.s_.blasRdense_=CholmodAllocate_dense(r, c, r, CHOLMOD_REAL, common_);
    x = (double*)(    s_.blasRdense_->x);
    y = (double*)(aux.s_.blasRdense_->x);
    for(i=0; i<r; i++)
    {
      for(j=0; j<c; j++)
      {
        y[j*r+i] = x[ cols[j]*s_.blasRdense_->nrow+i ];
      }
    }
    break;
  case(ESC_chlmRsparse ) :
    aux.code_ = ESC_chlmRsparse;
    aux.s_.chlmRsparse_=cholmod_submatrix
    ( s_.chlmRsparse_,NULL,-1,(int*)cols.Buffer(),c,1,1,common_);
    TRACE_CHOLMOD_ALLOCATE("Cholmod.R.Sparse",aux.s_.chlmRsparse_);
    break;
  default:
    err_invalid_subtype("SubCols",*this); 
    return(-2); }
  return(0);
};

////////////////////////////////////////////////////////////////////////////////
  BVMat BVMat::SubCols(const BArray<int>& cols) const
//Matrix algebra operator
////////////////////////////////////////////////////////////////////////////////
{
  BVMat aux;
  SubCols(cols, aux);
  return(aux);
};

////////////////////////////////////////////////////////////////////////////////
  int BVMat::SubBand(int from, int until, BVMat& aux) const
//Matrix algebra operator
////////////////////////////////////////////////////////////////////////////////
{
  aux.Delete();
  int nnz,nrow,ncol, i, j, k, h;
  int *r_,*c_,*r,*c;
  double *x_, *x;

  switch(code_) {
  case(ESC_chlmRsparse ) :
    aux.code_ = ESC_chlmRsparse;
    aux.s_.chlmRsparse_= cholmod_band
    (
      /* ---- input ---- */
      s_.chlmRsparse_,  /* matrix to extract band matrix from */
      from,  /* ignore entries below the k1-st diagonal */
      until, /* ignore entries above the k2-nd diagonal */
      1,     /* >0: numerical, 0: pattern, <0: pattern (no diag) */
      /* --------------- */
      common_
    );
    break;
  case(ESC_blasRdense) :
    aux.code_ = ESC_blasRdense;
    nrow = s_.blasRdense_->nrow;
    ncol = s_.blasRdense_->ncol;
    x_ = (double*)s_.blasRdense_->x;
    aux.s_.blasRdense_ = 
      CholmodAllocate_dense(nrow, ncol, nrow, CHOLMOD_REAL, common_);
    x = (double*)aux.s_.blasRdense_->x;
//  memset(x,0,nrow*ncol*sizeof(double));
    for (j=k=0; j<ncol; j++) 
    {
      for (i=0; i<nrow; i++, k++) 
      {
        h = j-i;
        if((h>=from)&&(h<=until)) { x[k] = x_[k]; }
        else                      { x[k] = 0;     }
      }
    }

    break;
  case(ESC_chlmRtriplet ) :
    aux.code_ = ESC_chlmRtriplet;
    r_ = (int*)   s_.chlmRtriplet_->i;
    c_ = (int*)   s_.chlmRtriplet_->j;
    x_ = (double*)s_.chlmRtriplet_->x;
    for(k=nnz=0; k<s_.chlmRtriplet_->nnz; k++)
    {
      i = r_[k];
      j = c_[k];
      h = j-i;
      if((h>=from)&&(h<=until)&&(x_[k]!=0.0))
      {
        nnz++;
      } 
    }
    aux.s_.chlmRtriplet_ = CholmodAllocate_triplet
      (s_.chlmRtriplet_->nrow,s_.chlmRtriplet_->ncol,nnz,0,CHOLMOD_REAL,common_);
    nnz=0;
    r = (int*)   aux.s_.chlmRtriplet_->i;
    c = (int*)   aux.s_.chlmRtriplet_->j;
    x = (double*)aux.s_.chlmRtriplet_->x;
    for(k=0; k<s_.chlmRtriplet_->nnz; k++)
    {
      i = r_[k];
      j = c_[k];
      h = j-i;
      if((h>=from)&&(h<=until)&&(x_[k]!=0.0))
      {
        r[nnz] = i;
        c[nnz] = j;
        x[nnz] = x_[k];
        nnz++;
      } 
    }
    aux.s_.chlmRtriplet_->nnz = nnz;
    break;
  default:
    err_cannot_apply("SubBand",I2("(Not implemented)",
                   "(Metodo no implementado)"),*this);
    return(-2); }

  return(0);
};

////////////////////////////////////////////////////////////////////////////////
  BVMat BVMat::SubBand(int from, int until) const
//Matrix algebra operator
////////////////////////////////////////////////////////////////////////////////
{
  BVMat aux;
  SubBand(from, until, aux);
  return(aux);
};


////////////////////////////////////////////////////////////////////////////////
  int BVMat::SubDiag(int numDiag, BVMat& aux) const
//Matrix algebra operator
//Extracts cell (i,j) matching i-j=numDiag
////////////////////////////////////////////////////////////////////////////////
{
  int fail = 0;
  int rows = Rows();
  int cols = Columns();
  int dMin = -rows+1;
  int dMax =  cols-1;
  bool outOfRange = (numDiag<dMin)||(numDiag>dMax);
  if(!outOfRange)
  {
    BVMat band;
    fail = SubBand(numDiag, numDiag, band);
    if(!fail)
    {
      int i0 = (numDiag>=0)?0:-numDiag;
      int j0 = (numDiag<=0)?0:+numDiag;
      int len = Minimum(rows-i0,cols-j0);
      assert(len>0);
      int k;
      aux.BlasRDense(1,len);
      double* x = (double*)(aux.s_.blasRdense_->x);
      for(k=0; k<len; k++)
      {
        x[k] = band.GetCell(k+numDiag,k);
      }
    }
  }
  else
  {
    err_cannot_apply("SubDiag",I2("(Diagonal number out of range)",
                     "(N�mero de diagonal fuera de rango)")+
                     "["+dMin+","+dMax+"]",*this);
    fail = -3;
  }
  return(fail);
};

////////////////////////////////////////////////////////////////////////////////
  BVMat BVMat::SubDiag(int numDiag) const
//Matrix algebra operator
//Extracts cell (i,j) matching i-j=numDiag
////////////////////////////////////////////////////////////////////////////////
{
  BVMat aux;
  SubDiag(numDiag, aux);
  return(aux);
}
