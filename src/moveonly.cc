#include <iostream>

class MoveOnlyType {
 public:
  MoveOnlyType() { std::cout << "constructor" << std::endl; }
  ~MoveOnlyType() { std::cout << "destructor" << std::endl;  }

  // Defines a move constructor
  MoveOnlyType(MoveOnlyType&& other) {
    std::cout << "move constructor" << std::endl;
  }

  // This deletes the copy constructor.
  MoveOnlyType(const MoveOnlyType &other) = delete;
  // This deletes the assignment operator.
  MoveOnlyType& operator=(const MoveOnlyType &other) = delete;
};

MoveOnlyType build() {
  MoveOnlyType result;
  return result;
}

void f(MoveOnlyType&& foo) {
  // Takes ownership over foo.
  MoveOnlyType bar = static_cast<MoveOnlyType&&>(foo);
}

int main() {
  f(build());
}
