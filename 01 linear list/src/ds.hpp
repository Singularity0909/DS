#pragma once
#define size age
using namespace std;

struct examinee // 考生信息
{
    char id[6]; // 准考证号
    char name[10]; // 姓名
    char sex; // 性别
    int age; // 年龄（在头结点中为链表有效节点个数）
    char major[20]; // 报考专业
    examinee* next; // 下一个节点指针
    examinee(const string& s) // 字符串传参构造函数
    {
        memset(id, 0, sizeof(id));
        memset(name, 0, sizeof(name));
        memset(major, 0, sizeof(major));
        int pos[5] = { 0 }; // pos[1: 4] 表示每行中空格的位置
        for (int i = 1; i <= 4; i++) pos[i] = (int)s.find(' ', pos[i - 1] + 1);
        memcpy(this->id, s.substr(0, pos[1]).c_str(), pos[1]);
        memcpy(this->name, s.substr(pos[1] + 1, pos[2] - pos[1] - 1).c_str(), pos[2] - pos[1] - 1);
        this->sex = s[pos[2] + 1];
        this->age = stoi(s.substr(pos[3] + 1, pos[4] - pos[3] - 1));
        memcpy(this->major, s.substr(pos[4] + 1).c_str(), s.length() - pos[4] - 1);
        next = nullptr;
    }
    examinee(){ memset(this, 0, sizeof(examinee)); }
};

using ptr = examinee*; // 链表节点指针
using list = examinee*; // 链表头指针
