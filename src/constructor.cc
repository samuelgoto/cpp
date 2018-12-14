#include <iostream>

class Foo {
 public:
  Foo() {
    std::cout << "1) Foo() constructor called!" << std::endl;
  }
  Foo(int a) {
    std::cout << "2) Foo(num) constructor called!" << std::endl;
  }
};

int main() {
  Foo foo;
  Foo bar(1);
  Foo *hello = new Foo();
  Foo *world = new Foo(1);
  delete hello;
  delete world;
  return 0;
}
