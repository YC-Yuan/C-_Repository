//
// Created by AAA on 2021/6/21.
//

#ifndef PAPERTEST_QUEUE_H
#define PAPERTEST_QUEUE_H

using namespace std;

class Queue {
    enum {
        qsize = 100
    };
    void* queue[qsize];
    int front;
    int tail;
public:
    Queue() : front(0), tail(0) {};

    int size() const{
        return (tail-front)%100;
    }

    void enqueue(void* t) {
        if (increase(tail)==front){
            cout<<"队列满啦，不能再enqueue"<<endl;
            exit(1);
        }
        queue[tail] = t;
        tail = increase(tail);
    };

    void* dequeue() {
        if (isEmpty()) {
            cout << "队列空啦，不能再dequeue" << endl;
            exit(1);
        } else {
            void* t = queue[front];
            front = increase(front);
            return t;
        }
    };
private:
    bool isEmpty() const {
        return front == tail;
    }

    static int increase(int index) {
        return index == qsize - 1 ? 0 : index+1;
    }
};


#endif //PAPERTEST_QUEUE_H
