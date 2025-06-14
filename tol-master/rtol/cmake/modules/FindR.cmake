
#
# - This module locates an installed R distribution.
#
# Defines the following:
#  R_COMMAND           - Path to R command
#  Rscript_COMMAND     - Path to Rscript command
#  R_HOME              - Path to 'R home', as reported by R
#  R_INCLUDE_DIR       - Path to R include directory
#  R_LIBRARY_BASE      - Path to R library
#  R_LIBRARY_BLAS      - Path to Rblas / blas library
#  R_LIBRARY_LAPACK    - Path to Rlapack / lapack library
#  R_LIBRARY_READLINE  - Path to readline library
#  R_LIBRARIES         - Array of: R_LIBRARY_BASE, R_LIBRARY_BLAS, R_LIBRARY_LAPACK, R_LIBRARY_BASE [, R_LIBRARY_READLINE]
#
#  VTK_R_HOME          - (deprecated, use R_HOME instead) Path to 'R home', as reported by R
#
# Variable search order:
#   1. Attempt to locate and set R_COMMAND
#     - If unsuccessful, generate error and prompt user to manually set R_COMMAND
#   2. Use R_COMMAND to set R_HOME
#   3. Locate other libraries in the priority:
#     1. Within a user-built instance of R at R_HOME
#     2. Within an installed instance of R
#     3. Within external system libraries
#

set(TEMP_CMAKE_FIND_APPBUNDLE ${CMAKE_FIND_APPBUNDLE})
set(CMAKE_FIND_APPBUNDLE "NEVER")
find_program(R_COMMAND R DOC "R executable.")
find_program(Rscript_COMMAND Rscript DOC "Rscript executable.")
set(CMAKE_FIND_APPBUNDLE ${TEMP_CMAKE_FIND_APPBUNDLE})

if(R_COMMAND)
  execute_process(WORKING_DIRECTORY .
                  COMMAND ${R_COMMAND} RHOME
                  OUTPUT_VARIABLE R_ROOT_DIR
                  OUTPUT_STRIP_TRAILING_WHITESPACE)
  # deprecated
  if(VTK_R_HOME)
    set(R_HOME ${VTK_R_HOME} CACHE PATH "R home directory obtained from R RHOME")
  else(VTK_R_HOME)
    set(R_HOME ${R_ROOT_DIR} CACHE PATH "R home directory obtained from R RHOME")
    set(VTK_R_HOME ${R_HOME})
  endif(VTK_R_HOME)
  # /deprecated
  # the following command does nothing currently, but will be used when deprecated code is removed
  set(R_HOME ${R_ROOT_DIR} CACHE PATH "R home directory obtained from R RHOME")

  if( WIN32 )
    find_path( R_INCLUDE_DIR R.h
      PATHS ${R_ROOT_DIR}
      PATH_SUFFIXES include R/include
      DOC "Path to file R.h"
      NO_DEFAULT_PATH )

    if( CMAKE_SIZEOF_VOID_P EQUAL 4 )
      set( path_suffix "i386" )
    else( CMAKE_SIZEOF_VOID_P EQUAL 4 )
      set( path_suffix "x64" )
    endif( CMAKE_SIZEOF_VOID_P EQUAL 4 )

    find_library(R_LIBRARY_BASE R
      PATHS ${R_ROOT_DIR}/bin
      PATH_SUFFIXES ${path_suffix}
      DOC "R library (example libR.a, libR.dylib, etc.)."
      NO_DEFAULT_PATH )

    find_library(R_LIBRARY_BLAS NAMES Rblas blas
      PATHS ${R_ROOT_DIR}/bin
      PATH_SUFFIXES ${path_suffix}
      DOC "Rblas library (example libRblas.a, libRblas.dylib, etc.)."
      NO_DEFAULT_PATH )

    find_library(R_LIBRARY_LAPACK NAMES Rlapack lapack
      PATHS ${R_ROOT_DIR}/bin
      PATH_SUFFIXES ${path_suffix}
      DOC "Rlapack library (example libRlapack.a, libRlapack.dylib, etc.)."
      NO_DEFAULT_PATH )
  else( WIN32 )
    execute_process( COMMAND ${R_COMMAND} CMD config --cppflags
      OUTPUT_VARIABLE R_CPPFLAGS OUTPUT_STRIP_TRAILING_WHITESPACE)
    if ( ${R_CPPFLAGS} MATCHES "[-][I]([^ ;])+" )
      string( SUBSTRING ${CMAKE_MATCH_0} 2 -1 _INCL )
      set( R_INCL_DIR ${_INCL} )
      message( STATUS "R_INCL_DIR = ${RCPP_INCL_DIR}" )
    endif( )

    find_path( R_INCLUDE_DIR R.h
      PATHS ${R_INCL_DIR}
      DOC "Path to file R.h" )

    find_library(R_LIBRARY_BASE R
      HINTS ${R_ROOT_DIR}/lib
      DOC "R library (example libR.a, libR.dylib, etc.).")

    find_library(R_LIBRARY_BLAS NAMES Rblas blas
      HINTS ${R_ROOT_DIR}/lib
      DOC "Rblas library (example libRblas.a, libRblas.dylib, etc.).")

    find_library(R_LIBRARY_LAPACK NAMES Rlapack lapack
      HINTS ${R_ROOT_DIR}/lib
      DOC "Rlapack library (example libRlapack.a, libRlapack.dylib, etc.).")
  endif( WIN32 )

  find_library(R_LIBRARY_READLINE readline
    DOC "(Optional) system readline library. Only required if the R libraries were built with readline support.")

else(R_COMMAND)
  message(SEND_ERROR "FindR.cmake requires the following variables to be set: R_COMMAND")
endif(R_COMMAND)

# Note: R_LIBRARY_BASE is added to R_LIBRARIES twice; this may be due to circular linking dependencies; needs further investigation
set(R_LIBRARIES ${R_LIBRARY_BASE} ${R_LIBRARY_BLAS} ${R_LIBRARY_LAPACK} ${R_LIBRARY_BASE})
if(R_LIBRARY_READLINE)
  set(R_LIBRARIES ${R_LIBRARIES} ${R_LIBRARY_READLINE})
endif(R_LIBRARY_READLINE)
