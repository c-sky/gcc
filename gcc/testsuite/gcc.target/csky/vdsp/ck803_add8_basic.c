/* { dg-do compile } */
/*  {  dg-skip-if  "test is specific to ck803"  { csky-*-* }  { "*" }  { "-mcpu=ck803er*" "-mcpu=ck803efr*" }  }  */
/* { dg-options "" } */

char a[4];
char b[]={1,2,3,4};
char c[]={0,1,2,3};


 __simd32_int8_t *pa = (__simd32_int8_t*)a, *pb = (__simd32_int8_t*)b, *pc = (__simd32_int8_t*)c;

int main()
{
*pa=*pb+*pc;

 return 0;
}

/* { dg-final { scan-assembler "padd\.8" } }*/
