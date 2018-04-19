/* 
   check dump const
*/
extern void patch_lib() __attribute__ ((section(".patch_lib")));

int g_test;

void patch_normal()
{
	g_test = 0x10;
}

void patch_lib()
{

}
