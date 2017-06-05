/*/////////////////////////////////////////////////////////
////       Run-time Target Specification               ////
/////////////////////////////////////////////////////////*/

#undef STARTFILE_SPEC
#define STARTFILE_SPEC \
	"crt0.o%s crti.o%s crtbegin.o%s"

#undef ENDFILE_SPEC
#define ENDFILE_SPEC "crtend.o%s crtn.o%s"

#undef CC1_SPEC
#define CC1_SPEC	\
	"%{EB:-EB}		\
	 %{EL:-EL}		\
	 %{fpic|fPIC:-DPIC}		\
	"

#undef ASM_SPEC
#ifdef __CSKYABIV2__
#define ASM_SPEC 	\
	"%{mbig-endian:-mbig-endian}	\
	%{EB:-EB}	\
	%{EL:-EL}	\
	%{fpic|fPIC:-pic}	\
	%{mcpu=*:-mcpu=%*}		\
	%{march=*:-march=%*}	\
	%{mhard-float:-mhard-float}	\
	%{mdsp:-mdsp}	\
	%{mmac:-mmac}	\
	%{manchor:-manchor}	\
	%{melrw:-melrw}	\
	%{mistack:-mistack}	\
    %{mbranch-stub:-mbranch-stub} \
    %{mno-branch-stub:-mno-branch-stub} \
	"
#else /* ABIV2 */
#define ASM_SPEC 	\
	"%{mbig-endian:-mbig-endian}	\
	%{EB:-EB}	\
	%{EL:-EL}	\
	%{fpic|fPIC:-pic}	\
	%{mcpu=*:-mcpu=%*}		\
	%{march=*:-march=%*}	\
	%{mhard-float:-mhard-float}	\
	%{mdsp:-mdsp}	\
	%{mmac:-mmac}	\
	%{manchor:-manchor}	\
	"
#endif

#undef	LINK_SPEC
#define LINK_SPEC		\
"%{mbig-endian:-EB}		\
 %{EB:-EB}				\
 %{EL:-EL} -X           \
 %{mbranch-stub:--branch-stub} \
 %{mno-branch-stub:--no-branch-stub} \
 "

#undef  LIB_SPEC
#define LIB_SPEC \
  "%{pthread:-lpthread} -lc"
/* FIXME add this to LIB_SPEC when need */
/*   %{!shared:%{profile:-lc_p}%{!profile:-lc}}" */

#define LIBGCC_SPEC "%{mccrt:-lcc-rt;!mccrt:-lgcc}"

#define CPLUSPLUS_CPP_SPEC "-D_GNU_SOURCE %(cpp)"

#undef TARGET_POSIX_IO
