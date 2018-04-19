/* { dg-do compile } */
/*  {  dg-skip-if  "test is specific to ck810"  { csky-*-* }  { "*" }  { "-mcpu=ck810*v*"  }  }  */
/* { dg-options " -mvdsp-width=64  -O1 -ftree-loop-vectorize" } */

int a[2];
int b[2]={1,2};
int c[2]={0,7};
int i;

int func()
{
  for (i=0;i<2;i++)
   a[i]= b[i]<c[i] ? b[i] : c[i];
}

/* { dg-final { scan-assembler "vmin\.s32" } }*/
