#include <iostream>
#include <cassert>

using namespace std;

class Foo {
 public:
  Foo() {
    cout << "1) Foo() constructor called!" << endl;
  }
  Foo(int a) : a(a) {
    cout << "2) Foo(num) constructor called!" << endl;
    b = 2;
  }
  int a;
  int b;
};

int main() {
  Foo foo;

  assert(foo.a == 0);
  assert(foo.b == 0);

  Foo bar(1);

  assert(bar.a == 1);
  assert(bar.b == 2);

  return 0;
}
