/* { dg-do compile } */
/*  {  dg-skip-if  "test is specific to the instruction v2"  { csky-*-* }  { "-march=*" }  { "-march=ck8*"  }  }  */
/* { dg-final { scan-assembler "\[ |\t\]cmplt\[ |\t\]\[^\n\]*\n\[ |\t\]mvc\[ |\t\]" } } */

int storecc(int a,int b)
{
	return (a < b);
}
