#include <stdlib.h>
#include <iostream>
#include <ww898/utf_sizes.hpp>
#include<iterator>

using namespace std;

const int inp_buf_size = 256;
const int name_buf_size = 64;
int main()
{
    const char secret[5]="1234";
    char name_buf[name_buf_size] = {};
    char inp_buf[inp_buf_size] = {};
    cout << "Enter your name: "<<endl;
    for (int i=0;i<inp_buf_size;++i)
        inp_buf[inp_buf_size] = 0x0;
    fgets(inp_buf,inp_buf_size,stdin);
    
    size_t user_inp_size = ww898::utf::size(inp_buf);
    if (user_inp_size > name_buf_size)
    {
        cout << "buffer overflow detected"<<endl;
        return 0;
    }
    int i=0;
    while (inp_buf[i] != '\n')
    {
        name_buf[i] = inp_buf[i];
        i++;
    }

    cout << "Hello: " << name_buf << endl;

    if (secret[0]=='p' and secret[1]=='i' and secret[2]=='n' and secret[3]=='g' )
    {
        cout << "fake flag"<<endl;
    }




}


/*


*/