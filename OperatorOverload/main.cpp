#include <iostream>

using namespace std;

class Money {
public:
    int num = 0;
    string category;

    Money(int num, const string &category = "CNY") {
        this->num = num;
        this->category = category;
    }

private:
    friend ostream &operator<<(ostream &output, const Money &m) {
        output << m.num << " " << m.category;
        return output;
    }

    friend Money &operator+=(Money &left, int num) {
        left.num += num;
        return left;
    }

    friend const Money &operator+(Money &left, Money &right) {
        if (left.category == right.category) {
            left.num += right.num;
            return left;
        } else {
            cout << "mismatch currency:" + left.category + " & " + right.category << endl;
            exit(1);
        }
    }


};

int main() {
    Money m1(100, "CNY");
    cout << m1 << endl;
    m1 += 10;
    cout << m1 << endl;
    Money m3 = 0;
    cout << m3 << endl;
    Money m2(200, "CNY");
    m3 = m1 + m2;
    cout << m3 << endl;
    Money m4(1000, "YEN");
    cout << m3 + m4 << endl;

}
