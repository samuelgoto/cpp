class Foo {
 public:
  Foo() {
  }
  Foo(const Foo &p) {
  }
  ~Foo() {
  }
};

int main() {
  Foo foo;
  Foo bar = foo;
  return 0;
}
