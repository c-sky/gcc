/* { dg-do compile } */
/*  {  dg-skip-if  "test is specific to ck803"  { csky-*-* }  { "*" }  { "-mcpu=ck803er*" "-mcpu=ck803efr*" }  }  */
/* { dg-options "" } */

short a[2];
short b[]={1,2};
short c[]={0,1};


 __simd32_int16_t *pa = (__simd32_int16_t*)a, *pb = (__simd32_int16_t*)b, *pc = (__simd32_int16_t*)c;

int main()
{
*pa=*pb-*pc;

 return 0;
}
/* { dg-final { scan-assembler "psub\.16" } }*/
