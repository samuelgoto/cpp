#include <iostream>
#include <cassert>

using namespace std;

class Foo {
 public:
  Foo(int count): count(count) {
    cout << "0) called contructor" << endl;
  }
  ~Foo() {
    cout << "4) called destructor" << endl;
  }
  Foo(const Foo &other) {
    cout << "called copy constructor" << endl;
  }
  Foo(Foo&& other) {
    cout << "2) called move constructor" << endl;
    count = other.count;
    other.count = 0;
  }

  int count;
};

void f(Foo foo) {
  // before entering f(), calls the move constructor
  cout << "3) foo count = " << foo.count << endl;
  assert(foo.count = 1);
  // before leaving f(), calls the destructor
}

int main() {
  Foo foo(1);

  // move constructors are called on:
  // (a) initialization, e.g. Foo bar = move(foo);
  // (b) function calls, e.g. f(move(foo)) and void f(Foo)
  // (c) function returns, e.g. Foo g() return foo; where Foo has a move

  cout << "1) calling f()" << endl;
  f(static_cast<Foo&&>(foo));
  cout << "5) exited f()" << endl;

  assert(foo.count == 0);

  return 0;
}
