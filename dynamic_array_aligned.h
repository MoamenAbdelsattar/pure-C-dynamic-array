/*
Copyright 2020 moamen abdelsattar

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation
files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy,
modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is 
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR 
IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef __DYNAMIC_ARRAY_ALIGNED_H__
#define __DYNAMIC_ARRAY_ALIGNED_H__
#include <stdlib.h>
#include "dynamic_array.h"


/*=================== ALIGNED =====================*/
/*use those methods if the data structure of the elements is aligned to the word size of the processor*/
/*WARNING: not tested yet*/

//WARNING: Those functions are built on the assumption that copying data of the same word size is 
//the fastest, but I'm not sure whether this assuption is true.

void initiate_dynamic_array_A(dynamic_array* the_array ,size_t initial_size_in_elements, size_t size_of_element_in_bytes);
void append_element_A(dynamic_array* the_array, void* location_of_element);
void append_elements_A(dynamic_array* the_array, void* location_of_elements, size_t num_added_elements);
void delete_element_A(dynamic_array* the_array, size_t index);
void delete_elements_A(dynamic_array* the_array, int_word* is_removed);
void free_array_A(dynamic_array* the_array);


#endif