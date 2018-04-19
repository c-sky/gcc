/* Check that certain preprocessor macros are defined, and do some
   consistency checks.  */
/* { dg-do compile } */


#if defined (__csky_hard_float__) == defined (__csky_soft_float__)
#error __csky_hard_float__ / __csky_soft_float__ mismatch
#endif

#if defined (__CSKYLE__) == defined (__CSKYBE__)
#error __CSKYLE__ / __CSKYBE__ mismatch
#endif
int i;
