#include <iostream>
#include <cassert>

using namespace std;

class Bar {
 public:
  Bar() {
    cout << "1) Bar() constructor called!" << endl;
  }
  ~Bar()  {
    cout << "4) Bar() destructor called!" << endl;
  }
};

class Foo {
 public:
  Foo() {
    cout << "2) Foo() constructor called!" << endl;
  }
  ~Foo() {
    cout << "3) Foo() destructor called!" << endl;
  }
  Bar a;
};

int main() {
  cout << "0) entering scope" << endl;
  {
    Foo foo;
  }
  cout << "5) left scope" << endl;

  return 0;
}
