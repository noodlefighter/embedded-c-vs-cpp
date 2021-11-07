# embedded-c-vs-cpp

```
$ pip install platformio

$ cd embedded-c-vs-cpp/
$ git submodule update --init
$ pio run
```

## c_list/cpp_list

C: .text=80Byte

```
 .text.c_list   0x0000000000000000       0x50 .pio/build/stm32/src/c_list.o
 .bss.items     0x0000000000000000      0x3e8 .pio/build/stm32/src/c_list.o
 .data.mylist   0x0000000000000000        0x8 .pio/build/stm32/src/c_list.o
 .rodata.c_list.str1.1
                0x0000000000000000       0x10 .pio/build/stm32/src/c_list.o
```

C++(case0)：.text=396Byte

```
 .text._ZN3etl5ilistI4itemE10push_frontEOS1_
                0x0000000000000000       0x5c .pio/build/stm32/src/cpp_list.o
 .text.cpp_list
                0x0000000000000000       0x7c .pio/build/stm32/src/cpp_list.o
 .rodata.cpp_list.str1.1
                0x0000000000000000       0x1f .pio/build/stm32/src/cpp_list.o
 .text.startup._GLOBAL__sub_I_cpp_list
                0x000000000000800c       0x78 .pio/build/stm32/src/cpp_list.o
 .text._ZN3etl4listI4itemLj25EED2Ev
                0x00000000000080d8       0x3c .pio/build/stm32/src/cpp_list.o
                0x00000000000080d8                etl::list<item, 25u>::~list()
                0x00000000000080d8                etl::list<item, 25u>::~list()
 .bss._ZL7mylist1
                0x00000000000186b0      0x220 .pio/build/stm32/src/cpp_list.o
 .bss._ZL7mylist2
                0x00000000000188d0      0x220 .pio/build/stm32/src/cpp_list.o
```

C++（case1）： .text=426Byte

```
 .text._ZN3etl5ilistI4itemE10push_frontEOS1_
                0x0000000000000000       0x5c .pio/build/stm32/src/cpp_list.o
 .text.cpp_list
                0x0000000000000000       0x7c .pio/build/stm32/src/cpp_list.o
 .rodata.cpp_list.str1.1
                0x0000000000000000       0x1f .pio/build/stm32/src/cpp_list.o
 .text.startup._GLOBAL__sub_I_cpp_list
                0x000000000000800c       0x78 .pio/build/stm32/src/cpp_list.o
 .text._ZN3etl5ilistI4itemE10initialiseEv
                0x00000000000080d8       0x42 .pio/build/stm32/src/cpp_list.o
                0x00000000000080d8                etl::ilist<item>::initialise()
 .text._ZN3etl4listI4itemLj51EED2Ev
                0x000000000000811a        0xc .pio/build/stm32/src/cpp_list.o
                0x000000000000811a                etl::list<item, 51u>::~list()
                0x000000000000811a                etl::list<item, 51u>::~list()
 .text._ZN3etl4listI4itemLj50EED2Ev
                0x0000000000008126        0xc .pio/build/stm32/src/cpp_list.o
                0x0000000000008126                etl::list<item, 50u>::~list()
                0x0000000000008126                etl::list<item, 50u>::~list()
 .bss._ZL7mylist1
                0x00000000000186d0      0x220 .pio/build/stm32/src/cpp_list.o
 .bss._ZL7mylist2
                0x00000000000188f0      0x234 .pio/build/stm32/src/cpp_list.o
```

C++(case2): .text=464Byte

```
 .text._ZN3etl5ipool13allocate_itemEv
                0x0000000000000000       0x3c .pio/build/stm32/src/cpp_list.o
 .text.cpp_list
                0x0000000000000000       0xa8 .pio/build/stm32/src/cpp_list.o
 .rodata.cpp_list.str1.1
                0x0000000000000000       0x1f .pio/build/stm32/src/cpp_list.o
 .text.startup._GLOBAL__sub_I_cpp_list
                0x000000000000800c       0x74 .pio/build/stm32/src/cpp_list.o
.text._ZN3etl4listI5item2Lj25EED2Ev
                0x00000000000080d4       0x3c .pio/build/stm32/src/cpp_list.o
                0x00000000000080d4                etl::list<item2, 25u>::~list()
                0x00000000000080d4                etl::list<item2, 25u>::~list()
 .text._ZN3etl4listI4itemLj25EED2Ev
                0x0000000000008110       0x3c .pio/build/stm32/src/cpp_list.o
                0x0000000000008110                etl::list<item, 25u>::~list()
                0x0000000000008110                etl::list<item, 25u>::~list()
 .bss._ZL7mylist1
                0x00000000000186e8      0x220 .pio/build/stm32/src/cpp_list.o
 .bss._ZL7mylist2
                0x0000000000018908      0x220 .pio/build/stm32/src/cpp_list.o
```
