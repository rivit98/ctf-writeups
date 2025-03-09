#include <stdio.h>
 
void super_long_funtion_name_not_sure_if_length_matters_probably_yes(int crash)
{
    if(crash == 1){
        int* a = NULL;
        *a = 3;
    } else {
        while(1);
    }
}