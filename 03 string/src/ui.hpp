#pragma once
using namespace std;

bool chooseFunc()
{
    int ope;
    cin >> ope;
    switch (ope)
    {
        case 1: createFile(); break;
        case 2: wordCount(); break;
        case 3: wordLocate(); break;
        case 4: return false;
        default: cout << "指令无效，请重新输入！" << endl;
    }
    system("pause");
    return true;
}

void showMenu()
{
    system("cls");
    cout << "请输入您需要进行的操作标号" << endl;
    cout << "---------------------" << endl << endl;
    cout << "1\t新建文本" << endl << endl;
    cout << "2\t单词计数" << endl << endl;
    cout << "3\t单词定位" << endl << endl;
    cout << "4\t退出程序" << endl << endl;
    cout << "---------------------" << endl;
}
