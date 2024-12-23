# Language

## Introduction

This my own language. The parser uses recursive descent and then it creates a tree. After that this tree is compiling into asmcode. Then this asmcode is runned by my own processor (prepared program is `../Processor/processor.out`, build it before).

## How to use
1) Copy For usage
2) Write your program (using keywords in file src/KEYWORDS) in file example.ll (Lukashenko Language)
3) Create asmcode, using `./compiler.out` and run it on my processor using `../Processor/processor.out`.

For usage:

```
git clone https://github.com/kefirRzevo/Dedinsky-C-course.git
cd Language
make
make clean
```
