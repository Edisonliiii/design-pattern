#ifndef LOKI_SMALLOBJ_INC_
#define LOKI_SMALLOBJ_INC_

// $Id$


#include <loki/LokiExport.h>
#include <loki/Threads.h>
#include <loki/Singleton.h>
#include <cstddef>
#include <new> // needed for std::nothrow_t parameter.

#ifndef LOKI_DEFAULT_CHUNK_SIZE
#define LOKI_DEFAULT_CHUNK_SIZE 4096
#endif

#ifndef LOKI_MAX_SMALL_OBJECT_SIZE
#define LOKI_MAX_SMALL_OBJECT_SIZE 256
#endif

#ifndef LOKI_DEFAULT_OBJECT_ALIGNMENT
#define LOKI_DEFAULT_OBJECT_ALIGNMENT 4
#endif

#ifndef LOKI_DEFAULT_SMALLOBJ_LIFETIME
#define LOKI_DEFAULT_SMALLOBJ_LIFETIME ::Loki::LongevityLifetime::DieAsSmallObjectParent
#endif

#if defined(LOKI_SMALL_OBJECT_USE_NEW_ARRAY) && defined(_MSC_VER)
#pragma message("Don't define LOKI_SMALL_OBJECT_USE_NEW_ARRAY when using a Microsoft compiler to prevent memory leaks.")
#pragma message("now calling '#undef LOKI_SMALL_OBJECT_USE_NEW_ARRAY'")
#undef LOKI_SMALL_OBJECT_USE_NEW_ARRAY
#endif

///  \defgroup  SmallObjectGroup Small objects
///
///  \defgroup  SmallObjectGroupInternal Internals
///  \ingroup   SmallObjectGroup


namespace Loki
{
  namespace Long
}; // namespace Loki





























