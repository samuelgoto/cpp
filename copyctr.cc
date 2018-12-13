#include <iostream>
#include <cassert>

using namespace std;

class Foo {
 public:
  Foo(int count): count(count){
    cout << "0) called constructor with " << count << endl;
  }
  Foo(const Foo &other) {
    cout << "    [called copy constructor with " << other.count << "]" << endl;
    count = other.count;
  }
  int count;
};

void f(Foo a) {
}

#pragma optimize("", off)
Foo g() {
  return Foo(2);
}
#pragma optimize("", on)

int main() {
  Foo foo(1);

  cout << "1) A copy constructor is called when:" << endl;

  cout << "  a) when an object is constructed based on another:" << endl;
  Foo bar = foo;

  // different instances
  assert(&foo != &bar);

  // bar was constructed from a copy.
  assert(bar.count == 1);

  cout << "  b) an object is passed as a function param:" << endl;
  f(foo);

  // TODO(goto): figure out why the copy-constructor is being
  // optimized away
  // cout << "  c) an object is returned by value" << endl;
  /// g();

  return 0;
}
