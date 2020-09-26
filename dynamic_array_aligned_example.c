#include "dynamic_array_aligned.h"
#include "stdio.h"
int main(){
    //to define an aligned data structure use the following syntax:
    typedef struct __attribute__((aligned(sizeof(int_word)))) {
    uint16_t i;
    }example_algined_type;
    //this will make the size of the structure a multiple of sizeof(int_word). 
    //this structure can elements for an aligned dynamic array
    example_algined_type get_element;
    dynamic_array example_algined_array;
    example_algined_type additional_element;
    printf("in program sucessful\n");
    initiate_dynamic_array_A(&example_algined_array, 10, sizeof(example_algined_type));
    printf("initiate sucessful\n");
    additional_element = (example_algined_type){.i = 50};
    append_element_A(&example_algined_array, &additional_element);
    printf("append sucessful\n");
    get_element = ((example_algined_type*)(example_algined_array.elements))[0];
    //cast the element pointer to our structure pointer then get element by index 
    printf("appended element value is %u\n", get_element.i);
    //test successful, output: 50
    additional_element = (example_algined_type){.i = 60};
    append_element_A(&example_algined_array, &additional_element);
    delete_element_A(&example_algined_array, 0); // now the index of the new added element is 0
    printf("delete sucessful\n");
    get_element = ((example_algined_type*)(example_algined_array.elements))[0];
    //cast the element pointer to our structure pointer then get element by index 
    printf("appended element value after delete is %u\n", get_element.i);
    //test successful, output: 60
    free_array_A(&example_algined_array);
    printf("free successful\n");
    printf("\n");
    printf("Press enter to continue...\n");
    getchar();
}