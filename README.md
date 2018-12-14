This is a series of studies of new C++ features to help me catch up with the lastest developments of the language.

It starts with some [warming up](#srchello) and syntactical sugar, but then goes deeper into destructors, operator overloading and move semantics.

Ultimately, I implement [unique_ptr](https://en.cppreference.com/w/cpp/memory/unique_ptr) in userland to convince myself that there isn't any magic going on in the compiler.

# [src/hello.cc](src/hello.cc)
```c++
#include <iostream>

int main() {
  std::cout << "Hello, World!" << std::endl;
  return 0;
}
```
Result: 
```bash
Hello, World!
```
# [src/constructor.cc](src/constructor.cc)
```c++
#include <iostream>

class Foo {
 public:
  Foo() {
    std::cout << "1) Foo() constructor called!" << std::endl;
  }
  Foo(int a) {
    std::cout << "2) Foo(num) constructor called!" << std::endl;
  }
};

int main() {
  Foo foo;
  Foo bar(1);
  Foo *hello = new Foo();
  Foo *world = new Foo(1);
  delete hello;
  delete world;
  return 0;
}
```
Result: 
```bash
1) Foo() constructor called!
2) Foo(num) constructor called!
1) Foo() constructor called!
2) Foo(num) constructor called!
```
# [src/delete.cc](src/delete.cc)
```c++
#include <iostream>

class Foo {
 public:
  void * operator new(size_t size) = delete;
  Foo() {
    std::cout << "1) Foo() constructor called!" << std::endl;
  }
};

int main() {
  Foo foo;

  /**
   * The following:
   *
   * Foo *bar = new Foo();
   *
   * Causes a compilation error:
   *
   * src/delete.cc:15:22: error: use of deleted function
   *      ‘static void* Foo::operator new(size_t)’
   *   Foo *bar = new Foo();
   *                      ^
   * src/delete.cc:7:10: note: declared here
   *   void * operator new(size_t size) = delete;
   *          ^~~~~~~~
   */

  return 0;
}
```
Result: 
```bash
1) Foo() constructor called!
```
# [src/destructor.cc](src/destructor.cc)
```c++
#include <iostream>

class Foo {
 public:
  Foo() {
    std::cout << "1) constructor called!" << std::endl;
  }
  ~Foo() {
    std::cout << "2) destructor called!" << std::endl;
  }
};

int main() {
  std::cout << "0) entering scope" << std::endl;
  {
    Foo foo;
  }
  std::cout << "3) leaving scope" << std::endl;
  return 0;
}
```
Result: 
```bash
0) entering scope
1) constructor called!
2) destructor called!
3) leaving scope
```
# [src/fields.cc](src/fields.cc)
```c++
#include <iostream>
#include <cassert>

using namespace std;

class Foo {
 public:
  Foo() {
    cout << "1) Foo() constructor called!" << endl;
  }
  Foo(int a) : a(a) {
    cout << "2) Foo(num) constructor called!" << endl;
    b = 2;
  }
  int a;
  int b;
};

int main() {
  Foo foo;

  assert(foo.a == 0);
  assert(foo.b == 0);

  Foo bar(1);

  assert(bar.a == 1);
  assert(bar.b == 2);

  return 0;
}
```
Result: 
```bash
1) Foo() constructor called!
2) Foo(num) constructor called!
```
# [src/fields_dtr.cc](src/fields_dtr.cc)
```c++
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
```
Result: 
```bash
0) entering scope
1) Bar() constructor called!
2) Foo() constructor called!
3) Foo() destructor called!
4) Bar() destructor called!
5) left scope
```
# [src/unique_ptr.cc](src/unique_ptr.cc)
```c++
#include <iostream>
#include <memory>

class Foo {
 public:
  Foo() {
    std::cout << "1) constructor called!" << std::endl;
  }
  ~Foo() {
    std::cout << "2) destructor called!" << std::endl;
  }
};

int main() {
  std::cout << "0) entering scope" << std::endl;
  {
    std::unique_ptr<Foo> foo(new Foo());
  }
  std::cout << "3) leaving scope" << std::endl;
  return 0;
}
```
Result: 
```bash
0) entering scope
1) constructor called!
2) destructor called!
3) leaving scope
```
# [src/overload.cc](src/overload.cc)
```c++
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
```
Result: 
```bash
1) ++foo called
3) foo++ called: 0
5) foo+= called: 1
7) foo + foo called
```
# [src/copy.cc](src/copy.cc)
```c++
#include <iostream>

using namespace std;

class Foo {
 public:
  Foo(): count(0){
  }
  Foo& operator =(Foo foo) {
    cout << "0) Foo= called" << endl;
    swap(count, foo.count);
  }

  int count;
};

void f(Foo foo) {
}

int main() {
  Foo foo;
  Foo bar;
  bar.count = 3;
  cout << "foo = 0? " << foo.count << endl;
  cout << "bar = 3? " << bar.count << endl;
  foo = bar;
  cout << "foo = 3? " << foo.count << endl;
  cout << "bar = 3? " << bar.count << endl;

  // doesn't trigger a copy-assignment operator
  f(foo);

  return 0;
}
```
Result: 
```bash
foo = 0? 0
bar = 3? 3
0) Foo= called
foo = 3? 3
bar = 3? 3
```
# [src/copyctr.cc](src/copyctr.cc)
```c++
#include <iostream>
#include <cassert>

using namespace std;

class Foo {
 public:
  Foo(int count): count(count){
    cout << "- called constructor with " << count << endl;
  }
  Foo(const Foo &other) {
    cout << "- called copy constructor with " << other.count << endl;
    count = other.count;
  }
  int count;
};

void f(Foo a) {
}

Foo g() {
  Foo foo(2);
  return foo;
}

int main() {
  Foo foo(1);

  cout << "- A copy constructor is called when:" << endl;

  cout << "a) when an object is constructed based on another:" << endl;
  Foo bar = foo;

  // different instances
  assert(&foo != &bar);

  // bar was constructed from a copy.
  assert(bar.count == 1);

  cout << "b) an object is passed as a function param:" << endl;
  f(foo);

  // TODO(goto): figure out why the copy-constructor is being
  // optimized away
  cout << "c) an object is returned by value" << endl;
  g();

  return 0;
}
```
Result: 
```bash
- called constructor with 1
- A copy constructor is called when:
a) when an object is constructed based on another:
- called copy constructor with 1
b) an object is passed as a function param:
- called copy constructor with 1
c) an object is returned by value
- called constructor with 2
- called copy constructor with 2
```
# [src/deepctr.cc](src/deepctr.cc)
```c++
#include <iostream>
#include <cassert>

using namespace std;

// tests that verify that the default constructor does a shallow copy
// https://www.geeksforgeeks.org/copy-constructor-in-cpp/

class Foo {
 public:
  Foo(int *count): count(count) {
    cout << "0) called constructor with " << *count << endl;
  }
  int *count;
};

int main() {
  int i = 1;
  Foo foo(&i);
  Foo bar = foo;

  assert(foo.count == &i);
  assert(bar.count == &i);
  assert(foo.count == bar.count);

  assert(*foo.count = 1);
  assert(*bar.count = 1);

  i = 2;

  assert(*foo.count = 2);
  assert(*bar.count = 2);

  return 0;
}
```
Result: 
```bash
0) called constructor with 1
```
# [src/movectr.cc](src/movectr.cc)
```c++
#include <iostream>
#include <cassert>

using namespace std;

class Foo {
 public:
  Foo(int count): count(count) {
    cout << "0) called contructor" << endl;
  }
  ~Foo() {
    cout << "4) called destructor" << endl;
  }
  Foo(const Foo &other) {
    cout << "called copy constructor" << endl;
  }
  Foo(Foo&& other) {
    cout << "2) called move constructor" << endl;
    count = other.count;
    other.count = 0;
  }

  int count;
};

void f(Foo foo) {
  // before entering f(), calls the move constructor
  cout << "3) foo count = " << foo.count << endl;
  assert(foo.count = 1);
  // before leaving f(), calls the destructor
}

int main() {
  Foo foo(1);

  // move constructors are called on:
  // (a) initialization, e.g. Foo bar = move(foo);
  // (b) function calls, e.g. f(move(foo)) and void f(Foo)
  // (c) function returns, e.g. Foo g() return foo; where Foo has a move

  cout << "1) calling f()" << endl;
  f(static_cast<Foo&&>(foo));
  cout << "5) exited f()" << endl;

  assert(foo.count == 0);

  return 0;
}
```
Result: 
```bash
0) called contructor
1) calling f()
2) called move constructor
3) foo count = 1
4) called destructor
5) exited f()
4) called destructor
```
# [src/parameters.cc](src/parameters.cc)
```c++
#include <iostream>
#include <memory>
#include <cassert>

using namespace std;

class Foo {
 public:
  Foo(int count): count(count) {
    cout << "constructor called: " << count << endl;
  }
  ~Foo() {
    cout << "destructor called: " << count << endl;
  }
  Foo(Foo &other) {
    cout << "copy constructor called: " << other.count << endl;
    count = other.count;
  }
  Foo(Foo &&other) {
    cout << "move constructor called: " << other.count << endl;
    count = other.count;
    other.count = 0;
  }
  Foo operator +(Foo const& other) {
    cout << "+operator called: " << count << " + " << other.count << endl;
    Foo result(count + other.count);
    cout << "+operator returning" << endl;
    return result;
  }
  int count;
};

Foo sum(Foo& a, Foo& b) {
  cout << "adding" << endl;
  Foo c = a + b;
  cout << "done adding" << endl;
  return c;
}

int main() {
  Foo foo(1);
  Foo bar(2);

  cout << "entering sum()" << endl;
  {
    assert((foo + bar).count == 3);
  }
  cout << "left sum()" << endl;

  assert(foo.count == 1);
  assert(bar.count == 2);

  return 0;
}
```
Result: 
```bash
constructor called: 1
constructor called: 2
entering sum()
+operator called: 1 + 2
constructor called: 3
+operator returning
move constructor called: 3
destructor called: 0
destructor called: 3
left sum()
destructor called: 2
destructor called: 1
```
# [src/templates.cc](src/templates.cc)
```c++
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
```
Result: 
```bash
```
# [src/userland.cc](src/userland.cc)
```c++
#include <iostream>
#include <memory>
#include <cassert>

template <typename T>
class UniquePtr {
 public:
  UniquePtr(T* ref): ref_(ref), empty_(false) {
    std::cout << "UniquePtr constructor" << std::endl;
  }
  ~UniquePtr() {
    std::cout << "UniquePtr destructor" << std::endl;
    // deletes the reference when this goes out of scope
    if (empty_) {
      std::cout << "empty, skipping" << std::endl;
      return;
    }
    empty_ = true;
    delete ref_;
  }
  UniquePtr(UniquePtr&& other) {
    std::cout << "move constructor" << std::endl;
    other.empty_ = true;
    ref_ = other.get();
  }
  UniquePtr<T>& operator= (UniquePtr<T>&& other) {
    std::cout << "move assignment" << std::endl;
  }
  bool empty() {
    return empty_;
  }
  T* get() {
    return ref_;
  }
 private:
  T* ref_;
  bool empty_;
};

class Foo {
 public:
  Foo(int count): count(count) {
    std::cout << "Foo constructor" << std::endl;
  }
  ~Foo() {
    std::cout << "Foo destructor" << std::endl;
  }
  int count;
};

void f(UniquePtr<Foo> foo) {
  assert(!foo.empty());
}

int main() {
  UniquePtr<Foo> foo(new Foo(3));

  assert(foo.get()->count == 3);
  assert(!foo.empty());

  std::cout << "assigning " << std::endl;
  UniquePtr<Foo> bar = static_cast<UniquePtr<Foo>&&>(foo);
  std::cout << "done " << std::endl;

  assert(foo.empty());
  assert(!bar.empty());

  UniquePtr<Foo> hello = static_cast<UniquePtr<Foo>&&>(bar);

  assert(foo.empty());
  assert(bar.empty());
  assert(!hello.empty());

  // UniquePtr<Foo> bar = foo; leads to a compilation error
  // because we delete the operator+ (UniquePtr<Foo>&) from UniquePtr.
  // UniquePtr<Foo> world = hello;

  f(static_cast<UniquePtr<Foo>&&>(hello));

  assert(hello.empty());

  return 0;
}
```
Result: 
```bash
Foo constructor
UniquePtr constructor
assigning 
move constructor
done 
move constructor
move constructor
UniquePtr destructor
empty, skipping
UniquePtr destructor
empty, skipping
UniquePtr destructor
empty, skipping
UniquePtr destructor
empty, skipping
```
