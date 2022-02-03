#ifndef LOKI_TYPETRAITS_INC_
#define LOKI_TYPETRAITS_INC_

#include <loki/Typelist.h>
#include <loki/Sequence.h>

#if (defined _MSC_VER) && (_MSC_VER < 1400)
#include <string>
#endif

#ifdef _MSC_VER
#pragma warning (push)
//qualifier applied to function type has no meaning; ignored
#pragma warning (disable: 4180)
#endif

namespace Loki
{

}; // namespace Loki

#endif // LOKI_TYPETRAITS_INC_