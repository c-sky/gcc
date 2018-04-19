/* { dg-do compile } */
/*  {  dg-skip-if  "test is specific to the instruction v2"  { csky-*-* }  { "-march=*" }  { "-march=ck8*"  }  }  */
/* { dg-options "-O2" } */
/* { dg-final { scan-assembler-times "\[ |\t\]cmpne\[ |\t\]" 1 } } */
/* { dg-final { scan-assembler "\[ |\t\]cmpnei\[^\n\]*, 0" } } */
/* { dg-final { scan-assembler "\[ |\t\]cmpnei\[^\n\]*, 65535" } } */
/* { dg-final { scan-assembler-times "\[ |\t\]cmplt\[ |\t\]" 2 } } */
/* { dg-final { scan-assembler "\[ |\t\]cmplti\[^\n\]*, 1" } } */
/* { dg-final { scan-assembler "\[ |\t\]cmplti\[^\n\]*, 65536" } } */
/* { dg-final { scan-assembler "\[ |\t\]btsti\[^\n\]*, 31" } } */
/* { dg-final { scan-assembler-times "\[ |\t\]cmphs\[ |\t\]" 2 } } */
/* { dg-final { scan-assembler "\[ |\t\]cmphsi\[^\n\]*, 2" } } */
/* { dg-final { scan-assembler "\[ |\t\]cmphsi\[^\n\]*, 65536" } } */

int cmpne(int a,int b)
{
	return (a != b);
}

int cmpnei_0(int a)
{
	return (a != 0);
}

int cmpnei_65535(int a)
{
	return (a != 65535);
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
	return (a < 65536);
}

int cmplt_0(int a, int b, int c)
{
	if (a < 0)
		b  =  c;
	return b;
}

int cmphs_geu(unsigned int a, unsigned int b)
{
	return (a >= b);	
}

int cmphs_leu(unsigned int a,unsigned int b)
{
	return (a <= b);	
}

int cmphsi_2(unsigned int a)
{
	return (a >= 2);	
}

int cmphsi_65535(unsigned int a)
{
	return (a >= 65536);	
}
