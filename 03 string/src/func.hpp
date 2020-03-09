#pragma once
using namespace std;

void createFile()
{
    cout << "请输入要新建的文件名：";
    string name;
    cin >> name;
    getchar();
    ofstream out;
    out.open("data/" + name + ".txt");
    if (!out)
    {
        cout << endl << "文本创建失败！" << endl;
        return;
    }
    cout << "请开始逐行输入文本内容 以文件尾为结束符" << endl;
    string line;
    while (getline(cin, line)) out << line << endl;
    cout << endl << "文本创建成功" << endl;
    cin.clear();
    out.close();
}

void wordCount()
{
    cout << "请输入文本文件名：";
    string name;
    cin >> name;
    cout << "请输入模式串（不带空格）：";
    char p[maxn], s[maxn];
    cin >> (p + 1);
    getNext(p);
    ifstream in;
    in.open("data/" + name + ".txt");
    if (!in)
    {
        cout << endl << "文本打开失败，可能不存在该文件！" << endl;
        return;
    }
    string line;
    int cnt = 0;
    while (getline(in, line))
    {
        int len = (int)line.length();
        for (int i = 0; i < len; i++) s[i + 1] = line[i];
        s[0] = s[len + 1] = '\0';
        cnt += kmp(s, p);
    }
    cout << endl << "匹配完成" << endl;
    cout << (p + 1) << " 在文本中共出现" << cnt << "次" << endl;
    in.close();
}

void wordLocate()
{
    cout << "请输入文本文件名：";
    string name;
    cin >> name;
    cout << "请输入模式串（不带空格）：";
    char p[maxn], s[maxn];
    cin >> (p + 1);
    getNext(p);
    ifstream in;
    in.open("data/" + name + ".txt");
    if (!in)
    {
        cout << endl << "文本打开失败，可能不存在该文件！" << endl;
        return;
    }
    string line;
    int nline = 0;
    cout << endl;
    while (getline(in, line))
    {
        nline++;
        int cnt = 0;
        int len = (int)line.length();
        for (int i = 0; i < len; i++) s[i + 1] = line[i];
        s[0] = s[len + 1] = '\0';
        cnt += kmp(s, p);
        if (cnt)
        {
            cout << "在第" << nline << "行出现" << cnt << "次，位置为 ";
            for (int i = 0; i < cnt; i++)
            {
                if (i) cout << "，";
                cout << pos[i];
            }
            cout << endl;
        }
    }
    in.close();
}
