
#include "config.h"
#include "system.h"
#include "coretypes.h"
#include "tm.h"
#include "common/common-target.h"
#include "common/common-target-def.h"

/* Set default optimization options.  */
static const struct default_options csky_option_optimization_table[] =
  {
    /* Enable section anchors by default at -O1 or higher.  */
    { OPT_LEVELS_1_PLUS, OPT_fomit_frame_pointer, NULL, 1 },
    { OPT_LEVELS_NONE, 0, NULL, 0 }
  };

#undef  TARGET_DEFAULT_TARGET_FLAGS
#define TARGET_DEFAULT_TARGET_FLAGS TARGET_DEFAULT

#undef  TARGET_OPTION_OPTIMIZATION_TABLE
#define TARGET_OPTION_OPTIMIZATION_TABLE csky_option_optimization_table

struct gcc_targetm_common targetm_common = TARGETM_COMMON_INITIALIZER;
