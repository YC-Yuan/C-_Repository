#include "ctime"
#include <iostream>
#include "chrono"
#include <sys/timeb.h>

using namespace std;

int main() {
    CTime tm=CTime::GetCurrentTime();
    tm.GetMinSecond();



    auto t1=std::chrono::steady_clock::now();
    for (int i = 0; i < 100000000; ++i) {
        i++;
        i--;
    }
    auto t2=std::chrono::steady_clock::now();
    int dr_ms=std::chrono::duration<double,std::milli>(t2-t1).count();
    cout<< dr_ms<<endl;
}