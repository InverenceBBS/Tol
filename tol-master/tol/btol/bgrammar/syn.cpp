/* syn.cpp: Member functions of BSyntaxObject.
            GNU/TOL Language.

   Copyright (C) 2003 - Bayes Decision, SL (Spain [EU])

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

#include <tol/tol_bsyntax.h>
#include <tol/tol_btext.h>
#include <tol/tol_bdir.h>
#include <tol/tol_btimer.h>
#include <tol/tol_bgrammar.h>
#include <tol/tol_bsetgra.h>
#include <tol/tol_bcodgra.h>
#include <tol/tol_blanguag.h>
#include <tol/tol_btxtgra.h>
#include <tol/tol_bnameblock.h>

BTraceInit("syn.cpp");

//#define TRACE_MEMORY
#ifdef TRACE_MEMORY
//Allows enabling and disabling of traces
BDat& EnableTraceMemory()
{
  static BDat aux_ = 0;
  return(aux_);
}

//Initializes historic data base of events
static FILE* InitTraceMemHist()
{
  static FILE* traceMemHist = NULL;
  if(traceMemHist) { return(traceMemHist); }
  BText path = BSys::TolAppData()+"syslog/TRACE_MEMORY.log";
  Std(BText("InitTraceMemHist saved at ")+GetAbsolutePath(path)+"\n");
  traceMemHist = fopen(path,"w");
  fprintf(traceMemHist,
  "TRUNCATE TABLE tol_trace_memory.events;\n"
  "INSERT INTO tol_trace_memory.events(address, mode, type, identify,\n"
  "message, level, sourcepath, ishashed, nrefs, aliveobjects)\n"
  "VALUES \n");
  fflush(traceMemHist);
  return(traceMemHist);
}

static FILE* traceMemHist_ = NULL;


#endif


//--------------------------------------------------------------------
// INICIALIZATION
//   Global variables (static in the class BSyntaxObject).
//--------------------------------------------------------------------
#ifdef TRACE_OPTINFO
int    BSyntaxObject::BSynObjOptInfo::count_  = 0;
int    BSyntaxObject::BSynObjOptInfo::countName_  = 0;
int    BSyntaxObject::BSynObjOptInfo::countExpression_  = 0;
int    BSyntaxObject::BSynObjOptInfo::countDescription_  = 0;
double BSyntaxObject::BSynObjOptInfo::kBytes_ = 0.0;
#endif
BInt   BSyntaxObject::nSyntaxObject_ = 0;


static BText tmp_ = "$tmp$";



//--------------------------------------------------------------------
  BText DumpSyntaxObject(BSyntaxObject* obj)
//--------------------------------------------------------------------
{
    return(obj->Dump());
}

//--------------------------------------------------------------------
 BText TOL_API AliveObjInfo()
//--------------------------------------------------------------------
{
//int aliveObjects = BSyntaxObject::NSyntaxObject()-BDeadObject::DeadObjects();
  int aliveObjects = BSyntaxObject::NSyntaxObject();
    return(BText("\n Alive objects:\t")<<aliveObjects<<"\t" << 
                 "Time:\t\""<<BTimer::Text()<<"\"\t");
}

//--------------------------------------------------------------------
static const BText& _CBTextNullRef_()
//--------------------------------------------------------------------
{
  static BText* aux_ = new BText("");
  assert((aux_->Length()==0)&&(aux_->Buffer()[0]=='\0'));
  return(*aux_);
}

//--------------------------------------------------------------------
 const BText& BSyntaxObject::CBTextNullRef() 
//--------------------------------------------------------------------
{
	return(_CBTextNullRef_());
}

//--------------------------------------------------------------------
void BSyntaxObject::TraceMemory(const char* msg) const
//--------------------------------------------------------------------
{

#ifdef TRACE_MEMORY
  static BText beginLine = "(";
  static BText endLine = ")";
  static BText sepField = ",";
  static BText quotes = "'";
  static int numEvent = 0;
  int mode = Mode();
  BBool ok = EnableTraceMemory().Value() && 
             !System() && 
             !IsDeadObj() &&
             (mode!=BIMAGEMODE) &&
             (mode!=BGRAMMARMODE) &&
             (mode!=BFIELDMODE); 
  if(ok)
  {
    int aliveObjects = BSyntaxObject::NSyntaxObject();
    BText type = (!Grammar())?BText("NO_TYPED"):Grammar()->Name();
    BText id = Identify();
    id.Replace('\'','�');
    if(Grammar()) { type = Grammar()->Name(); }

    BText reg = 
    BText((numEvent==0)?"":",\n") +
    beginLine + 
    quotes+"PTR_"+TxtFmt(BInt(this),"%X")+quotes+sepField+
    quotes+ModeName()+quotes+sepField+
    quotes+type+quotes+sepField+
    quotes+id+quotes+sepField+
    quotes+msg+quotes+sepField+
    Level()+sepField+
    quotes+((sourcePath_!=NULL)?sourcePath_->Name():BText("NO_SOURCE_PATH"))+quotes+sepField+
    (int)IsHashed()+sepField+
    NRefs()+sepField+
    aliveObjects+endLine;
    if(!traceMemHist_) { traceMemHist_ = InitTraceMemHist(); }
  //Std(reg);
    fprintf(traceMemHist_,reg.String());
    fflush(traceMemHist_);
    numEvent++;
  }
#endif
}

//--------------------------------------------------------------------
  void BSyntaxObject::InitSynObj(bool isDeadObj)
//--------------------------------------------------------------------
{
  memset(&flags_,0,1);
  flags_.isDeadObj_=isDeadObj;
  sourcePath_  = BSourcePath::Current();
  ems_ = -1;
  nSyntaxObject_ ++;
  PutSystem(!TOLHasBeenInitialized());
  flags_.isConst_= false;
  flags_.isMethod_ = false;
  if(flags_.system_) { IncNRefs(); IncNRefs(); IncNRefs(); }
  TRACE_MEMORY_SHOW(this, "BSyntaxObject::InitSynObj");
}


//! BSyntaxObject constructor
BSyntaxObject::BSyntaxObject(bool isDeadObj)
    : BAtom(), optInfo_(NULL), level_(BGrammar::Level()), oisOffset_(0)
{
    InitSynObj(isDeadObj);
}
BSyntaxObject::BSyntaxObject(const BText& name, bool isDeadObj)
    : BAtom(), optInfo_(NULL), level_(BGrammar::Level()), oisOffset_(0)
{
    PutName(name);
    InitSynObj(isDeadObj);
}
BSyntaxObject::BSyntaxObject(const BText& name, const BText& desc, bool isDeadObj)
    : BAtom(), optInfo_(NULL), level_(BGrammar::Level()), oisOffset_(0)
{
    PutName(name);
    PutDescription(desc);
    InitSynObj(isDeadObj);
}

//--------------------------------------------------------------------
  BSyntaxObject::~BSyntaxObject()
//--------------------------------------------------------------------
{
  TRACE_MEMORY_SHOW(this,"BSyntaxObject::~BSyntaxObject");
# ifdef TRACE_MEMORY
  if(System() && HasName() && !IsDeadObj()) 
  { 
    Error(BText("Attempt to destroy system object ")+Name()); 
  }
# endif
  if(optInfo_) { delete optInfo_; optInfo_ = NULL; }
  nSyntaxObject_ --;
}


//--------------------------------------------------------------------
    BInt BSyntaxObject::IncNRefs()      
//! \a nRefs increase attribute 
//--------------------------------------------------------------------
{
  TRACE_MEMORY_SHOW(this,"BSyntaxObject::IncNRefs");
//if((Name()=="ClassA")||(Name()=="inst_a")||(Name()=="inst_a_")||(Name()=="inst_b"))
//  Std(BText("\nBSyntaxObject::IncNRefs() ")+Name()+" -> "+(NRefs()+1)+"\n");
  return(BAtom::IncNRefs()); 
}

//--------------------------------------------------------------------
    BInt BSyntaxObject::DecNRefs()      
//! \a nRefs decrease attribute
//--------------------------------------------------------------------
{ 
  TRACE_MEMORY_SHOW(this,"BSyntaxObject::DecNRefs");
  if(System() && (BAtom::NRefs() == 1)) 
  { 
#  ifdef TRACE_MEMORY
    if(HasName() && !IsDeadObj()) 
    { 
      Error(BText("Attempt to decrease NRefs for system object ")+Name()); 
    }
#  endif
    return(1); 
  }
  else               
  { 
  //if((Name()=="ClassA")||(Name()=="inst_a")||(Name()=="inst_a_")||(Name()=="inst_b"))
  //  Std(BText("\nBSyntaxObject::DecNRefs() ")+Name()+" -> "+(NRefs()-1)+"\n");
    return(BAtom::DecNRefs()); 
  }
}
   

//--------------------------------------------------------------------
  const BSetFromFile* BSyntaxObject::Source() const
/*! Returns its owner file
 */
//--------------------------------------------------------------------
{
  TRACE_MEMORY_SHOW(this,"BSyntaxObject::Source");
  if(!sourcePath_) { return(NULL); }
  else             { return(sourcePath_->Set()); }
}

//--------------------------------------------------------------------
  const BSetFromFile* BSyntaxObject::GlobalSource() const
//--------------------------------------------------------------------
{
  const BSetFromFile* source = Source();
  if(source) 
  {
    if(source->Level()>0)
    {
      source = source->GlobalSource();
    }
  }
  return(source);
};

//--------------------------------------------------------------------
    const BText& BSyntaxObject::SourcePath() const
/*! Returns the path of its owner file
 */
//--------------------------------------------------------------------
{
  TRACE_MEMORY_SHOW(this,"BSyntaxObject::SourcePath");
  if(sourcePath_ && BSourcePath::IsAlive(sourcePath_))
  {
    return(sourcePath_->Name()); 
  }
  else if(System() && Mode()==BBUILTINFUNMODE)
  {
    BOperator* opr = (BOperator*)this;
    return(opr->CppFile());
  }
  else if(System() && (Mode()==BOBJECTMODE) && (Grammar()==GraCode()))
  {
    BUserCode* uCode = (BUserCode*)this;
    BOperator* opr = uCode->Contens().Operator();
    if(opr)
    {
      return(opr->CppFile());
    }
    else
    {
      return(BSyntaxObject::CBTextNullRef());
    }
  }
  else
  {
    return(BSyntaxObject::CBTextNullRef());
  }
}

//--------------------------------------------------------------------
  const BSourcePath* BSyntaxObject::GetSourcePath   () const 
//--------------------------------------------------------------------
{ 
  TRACE_MEMORY_SHOW(this,"BSyntaxObject::GetSourcePath");
  return((BSourcePath::IsAlive(sourcePath_))?sourcePath_:NULL); 
}


//--------------------------------------------------------------------
  const char* GetModeName(int mode)
//--------------------------------------------------------------------
{ 
  static const char* modeName_ [12] =
  {
    "NOMODE\0",
    "IMAGEMODE\0",
    "OBJECTMODE\0",
    "BUILTINFUNMODE\0",
    "GRAMMARMODE\0",
    "FIELDMODE\0",
    "STRUCTMODE\0",
    "METHODMODE\0",
    "CLASSMODE\0",
    "DATABASEMODE\0",
    "USERFUNMODE\0"
    "BSOURCEPATHMODE\0"
  };
  return(modeName_[mode]);
}

//--------------------------------------------------------------------
  const char* BSyntaxObject::ModeName    () const
//--------------------------------------------------------------------
{ 
  return(GetModeName(Mode()));
}


//--------------------------------------------------------------------
const BText& BSyntaxObject::Identify() const

/*! Returns a text terse-description of the object.
 */
//--------------------------------------------------------------------
{
       if(Name       ().HasName()) { return(Name       ()); }
  else if(Expression ().HasName()) { return(Expression ()); }
  else if(LocalName  ().HasName()) { return(LocalName  ()); }
  else if(Description().HasName()) { return(Description()); }
  else                             { return(tmp_); }
}

//--------------------------------------------------------------------
const BText& BSyntaxObject::Description() const 
//--------------------------------------------------------------------
{ 
  if(optInfo_ && optInfo_->description_.HasName())
  {
    return(optInfo_->description_); 
  }
#ifndef TRACE_MEMORY
  else if((Mode()==BOBJECTMODE) && (Grammar()==GraNameBlock()))
  {
    BUserNameBlock* uns = UNameBlock((BSyntaxObject*)this);
    BNameBlock& ns = uns->Contens();
    BSyntaxObject* autodoc = ns.Member("_.autodoc.description");
    if(autodoc && autodoc->Grammar()==GraText())
    {
      BText& desc = Text(autodoc);
      uns->PutDescription(desc);
      return(optInfo_->description_);
    }
    return(CBTextNullRef());
  }
#endif
  return(CBTextNullRef());
}

//--------------------------------------------------------------------
  void BSyntaxObject::PutNameBlock(const BNameBlock* nameBlock)
//--------------------------------------------------------------------
{ 
  if(!optInfo_) 
  { 
    optInfo_ = new BSynObjOptInfo; 
  }
//if(!optInfo_->nameBlock_)
  { 
    optInfo_->nameBlock_ = nameBlock;
  }
}

//--------------------------------------------------------------------
  BText BSyntaxObject::FullName() const

/*! Returns a text terse-description of the object.
 */
//--------------------------------------------------------------------
{
  const BNameBlock* nb = NameBlock();
  if(nb && nb->EnsureIsAssigned() && nb->HasName())
  {
    return(nb->Name()+"::"+Name());
  }
  else
  {
    return(Name());
  }
}


//--------------------------------------------------------------------
  BText BSyntaxObject::LexInfo() const
//! Returns the standard declaration expression of an object  
//--------------------------------------------------------------------
{
  if(Mode()==BSTRUCTMODE)
  {
    return(Dump());
  }
  else if((Grammar()==GraCode()) && (Mode()==BOBJECTMODE))
  {
    BUserCode* uCode = UCode((BSyntaxObject*)this);
    BOperator* opr   = GetOperator(uCode);
    assert(opr);
    return(BText("Code (")+opr->Grammar()->Name()+" "+FullName()+opr->Arguments()+")");
  }
  else if((Mode()==BBUILTINFUNMODE)||(Mode()==BUSERFUNMODE))
  {
    BOperator* opr = (BOperator*)this;
    return(opr->Grammar()->Name()+" "+FullName()+opr->Arguments());
  }
  else if(Mode()==BOBJECTMODE)
  {
    return(Grammar()->Name()+" "+FullName());
  }
  else
  {
    return(BText(ModeName())+" "+FullName());
  }
}


//--------------------------------------------------------------------
union BIntPointerMask
//--------------------------------------------------------------------
{
  BIntPair                    pair_;
  const BSyntaxObject*        obj_;
  const BGrammar*             gra_;
#if (__USE_POOL__==__POOL_BFSMEM__)
  const BFixedSizeMemoryBase* mhn_;
#endif
};


//--------------------------------------------------------------------
  BSyntaxObject* BSyntaxObject::GetObjectFromAddress(const BText& address)
//--------------------------------------------------------------------
{
  const BSyntaxObject* obj = NULL;
  BIntPointerMask objMask, graMask, mhnMask;
  int mode;
  int size;
  int pageNum;
  sscanf(address.String(), "%X:%X:%X:%X:%X:%X:%X:%X:%X",
    &objMask.pair_.r_,
    &objMask.pair_.c_,
    &graMask.pair_.r_,
    &graMask.pair_.c_,
    &mhnMask.pair_.r_,
    &mhnMask.pair_.c_,
    &mode,
    &size,
    &pageNum);
  if( objMask.obj_ &&
      (pageNum >= 0) && (pageNum <= 65535) && 
      (mode >= 1) && (mode < BLASTMODE) && 
      (size >= 1) && (sizeof(objMask.obj_) == size))
  {
    if(
     (objMask.obj_->GetPageNum() == pageNum) &&
     (objMask.obj_->Grammar() == graMask.gra_) &&
     (objMask.obj_->Mode() == mode) &&
#if (__USE_POOL__==__POOL_BFSMEM__)
     (objMask.obj_->GetMemHandler() == mhnMask.mhn_)&&
#endif
     (objMask.obj_->IsAssigned()!=0))
    {
      obj = objMask.obj_;
    }
  }
  return((BSyntaxObject*)obj);
}

//--------------------------------------------------------------------
  BText BSyntaxObject::GetAddressFromObject() const
//--------------------------------------------------------------------
{
  static char address[7*32];
  BIntPointerMask objMask, graMask, mhnMask;
  objMask.pair_.r_ = 0;
  objMask.pair_.c_ = 0;
  graMask.pair_.r_ = 0;
  graMask.pair_.c_ = 0;
  mhnMask.pair_.r_ = 0;
  mhnMask.pair_.c_ = 0;
  objMask.obj_ = this;
  graMask.gra_ = Grammar();
#if (__USE_POOL__==__POOL_BFSMEM__)
  mhnMask.mhn_ = GetMemHandler();
#endif
  int mode = Mode();
  int size = sizeof(this);
  int pageNum = GetPageNum();
  sprintf(address, "%X:%X:%X:%X:%X:%X:%X:%X:%X",
    objMask.pair_.r_,
    objMask.pair_.c_,
    graMask.pair_.r_,
    graMask.pair_.c_,
    mhnMask.pair_.r_,
    mhnMask.pair_.c_,
    mode,
    size,
    pageNum);
  return(BText(address));
}

