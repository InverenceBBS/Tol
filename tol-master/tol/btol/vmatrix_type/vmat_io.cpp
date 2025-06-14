/* vmat_io.cpp: BVMat input-output methods
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
#include <tol/tol_oiscreator.h>
#include <tol/tol_oisloader.h>
#include <tol/tol_oisstream_dir.h>
#include <tol/tol_bdir.h>
#include <stdarg.h>

//#define _USE_MM_IO_
#ifdef _USE_MM_IO_
#include "mmio.h"
#endif

////////////////////////////////////////////////////////////////////////////////
// BVMat members
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
#if defined( USE_CHOLMOD_VER1 )
void BVMat::cholmod_error_handler(int status, char *file, int line, char *message)
#else
void BVMat::cholmod_error_handler(int status, const char *file, int line, const char *message)
#endif
////////////////////////////////////////////////////////////////////////////////
{
  int len = strlen(message)+strlen(file)+100;
  char * buffer = new char[len];

  sprintf(buffer, "[CHOLMOD %d] at line %s:%d: %s", 
          status, file, line, message);
  
       if(status<0) { Error  (buffer); }
  else if(status>0) { Warning(buffer); }
  else              { Std    (buffer); }
    
  delete [] buffer;
};

//--------------------------------------------------------------------
  int BVMat::cholmod_print_function(const char *fmt, ...)
//--------------------------------------------------------------------
{
  static char buffer_[1024*32];
  if(!cholmod_print_file_) { return(0); }
  int rc;
  va_list args;
  va_start(args, fmt);
  if(cholmod_print_file_!=stdout)
  {
    rc = vfprintf(cholmod_print_file_, fmt, args);
  }
  else
  {
    rc = vsprintf(buffer_, fmt, args);
    Std(buffer_);
  }
  va_end(args);
  return rc;
}

#ifndef NDEBUG 
#define DO_WARN_INEF_USE
#endif
#ifdef DO_WARN_INEF_USE
  #define DO_WARN_INEF_USE_all2bRd
  #define DO_WARN_INEF_USEall_all2cRs
  #define DO_WARN_INEF_USE_2cRt
#endif


////////////////////////////////////////////////////////////////////////////////
  static void warn_inefUse(const BText& msg)
////////////////////////////////////////////////////////////////////////////////
{
#ifdef DO_WARN_INEF_USE
  static BText aux_ = "Probably ineficient use. ";
  Warning(aux_+msg);
#endif
}

////////////////////////////////////////////////////////////////////////////////
  void BVMat::warn_convert2cRt(const char* fName, const BVMat& a)
//Message handler
////////////////////////////////////////////////////////////////////////////////
{
#ifdef DO_WARN_INEF_USE_2cRt
  static double minStoredCells_ = 50000.0;
  double storedCells = a.StoredCells();
  if(storedCells>=minStoredCells_)
  {
    warn_inefUse(I2("Converting to","Convirtiendo matriz a")+
            " Blas.R.Triplet "+CodeName(a.code_)+" "+
            I2("to apply","para aplicar")+" "+fName+" "+
            I2("to a virtual matrix","a una matriz virtual")+
            " "+CodeName(a.code_)+"("+a.Rows()+"x"+a.Columns()+")"+" ");
  }
#endif
}

////////////////////////////////////////////////////////////////////////////////
  void BVMat::warn_convert2cRs(const char* fName, const BVMat& a)
//Message handler
////////////////////////////////////////////////////////////////////////////////
{
#ifdef DO_WARN_INEF_USEall_all2cRs
  static double minStoredCells_ = 50000.0;
  double storedCells = a.StoredCells();
  if(storedCells>=minStoredCells_)
  {
    warn_inefUse(I2("Converting to","Convirtiendo matriz a")+
            " Cholmod.R.Sparse "+CodeName(a.code_)+" "+
            I2("to apply","para aplicar")+" "+fName+" "+
            I2("to a virtual matrix","a una matriz virtual")+
            " "+CodeName(a.code_)+"("+a.Rows()+"x"+a.Columns()+")"+" ");
  }
#endif
}

////////////////////////////////////////////////////////////////////////////////
  void BVMat::warn_convert2bRd(const char* fName, const BVMat& a)
//Message handler
////////////////////////////////////////////////////////////////////////////////
{
#ifdef DO_WARN_INEF_USE_all2bRd
  static double minLostCells_ = 50000.0;
  int    r = a.Rows();
  int    c = a.Columns();
  double storedCells = a.StoredCells();
  double denseCells  = r*c;
  double lostCells   = denseCells-storedCells;
  if( ((r>1)&&(c>1)) && (lostCells>=minLostCells_) )
  {
    double memKbLost = (lostCells*sizeof(double))/1024.0;
    warn_inefUse(I2("Converting from ","Convirtiendo de ")+CodeName(a.code_)+
      I2(" to"," a")+" Blas.R.Dense "+
      I2("to apply","para aplicar")+" "+fName+" "+
      I2("to a virtual matrix","a una matriz virtual")+
      " "+CodeName(a.code_)+"("+r+"x"+c+")"+" "+
      I2("with","con")+" "+storedCells+
      I2("stored cells","celdas almacendas")+".\n"+
      I2("It will be lost a total of ",
         "Se perder� un total de ")+memKbLost+" KBytes");
  }
#endif
}

////////////////////////////////////////////////////////////////////////////////
  void BVMat::warn_cannot_apply(const char* fName, const char* cond, 
                                const BVMat& a)
//Message handler
////////////////////////////////////////////////////////////////////////////////
{
  Warning(I2("Cannot apply",
           "No es posible aplicar")+" "+fName+" "+
        I2("to a",
           "a una matriz virtual")+" "+cond+" "+
        I2("virtual matrix","")+" "+CodeName(a.code_)+
           "("+a.Rows()+"x"+a.Columns()+")"+" ");
}

////////////////////////////////////////////////////////////////////////////////
  void BVMat::err_wrong_defined(const char* fName, const BVMat& a)
//Message handler
////////////////////////////////////////////////////////////////////////////////
{
  Error(I2("Cannot apply",
           "No es posible aplicar")+" "+fName+" "+
        I2("to a virtual matrix",
           "a una matriz virtual")+" "+
        I2("without defined constens of subtype",
           "sin contenido definido de subtipo")+" "+
        CodeName(a.code_));
}

////////////////////////////////////////////////////////////////////////////////
  void BVMat::err_cannot_apply(const char* fName, const char* cond, 
                               const BVMat& a)
//Message handler
////////////////////////////////////////////////////////////////////////////////
{
  Error(I2("Cannot apply",
           "No es posible aplicar")+" "+fName+" "+
        I2("to a",
           "a una matriz virtual")+" "+cond+" "+
        I2("virtual matrix","")+" "+CodeName(a.code_)+
           "("+a.Rows()+"x"+a.Columns()+")"+" ");
#ifndef NDEBUG
  FILE *f = fopen(BSys::TolAppData()+"tmp/vmatrix_err_cannot_apply.mtx", "w");
  if ( f ) {
    ((BVMat&)a).WriteMatrixMarket(f);
    fclose(f);
  }
#endif
}

////////////////////////////////////////////////////////////////////////////////
  void BVMat::err_cannot_create(const char* fName, ECode code)
//Message handler
////////////////////////////////////////////////////////////////////////////////
{
  Error(I2("Cannot apply",
           "No es posible aplicar")+" "+fName+" "+
        I2("to a virtual matrix",
           "a una matriz virtual")+" "+CodeName(code));
}
  
////////////////////////////////////////////////////////////////////////////////
  void BVMat::err_cannot_create(const char* fName, const char* cond)
//Message handler
////////////////////////////////////////////////////////////////////////////////
{
  Error(I2("Cannot apply",
           "No es posible aplicar")+" "+fName+" "+cond);
}
  
////////////////////////////////////////////////////////////////////////////////
  void BVMat::err_invalid_subtype(const char* fName, const BVMat& a)
//Message handler
////////////////////////////////////////////////////////////////////////////////
{
  Error(I2("Cannot apply",
           "No es posible aplicar")+" "+fName+" "+
        I2("to a virtual matrix of subtype",
           "a una matriz virtual de subtipo")+" "+
          CodeName(a.code_));
}
  
////////////////////////////////////////////////////////////////////////////////
  void BVMat::err_invalid_subtypes(const char* fName, 
                                    const BVMat& a, const BVMat& b)
//Message handler
////////////////////////////////////////////////////////////////////////////////
{
  Error(I2("Cannot apply",
           "No es posible aplicar")+" "+fName+" "+
        I2("to virtual matrices of subtypes",
           "a matrices virtuales de subtipos")+" "+
          CodeName(a.code_)+","+CodeName(b.code_));
}
  
////////////////////////////////////////////////////////////////////////////////
  void BVMat::err_invalid_dimensions(const char* fName, int nrow, int ncol)
//Message handler
////////////////////////////////////////////////////////////////////////////////
{
  Error(I2("Cannot apply",
           "No es posible aplicar")+" "+fName+" "+
        I2("to create a virtual matrix of dimensions",
           "para crear una matriz virtual de dimensiones")+" "+
          "("+nrow+"x"+ncol+")");
}
  
////////////////////////////////////////////////////////////////////////////////
  void BVMat::err_invalid_dimensions(const char* fName, 
                                     const BVMat& a, const BVMat& b)
//Message handler
////////////////////////////////////////////////////////////////////////////////
{
  Error(I2("Cannot apply",
           "No es posible aplicar")+" "+fName+" "+
        I2("to virtual matrices of dimensions",
           "a matrices virtuales de dimensiones")+" "+
          "("+a.Rows()+"x"+a.Columns()+")"+" "+
          "("+b.Rows()+"x"+b.Columns()+")");
}
  
////////////////////////////////////////////////////////////////////////////////
  void BVMat::err_invalid_dimensions(const char* fName, 
                                const BVMat& a, const BVMat& b, const BVMat& c)
//Message handler
////////////////////////////////////////////////////////////////////////////////
{
  Error(I2("Cannot apply",
           "No es posible aplicar")+" "+fName+" "+
        I2("to virtual matrices of dimensions",
           "a matrices virtuales de dimensiones")+" "+
          "("+a.Rows()+"x"+a.Columns()+")"+" "+
          "("+b.Rows()+"x"+b.Columns()+")"+" "+
          "("+c.Rows()+"x"+c.Columns()+")");
}
  

////////////////////////////////////////////////////////////////////////////////
  void BVMat::Print(FILE* file, const char* name_, int level) const
//Exporting method
////////////////////////////////////////////////////////////////////////////////
{
  int oldLevel = common_->print;
  FILE* oldFile = cholmod_print_file_;
  common_->print = level;
  char* name = (char*)name_;
  cholmod_print_file_ = file;
  switch(code_) {
  case(ESC_blasRdense  ) : 
    cholmod_print_dense(s_.blasRdense_, name, common_); break; 
  case(ESC_chlmRsparse ) : 
    cholmod_print_sparse(s_.chlmRsparse_, name, common_); break; 
  case(ESC_chlmRfactor ) : 
    cholmod_print_factor(s_.chlmRfactor_, name, common_); break; 
  case(ESC_chlmRtriplet) : 
    cholmod_print_triplet(s_.chlmRtriplet_, name, common_); break; 
  default: ;}
  cholmod_print_file_ = oldFile;
  common_->print = oldLevel;
};

////////////////////////////////////////////////////////////////////////////////
  void BVMat::Scan(FILE* file)
//Exporting method
////////////////////////////////////////////////////////////////////////////////
{
  Delete();
  code_ = ESC_chlmRtriplet;
  s_.chlmRtriplet_ = cholmod_read_triplet(file,common_);
};

#ifdef _USE_MM_IO_
////////////////////////////////////////////////////////////////////////////////
  void BVMat::WriteMatrixMarket(FILE* file)
//Exporting method
////////////////////////////////////////////////////////////////////////////////
{
  cholmod_triplet *ptr_triplet = NULL;
  bool should_free = false;
  MM_typecode matcode;
  
  if (code_==ESC_chlmRsparse) {
    cholmod_R_sparse *unsym = CholmodCopy(s_.chlmRsparse_, 0, 1, common_);
    ptr_triplet = CholmodSparseToTriplet(unsym, common_);
    CholmodFree_sparse(&unsym, common_); 
    should_free = true;
  } else if (code_==ESC_chlmRtriplet) {
    ptr_triplet = s_.chlmRtriplet_;
  }
  if (ptr_triplet) {
    mm_initialize_typecode(&matcode);
    mm_set_matrix(&matcode);
    mm_set_coordinate(&matcode);
    mm_set_real(&matcode);

    mm_write_banner(file, matcode); 
    mm_write_mtx_crd_size(file,
                          ptr_triplet->nrow,
                          ptr_triplet->ncol,
                          ptr_triplet->nnz);

    /* NOTE: matrix market files use 1-based indices, i.e. first element
       of a vector has index 1, not 0.  */

    int *Ti = (int*)ptr_triplet->i;
    int *Tj = (int*)ptr_triplet->j;
    double *Val = (double*)ptr_triplet->x;
    for (int i=0; i<ptr_triplet->nnz; i++)
        fprintf(file,
                "%d %d %10.7g\n", Ti[i]+1, Tj[i]+1, Val[i]);
    
    if (should_free) {
      CholmodFree_triplet(&ptr_triplet, common_);
    }
  }
};
#else
void BVMat::WriteMatrixMarket(FILE* file)
{
}
#endif



////////////////////////////////////////////////////////////////////////////////
  size_t BVMat::bytes_blasRdense(int nzmax) 
//Exporting method
////////////////////////////////////////////////////////////////////////////////
{
  return(sizeof(cholmod_dense)+ nzmax*sizeof(double));
};

////////////////////////////////////////////////////////////////////////////////
  size_t BVMat::bytes_chlmRsparse(int nzmax, int ncol, bool packed) 
//Exporting method
////////////////////////////////////////////////////////////////////////////////
{
  return(sizeof(cholmod_sparse)+ 
         (ncol+1+((packed)?0:ncol))*sizeof(int)+
         nzmax*(sizeof(int) + sizeof(double)) );
};

////////////////////////////////////////////////////////////////////////////////
  size_t BVMat::bytes(const cholmod_R_dense* a) 
//Exporting method
////////////////////////////////////////////////////////////////////////////////
{
  return(bytes_blasRdense(a->nzmax));
};

////////////////////////////////////////////////////////////////////////////////
  size_t BVMat::bytes(const cholmod_R_sparse* a) 
//Exporting method
////////////////////////////////////////////////////////////////////////////////
{
  return(bytes_chlmRsparse(a->nzmax,a->ncol,a->packed!=0));
};

////////////////////////////////////////////////////////////////////////////////
  size_t BVMat::bytes(const cholmod_R_factor* a) 
//Exporting method
////////////////////////////////////////////////////////////////////////////////
{
  size_t bytes = sizeof(cholmod_factor)+ 
                 a->n * 2 * sizeof(int);
  if (a->xtype != CHOLMOD_PATTERN && !(a->is_super))
  {
	//writes the contents of a simplicial numeric factor 
    bytes+= ((1+a->n)+(2+a->n)+(2+a->n)+a->n+a->nzmax)*sizeof(int)+
            a->nzmax*sizeof(double);
  }
  else if (a->is_super)
  {
    bytes += ((a->nsuper+1)*3+a->ssize)*sizeof(int)+
             a->xsize*sizeof(double);
  }
  return(bytes);
};

////////////////////////////////////////////////////////////////////////////////
  size_t BVMat::bytes(const cholmod_R_triplet* a) 
//Exporting method
////////////////////////////////////////////////////////////////////////////////
{
  return(sizeof(cholmod_triplet)+
         a->nzmax*(2*sizeof(int)+sizeof(double)));
};



////////////////////////////////////////////////////////////////////////////////
  size_t BVMat::bytes_blasRdense() const
//Exporting method
////////////////////////////////////////////////////////////////////////////////
{
  return(bytes(s_.blasRdense_));
};

////////////////////////////////////////////////////////////////////////////////
  size_t BVMat::bytes_chlmRsparse() const
//Exporting method
////////////////////////////////////////////////////////////////////////////////
{
  return(bytes(s_.chlmRsparse_));
};

////////////////////////////////////////////////////////////////////////////////
  size_t BVMat::bytes_chlmRfactor() const
//Exporting method
////////////////////////////////////////////////////////////////////////////////
{
  return(bytes(s_.chlmRfactor_));
};

////////////////////////////////////////////////////////////////////////////////
  size_t BVMat::bytes_chlmRtriplet() const
//Exporting method
////////////////////////////////////////////////////////////////////////////////
{
  return(bytes(s_.chlmRtriplet_));
};

////////////////////////////////////////////////////////////////////////////////
  size_t BVMat::Bytes() const
//Exporting method
////////////////////////////////////////////////////////////////////////////////
{
  size_t s0 = sizeof(BVMat);
  switch(code_) {
  case(ESC_blasRdense  ) : return(s0+bytes_blasRdense  ()); 
  case(ESC_chlmRsparse ) : return(s0+bytes_chlmRsparse ()); 
  case(ESC_chlmRfactor ) : return(s0+bytes_chlmRfactor ()); 
  case(ESC_chlmRtriplet) : return(s0+bytes_chlmRtriplet()); 
  default: return(s0);}
};


////////////////////////////////////////////////////////////////////////////////
  bool BVMat::write_blasRdense(BOisCreator& ois, BStream* stream) const
//Exporting method
////////////////////////////////////////////////////////////////////////////////
{
  cholmod_dense& a = *s_.blasRdense_;
  if(!cholmod_check_dense(&a,common_))
  {
    Error("Cannot save image OIS of a non valid VMatrix(Blas.R.Dense)");
    return(false);
  }
  Ensure(ois.Write_size_t(a.nrow,  stream));
  Ensure(ois.Write_size_t(a.ncol,  stream));
  Ensure(ois.Write_size_t(a.d,     stream));
  Ensure(ois.Write(a.xtype, stream));
  Ensure(ois.Write_size_t(a.nzmax, stream));
  Ensure(ois.Write(a.dtype, stream));
  Ensure(ois.Write(a.x,     a.nzmax, sizeof(double), stream));
  return(true);
};

////////////////////////////////////////////////////////////////////////////////
  bool BVMat::read_blasRdense(BOisLoader& ois, BStream* stream)
//Exporting method
////////////////////////////////////////////////////////////////////////////////
{
  code_ = ESC_blasRdense;
  s_.blasRdense_ = (cholmod_dense*)cholmod_malloc(1,
    sizeof(cholmod_dense),common_);
  cholmod_dense& a = *s_.blasRdense_;
  Ensure(ois.Read_size_t(a.nrow,  stream));
  Ensure(ois.Read_size_t(a.ncol,  stream));
  Ensure(ois.Read_size_t(a.d,     stream));
  Ensure(ois.Read(a.xtype, stream));
  Ensure(ois.Read_size_t(a.nzmax, stream));
  Ensure(ois.Read(a.dtype, stream));
  a.x = cholmod_malloc(a.nzmax, sizeof(double), common_);
  TRACE_CHOLMOD_ALLOCATE("Blas.R.Dense",&a);

  Ensure(ois.Read(a.x, a.nzmax, sizeof(double), stream));    
  a.z = NULL;
  if(!cholmod_check_dense(&a,common_))
  {
    Error("Cannot load image OIS of a non valid VMatrix(Blas.R.Dense)");
    Delete();
    return(false);
  }
  return(true);
};

////////////////////////////////////////////////////////////////////////////////
  bool BVMat::write_chlmRsparse(BOisCreator& ois, BStream* stream) const
//Exporting method
////////////////////////////////////////////////////////////////////////////////
{
  cholmod_sparse& a = *s_.chlmRsparse_;
  if(!cholmod_check_sparse(&a,common_))
  {
    Error("Cannot save image OIS of a non valid VMatrix(Cholmod.R.Sparse)");
    return(false);
  }
  Ensure(ois.Write_size_t(a.nrow,   stream));
  Ensure(ois.Write_size_t(a.ncol,   stream));
  Ensure(ois.Write_size_t(a.nzmax,  stream));
  Ensure(ois.Write(a.stype,  stream));
  Ensure(ois.Write(a.itype,  stream));
  Ensure(ois.Write(a.xtype,  stream));
  Ensure(ois.Write(a.dtype,  stream));
  Ensure(ois.Write(a.sorted, stream));
  Ensure(ois.Write(a.packed, stream));
  Ensure(ois.Write(a.p,  a.ncol+1,sizeof(int),    stream));
  Ensure(ois.Write(a.i,  a.nzmax, sizeof(int),    stream));
  Ensure(ois.Write(a.x,  a.nzmax, sizeof(double), stream));
  if(!a.packed) 
  {
    Ensure(ois.Write(a.nz, a.ncol, sizeof(int), stream)); 
  }
  return(true);
};

////////////////////////////////////////////////////////////////////////////////
  bool BVMat::read_chlmRsparse(BOisLoader& ois, BStream* stream)
//Exporting method
////////////////////////////////////////////////////////////////////////////////
{
  code_ = ESC_chlmRsparse;
  s_.chlmRsparse_ = (cholmod_sparse*)cholmod_malloc(1,
    sizeof(cholmod_sparse),common_);
  cholmod_sparse& a = *s_.chlmRsparse_;
  Ensure(ois.Read_size_t(a.nrow,   stream));
  Ensure(ois.Read_size_t(a.ncol,   stream));
  Ensure(ois.Read_size_t(a.nzmax,  stream));
  Ensure(ois.Read(a.stype,  stream));
  Ensure(ois.Read(a.itype,  stream));
  Ensure(ois.Read(a.xtype,  stream));
  Ensure(ois.Read(a.dtype,  stream));
  Ensure(ois.Read(a.sorted, stream));
  Ensure(ois.Read(a.packed, stream));
  a.p = cholmod_malloc(a.ncol+1,sizeof(int),    common_);
  a.i = cholmod_malloc(a.nzmax, sizeof(int),    common_);
  a.x = cholmod_malloc(a.nzmax, sizeof(double), common_);
  Ensure(ois.Read(a.p, a.ncol+1,sizeof(int),    stream));
  Ensure(ois.Read(a.i, a.nzmax, sizeof(int),    stream));
  Ensure(ois.Read(a.x, a.nzmax, sizeof(double), stream));
  if(!a.packed) 
  {
    a.nz = cholmod_malloc(a.ncol, sizeof(int), common_);
    Ensure(ois.Read(a.nz, a.ncol, sizeof(int), stream)); 
  }
  else
  {
    a.nz = NULL;
  }
  a.z = NULL;
  if((a.nrow>10000) && (a.ncol>100) && (a.nzmax>(a.nrow*a.ncol*.10)))
    printf("");
  TRACE_CHOLMOD_ALLOCATE("Cholmod.R.Sparse",&a);
  if(!cholmod_check_sparse(&a,common_))
  {
    Error("Cannot load image OIS of a non valid VMatrix(Cholmod.R.Sparse)");
    Delete();
    return(false);
  }
  return(true);
};

////////////////////////////////////////////////////////////////////////////////
  bool BVMat::write_chlmRfactor(BOisCreator& ois, BStream* stream) const
//Exporting method
////////////////////////////////////////////////////////////////////////////////
{
  cholmod_factor& a = *s_.chlmRfactor_;
  if(!cholmod_check_factor(&a,common_))
  {
    Error("Cannot save image OIS of a non valid VMatrix(Cholmod.R.Factor)");
    return(false);
  }
  Ensure(ois.Write_size_t(a.n,            stream));
  Ensure(ois.Write_size_t(a.minor,        stream));
  Ensure(ois.Write_size_t(a.nzmax,        stream));
  Ensure(ois.Write(a.itype,        stream));
  Ensure(ois.Write(a.xtype,        stream));
  Ensure(ois.Write(a.dtype,        stream));
  Ensure(ois.Write(a.ordering,     stream));
  Ensure(ois.Write(a.is_ll,        stream));
  Ensure(ois.Write(a.is_super,     stream));
  Ensure(ois.Write(a.is_monotonic, stream));
  Ensure(ois.Write(a.Perm,     a.n, sizeof(int), stream));
  Ensure(ois.Write(a.ColCount, a.n, sizeof(int), stream));
  if (a.xtype != CHOLMOD_PATTERN && !(a.is_super))
  {
	//writes the contents of a simplicial numeric factor 
    Ensure(ois.Write(a.p,    1+a.n, sizeof(int),    stream));
    Ensure(ois.Write(a.prev, 2+a.n, sizeof(int),    stream));
    Ensure(ois.Write(a.next, 2+a.n, sizeof(int),    stream));
    Ensure(ois.Write(a.nz,     a.n, sizeof(int),    stream));
    Ensure(ois.Write(a.i,  a.nzmax, sizeof(int),    stream));
    Ensure(ois.Write(a.x,  a.nzmax, sizeof(double), stream));
  }
  else if (a.is_super)
  {
	//writes a supernodal factor
    Ensure(ois.Write_size_t(a.nsuper,   stream));
    Ensure(ois.Write_size_t(a.xsize,    stream));
    Ensure(ois.Write_size_t(a.ssize,    stream));
    Ensure(ois.Write_size_t(a.maxcsize, stream));
    Ensure(ois.Write_size_t(a.maxesize, stream));
    Ensure(ois.Write(a.super,    a.nsuper+1, sizeof(int),    stream));
    Ensure(ois.Write(a.pi,       a.nsuper+1, sizeof(int),    stream));
    Ensure(ois.Write(a.px,       a.nsuper+1, sizeof(int),    stream));
    Ensure(ois.Write(a.s,        a.ssize,    sizeof(int),    stream));
    Ensure(ois.Write(a.x,        a.xsize,    sizeof(double), stream));
  }
  return(true);
};

////////////////////////////////////////////////////////////////////////////////
  bool BVMat::read_chlmRfactor(BOisLoader& ois, BStream* stream)
//Exporting method
////////////////////////////////////////////////////////////////////////////////
{
  code_ = ESC_chlmRfactor;
  size_t n;
  Ensure(ois.Read_size_t(n, stream));
  s_.chlmRfactor_ = (cholmod_factor*)cholmod_malloc(1,
    sizeof(cholmod_factor),common_);
  cholmod_factor& a = *s_.chlmRfactor_;
  a.n = n;
  size_t& nzmax = a.nzmax;
  Ensure(ois.Read_size_t(a.minor,        stream));
  Ensure(ois.Read_size_t(a.nzmax,        stream));
  Ensure(ois.Read(a.itype,        stream));
  Ensure(ois.Read(a.xtype,        stream));
  Ensure(ois.Read(a.dtype,        stream));
  Ensure(ois.Read(a.ordering,     stream));
  Ensure(ois.Read(a.is_ll,        stream));
  Ensure(ois.Read(a.is_super,     stream));
  Ensure(ois.Read(a.is_monotonic, stream));
//allocates common factor vectors
  a.Perm     = cholmod_malloc(n, sizeof(int), common_);
  a.ColCount = cholmod_malloc(n, sizeof(int), common_);
//read common factor vectors
  Ensure(ois.Read(a.Perm,     n, sizeof(int), stream));
  Ensure(ois.Read(a.ColCount, n, sizeof(int), stream));
  if (a.xtype != CHOLMOD_PATTERN && !(a.is_super))
  {
  //Set to zero non used fields
    a.nsuper   = 0;
    a.xsize    = 0;
    a.ssize    = 0;
    a.maxcsize = 0;
    a.maxesize = 0;
    a.super = NULL;
    a.pi    = NULL;
    a.px    = NULL;
    a.s     = NULL;
  //allocate simplicial vectors
    a.p     = cholmod_malloc(  1+n, sizeof(int),    common_);
    a.prev  = cholmod_malloc(  2+n, sizeof(int),    common_);
    a.next  = cholmod_malloc(  2+n, sizeof(int),    common_);
    a.nz    = cholmod_malloc(    n, sizeof(int),    common_);
    a.i     = cholmod_malloc(nzmax, sizeof(int),    common_);
    a.x     = cholmod_malloc(nzmax, sizeof(double), common_);
	//reads the contents of a simplicial numeric factor 
    Ensure(ois.Read(a.p,      1+n, sizeof(int),    stream));
    Ensure(ois.Read(a.prev,   2+n, sizeof(int),    stream));
    Ensure(ois.Read(a.next,   2+n, sizeof(int),    stream));
    Ensure(ois.Read(a.nz,       n, sizeof(int),    stream));
    Ensure(ois.Read(a.i,    nzmax, sizeof(int),    stream));
    Ensure(ois.Read(a.x,    nzmax, sizeof(double), stream));
  }
  else if (a.is_super)
  {
  //Set to zero non used fields
    a.p     = NULL;
    a.prev  = NULL;
    a.next  = NULL;
    a.nz    = NULL;
    a.i     = NULL;
	//reads supernodal dimensions
    Ensure(ois.Read_size_t(a.nsuper,   stream));
    Ensure(ois.Read_size_t(a.xsize,    stream));
    Ensure(ois.Read_size_t(a.ssize,    stream));
    Ensure(ois.Read_size_t(a.maxcsize, stream));
    Ensure(ois.Read_size_t(a.maxesize, stream));
  //allocate supernodal vectors
    a.super = cholmod_malloc(a.nsuper+1, sizeof(int),    common_);
    a.pi    = cholmod_malloc(a.nsuper+1, sizeof(int),    common_);
    a.px    = cholmod_malloc(a.nsuper+1, sizeof(int),    common_);
    a.s     = cholmod_malloc(a.ssize,    sizeof(int),    common_);
    a.x     = cholmod_malloc(a.xsize,    sizeof(double), common_);
	//reads supernodal vectors
    Ensure(ois.Read(a.super, a.nsuper+1, sizeof(int),    stream));
    Ensure(ois.Read(a.pi,    a.nsuper+1, sizeof(int),    stream));
    Ensure(ois.Read(a.px,    a.nsuper+1, sizeof(int),    stream));
    Ensure(ois.Read(a.s,     a.ssize,    sizeof(int),    stream));
    Ensure(ois.Read(a.x,     a.xsize,    sizeof(double), stream));
  }
  a.z = NULL;
  TRACE_CHOLMOD_ALLOCATE("Cholmod.R.Factor",&a);
  if(!cholmod_check_factor(&a,common_))
  {
    Error("Cannot load image OIS of a non valid VMatrix(Cholmod.R.Factor)");
    Delete();
    return(false);
  }
  return(true);
};

////////////////////////////////////////////////////////////////////////////////
  bool BVMat::write_chlmRtriplet(BOisCreator& ois, BStream* stream) const
//Exporting method
////////////////////////////////////////////////////////////////////////////////
{
  cholmod_triplet& a = *s_.chlmRtriplet_;
  if(!cholmod_check_triplet(&a,common_))
  {
    Error("Cannot save image OIS of a non valid VMatrix(Cholmod.R.Triplet)");
    return(false);
  }
  Ensure(ois.Write_size_t(a.nrow,  stream));
  Ensure(ois.Write_size_t(a.ncol,  stream));
  Ensure(ois.Write_size_t(a.nzmax, stream));
  Ensure(ois.Write(a.stype, stream));
  Ensure(ois.Write(a.xtype, stream));
  Ensure(ois.Write_size_t(a.nnz,   stream));
  Ensure(ois.Write(a.itype, stream));
  Ensure(ois.Write(a.dtype, stream));
  Ensure(ois.Write(a.i,     a.nzmax, sizeof(int),    stream));    
  Ensure(ois.Write(a.j,     a.nzmax, sizeof(int),    stream));    
  Ensure(ois.Write(a.x,     a.nzmax, sizeof(double), stream));
  return(true);
};

////////////////////////////////////////////////////////////////////////////////
  bool BVMat::read_chlmRtriplet(BOisLoader& ois, BStream* stream)
//Exporting method
////////////////////////////////////////////////////////////////////////////////
{
  code_ = ESC_chlmRtriplet;
  s_.chlmRtriplet_ = (cholmod_triplet*)cholmod_malloc(1,
    sizeof(cholmod_triplet),common_);
  cholmod_triplet& a = *s_.chlmRtriplet_;
  Ensure(ois.Read_size_t(a.nrow,  stream));
  Ensure(ois.Read_size_t(a.ncol,  stream));
  Ensure(ois.Read_size_t(a.nzmax, stream));
  Ensure(ois.Read(a.stype, stream));
  Ensure(ois.Read(a.xtype, stream));
  Ensure(ois.Read_size_t(a.nnz,   stream));
  Ensure(ois.Read(a.itype, stream));
  Ensure(ois.Read(a.dtype, stream));
  a.i = cholmod_malloc(a.nzmax, sizeof(int),    common_);
  a.j = cholmod_malloc(a.nzmax, sizeof(int),    common_);
  a.x = cholmod_malloc(a.nzmax, sizeof(double), common_);
  Ensure(ois.Read(a.i, a.nzmax, sizeof(int),    stream));    
  Ensure(ois.Read(a.j, a.nzmax, sizeof(int),    stream));    
  Ensure(ois.Read(a.x, a.nzmax, sizeof(double), stream)); 
  a.z = NULL;
  TRACE_CHOLMOD_ALLOCATE("Cholmod.R.Triplet",&a);
  if(!cholmod_check_triplet(&a,common_))
  {
    Error("Cannot load image OIS of a non valid VMatrix(Cholmod.R.Triplet)");
    Delete();
    return(false);
  }
  return(true);
};

////////////////////////////////////////////////////////////////////////////////
  bool BVMat::Write(BOisCreator& ois, BStream* stream) const
//Exporting method
////////////////////////////////////////////////////////////////////////////////
{
  unsigned short code = (unsigned short)code_;
  Ensure(ois.Write(code,stream));
  switch(code_) {
  case(ESC_blasRdense  ) : return(write_blasRdense  (ois,stream)); 
  case(ESC_chlmRsparse ) : return(write_chlmRsparse (ois,stream)); 
  case(ESC_chlmRfactor ) : return(write_chlmRfactor (ois,stream)); 
  case(ESC_chlmRtriplet) : return(write_chlmRtriplet(ois,stream)); 
  default: return(false);}
};

////////////////////////////////////////////////////////////////////////////////
  bool BVMat::Read(BOisLoader& ois, BStream* stream)
//Exporting method
////////////////////////////////////////////////////////////////////////////////
{
  unsigned short code;
  Delete();
  Ensure(ois.Read(code,stream));
  switch(code) {
  case(ESC_blasRdense  ) : return(read_blasRdense  (ois,stream));
  case(ESC_chlmRsparse ) : return(read_chlmRsparse (ois,stream));
  case(ESC_chlmRfactor ) : return(read_chlmRfactor (ois,stream)); 
  case(ESC_chlmRtriplet) : return(read_chlmRtriplet(ois,stream)); 
  default: return(false);}
};


////////////////////////////////////////////////////////////////////////////////
  bool BVMat::Write(const BText& filePath) const
//Exporting method
////////////////////////////////////////////////////////////////////////////////
{
  BText dirPath = GetFilePath(filePath);
  BText fileName = GetFileName(filePath);
  BDirStreamHandler dir;
  if(!dir.Connect(dirPath,BStreamHandler::BSHOM_WRITE,true)) { return(false); }
  BStream* stream = dir.Open(fileName, fileName, -1);
  BOisCreator ois;
  ois.SetControl();
  ois.options_.compressor_.serialization_.engine_ = BOis::BSE_NONE_;
  char* buf = ois.control_.oisEngine_.oisVersion_.Buffer();
  int len = ois.control_.oisEngine_.oisVersion_.Length();
  stream->Write(&len, sizeof(int), 1);
  stream->Write(buf, 1, len+1);
  stream->Write(&ois.control_.machine_.isLittleEndian_, sizeof(bool), 1);
  stream->Write(&ois.options_.compressor_.serialization_.engine_, sizeof(BOis::BSerialEngine), 1);
  stream->Write(&ois.options_.compressor_.serialization_.minSizeCmprs_, sizeof(int), 1);
  stream->Write(&ois.options_.compressor_.serialization_.level_, sizeof(int), 1);
  bool ok = Write(ois,stream);
  stream->Close();
  return(ok);
}

////////////////////////////////////////////////////////////////////////////////
  bool BVMat::Read(const BText& filePath) 
//Exporting method
////////////////////////////////////////////////////////////////////////////////
{
  BText dirPath = GetFilePath(filePath);
  BText fileName = GetFileName(filePath);
  BDirStreamHandler dir;
  if(!dir.Connect(dirPath,BStreamHandler::BSHOM_READ,true)) { return(false); }
  BStream* stream = dir.Open(fileName, fileName, -1);
  BOisLoader ois;
  int len;
  stream->Read(&len, sizeof(int), 1);
  ois.control_.oisEngine_.oisVersion_.PutLength(len);
  stream->Read( ois.control_.oisEngine_.oisVersion_.Buffer(), 1, len+1);
  stream->Read(&ois.control_.machine_.isLittleEndian_, sizeof(bool), 1);
  stream->Read(&ois.options_.compressor_.serialization_.engine_, sizeof(BOis::BSerialEngine), 1);
  stream->Read(&ois.options_.compressor_.serialization_.minSizeCmprs_, sizeof(int), 1);
  stream->Read(&ois.options_.compressor_.serialization_.level_, sizeof(int), 1);
  bool ok = Read(ois,stream);
  stream->Close();
  return(ok);
}
