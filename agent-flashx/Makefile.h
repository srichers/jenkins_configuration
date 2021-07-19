# FLASH makefile definitions for x86-64 Linux (GNU compilers)
#----------------------------------------------------------------------------
# Set the HDF5/MPI library paths -- these need to be updated for your system
#----------------------------------------------------------------------------

#MPI_PATH   = /usr/local/mpich2/
HDF4_PATH  =
#HDF5_PATH  = /usr/local/hdf5
#HYPRE_PATH = /usr/local/hypre

ZLIB_PATH  =

PAPI_PATH  =
PAPI_FLAGS =

#NCMPI_PATH = /usr/local/netcdf
MPE_PATH   =

#----------------------------------------------------------------------------
# Compiler and linker commands
#
#   Use the MPICH wrappers around the compilers -- these will automatically
#   load the proper libraries and include files.  Version of MPICH prior
#   to 1.2.2 (?) do not recognize .F90 as a valid Fortran file extension.
#   You need to edit mpif90 and add .F90 to the test of filename extensions,
#   or upgrade your MPICH.
#----------------------------------------------------------------------------

FCOMP   = mpif90
CCOMP   = mpicc
CPPCOMP = mpicxx
LINK    = mpif90

# pre-processor flag
PP      = -D

#----------------------------------------------------------------------------
# Compilation flags
#
#  Three sets of compilation/linking flags are defined: one for optimized
#  code, one for testing, and one for debugging.  The default is to use the
#  _OPT version.  Specifying -debug to setup will pick the _DEBUG version,
#  these should enable bounds checking.  Specifying _TEST is used for
#  flash_test, and is set for quick code generation, and (sometimes)
#  profiling.  The Makefile generated by setup will assign the generic token
#  (ex. FFLAGS) to the proper set of flags (ex. FFLAGS_OPT).
#----------------------------------------------------------------------------

OPENMP = -fopenmp

FFLAGS_OPT = -ggdb -c -O2 -fdefault-real-8 -fdefault-double-8 \
-Wuninitialized

#I explictly add -O0 because I found that compiling source files without
#an optimization flag generates the same object code as compiling source
#files with -O2.  The -O0 is required so that gdb no longer shows
#"<value optimized out>" for certain function arguments.

FFLAGS_DEBUG = -ggdb -c -O0 -fdefault-real-8 -fdefault-double-8 \
-pedantic -Wall -Waliasing \
-Wsurprising -Wconversion -Wunderflow \
-ffpe-trap=invalid,zero,overflow -fbounds-check \
-fimplicit-none -fstack-protector-all

FFLAGS_TEST = -ggdb -c -O0 -fdefault-real-8 -fdefault-double-8

FFLAGS_HYPRE = -I${HYPRE_PATH}/include


F90FLAGS = -I/usr/include/hdf5/serial/ -ffree-line-length-none


#The macro _FORTIFY_SOURCE adds some lightweight checks for buffer
#overflows at both compile time and run time (only active at -O1 or higher)
#http://gcc.gnu.org/ml/gcc-patches/2004-09/msg02055.html
CFLAGS_OPT = -ggdb -c -O2 -Wuninitialized -D_FORTIFY_SOURCE=2

CFLAGS_DEBUG = -ggdb -c -O0 -Wno-div-by-zero -Wundef \
-Wconversion -Wstrict-prototypes -Wunreachable-code \
-pedantic -Wall -Winit-self -ftree-vrp -Wfloat-equal \
-Wunsafe-loop-optimizations -Wpadded -fstack-protector-all

CFLAGS_TEST = -ggdb -O0 -c

CFLAGS_HYPRE = -I${HYPRE_PATH}/include

# if we are using HDF5, we need to specify the path to the include files
CFLAGS_HDF5 = -I/usr/include/hdf5/serial -DH5_USE_16_API
CFLAGS_NCMPI = -I${NCMPI_PATH}/include

#----------------------------------------------------------------------------
# Linker flags
#
#  There is a seperate version of the linker flags for each of the _OPT,
#  _DEBUG, and _TEST cases.
#----------------------------------------------------------------------------

LFLAGS_OPT   = -ggdb -o
LFLAGS_DEBUG = -ggdb -O0 -o
LFLAGS_TEST  = -ggdb -O0 -o


#----------------------------------------------------------------------------
# Library specific linking
#
#  If a FLASH module has a 'LIBRARY xxx' line in its Config file, we need to
#  create a macro in this Makefile.h for LIB_xxx, which will be added to the
#  link line when FLASH is built.  This allows us to switch between different
#  (incompatible) libraries.  We also create a _OPT, _DEBUG, and _TEST
#  library macro to add any performance-minded libraries (like fast math),
#  depending on how FLASH was setup.
#----------------------------------------------------------------------------

LIB_OPT   =
LIB_DEBUG =
LIB_TEST  =

LIB_HDF4  =
LIB_HDF5  = -L/usr/lib/x86_64-linux-gnu/hdf5/serial -lhdf5 -lz -lhdf5_fortran

LIB_PAPI  =
LIB_MATH  =

LIB_MPI   =
LIB_NCMPI = -L ${NCMPI_PATH}/lib -lpnetcdf
LIB_MPE   =

LIB_HYPRE = -L${HYPRE_PATH}/lib -lHYPRE

# Uncomment the following line to use electic fence memory debugger.
# export EF_ALLOW_MALLOC_0=1
#CONFIG_LIB = -L/usr/lib64 -lefence

#----------------------------------------------------------------------------
# Additional machine-dependent object files
#
#  Add any machine specific files here -- they will be compiled and linked
#  when FLASH is built.
#----------------------------------------------------------------------------

MACHOBJ =

#----------------------------------------------------------------------------
# Additional commands
#----------------------------------------------------------------------------

MV = mv -f
AR = ar -r
RM = rm -f
CD = cd
RL = ranlib
ECHO = echo


#----------------------------------------------------------------------------
# Fake existence of iso_c_bindings module to prevent unnecessary recompilations.
#---------------------------------------------------------------------------- 
ifeq ($(FLASHBINARY),true)
iso_c_binding.mod :
	touch $@
endif
