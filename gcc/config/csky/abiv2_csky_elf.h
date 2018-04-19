/******************************************************************
 *               Run-time Target Specification                    *
 ******************************************************************/

#undef STARTFILE_SPEC
#define STARTFILE_SPEC \
  "crt0.o%s crti.o%s crtbegin.o%s"

#undef ENDFILE_SPEC
#define ENDFILE_SPEC "crtend.o%s crtn.o%s"

#undef CC1_SPEC
#define CC1_SPEC                 \
  "%{EB:-EB}                     \
   %{EL:-EL}                     \
   %{fpic|fPIC:-DPIC}            \
   %{march=ck803s:-march=ck803}  \
  "

#undef ASM_SPEC
#define ASM_SPEC                \
  "%{mbig-endian:-mbig-endian}  \
  %{EB:-EB}                     \
  %{EL:-EL}                     \
  %{fpic|fPIC:-pic}             \
  %{mcpu=*:-mcpu=%*}            \
  %{march=*:-march=%*}          \
  %{mhard-float:-mhard-float}   \
  %{mfloat-abi=softfp:-mhard-float}   \
  %{mfloat-abi=hard:-mhard-float}   \
  %{mdsp:-mdsp}                 \
  %{medsp:-medsp}                 \
  %{mmac:-mmac}                 \
  %{manchor:-manchor}           \
  %{melrw:-melrw}               \
  %{mistack:-mistack}           \
  %{mtrust:-mtrust}             \
  "

#undef  LINK_SPEC
#define LINK_SPEC     \
"%{mbig-endian:-EB}   \
 %{EB:-EB}            \
 %{EL:-EL} -X"

#undef  LIB_SPEC
#define LIB_SPEC \
  "%{pthread:-lpthread} -lc"
/* FIXME add this to LIB_SPEC when need */
/*   %{!shared:%{profile:-lc_p}%{!profile:-lc}}" */

#define LIBGCC_SPEC "%{mccrt: -lcc-rt;!mccrt: -lgcc}"

#define CPLUSPLUS_CPP_SPEC "-D_GNU_SOURCE %(cpp)"

#undef TARGET_POSIX_IO
/* This flag used to enable or disable the sepical
   features only for linux toolchain.  */
#define TARGET_CSKY_LINUX 0
