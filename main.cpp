#include <iostream>
#include"Event.h"
#include<list>
#include<memory>
#include<algorithm>

#include"TaskController.h"

class A{
private:
    int _a;
public:
    virtual ~A() = default;
    A():_a(0){};
    explicit A(int a):_a(a){}
    virtual void ShowClass() {
        std::cout << "class A\n";
    }

};

class B:public A {
    int _b;
public:
   virtual ~B() = default;
    B():A(),_b(0){};
    B(int a, int b):A(a),_b(b){}
    void ShowClass() override {
        std::cout << "Show B\n";
    };
};

int main()
{
   TaskController task_controller;
    task_controller.Run();
    return 0;
}
