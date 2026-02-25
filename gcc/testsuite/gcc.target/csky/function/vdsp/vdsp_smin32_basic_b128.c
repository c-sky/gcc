/* { dg-do compile } */
/*  {  dg-skip-if  "test is specific to ck810"  { csky-*-* }  { "*" }  { "-mcpu=ck810*v*"  }  }  */
/* { dg-options " -mvdsp-width=128  -O1 -ftree-loop-vectorize" } */

int a[4];
int b[4]={1,2,3,4};
int c[4]={0,7,6,3};
int i;

int func()
{
  for (i=0;i<4;i++)
   a[i]= b[i]<c[i] ? b[i] : c[i];
}

/* { dg-final { scan-assembler "vmin\.s32" } }*/
