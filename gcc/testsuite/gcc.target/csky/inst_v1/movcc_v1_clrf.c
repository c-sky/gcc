/* { dg-do compile } */
/* { dg-final { scan-assembler "\tcmpnei\t\[^\n\]*, 1\n\tmovt\[^\n\]*\n\tclrf\t" } } */

int movcc(int a,int b)
{
	if(a != 1)
		a = b;
	else
		a = 0;
	return a;
}
