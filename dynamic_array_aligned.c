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

#ifndef __DYNAMIC_ARRAY_ALIGNED_C__
#define __DYNAMIC_ARRAY_ALIGNED_C__
#include "dynamic_array_aligned.h"
#include <string.h>

void initiate_dynamic_array_A(dynamic_array* the_array , size_t initial_number_of_elements, size_t size_of_element_in_bytes){
    //must be called each time we create a new array
    the_array->size_of_element = size_of_element_in_bytes;
    the_array->number_of_elements = 0;
    the_array->capacity = initial_number_of_elements;
    the_array->elements = malloc(initial_number_of_elements * size_of_element_in_bytes);
    //const div_t division = div(size_of_element_in_bytes, sizeof(int));
    the_array->num_integers = size_of_element_in_bytes / sizeof(int_word); //for aligned data structure: this division has no remainant
    the_array->num_chars = 0;
    return;
}
void append_element_A(dynamic_array* the_array, void* type_casted_element){
    const size_t num = the_array->number_of_elements;
    const size_t size_element = the_array->size_of_element;
    const size_t num_integers = the_array->num_integers;
    const size_t offset = num * num_integers;
    if (the_array->capacity == 0){
        size_t new_num = (num + num/2);
        the_array->elements = realloc(the_array->elements, new_num * size_element);
        the_array->capacity = new_num - num;
    }
    int_word* elements = the_array->elements;
    for (size_t i = 0; i < num_integers; i++)
    {
        elements[offset + i] = ((int_word*)(type_casted_element))[i];
    }
    
    //memcpy(the_array->elements + offset, type_casted_element, size_element);
    (the_array->capacity)--;
    //number of elements not updated!!!!
    (the_array->number_of_elements)++;
    return;
}
void append_elements_A(dynamic_array* the_array, void* type_casted_elements, const size_t num_added_elements){
    const size_t num = the_array->number_of_elements;
    const size_t size_element = the_array->size_of_element;
    const size_t num_integers = the_array->num_integers;
    const size_t offset = num * num_integers;
    const size_t integers_copied = num_added_elements * num_integers;
    int_word* elements = the_array->elements;
    if (the_array->capacity < num_added_elements){
        the_array->elements = realloc(the_array->elements, (num + num_added_elements) * size_element);
        the_array->capacity = 0;
    }
    else{
        the_array->capacity = the_array->capacity - num_added_elements;
    }
    //copy memory
    for (size_t element = 0; element < integers_copied; element+=num_integers)// increase num integers!!!!!!!!!!!!!!
    {    
        for (size_t i = 0; i < num_integers; i++)
        {
            elements[offset + element + i] = ((int_word*)(type_casted_elements))[element + i];
        }
    }
    (the_array->number_of_elements) += num_added_elements;
    return;
}

void delete_element_A(dynamic_array* the_array, size_t index){
    int_word* elements = the_array->elements;
    const size_t new_num_elements = the_array->number_of_elements - 1;
    const size_t num_integers = the_array->num_integers;
    size_t start_index = index * num_integers;
    const size_t end_index = new_num_elements * num_integers;
    while (start_index < end_index){
        for (size_t i = 0; i < num_integers; i++)
        {
            elements[start_index + i] = elements[start_index + i + 1];
        }
        start_index+=num_integers;
        // increase num integers!!!!!!!!!!!!!!
    }
    the_array->elements = realloc(elements, end_index * sizeof(int_word));
    the_array->capacity = 0;
    the_array->number_of_elements = new_num_elements;

    return;
}
void delete_elements_A(dynamic_array* the_array, int_word* is_removed){
    int_word* elements = the_array->elements;
    const size_t num_elements = the_array->number_of_elements;
    const size_t num_integers = the_array->num_integers;
    const size_t total_integers = num_elements * num_integers;
    size_t read = 0, write = 0, index = 0, num_written = 0;
    while (read < total_integers)
    {
        if(!is_removed[read]){
            for (size_t i = 0; i < num_integers; i++)
            {
                elements[write + i] = elements[read + i];
            }
            write += num_integers;
            num_written++;
        }
        read += num_integers;
        index++;
    }
    the_array->elements = realloc(elements, num_written * num_integers * sizeof(int));
    the_array->capacity = 0;
    the_array->number_of_elements = num_written;
    return;
}
void free_array_A(dynamic_array* the_array){
    free(the_array->elements);
    the_array->number_of_elements = 0;
    the_array->capacity = 0;
    return;   
}

#endif