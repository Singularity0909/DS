#include <iostream>
#include <fstream>
#include <streambuf>
#include <cmath>
#include <vector>
#include <queue>
using namespace std;

int tot, cnt[256], val[256];
string code[256];
struct node
{
    char c;
    int v;
    node *ls, *rs;
    node(char c, int v)
    {
        this->c = c;
        this->v = v;
        this->ls = this->rs = nullptr;
    }
    bool isLeaf() { return !ls && !rs; }
    bool operator < (const node& x) { return v > x.v; }
};
struct cmp { bool operator () (node* a, node* b) { return *a < *b; } };
priority_queue<node*, vector<node*>, cmp> q;

node* build()
{
    node* rt = nullptr;
    while (q.size() > 1)
    {
        node* a = q.top();
        q.pop();
        node* b = q.top();
        q.pop();
        node* c = new node(0, a->v + b->v);
        c->ls = a;
        c->rs = b;
        q.push(rt = c);
    }
    q.pop();
    return rt;
}

void dfs(node* now, string path)
{
    if (now->isLeaf())
    {
        code[now->c] = path;
        return;
    }
    if (now->ls) dfs(now->ls, path + "0");
    if (now->rs) dfs(now->rs, path + "1");
}

int getVal(const string& s)
{
    int sum = 0;
    int len = (int)s.length();
    for (int i = len - 1; i >= 0; i--) sum += pow(2, len - i - 1) * (s[i] - '0');
    return sum;
}

void encode()
{
    string file_in, file_out;
    cout << "请输入需要加密的文本文件名: ";
    cin >> file_in;
    cout << "请输入加密后的文件名: ";
    cin >> file_out;
    tot = 0;
    memset(cnt, 0, sizeof(cnt));
    ifstream in(file_in + ".txt");
    string text((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());
    int len = (int)text.length();
    for (int i = 0; i < len; i++) cnt[text[i]]++;
    in.close();
    for (int i = 0; i < 256; i++)
    {
        if (cnt[i])
        {
            tot++;
            q.push(new node(i, cnt[i]));
        }
    }
    node* rt = build();
    dfs(rt, "");
//    for (int i = 0; i < 256; i++) if (cnt[i]) cout << char(i) << " " << code[i] << endl;
    ofstream out(file_out + ".txt", ios::binary);
    out.write((char*)&tot, 4);
    for (int i = 0; i < 256; i++)
    {
        if (cnt[i])
        {
            int val = getVal(code[i]);
            int len = (int)code[i].length();
            out.write((char*)&i, 1);
            out.write((char*)&val, 2);
            out.write((char*)&len, 4);
        }
    }
    string codes;
    out.write((char*)&len, 4);
    for (int i = 0; i < len; i++) codes += code[text[i]];
    len = (int)codes.length();
    int tail = len % 8;
    len += tail;
    for (int i = 0; i < 8 - tail; i++) codes += "0";
    for (int i = 0; i < len / 8; i++)
    {
        int c = getVal(codes.substr(i * 8, 8));
        out.write((char*)&c, 1);
    }
    out.close();
    cout << endl << "加密成功" << endl;
}

string getStr(int v)
{
    string res;
    for (int i = 0; i < 8; i++)
    {
        if (v & 1) res = "1" + res;
        else res = "0" + res;
        v >>= 1;
    }
    return res;
}

char find(int v, int len)
{
    for (int i = 0; i < 256; i++)
        if (val[i] == v && cnt[i] == len)
            return i;
    return 0;
}

void decode()
{
    string file_in, file_out;
    cout << "请输入需要解密的文本文件名: ";
    cin >> file_in;
    cout << "请输入解密后的文件名: ";
    cin >> file_out;
    memset(val, 0, sizeof(val));
    ifstream in(file_in + ".txt", ios::binary);
    in.read((char*)&tot, 4);
    for (int i = 0; i < tot; i++)
    {
        char c;
        in.read((char*)&c, 1);
        in.read((char*)&val[c], 2);
        in.read((char*)&cnt[c], 4);
    }
    int tlen;
    in.read((char*)&tlen, 4);
    string codes, text;
    while (!in.eof())
    {
        int code;
        in.read((char*)&code, 1);
        codes += getStr(code);
    }
    in.close();
    for (int i = 0, v = 0, last = -1; tlen; i++)
    {
        v = v << 1 | codes[i] - '0';
        char ch;
        if ((ch = find(v, i - last)))
        {
            text.push_back(ch);
            tlen--;
            v = 0;
            last = i;
        }
    }
    ofstream out(file_out + ".txt");
    out << text;
    out.close();
    cout << endl << "解密成功" << endl;
}

bool chooseFunc()
{
    int op;
    cin >> op;
    switch (op)
    {
        case 1: encode(); break;
        case 2: decode(); break;
        case 3: return false;
        default: cout << "指令无效，请重新输入！" << endl;
    }
    return true;
}

void showMenu()
{
    cout << "请输入您需要进行的操作标号" << endl;
    cout << "---------------------" << endl << endl;
    cout << "1\t加密文本" << endl << endl;
    cout << "2\t解密文本" << endl << endl;
    cout << "3\t退出程序" << endl << endl;
    cout << "---------------------" << endl;
}

int main()
{
    do showMenu();
    while (chooseFunc());
    return 0;
}
