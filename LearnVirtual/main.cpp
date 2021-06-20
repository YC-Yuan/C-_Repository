#include <iostream>

class Parent{
public:
    int a=1;
    void print(){
        std::cout<<"Print in parent"<<std::endl;
        std::cout<<a<<std::endl;
    }
};

class Middle:public Parent{
public:
    void print(){
        std::cout<<"Print in middle"<<std::endl;
    }
};

class Child:public Middle{
public:
    void print(){
        std::cout<<"Print in child"<<std::endl;
    }

};

// 此处传入一个parent的引用，在使用时也可以传入child，将子类视作父类对待
// 如果父类中的函数没有virtual，那子类将无法成功重写函数(带有virtual后，传入child调用Child的print，否则调用的还是Parent的print)
void printParent(Parent& parent){
    parent.print();
}

void printMiddle(Middle& middle){
    middle.print();
}

int main() {
    Child child;
    Middle middle;
    printParent(middle);
    printParent(child);
    printMiddle(child);
    return 0;
}
