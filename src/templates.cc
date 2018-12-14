#include <iostream>
#include <memory>
#include <cassert>

using namespace std;

template <typename T> T sum(T a, T b) {
  return a + b;
}

template <typename T>
class Adder {
 public:
  Adder(T a, T b): a(a), b(b) {
  }
  T add() {
    return a + b;
  }
 private:
  T a;
  T b;
};

int main() {
  // function templates
  assert(sum(1, 2) == 3);

  // class templates
  Adder<int> adder(1, 2);
  assert(adder.add() == 3);
  return 0;
}
