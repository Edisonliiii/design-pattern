#ifndef LOKI_SINGLETON_INC_
#define LOKI_SINGLETON_INC_

#include <loki/LokiExport.h>
#include <loki/Threads.h>

#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <list>
#include <memory>
#include <new>
#include <stdexcept>
#include <vector>

#ifdef __MSC_VER
#define LOKI_C_CALLING_CONVENTION_QUALIFIER __cdecl
#else
#define LOKI_C_CALLING_CONVENTION_QUALIFIER
#endif

namespace Loki {
typedef void(LOKI_C_CALLING_CONVENTION_QUALIFIER* atexit_pfn_t)();
namespace Private {
#ifndef LOKI_MAKE_DLL
void LOKI_C_CALLING_CONVENTION_QUALIFIER
AtExitFn();  // declaration needed below
#else
void LOKI_EXPORT AtExitFn();
#endif

class LifetimeTracker;

#define LOKI_ENABLE_NEW_SETLONGLIVITY_HELPER_DATA_IMPL
#ifdef LOKI_ENABLE_NEW_SETLONGLIVITY_HELPER_DATA_IMPL
// helper data
// std::list because of the inserts
typedef std::list<LifetimeTracker*> TrackerArray;
extern LOKI_EXPORT TrackerArray* pTrackerArray;
#else
typedef LifetimeTracker** TrackerArray;
extern TrackerArray pTrackerArray;
extern unsigned int elements;
#endif

};  // namespace Private
};  // namespace Loki

#endif  // end of LOKI_SINGLETON_INC_