/* { dg-do compile } */
/*  {  dg-skip-if  "test is specific to ck802"  { csky-*-* }  { "*" }  { "-mcpu=ck802*" }  }  */

/* { dg-options "-O2 " } */

int cmpnei(int a){
	if(a != 1000)
		return 0;
	return 1;
}
/* { dg-final { scan-assembler "cmpnei"} } */

int cmphsi(int a){
	if(a >= 1000)
		return 0;
	return 1;
}
/* { dg-final { scan-assembler "cmplti"} } */

int cmplti(int a){
	if(a < 1000)
		return 0;
	return 1;
}
/* { dg-final { scan-assembler "cmplti"} } */

int cmplei(int a){
	if(a <= 1000)
		return 0;
	return 1;
}
/* { dg-final { scan-assembler "cmplti"} } */

int cmphi(int a){
	if(a > 1000)
		return 0;
	return 1;
}
/* { dg-final { scan-assembler "cmplti"} } */

unsigned ucmpnei(unsigned a){
	if(a != 1000)
		return 0;
	return 1;
}
/* { dg-final { scan-assembler "cmpnei"} } */

unsigned ucmphsi(unsigned a){
	if(a >= 1000)
		return 0;
	return 1;
}
/* { dg-final { scan-assembler "cmphsi"} } */

unsigned ucmplti(unsigned a){
	if(a < 1000)
		return 0;
	return 1;
}
/* { dg-final { scan-assembler "cmphsi"} } */

unsigned ucmplei(unsigned a){
	if(a <= 1000)
		return 0;
	return 1;
}
/* { dg-final { scan-assembler "cmphsi"} } */

unsigned ucmphi(unsigned a){
	if(a > 1000)
		return 0;
	return 1;
}
/* { dg-final { scan-assembler "cmphsi"} } */
