class Foo {
 public:
  Foo() {}
  // This deletes the assignment operator.
  Foo& operator=(const Foo &other) = delete;
};

int main() {
  Foo foo;
  Foo bar;
  // This is a compilation error, because we have deleted the assignment
  // operator.
  bar = foo;
}
