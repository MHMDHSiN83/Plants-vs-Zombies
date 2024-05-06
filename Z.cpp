#include <iostream>
#include <vector>
#include <memory>
using namespace std;
// Base class
class Base {
public:
    virtual void print() const {
        cout << "Base" << endl;
    }
    virtual ~Base() {} // Making the base class polymorphic
};

// Derived class 1
class Derived1 : public Base {
public:
    void print() const override {
        cout << "Derived1" << endl;
    }
};

// Derived class 2
class Derived2 : public Base {
public:
    void print() const override {
        cout << "Derived2" << endl;
    }
};

int main() {
    vector<Base*> objects;
    
    objects.push_back(new Derived1);
    objects.push_back(new Derived2);
    
    for (const auto& obj : objects) {
        obj->print();
    }

    return 0;
}