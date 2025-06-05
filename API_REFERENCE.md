# TOL API Manual

## Table of Contents
- [Installation](#installation)
- [User API Documentation](#user-api-documentation)
  - [BCTime](#bctime)
  - [BMatrixGen](#bmatrixgen)
  - [Monte Carlo Integrator](#monte-carlo-integrator)
  - [BCTimeSet](#bctimeset)
  - [BSet](#bset)
  - [Gibbs Sampler](#gibbs-sampler)
- [Developer API Documentation](#developer-api-documentation)
  - [BCTime Internals](#bctime-internals)
  - [Matrix Utilities](#matrix-utilities)
  - [Monte Carlo Classes](#monte-carlo-classes)
  - [Gibbs Sampler Internals](#gibbs-sampler-internals)

  - [Parser Overview](#parser-overview)
  - [TolTcl Binding](#toltcl-binding)
  - [TolSH Shell](#tolsh-shell)
  - [RTOL R Binding](#rtol-r-binding)
  - [TolJava Binding](#toljava-binding)
---

## Installation

TOL follows the standard GNU installation procedure. A typical build on Unix looks like:

```bash
./configure --with-gsl=/path/to/gsl \
            --with-cblas=/path/to/cblas \
            --with-cholmod=/path/to/cholmod
make
sudo make install
```

Additional configuration options are described in the `INSTALL` file.

---

## User API Documentation

### BCTime
Represents a calendar time with configurable granularity.

```cpp
BCTime();
BCTime(long int year, int month=0, int day=0,
       int hour=-1, int minute=-1, int second=-1);
```

**Parameters**
- `year` (long, required) – Year component.
- `month` (int, optional) – Month (1–12).
- `day` (int, optional) – Day of month.
- `hour` (int, optional) – Hour of day.
- `minute` (int, optional) – Minute of hour.
- `second` (int, optional) – Second of minute.

**Returns**
- Instance of `BCTime` representing the specified date and time.

**Example**
```cpp
BCTime date(2024, 4, 1); // 1 April 2024
```

**Notes**
- Use `BCTime::Now()` to create an object with the current time.

### BMatrixGen
Generic matrix container supporting arbitrary element types.

```cpp
template <class Any> class BMatrixGen {
  BMatrixGen();
  BMatrixGen(BInt rows, BInt cols, const Any* buffer=NIL);
  Any& operator()(BInt i, BInt j);
  BInt Rows() const;
  BInt Columns() const;
};
```

**Parameters (constructor)**
- `rows` (BInt) – Number of rows.
- `cols` (BInt) – Number of columns.
- `buffer` (pointer, optional) – Optional initialization data.

**Example**
```cpp
BMatrixGen<double> m(2, 2);
m(0,0) = 1.0;
m(1,1) = 2.0;
```

### Monte Carlo Integrator
Implements numeric integration using the Plain, MISER, and VEGAS methods.

```cpp
Set MonteCarloPlain(Code function, Real dim, Matrix xlower, Matrix xupper,
                    [Real calls=100000]);
```

**Parameters**
- `function` – User function returning a `Real` given a `Matrix` argument.
- `dim` – Dimensionality of the integration domain.
- `xlower`, `xupper` – Column matrices defining the integration volume.
- `calls` – (optional) Number of function evaluations (default `100000`).

**Example**
```tol
Real UserFunc(Matrix X) {
    Real d = Rows(X);
    Real A = 1 / Pi ^ d;
    A / (1.0 - MatProd(Cos(X)))
};
Set result = MonteCarloPlain(UserFunc, 3, Col(0,0,0), Col(Pi,Pi,Pi), 100000);
```

### BCTimeSet
Represents a collection of calendar instants with a shared granularity.

```cpp
class BCTimeSet {
public:
    bool includes(const BCTime& t) const;
    BCTime succ(const BCTime& t);
    BCTime pred(const BCTime& t);
};
```

**Example**
```cpp
BCTimeSet holidays;
if (holidays.includes(date)) {
    // date is a holiday
}
```

### BSet
Container for heterogeneous objects indexed by name or position.

```cpp
class BSet {
public:
    BSyntaxObject* operator[](BInt index) const;
    BSyntaxObject* operator[](const char* name) const;
    BInt Card() const;
};
```

**Example**
```cpp
BSet params;
params.AddElement(code);
BSyntaxObject* first = params[1];
```

### Gibbs Sampler
Tools for performing Gibbs sampling with customizable conditional densities.

Key class excerpt (from `gibbssampler.cpp`):
```cpp
class FullConditional : public RealGSLFunctionR1 {
  static FullConditional* New(BSet* args, BUserMat* condpar);
  virtual double Sample() = 0;
  virtual double Sample() = 0;
};
```

Usage involves deriving specialized conditionals and invoking `Sample()`
within a Gibbs sampling loop.

---

## Developer API Documentation

### BCTime Internals
Private helper functions provide conversion utilities and boundary checks.
Example (simplified):
```cpp
struct caltime caltime() const {
    int wd, yd;
    struct caltime ct;
    struct tai t = tai_;
    caltime_utc(&ct, &t, &wd, &yd);
    return ct;
}
```

### Matrix Utilities
Sparse matrix updates are available through inline templates
(`tol_bsparse.h`):
```cpp
template<class Any>
void ShermanMorrison(BMatrix<Any>& B,
                     const BMatrix<Any>& u,
                     const BMatrix<Any>& v);
```
These routines update matrix inverses efficiently.

### Monte Carlo Classes
The `mc-integrator.cpp` module defines classes
`BMonteCarloPlain`, `BMonteCarloMiser`, and `BMonteCarloVegas`.
Each class implements `DoMonteCarlo()` to interface with
corresponding GSL integrators.

### Gibbs Sampler Internals
`gibbssampler.cpp` provides base classes for building Gibbs samplers.
Important members include:
```cpp
BUserMat* ConditionalParameters();
BUserDat* PreviousSampleDat();
```
which give access to shared parameter matrices and previous samples.

### Parser Overview
High level C++ parser for the TOL language. The `bparser` module handles scanning and parsing of TOL source code. Key components include `tol_bscanner.h` for tokenization and `tol_bparser.h` for syntax analysis.

### TolTcl Binding
C and C++ library that exposes TOL functionality as Tcl commands. Applications embed it via `Toltcl_Init()` and then call `tol::<cmd>` procedures.

### TolSH Shell
Interactive Tcl/Tk shell packaged with Starkit. It provides command history and executes `.tol` scripts through the embedded interpreter.

### RTOL R Binding
C++ extension for the R language. Functions like `tol.eval()` run TOL code and exchange matrices or series with R vectors.

### TolJava Binding
Java and JNI layers for executing TOL from Java programs. Classes such as `TolInterpreter` wrap native calls implemented in `toljavajni.cpp`.

---

## Notes
- The documentation intentionally omits Windows-specific build and
  runtime details.
- Many modules use extensive templates; template parameter types are
  preserved from the original headers.

