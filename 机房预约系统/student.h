#pragma once
#include <iostream>
using namespace std;
#include "Identity.h"

class Student : public Identity
{
public:
    Student();
    Student(int id, string name, string pwd);
    virtual void open_menu();
    void applyOrder();
    void showOrder();
    void showAllOrder();
    void cancelOrder();
    int id;
    string name, pwd;
};
