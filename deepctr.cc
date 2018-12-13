#include <iostream>
#include <cassert>

using namespace std;

// tests that verify that the default constructor does a shallow copy
// https://www.geeksforgeeks.org/copy-constructor-in-cpp/

class Foo {
 public:
  Foo(int *count): count(count) {
    cout << "0) called constructor with " << *count << endl;
  }
  int *count;
};

int main() {
  int i = 1;
  Foo foo(&i);
  Foo bar = foo;

  assert(foo.count == &i);
  assert(bar.count == &i);
  assert(foo.count == bar.count);

  assert(*foo.count = 1);
  assert(*bar.count = 1);

  i = 2;

  assert(*foo.count = 2);
  assert(*bar.count = 2);

  return 0;
}
