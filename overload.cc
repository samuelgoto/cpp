#include <iostream>

class Foo {
 public:
  Foo(): count(0){
  }
  void operator ++() {
    std::cout << "1) ++foo called" << std::endl;
    count = count + 1;
  }
  void operator ++(int num) {
    std::cout << "3) foo++ called: " << num << std::endl;
    count = count + 1 + num;
  }
  void operator +=(int num) {
    std::cout << "5) foo+= called: " << num << std::endl;
    count = count + num;
  }
  Foo& operator +(const Foo& foo) {
    std::cout << "7) foo + foo called" << std::endl;
  }

  int count;
};

int main() {
  Foo foo;
  std::cout << "0) count == 0? " << foo.count << std::endl;
  ++foo;
  std::cout << "2) count == 1? " << foo.count << std::endl;
  foo++;
  std::cout << "4) count == 2? " << foo.count << std::endl;
  foo += 1;
  std::cout << "6) count == 3? " << foo.count << std::endl;
  Foo bar;
  foo + bar;
  return 0;
}
