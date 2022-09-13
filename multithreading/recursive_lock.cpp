
#include <map>
#include <mutex>
#include <shared_mutex>
#include <string>

// user can acquire multiple locks on a single
// instance from the same thread

// user must release all locks before it can be locked by
// another thread

// not recommend, better switch the design patter