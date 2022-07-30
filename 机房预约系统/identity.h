#pragma once
#include <iostream>
using namespace std;

class Identity
{
public:
    virtual void open_menu() = 0;
    string name;
    string pwd;
};
