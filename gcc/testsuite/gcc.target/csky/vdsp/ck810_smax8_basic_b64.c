/* { dg-do compile } */
/*  {  dg-skip-if  "test is specific to ck810"  { csky-*-* }  { "*" }  { "-mcpu=ck810*v*"  }  }  */
/* { dg-options " -mvdsp-width=64  -O1 -ftree-loop-vectorize" } */

signed char a[8];
signed char b[8]={1,2,3,4};
signed char c[8]={2,3,4,5};
int i;

int func()
{
 for(i=0;i<8;i++)
 if(c[i]>b[i])
   a[i]=c[i];
 else
   a[i]=b[i];
}

/* { dg-final { scan-assembler "vmax\.s8" } }*/
