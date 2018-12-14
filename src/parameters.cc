#include <iostream>
#include <memory>
#include <cassert>

using namespace std;

class Foo {
 public:
  Foo(int count): count(count) {
    cout << "constructor called: " << count << endl;
  }
  ~Foo() {
    cout << "destructor called: " << count << endl;
  }
  Foo(Foo &other) {
    cout << "copy constructor called: " << other.count << endl;
    count = other.count;
  }
  Foo(Foo &&other) {
    cout << "move constructor called: " << other.count << endl;
    count = other.count;
    other.count = 0;
  }
  Foo operator +(Foo const& other) {
    cout << "+operator called: " << count << " + " << other.count << endl;
    Foo result(count + other.count);
    cout << "+operator returning" << endl;
    return result;
  }
  int count;
};

Foo sum(Foo& a, Foo& b) {
  cout << "adding" << endl;
  Foo c = a + b;
  cout << "done adding" << endl;
  return c;
}

int main() {
  Foo foo(1);
  Foo bar(2);

  cout << "entering sum()" << endl;
  {
    assert((foo + bar).count == 3);
  }
  cout << "left sum()" << endl;

  assert(foo.count == 1);
  assert(bar.count == 2);

  return 0;
}
