#include <iostream>

using namespace std;

class Foo {
 public:
  Foo(): count(0){
  }
  Foo& operator =(Foo foo) {
    cout << "0) Foo= called" << endl;
    swap(count, foo.count);
  }

  int count;
};

void f(Foo foo) {
}

int main() {
  Foo foo;
  Foo bar;
  bar.count = 3;
  cout << "foo = 0? " << foo.count << endl;
  cout << "bar = 3? " << bar.count << endl;
  foo = bar;
  cout << "foo = 3? " << foo.count << endl;
  cout << "bar = 3? " << bar.count << endl;

  // doesn't trigger a copy-assignment operator
  f(foo);

  return 0;
}
