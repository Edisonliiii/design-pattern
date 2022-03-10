#include <iostream>

/**
 * @brief Problem singleton solved:
 * 1. static initialization issue across different files
 * 2. uniqueness of static vars
 *
 */

class pesudoSingleton {
 public:
  static pesudoSingleton& getInstance() { return obj; }
  pesudoSingleton(const pesudoSingleton&) = delete;
  pesudoSingleton& operator=(const pesudoSingleton&) = delete;

 private:
  pesudoSingleton() {}
  static pesudoSingleton obj;  // here is the problem, it still can't assure the
                               // init sequence between diff files
};                             // pesudoSingleton

pesudoSingleton pesudoSingleton::obj;

class Singleton {
 public:
  // rely on the language mechanisms & compiler to solve d'tor issue
  // the compile will release the resource when exit the main, just like
  // register on function std::atexit()
  static Singleton& getInstance() {
    static Singleton instance_;  // this obj will be init at run time, cuz it is
                                 // not a const value
    return instance_;
  }

 private:
  Singleton() {}
  ~Singleton() {}
  Singleton(const Singleton&) = delete;
  Singleton& operator=(const Singleton&) = delete;
};  // Singleton

/**
 * @brief Dead reference issue
 * if an app uses multiple interacting singletons, we can NOT provide an
 * automated way to control their lifecycle, especially on the case of
 * cross-file. Such kind of  problem is called dead-ref
 *
 * Still highly rely on compiler to do the work(d'tor)
 *
 * [Case]:
 * (Keyboard, Display, Logger)
 * - Keyboard initialized
 * - Display is trying to initialize
 *   It's c'tor creates Log, because it needs to record the error
 *   During this period(initializing Display), if there is any error, it will
 *   trigger Log to record it, and then the app is likely to exit
 *   Here, the compiler will try to release the created local static parameters
 *   in the reverse order of creation,
 *   Therefore, 'Log' will get destroied before 'Display' & 'Keyboard'f for some
 *   reason Keyboard fails to shut down and tries to report an error to Log,
 *   Log::Instance unwittingly returns a reference to the "shell" of a destroyed
 *   Log object. The program steps into the shady realm of undefined behavior.
 *   This is the dead- reference problem.
 */
class Singleton_dead_reference {
 public:
  Singleton_dead_reference* getInstance() {
    if (!pInstance_) {
      // check for dead reference
      if (destroy_) {
        OnDeadReference();
      } else {
        create();
      }
    }
    return pInstance_;
  }
  virtual ~Singleton_dead_reference() {
    destroy_ = true;
    pInstance_ = nullptr;
  }

  static Singleton_dead_reference* pInstance_;
  static bool destroy_;

 private:
  Singleton_dead_reference(){};
  Singleton_dead_reference(const Singleton_dead_reference&) = delete;
  Singleton_dead_reference& operator=(const Singleton_dead_reference&) = delete;
  static void OnDeadReference() {
    throw std::runtime_error("Dead Reference Detected");
  }
  static void create() {
    static Singleton_dead_reference instance_;
    pInstance_ = &instance_;
  }

};  // Singleton_dead_reference

/**
 * @brief pInstance_ is available at any time we need
 * Compare with the previous design, there is not only a thown expectaion,
 * there is a solution
 *
 * This is a strong enough guarantee to make the Phoenix singleton an appealing
 * solution for robust, all-terrain objects, like the Log in our problem.
 */
class Singleton_Phoenix {
 public:
  static bool destroy_;
  static Singleton_Phoenix* pInstance_;

  Singleton_Phoenix* getInstance() {
    if (!pInstance_) {
      if (destroy_) {
        onDeadReference();
      } else {
        create();
      }
    }
    return pInstance_;
  }

  virtual ~Singleton_Phoenix() {
    destroy_ = true;
    pInstance_ = nullptr;
  }

 private:
  Singleton_Phoenix(){};
  Singleton_Phoenix(const Singleton_Phoenix&) = delete;
  Singleton_Phoenix& operator=(const Singleton_Phoenix&) = delete;
  static void create() {
    static Singleton_Phoenix instance_;
    pInstance_ = &instance_;
  }
  // here, it has to be static function
  static void killSingleton() { pInstance_->~Singleton_Phoenix(); }
  void onDeadReference() {
    create();
    // placement new, use the origianl address and create a new one on the top
    // of it, now it's on heap, we should make sure we will manually destroy it
    new (pInstance_) Singleton_Phoenix;
    std::atexit(killSingleton);
    // reset to init state so that we can get back to business
    destroy_ = false;
  }
};  // Singleton_Phoenix

/**
 * @brief Pheonix disadvantage:
 * The Phoenix singleton breaks the normal lifetime cycle of a singleton, which
 * may confuse some clients. If the singleton keeps state, that state is lost
 * after a destruction-creation cycle. The implementer of a concrete singleton
 * that uses the Phoenix strategy must pay extra attention to keeping state
 * between the moment of destruction and the moment of reconstruction.
 */
namespace Private {
class LifetimeTracker {
 public:
  LifetimeTracker(unsigned int x) : longevity_(x) {}
  virtual ~LifetimeTracker() = 0;
  friend inline bool Compare(unsigned int longevity, const LifetimeTracker* p) {
    return p->longevity_ > longevity;
  }

 private:
  unsigned int longevity_;
};  // LifetimeTracker
inline LifetimeTracker::~LifetimeTracker() {}
}  // namespace Private

namespace Private {
template <typename T, typename Destroyer>
class ConcreteLifetimeTracker : public LifetimeTracker {
 public:
  ConcreteLifetimeTracker(T* p, unsigned int longevity, Destroyer d)
      : LifetimeTracker(longevity), pTracked_(p), destroyer_(d) {}
  ~ConcreteLifetimeTracker() { destroyer_(pTracked_); }

 private:
  T* pTracked_;
  Destroyer destroyer_;
};                // ConcreteLifetimeTracker
void AtExitFn();  // declare needed below
};                // namespace Private

namespace Private {
// private variables
typedef LifetimeTracker** TrackerArray;  // typedef
extern TrackerArray pTrackerArray;       // global
extern unsigned int elements;            // increasing
};                                       // namespace Private

namespace Private {
// private functor
template <typename T>
struct Deleter {
  static void Delete(T* pObj) { delete pObj; }
};  // Deleter
};  // namespace Private

namespace Private {
// public interface
template <typename T, typename Destroyer>
void SetLongevity(T* pDynObject, unsigned int longevity,
                  Destroyer d = Deleter<T>::Delete) {
  TrackerArray pNewArray = static_cast<TrackerArray>(std::realloc(
      pTrackerArray, sizeof(T) * (elements + 1)));  // realloc space
  if (!pNewArray) throw std::bad_alloc();
  pTrackerArray = pNewArray;  // reassign long-live obj
  LifetimeTracker* p =
      new ConcreteLifetimeTracker<T, Destroyer>(pDynObject, longevity, d);
  TrackerArray pos = std::upper_bound(pTrackerArray, pTrackerArray + elements,
                                      pTrackerArray + elements + 1);
  *pos = p;
  ++elements;
  std::atexit(AtExitFn);
}
};  // namespace Private

// test for Singleton_dead_reference
Singleton_dead_reference* Singleton_dead_reference::pInstance_ = nullptr;
bool Singleton_dead_reference::destroy_ = false;
// test for Singleton_Phoenix
Singleton_Phoenix* Singleton_Phoenix::pInstance_ = nullptr;
bool Singleton_Phoenix::destroy_ = false;

int main(int argc, char const* argv[]) {
  std::cout << "Test for Singleton_dead_reference" << std::endl;
  Singleton_dead_reference* obj_;
  std::cout << obj_->getInstance() << std::endl;
  std::cout << obj_->getInstance() << std::endl;

  std::cout << "Test for Singleton_Phoenix" << std::endl;
  Singleton_Phoenix* SP_obj_;
  std::cout << SP_obj_->getInstance() << std::endl;
  std::cout << SP_obj_->getInstance() << std::endl;
  // the right way to use phoenix is to se the pointer to nullptr,
  // rather than using 'delete', because 'delete' will return it back to where
  // it should be
  Singleton_Phoenix::pInstance_ = nullptr;
  std::cout << SP_obj_->getInstance() << std::endl;
  return 0;
}
