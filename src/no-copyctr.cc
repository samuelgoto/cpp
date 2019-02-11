class Foo {
 public:
  Foo() {}
  // This deletes the copy constructor.
  Foo(const Foo &other) = delete;
};

int main() {
  Foo foo;
  // This is a compilation error, because we have deleted the copy constructor.
  Foo bar = foo;
}
