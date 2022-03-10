#include <iostream>
#include <list>
#include <memory>
#include <string>
#include <vector>

// common interfaces
// base class of CurrentTarget and HistoryTarget
/* 接口类本身最上头就有vptr
 */
class ObserverCommonInterface
    : public std::enable_shared_from_this<ObserverCommonInterface> {
 public:
  virtual void update(std::string na_, int loc_, int id_) = 0;
  virtual void printer() = 0;
  virtual ~ObserverCommonInterface() {}
};

// observee 的数据结构
class TraceTarget {
 private:
  std::string name;
  int location;
  int id;
  // 此处乃设计缺陷之一 observer越多 效率越低 就越难做到真正的同步
  // 虽然做到了主动更新信息 但是还是没做到同步更新信息
  /* 这里之所以会work是因为 mount接受参数的时候 使用base
     class的ptr指向了子类的地址 搜索的virtual table 不同 所以调用的函数不一样
     因为接口类(此处是ObserverCommonInterface)本身就有vptr
     所以用夫类的指针可以无缝接轨子类的object 而vptr指向的内容是不一样的
     所以就实现了自动筛选
  */
  std::list<std::shared_ptr<ObserverCommonInterface>> waitingQueue;
  void launchSignal() {
    // std::cout << "Check waitingQueue length: " << waitingQueue.size()
    //           << std::endl;
    std::list<std::shared_ptr<ObserverCommonInterface>>::iterator itr =
        waitingQueue.begin();
    while (itr != waitingQueue.end()) {
      //   std::shared_ptr<ObserverCommonInterface> obj(itr->lock());
      //   std::cout << "check ref count" << obj.use_count() << std::endl;
      std::cout << "check ref count -- :" << itr->use_count() << std::endl;
      if (itr->use_count()) {
        (*itr)->update(name, location, id);
        (*itr)->printer();
        ++itr;
      } else {
        std::cout << "Erasing" << std::endl;
        itr = waitingQueue.erase(itr);
      }
    }
  }

 public:
  // one-off
  void mount(std::shared_ptr<ObserverCommonInterface> obj) {
    // std::cout << "check ref count " << obj.use_count() << std::endl;
    // std::weak_ptr<ObserverCommonInterface> _tmp(obj);
    std::cout << "check ref count before pb " << obj.use_count() << std::endl;
    // std::endl;
    waitingQueue.push_back(obj);
    std::cout << "check ref count after pb " << obj.use_count() << std::endl;
    // std::cout << "check ref count after push_back " << obj.use_count()
    //           << std::endl;
  }
  void unmount(const std::shared_ptr<ObserverCommonInterface>& obj) {
    // in here, we delete the current obj directly
    // std::weak_ptr<ObserverCommonInterface> _tmp(obj);
    // if (obj.lock()) {
    //   ObserverCommonInterface* raw_ptr = obj.get();
    //   delete raw_ptr;
    //   raw_ptr = nullptr;
    // }
  }

  // keep updating
  void changeState(std::string na_new, int loc_new, int id_new) {
    name = na_new;
    location = loc_new;
    id = id_new;
    launchSignal();
  }
};

// the first observer
class CurrentTarget : public ObserverCommonInterface {
 private:
  std::string C_name;
  int C_location;
  int C_id;

  std::shared_ptr<ObserverCommonInterface> shareThis() {
    return shared_from_this();
  }

  TraceTarget& tmp;

 public:
  CurrentTarget(TraceTarget& obj) : tmp(obj) {
    std::shared_ptr<CurrentTarget> _tmp(this);
    std::cout << "check ref count before mount: " << _tmp.use_count()
              << std::endl;
    tmp.mount(_tmp);
    std::cout << "check ref count after mount: " << _tmp.use_count()
              << std::endl;
  }

  void update(std::string na_, int loc_, int id_) override {
    C_name = na_;
    C_location = loc_;
    C_id = id_;
  }

  void printer() override {
    std::cout << "------------CurrentTarget-------------" << std::endl;
    std::cout << "name: " << C_name << std::endl;
    std::cout << "location: " << C_location << std::endl;
    std::cout << "id: " << C_id << std::endl;
    std::cout << "---------------------------------------" << std::endl;
  }
  ~CurrentTarget() override {
    std::cout << "releaseing CurrentTarget" << std::endl;
  }
};

// the second observer
class HistoryTarget : public ObserverCommonInterface {
 private:
  std::vector<std::string> H_name;
  std::vector<int> H_location;
  std::vector<int> H_id;

  TraceTarget& tmp;

  std::shared_ptr<ObserverCommonInterface> shareThis() {
    return shared_from_this();
  }

 public:
  HistoryTarget(TraceTarget& obj) : tmp(obj) {
    // std::shared_ptr<ObserverCommonInterface> _tmp =
    //     std::make_shared<HistoryTarget>(*this);
    tmp.mount(std::make_shared<HistoryTarget>(*this));
  }

  void update(std::string na_, int loc_, int id_) override {
    H_name.push_back(na_);
    H_location.push_back(loc_);
    H_id.push_back(id_);
  }

  void printer() override {
    std::cout << "-----------HistoryTarget-----------" << std::endl;
    for (auto ele : H_name) std::cout << ele << " ";
    std::cout << std::endl;
    for (auto ele : H_location) std::cout << ele << " ";
    std::cout << std::endl;
    for (auto ele : H_id) std::cout << ele << " ";
    std::cout << std::endl;
    std::cout << "-----------------------------------" << std::endl;
  }
  ~HistoryTarget() override {
    std::cout << "releaseing HistoryTarget" << std::endl;
  }
};

int main(int argc, char const* argv[]) {
  TraceTarget obj;
  //   CurrentTarget c_listener(obj);
  //   HistoryTarget h_listener(obj);
  std::shared_ptr<CurrentTarget> c_listener =
      std::make_shared<CurrentTarget>(obj);
  std::cout << "check in main: " << c_listener.use_count() << std::endl;
  std::shared_ptr<HistoryTarget> h_listener =
      std::make_shared<HistoryTarget>(obj);

  obj.changeState("hello", 100, 1000);
  obj.changeState("edee", 110, 1010);
  obj.changeState("stephanie", 111, 1110);
  return 0;
}