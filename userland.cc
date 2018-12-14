#include <iostream>
#include <memory>
#include <cassert>

template <typename T>
class UniquePtr {
 public:
  UniquePtr(T* ref): ref_(ref), empty_(false) {
    std::cout << "UniquePtr constructor" << std::endl;
  }
  ~UniquePtr() {
    std::cout << "UniquePtr destructor" << std::endl;
    // deletes the reference when this goes out of scope
    if (empty_) {
      std::cout << "empty, skipping" << std::endl;
      return;
    }
    empty_ = true;
    delete ref_;
  }
  UniquePtr(UniquePtr&& other) {
    std::cout << "move constructor" << std::endl;
    other.empty_ = true;
    ref_ = other.get();
  }
  UniquePtr<T>& operator= (UniquePtr<T>&& other) {
    std::cout << "move assignment" << std::endl;
  }
  bool empty() {
    return empty_;
  }
  T* get() {
    return ref_;
  }
 private:
  T* ref_;
  bool empty_;
};

class Foo {
 public:
  Foo(int count): count(count) {
    std::cout << "Foo constructor" << std::endl;
  }
  ~Foo() {
    std::cout << "Foo destructor" << std::endl;
  }
  int count;
};

int main() {
  UniquePtr<Foo> foo(new Foo(3));

  assert(foo.get()->count == 3);
  assert(!foo.empty());

  std::cout << "assigning " << std::endl;
  UniquePtr<Foo> bar = static_cast<UniquePtr<Foo>&&>(foo);
  std::cout << "done " << std::endl;

  assert(foo.empty());
  assert(!bar.empty());

  UniquePtr<Foo> hello = static_cast<UniquePtr<Foo>&&>(bar);

  assert(foo.empty());
  assert(bar.empty());
  assert(!hello.empty());

  // UniquePtr<Foo> bar = foo; leads to a compilation error
  // because we delete the operator+ (UniquePtr<Foo>&) from UniquePtr.
  // UniquePtr<Foo> world = hello;

  return 0;
}
