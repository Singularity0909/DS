#pragma once
using namespace std;

bool chooseFunc()
{
    int ope;
    cin >> ope;
    switch (ope)
    {
        case 1: init(); break;
        case 2: dijkstra(); break;
        case 3: floyd(); break;
        case 4: return false;
        default: cout << "指令无效，请重新输入" << endl;
    }
    return true;
}

void showMenu()
{
    cout << "请输入您需要进行的操作标号" << endl;
    cout << "---------------------" << endl << endl;
    cout << "1\t初始化交通网络图" << endl << endl;
    cout << "2\t获取单源最短路径" << endl << endl;
    cout << "3\t获取多源最短路径" << endl << endl;
    cout << "4\t退出程序" << endl << endl;
    cout << "---------------------" << endl;
}
