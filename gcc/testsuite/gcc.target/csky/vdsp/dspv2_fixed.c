/* { dg-do compile } */
/*  {  dg-skip-if  "test is specific to ck803"  { csky-*-* }  { "*" }  { "-mcpu=ck803er*" "-mcpu=ck803efr*" }  }  */
/* { dg-options "" } */

long _Sat _Fract addss (long _Sat _Fract a, long _Sat _Fract b)
{
  return a + b;
}

/* { dg-final { scan-assembler "add\.s32\.s" } }*/

unsigned long _Sat _Fract addsu (unsigned long _Sat _Fract a, unsigned long _Sat _Fract b)
{
  return a + b;
}

/* { dg-final { scan-assembler "add\.u32\.s" } }*/

long _Sat _Fract subss (long _Sat _Fract a, long _Sat _Fract b)
{
  return a - b;
}

/* { dg-final { scan-assembler "sub\.s32\.s" } }*/

unsigned long _Sat _Fract subsu (unsigned long _Sat _Fract a, unsigned long _Sat _Fract b)
{
  return a - b;
}

/* { dg-final { scan-assembler "sub\.u32\.s" } }*/


long long _Sat _Fract addssl (long long _Sat _Fract a, long long _Sat _Fract b)
{
  return a + b;
}

/* { dg-final { scan-assembler "add\.s64\.s" } }*/

unsigned long long _Sat _Fract addsul (unsigned long long _Sat _Fract a, unsigned long long _Sat _Fract b)
{
  return a + b;
}

/* { dg-final { scan-assembler "add\.u64\.s" } }*/

long long _Sat _Fract subssl (long long _Sat _Fract a, long long _Sat _Fract b)
{
  return a - b;
}

/* { dg-final { scan-assembler "sub\.s64\.s" } }*/

unsigned long long _Sat _Fract subsul (unsigned long long _Sat _Fract a, unsigned long long _Sat _Fract b)
{
  return a - b;
}

/* { dg-final { scan-assembler "sub\.u64\.s" } }*/



long _Sat _Fract negs (long _Sat _Fract a)
{
  return -a;
}

/* { dg-final { scan-assembler "neg\.s32\.s" } }*/
