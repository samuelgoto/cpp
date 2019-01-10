# [main.cc](main.cc)

```c++
int main() {
  return 0;
}
```

Machine code: 

```assembly
main:
        push    rbp
        mov     rbp, rsp
        mov     eax, 0
        pop     rbp
        ret

```
# [constructor.cc](constructor.cc)

```c++
class Foo {
 public:
  Foo() {
  }
  ~Foo() {
  }
};

int main() {
  Foo foo;
  return 0;
}
```

Machine code: 

```assembly
Foo::Foo() [base object constructor]:
        push    rbp
        mov     rbp, rsp
        mov     QWORD PTR [rbp-8], rdi
        nop
        pop     rbp
        ret
Foo::~Foo() [base object destructor]:
        push    rbp
        mov     rbp, rsp
        mov     QWORD PTR [rbp-8], rdi
        nop
        pop     rbp
        ret
main:
        push    rbp
        mov     rbp, rsp
        push    rbx
        sub     rsp, 24
        lea     rax, [rbp-17]
        mov     rdi, rax
        call    Foo::Foo() [complete object constructor]
        mov     ebx, 0
        lea     rax, [rbp-17]
        mov     rdi, rax
        call    Foo::~Foo() [complete object destructor]
        mov     eax, ebx
        add     rsp, 24
        pop     rbx
        pop     rbp
        ret

```
# [copy.cc](copy.cc)

```c++
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
```

Machine code: 

```assembly
Foo::Foo() [base object constructor]:
        push    rbp
        mov     rbp, rsp
        mov     QWORD PTR [rbp-8], rdi
        nop
        pop     rbp
        ret
Foo::~Foo() [base object destructor]:
        push    rbp
        mov     rbp, rsp
        mov     QWORD PTR [rbp-8], rdi
        nop
        pop     rbp
        ret
Foo::operator=(Foo):
        push    rbp
        mov     rbp, rsp
        mov     QWORD PTR [rbp-8], rdi
        mov     QWORD PTR [rbp-16], rsi
        nop
        pop     rbp
        ret
main:
        push    rbp
        mov     rbp, rsp
        push    rbx
        sub     rsp, 24
        lea     rax, [rbp-18]
        mov     rdi, rax
        call    Foo::Foo() [complete object constructor]
        lea     rax, [rbp-19]
        mov     rdi, rax
        call    Foo::Foo() [complete object constructor]
        lea     rdx, [rbp-17]
        lea     rax, [rbp-18]
        mov     rsi, rdx
        mov     rdi, rax
        call    Foo::operator=(Foo)
        lea     rax, [rbp-17]
        mov     rdi, rax
        call    Foo::~Foo() [complete object destructor]
        mov     ebx, 0
        lea     rax, [rbp-19]
        mov     rdi, rax
        call    Foo::~Foo() [complete object destructor]
        lea     rax, [rbp-18]
        mov     rdi, rax
        call    Foo::~Foo() [complete object destructor]
        mov     eax, ebx
        add     rsp, 24
        pop     rbx
        pop     rbp
        ret

```
