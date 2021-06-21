#include <iostream>

using namespace std;

class Customer {
private:
    const string name;
public:
    const string &getName() {
        cout<< "non-const getName"<<endl;
        return name;
    }
    const string &getName() const{
        cout<< "const getName"<<endl;
        return name;
    }

};

void printCustomer(const Customer &customer)  {
    cout << customer.getName() << endl;
}

int main() {
    Customer customer;
    customer.getName();
    return 0;
}
