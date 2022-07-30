#pragma once
#include <iostream>
#include <vector>
using namespace std;
#include "identity.h"
#include "student.h"
#include "teacher.h"
#include "computerRoom.h"

class Manager : public Identity
{
public:
    //默认构造
    Manager();

    //有参构造  管理员姓名，密码
    Manager(string name, string pwd);

    //选择菜单
    virtual void open_menu();

    //添加账号
    void addPerson();

    //查看账号
    void showPerson();

    //查看机房信息
    void showComputer();

    //清空预约记录
    void cleanFile();

    void initVector();

    void initComputerVec();
    // 检测重复(学生或教师id, 传入类型), 返回true表示有重复
    bool checkRepeat(int id, int type);

    vector<Student> vStu;
    vector<Teacher> vTea;
    vector<ComputerRoom> vCom;
};