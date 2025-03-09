 
void looper(int crash)
{
    if(crash == 1){
        int* a = 0;
        *a = 3;
    } else {
        while(1);
    }
}