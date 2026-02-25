/* { dg-do compile } */
/*  {  dg-skip-if  "test is specific to the instruction v1"  { csky-*-* }  { "-march=*" }  { "-march=ck\[56\]*"  }  }  */
/* { dg-options "-O2 " } */
/* { dg-final { scan-assembler-times "\tcmpne\t" 1 } }*/
/* { dg-final { scan-assembler "\tcmpnei\t.*\[^\n\]*, 0" } }*/
/* { dg-final { scan-assembler "\tcmpnei\t.*\[^\n\]*, 31" } }*/
/* { dg-final { scan-assembler-times "\tcmplt\tr" 2  } }*/
/* { dg-final { scan-assembler "\tcmplti\t.*\[^\n\]*, 1" } }*/
/* { dg-final { scan-assembler "\tcmplti\t.*\[^\n\]*, 32" } }*/
/* { dg-final { scan-assembler "\tbtsti\t.*\[^\n\]*, 31" } }*/
/* { dg-final { scan-assembler-times "\tcmphs\t" 2 } }*/

int cmpne(int a,int b)
{
	return (a != b);
}

int cmpnei_1(int a)
{
	return (a != 0);
}

int cmpnei_2(int a)
{
	return (a != 31);
}

int cmplt(int a, int b)
{
	return (a < b);
}

int cmpgt(int a,int b)
{
	return (a > b);	
}

int cmplt_1(int a)
{
	return (a < 1);
}

int cmplt_32(int a)
{
	return (a < 32);
}

int cmplt_0(int a)
{
        if (a < 0)
             a = a + 2;
	return a ;
}

int cmphs_geu(unsigned int a, unsigned int b)
{
	return (a >= b);	
}

int cmphs_leu(unsigned int a, unsigned int b)
{
	return (a <= b);	
}
