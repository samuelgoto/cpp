#include <iostream>

class Foo {
 public:
  Foo() {
    std::cout << "1) constructor called!" << std::endl;
  }
  ~Foo() {
    std::cout << "2) destructor called!" << std::endl;
  }
};

int main() {
  std::cout << "0) entering scope" << std::endl;
  {
    Foo foo;
  }
  std::cout << "3) leaving scope" << std::endl;
  return 0;
}
