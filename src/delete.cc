#include <iostream>

class Foo {
 public:
  void * operator new(size_t size) = delete;
  Foo() {
    std::cout << "1) Foo() constructor called!" << std::endl;
  }
};

int main() {
  Foo foo;

  /**
   * The following:
   *
   * Foo *bar = new Foo();
   *
   * Causes a compilation error:
   *
   * src/delete.cc:15:22: error: use of deleted function
   *      ‘static void* Foo::operator new(size_t)’
   *   Foo *bar = new Foo();
   *                      ^
   * src/delete.cc:7:10: note: declared here
   *   void * operator new(size_t size) = delete;
   *          ^~~~~~~~
   */

  return 0;
}
