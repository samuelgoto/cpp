#include <iostream>

using namespace std;

class Foo {
 public:
  Foo(int count): count(count){
  }
  int count;
};

int main() {
  Foo foo(1);
  //Foo bar;
  //bar.count = 3;
  //cout << "foo = 0? " << foo.count << endl;
  //cout << "bar = 3? " << bar.count << endl;
  //foo = bar;
  //cout << "foo = 3? " << foo.count << endl;
  //cout << "bar = 3? " << bar.count << endl;

  return 0;
}
