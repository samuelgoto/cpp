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
