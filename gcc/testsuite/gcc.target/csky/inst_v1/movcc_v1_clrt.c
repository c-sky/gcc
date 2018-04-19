/* { dg-do compile } */
/* { dg-final { scan-assembler "\tcmpnei\t.*\[^\n\]*, 1\n\t" } } */

int movcc(int a,int b)
{
	if(a != 1)
		a = 0;
	else
		a = b;
	return a;
}
