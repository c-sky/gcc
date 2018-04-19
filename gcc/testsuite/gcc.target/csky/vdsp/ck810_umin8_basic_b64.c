/* { dg-do compile } */
/* {  dg-skip-if  "test is specific to ck810"  { csky-*-* }  { "*" }  { "-mcpu=ck810*v*"  }  }  */
/* { dg-options " -mvdsp-width=64  -O1 -ftree-loop-vectorize" } */

char a[8];
char b[8]={1,2,3,4};
char c[8]={2,3,4,5};
int i;

int func()
{
 for(i=0;i<8;i++)
 if(c[i]<b[i])
   a[i]=c[i];
 else
   a[i]=b[i];
}

/* { dg-final { scan-assembler "vmin\.u8" } }*/
