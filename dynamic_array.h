/*
Copyright 2020 Moamen Abdelsattar

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
/*WARNING: not tested*/
#ifndef __DYNAMIC_ARRAY_H__
#define __DYNAMIC_ARRAY_H__
#include <stdlib.h>
typedef struct {
    void* elements; //a type casted pointer to the first element
    void* special_common_data; // a type-casted common data between all elements
    size_t number_of_elements; //in the array
    size_t capacity; //in elements
    size_t size_of_element; //size of each element in bytes
    size_t num_integers;//related to read and write fast with unknown type
    size_t num_chars;//related to read and write fast with unknown type
} dynamic_array;
void initiate_dynamic_array(dynamic_array* the_array ,size_t initial_size_in_elements, size_t size_of_element_in_bytes);
void append_element(dynamic_array* the_array, void* type_casted_element);
void append_elements(dynamic_array* the_array, void* type_casted_elements, size_t num_elements);
void delete_element(dynamic_array* the_array, size_t index);
void delete_elements(dynamic_array* the_array, int* is_removed);
void free_array(dynamic_array* the_array);

#endif
