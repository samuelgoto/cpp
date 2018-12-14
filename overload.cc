#include <iostream>
#include <cassert>

using namespace std;

class Foo {
 public:
  Foo(): count(0){
  }
  void operator ++() {
    cout << "1) ++foo called" << endl;
    count = count + 1;
  }
  void operator ++(int num) {
    cout << "3) foo++ called: " << num << endl;
    count = count + 1 + num;
  }
  void operator +=(int num) {
    cout << "5) foo+= called: " << num << endl;
    count = count + num;
  }
  Foo& operator +(const Foo& foo) {
    cout << "7) foo + foo called" << endl;
    count = count + foo.count;
  }

  int count;
};

int main() {
  Foo foo;
  assert(foo.count == 0);
  ++foo;
  assert(foo.count == 1);
  foo++;
  assert(foo.count == 2);
  foo += 1;
  assert(foo.count == 3);

  Foo bar;
  bar.count = 1;
  Foo hello = foo + bar;
  assert(hello.count == 4);

  // interesting ... so, it do a copy constructor
  // or a move constructor?
  assert(foo.count == 4);
  assert(bar.count == 1);

  // lets see ...
  hello.count = 5;
  assert(hello.count == 5);
  assert(foo.count == 4);
  assert(bar.count == 1);

  // ah, copy constructor then.

  return 0;
}
