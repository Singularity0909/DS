#pragma once
using namespace std;

void welcome()
{
    system("color 3f");
    cout << "--------------------------" << endl;
    cout << "欢迎使用考试报名管理工具！" << endl;
    cout << "--------------------------" << endl;
    cout << endl << "正在加载，请稍后" << endl;
    for (int i = 0; i < 20; i++)
    {
        Sleep(200);
        cout << "■";
    }
    cout << endl << endl;
    system("pause");
}

bool chooseFunc(list& L)
{
    int ope;
    cin >> ope;
    switch (ope)
    {
        case 0: return false;
        case 1: list_all(L); break;
        case 2: insert_one(L); break;
        case 3: delete_one(L); break;
        case 4: query(L); break;
        case 5: update(L); break;
        default: cout << "指令无效，请重新输入！" << endl;
    }
    system("pause");
    return true;
}

void showMenu()
{
    system("cls");
    cout << "请输入您需要进行的操作标号" << endl;
    cout << "---------------------" << endl;
    cout << endl << "0\t退出" << endl << endl;
    cout << "1\t列出全部考生信息" << endl << endl;
    cout << "2\t添加考生信息" << endl << endl;
    cout << "3\t删除考生信息" << endl << endl;
    cout << "4\t查询考生信息" << endl << endl;
    cout << "5\t修改考生信息" << endl << endl;
    cout << "---------------------" << endl;
}
