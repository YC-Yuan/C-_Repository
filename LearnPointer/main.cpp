#include <iostream>

int dog = 1, cat = 2, bir = 3, fis = 4;

void func(){
    std::cout<<"function called"<<std::endl;
}

int main() {
    int i = 10, j = 11, k = 126;
    int *p = &dog;
    int *q = &k;
    std::cout << *(p) << std::endl;
    std::cout << *(p + 1) << std::endl;
    std::cout << *(p + 2) << std::endl;
    std::cout << *(p + 3) << std::endl;
    std::cout << (long) &i << std::endl;
    std::cout << (long) &j << std::endl;
    std::cout << (long) &k << std::endl;
    std::cout << *(q + 2) << std::endl;

    void (*fp[3])();//如果不初始化，就相当于啥都没调用；而调用nullptr会导致报错

    fp[0]=func;
    fp[0]();
}
