#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>
#include "manager.h"
#include "globalFile.h"

//默认构造
Manager::Manager()
{
}

//有参构造
Manager::Manager(string name, string pwd)
{
    this->name = name;
    this->pwd = pwd;

    this->initVector();
    this->initComputerVec();
}

void Manager::initComputerVec()
{
    ifstream ifs;
    ifs.open(COMPUTER_FILE, ios::in);
    if (!ifs.is_open())
    {
        cout << "打开文件失败";
        return;
    }
    ComputerRoom c;
    while (ifs >> c.m_ComId && ifs >> c.m_MaxNum)
    {
        vCom.push_back(c);
    }
    cout << "当前机房数量: " << vCom.size() << endl;
    ifs.close();
}

//选择菜单
void Manager::open_menu()
{
    cout << "欢迎管理员：" << this->name << "登录！" << endl;
    cout << "\t\t ---------------------------------\n";
    cout << "\t\t|                                |\n";
    cout << "\t\t|          1.添加账号            |\n";
    cout << "\t\t|                                |\n";
    cout << "\t\t|          2.查看账号            |\n";
    cout << "\t\t|                                |\n";
    cout << "\t\t|          3.查看机房            |\n";
    cout << "\t\t|                                |\n";
    cout << "\t\t|          4.清空预约            |\n";
    cout << "\t\t|                                |\n";
    cout << "\t\t|          0.注销登录            |\n";
    cout << "\t\t|                                |\n";
    cout << "\t\t ---------------------------------\n";
    cout << "请选择您的操作： " << endl;
}

//添加账号
void Manager::addPerson()
{
    cout << "请输入添加账号的类型" << endl;
    cout << "1、添加学生" << endl;
    cout << "2、添加老师" << endl;
    string fileName, tip, error_tip;
    ofstream ofs;
    int select = 0;
    cin >> select;

    if (select == 1)
    {
        fileName = STUDENT_FILE;
        tip = "请输入学号: ";
        error_tip = "学号重复, 请重新输入";
    }
    else
    {
        fileName = TEACHER_FILE;
        tip = "请输入职工编号: ";
        error_tip = "职工编号重复, 请重新输入";
    }

    int id;
    string name, pwd;
    ofs.open(fileName, ios::app);

    while (true)
    {
        cout << tip << endl;
        cin >> id;
        bool res = this->checkRepeat(id, select);
        if (res)
            cout << error_tip << endl;
        else
            break;
    }

    cout << "请输入姓名: " << endl;
    cin >> name;
    cout << "请输入密码: " << endl;
    cin >> pwd;

    ofs << id << ' ' << name << ' ' << pwd << endl;
    cout << "添加成功" << endl;
    system("pause");
    system("cls");
    ofs.close();
    this->initVector();
    return;
}

void printStudent(Student &s)
{
    cout << "学号： " << s.id << " 姓名： " << s.name << " 密码：" << s.pwd << endl;
}
void printTeacher(Teacher &t)
{
    cout << "职工号： " << t.m_EmpId << " 姓名： " << t.name << " 密码：" << t.pwd << endl;
}

//查看账号
void Manager::showPerson()
{
    cout << "请选择查看内容：" << endl;
    cout << "1、查看所有学生" << endl;
    cout << "2、查看所有老师" << endl;

    int select = 0;

    cin >> select;

    if (select == 1)
    {
        cout << "所有学生信息如下： " << endl;
        for_each(vStu.begin(), vStu.end(), printStudent);
    }
    else
    {
        cout << "所有老师信息如下： " << endl;
        for_each(vTea.begin(), vTea.end(), printTeacher);
    }
    system("pause");
    system("cls");
}

//查看机房信息
void Manager::showComputer()
{
    cout << "机房信息如下: " << endl;
    for (vector<ComputerRoom>::iterator it = vCom.begin(); it != vCom.end(); it++)
    {
        cout << "机房编号: " << it->m_ComId << "  机房最大容量: " << it->m_MaxNum << endl;
    }
    system("pause");
    system("cls");
}

//清空预约记录
void Manager::cleanFile()
{
    ofstream ofs(ORDER_FILE, ios::trunc);
    ofs.close();

    cout << "清空成功！" << endl;
    system("pause");
    system("cls");
}

void Manager::initVector()
{
    ifstream ifs;
    ifs.open(STUDENT_FILE, ios::in);
    if (!ifs.is_open())
    {
        cout << "文件读取失败" << endl;
        return;
    }

    vStu.clear();
    vTea.clear();

    Student s;
    while (ifs >> s.id && ifs >> s.name && ifs >> s.pwd)
    {
        vStu.push_back(s);
    }
    cout << "当前学生数量: " << vStu.size() << endl;
    ifs.close();

    ifs.open(TEACHER_FILE, ios::in);
    if (!ifs.is_open())
    {
        cout << "文件读取失败" << endl;
        return;
    }

    Teacher t;
    while (ifs >> t.m_EmpId && ifs >> t.name && ifs >> t.pwd)
    {
        vTea.push_back(t);
    }
    cout << "当前教师数量: " << vTea.size() << endl;
    ifs.close();
    return;
}

bool Manager::checkRepeat(int id, int type)
{
    if (type == 1)
    {
        for (vector<Student>::iterator it = vStu.begin(); it != vStu.end(); it++)
            if (id == it->id)
                return true;
    }
    else
    {
        for (vector<Teacher>::iterator it = vTea.begin(); it != vTea.end(); it++)
            if (id == it->m_EmpId)
                return true;
    }
    return false;
}
