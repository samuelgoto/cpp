#include <iostream>

using namespace std;

class Foo {
 public:
  Foo(): count(0){
  }
  Foo& operator =(Foo&& foo) {
    cout << "0) Foo= called" << endl;
    // swap(count, foo.count);
  }

  int count;
};

int main() {
  Foo foo;
  Foo bar;
  bar.count = 3;
  cout << "foo = 0? " << foo.count << endl;
  cout << "bar = 3? " << bar.count << endl;
  foo = std::move(bar);
  cout << "foo = 3? " << foo.count << endl;
  cout << "bar = 3? " << bar.count << endl;

  return 0;
}
