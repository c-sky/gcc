/* { dg-do compile } */
/*  {  dg-skip-if  "test is specific to ck803"  { csky-*-* }  { "*" }  { "-mcpu=ck803er*" "-mcpu=ck803efr*" }  }  */
/* { dg-options "" } */

short a[2];
short b[]={1,2};

__simd32_int16_t *pa = (__simd32_int16_t*)a, *pb = (__simd32_int16_t*)b;


int main()
{
*pa=(*pb)<<4;

 return 0;
}

/* { dg-final { scan-assembler "plsli\.16" } }*/
