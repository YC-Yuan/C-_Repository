#include <iostream>
#include <vector>
#include <random>
#include <ctime>


using namespace std;

class Matrix {
public:
    void print() {
        print_baseline();
        print_line(0);
        print_baseline();
        print_line(1);
        print_baseline();
        print_line(2);
        print_baseline();
        print_line(3);
        print_baseline();
        if (num_false == 0) {
            cout << "game over" << endl;
            exit(0);
        }
    }

    void change_one() {
        vector<int> numbers{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
        shuffle(numbers.begin(), numbers.end(), std::mt19937(std::random_device()()));
        for (int i = 0; i < 16; ++i) {
            if (!array[numbers.at(i)]) {
                array[numbers.at(i)] = true;
                break;
            }
        }
        num_false--;
    }

private:
    int num_false = 16;
    bool array[16] = {false, false, false, false, false, false, false, false, false, false, false, false, false, false,
                      false, false,};

    void print_one(int num) {
        if (array[num]) cout << '2';
        else cout << ' ';
    };

    static void print_baseline() {
        cout << "+-----+-----+-----+-----+" << endl;
    };

    void print_line(int num) {
        num = num * 4;
        cout << "|  ";
        print_one(num);
        cout << "  |  ";
        print_one(num + 1);
        cout << "  |  ";
        print_one(num + 2);
        cout << "  |  ";
        print_one(num + 3);
        cout << "  |" << endl;
    }
};

int main() {
    srand(time(0));
    for (int i = 0; i < 10; i++) {
        cout << rand()%4 << endl;
    }
}