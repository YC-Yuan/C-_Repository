#include <iostream>
#include "Queue.h"


using namespace std;



int main() {

    Queue q;

    string c("c"),d("d");


    q.enqueue(&c);
    q.enqueue(&d);
    c.append("_1");

    cout<<q.size()<<" "
    <<(*(string*)q.dequeue())<<" "
    <<(*(string*)q.dequeue())<<" "
    <<q.size()<<endl;

    Queue* fp=new Queue[100];
    delete[] fp;
    return 0;
}
