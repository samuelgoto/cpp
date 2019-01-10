# [main.cc](main.cc)

```c++
int main() {
  return 0;
}
```

Machine code: 

```assembly

main.o:     file format elf64-x86-64


Disassembly of section .text:

0000000000000000 <main>:
int main() {
   0:	55                   	push   rbp
   1:	48 89 e5             	mov    rbp,rsp
  return 0;
   4:	b8 00 00 00 00       	mov    eax,0x0
}
   9:	5d                   	pop    rbp
   a:	c3                   	ret    
```
