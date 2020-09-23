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
/*WARNING: not tested*/
#ifndef __DYNAMIC_ARRAY_C__
#define __DYNAMIC_ARRAY_C__
#include "dynamic_array.h"
#include <string.h>
//rounding division up:
//  int a = 59.0f / 4.0f + 0.5f;
//  int a = (59 + (4 - 1)) / 4;
//I'll use the second
void initiate_dynamic_array(dynamic_array* the_array , const size_t initial_number_of_elements, const size_t size_of_element_in_bytes){
    //must be called each time we create a new array
    the_array->size_of_element = size_of_element_in_bytes;
    the_array->number_of_elements = 0;
    the_array->capacity = initial_number_of_elements;
    the_array->elements = malloc(initial_number_of_elements * size_of_element_in_bytes);
    const div_t division = div(size_of_element_in_bytes, sizeof(int));
    the_array->num_integers = division.quot;
    the_array->num_chars = division.rem;
    return;
}
void append_element(dynamic_array* the_array, void* type_casted_element){
    const size_t num = the_array->number_of_elements;
    const size_t size_element = the_array->size_of_element;
    const size_t offset = num * size_element;
    if (the_array->capacity == 0){
        size_t new_num = (num + num/2);
        size_t new_size = new_num * size_element;
        the_array->elements = realloc(the_array->elements, new_size);
        the_array->capacity = new_num - num;
    }
    memcpy(the_array->elements + offset, type_casted_element, size_element);
    (the_array->capacity)--; 
    return;
}
void append_elements(dynamic_array* the_array, void* type_casted_elements, const size_t num_added_elements){
    const size_t num = the_array->number_of_elements;
    const size_t size_element = the_array->size_of_element;
    const size_t offset = num * size_element;
    const size_t size_copied = num_added_elements * size_element;
    if (the_array->capacity < num_added_elements){
        size_t new_num = num + num_added_elements;
        size_t new_size = new_num * size_element;
        the_array->elements = realloc(the_array->elements, new_size);
        the_array->capacity = 0;
    }
    else{
        the_array->capacity = the_array->capacity - num_added_elements;
    }
    memcpy((char*)(the_array->elements) + offset, type_casted_elements, size_copied);
    return;
}

void delete_element(dynamic_array* the_array, const size_t index){
    void* elements = the_array->elements;
    const size_t new_number = the_array->number_of_elements - 1;
    const size_t size_element = the_array->size_of_element;
    const size_t end_size = new_number * size_element;
    size_t start_size = index * size_element;
    while (start_size < end_size){
        memcpy((char*)(elements) + start_size, (char*)(elements) + start_size + size_element, size_element);
        //moving data from integer pointer to another will be faster, but we can't guarantee that the size of element
        //is devidable by sizeof(int)
        start_size += size_element;
    }
    the_array->elements = realloc(elements, end_size);
    the_array->capacity = 0;
    the_array->number_of_elements = new_number;
    return;
}

void delete_elements(dynamic_array* the_array, int* is_removed){
    //is_removed is an integer array that indicates whether a element is going to be removed
    //if the corresponding index of an element in this integer array is non-zero: the element will be removed
    //otherwise (it's a zero): it will remain
    void* elements = the_array->elements;
    const size_t num_elements = the_array->number_of_elements;
    const size_t size_element = the_array->size_of_element;
    const size_t total_size = num_elements * size_element;
    size_t read = 0, write = 0, index = 0, num_written = 0;
    while (read < total_size)
    {
        if(!is_removed[read]){
            memcpy((char*)(elements) + write, (char*)(elements) + read, size_element);
            //memory_copy_fast((char*)(elements) + write, (char*)(elements) + read, size_element);
            write += size_element;
            num_written++;
        }
        read += size_element;
        index++;
    }
    the_array->elements = realloc(elements, num_written * size_element);
    the_array->capacity = 0;
    the_array->number_of_elements = num_written;
    return;
}

void free_array(dynamic_array* the_array){
    free(the_array->elements);
    the_array->number_of_elements = 0;
    the_array->capacity = 0;
    return;
}
void memory_copy_general(int* dist, int* origin, size_t size_copied){
    //used memcpy instead of this method
    //integers are fastest to deal with
    const div_t division = div(size_copied, sizeof(int));
    const size_t num_integers = division.quot;
    const size_t num_chars = division.rem;
    const size_t start_char = num_integers * sizeof(int);
    const size_t end_char = num_chars + start_char;
    for (size_t i = 0; i < num_integers; i++)
    {
        dist[i] = origin[i];
    }
    for (size_t i = start_char; i < end_char; i++)
    {
        ((char*)(dist))[i] = ((char*)(origin))[i];
    }
    return;
}
void copy_element_dynamic_array(int* dist, int* origin, dynamic_array* the_array){
    //used memcpy instead of this method
    const size_t num_integers = the_array->num_integers;
    const size_t start_char = num_integers * sizeof(int);
    const size_t end_char = the_array->num_chars + start_char;
    for (size_t i = 0; i < num_integers; i++)
    {
        dist[i] = origin[i];
    }
    for (size_t i = start_char; i < end_char; i++)
    {
        ((char*)(dist))[i] = ((char*)(origin))[i];
    }
    return;
    
    
}
#endif