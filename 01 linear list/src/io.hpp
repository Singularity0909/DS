#pragma once
using namespace std;

void load(list& L) // 将文件中的考生信息读入内存
{
    ifstream in;
    in.open("data/info.txt");
    if (!in)
    {
        cout << "数据异常!" << endl;
        system("pause");
        exit(0);
    }
    string line;
    while (getline(in, line))
    {
        ptr p = new examinee(line);
        p->next = L->next;
        L->next = p;
        L->size++;
    }
    in.close();
}

void save(const list& L) // 将内存中的考生信息写入文件
{
    ofstream out;
    out.open("data/info.txt");
    if (!out)
    {
        cout << "数据异常!" << endl;
        system("pause");
        exit(0);
    }
    ptr now = L->next;
    while (now != nullptr)
    {
        string line;
        line += string(now->id) + " ";
        line += string(now->name) + " ";
        line += now->sex;
        line += " " + to_string(now->age) + " ";
        line += string(now->major);
        out << line << endl;
        now = now->next;
    }
    out.close();
}
