class Foo {
 public:
  Foo() {
  }
  ~Foo() {
  }
  Foo& operator =(Foo foo) {
  }
};

int main() {
  Foo foo;
  Foo bar;
  foo = bar;
  return 0;
}
