# pure C dynamic array
A dynamic array implementation that can be used to store any type of elements.

WARNING: not well tested yet!

# How to use
use `dynamic_array_packed.h` if the elements size is NOT a multiple of `sizeof(int_word)`. (`int_word` is a data dype defined in the `dynamic_array.h` file according to the word size of the processor.)

Use `dynamic_array_aligned.h` if the elements size is a multiple of `sizeof(int_word)`. To make a structure aligned so that its size is a multiple of `int_word` use `__attribute__((aligned(sizeof(int_word))))`. For more information see the aligned array example. I believe that this library is faster in appending and deleting elements.

WARNING: My assumption that the latter methods are faster is based on the assumption that copying data of the same word size is the fastest, but I'm not sure whether this assuption is true.
WARNING: The two libraries are not well tested yet.
