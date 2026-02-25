/* { dg-do compile } */
/*  {  dg-skip-if  "test is specific to ck803"  { csky-*-* }  { "*" }  { "-mcpu=ck803er*" "-mcpu=ck803efr*" }  }  */
/* { dg-options "" } */

unsigned short a[2];
unsigned short b[]={1,2};
int d=4;
 __simd32_uint16_t *pa = (__simd32_uint16_t*)a, *pb = (__simd32_uint16_t*)b;


int main()
{
*pa=(*pb)>>d;

 return 0;
}

/* { dg-final { scan-assembler "plsr\.u16" } }*/
