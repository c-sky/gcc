#include <math.h>
/*
#include <math_private.h>
*/

#define minus_zero		-0
#define plus_infty		HUGE_VAL
#define minus_infty		-HUGE_VAL

/*
 #if (__BYTE_ORDER == __BIG_ENDIAN)
*/
/*
#if defined(__cskyBE__)
typedef union
{
    double value;
    struct
    {
        unsigned int msw;
        unsigned int lsw;
    }parts;
}ieee_double_shape_type;

#else

typedef union
{
    double value;
    struct
    {
        unsigned int lsw;
        unsigned int msw;
    }parts;
}ieee_double_shape_type;

#endif
*/

static ieee_double_shape_type __Nanf;
static double _set_nan(void){
	__Nanf.parts.msw = 0x7ff80000;
	__Nanf.parts.lsw = 0;
	return __Nanf.value;
}
#define nan_value		_set_nan()



#define ACCURACY	1.0 / 100000.0

static int accuracy_test(double a, double b){
	if(fabs(a) < ACCURACY * ACCURACY && fabs(b) < ACCURACY * ACCURACY){
		return 1;
	}
	if(fabs((a - b) / b) <= ACCURACY) {
		return 1;
	}else {
		printf("a = %f\nb = %f\naccuracy = %f\n", a, b, (a - b) / b); 
		return 0;
	}
}

#define __IS_NAN_TEST(a, b) do{ \
	b = 0; \
	__Nanf.value = a; \
	if(__Nanf.parts.msw == 0xfff80000 || __Nanf.parts.msw == 0x7ff80000) { \
		b = 1; \
	} \
}while(0)
