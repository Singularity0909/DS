#pragma once
using namespace std;

void print_title()
{
    printf("%10s%10s%10s%10s%10s\n", "准考证号", "姓名", "性别", "年龄", "专业");
    printf("----------------------------------------------------\n");
}

void print_one(const ptr& p)
{
    string sex = p->sex == 'f' ? "女" : "男";
    printf("%10s%10s%10s%10d%10s\n\n", p->id, p->name, sex.c_str(), p->age, p->major);
}

bool cmp(const ptr& a, const ptr& b) { return strcmp(a->id, b->id) < 0; }

void list_all(const list& L)
{
    system("cls");
    ptr now = L->next;
    ptr* all = new ptr[L->size];
    for (int i = 0; i < L->size && now != nullptr; i++)
    {
        all[i] = now;
        now = now->next;
    }
    sort(all, all + L->size, cmp); // 根据节点准考证号排序
    print_title();
    for (int i = 0; i < L->size; i++) print_one(all[i]);
    cout << endl;
}

ptr find_id(const list& L, const string& id)
{
    ptr p = L->next;
    while (p != nullptr)
    {
        if (!strcmp(p->id, id.c_str())) return p;
        p = p->next;
    }
    return nullptr;
}

bool isNumeric(const string& s) // 判断字符串元素是否全为数字
{
    for (int i = 0; i < (int)s.length(); i++)
        if (s[i] < '0' && s[i] > '9')
            return false;
    return true;
}

void insert_one(list& L)
{
    system("cls");
    cout << "请输入考生的准考证号: ";
    string id, name, sex, age, major;
    cin >> id;
    if (find_id(L, id) != nullptr)
    {
        cout << "该号码已存在！" << endl;
        return;
    }
    else if (!isNumeric(id) || id.length() != 5)
    {
        cout << "号码格式有误！" << endl;
        return;
    }
    cout << "请输入考生的姓名: ";
    cin >> name;
    cout << "请输入考生的性别: ";
    cin >> sex;
    if (sex == "男") sex = "m";
    else if (sex == "女") sex = "f";
    else
    {
        cout << "性别有误！" << endl;
        return;
    }
    cout << "请输入考生的年龄: ";
    cin >> age;
    if (!isNumeric(age))
    {
        cout << "年龄有误！" << endl;
        return;
    }
    cout << "请输入考生所要报考的专业: ";
    cin >> major;
    string line = id + " " + name + " " + sex + " " + age + " " + major;
    ptr p = new examinee(line);
    p->next = L->next;
    L->next = p;
    L->size++;
    cout << "考生信息添加成功" << endl;
}

void delete_one(list& L)
{
    system("cls");
    cout << "请输入考生的准考证号: ";
    string id;
    cin >> id;
    ptr pre = L, now = L->next;
    bool found = false;
    while (now != nullptr)
    {
        if (now->id == id)
        {
            found = true;
            cout << "该考生当前信息如下: " << endl;
            print_title();
            print_one(now);
            cout << "输入【YES】确认删除，否则取消操作" << endl;
            string opt;
            cin >> opt;
            if (opt == "YES")
            {
                pre->next = now->next;
                delete now;
                L->size--;
                cout << "考生信息删除成功" << endl;
            }
            break;
        }
        pre = now;
        now = now->next;
    }
    if (!found) cout << "该号码不存在！" << endl;
}

void query(const list& L)
{
    system("cls");
    cout << "请输入查询方式（序号）" << endl;
    cout << "1: 准考证号\t" << "2: 姓名" << endl;
    int opt;
    cin >> opt;
    string id, name;
    ptr p;
    bool found = false;
    switch (opt)
    {
        case 1:
            cout << "请输入考生的准考证号: ";
            cin >> id;
            p = find_id(L, id);
            if (p != nullptr)
            {
                print_title();
                print_one(p);
            }
            else cout << "该号码不存在！" << endl;
            break;
        case 2:
            cout << "请输入考生的姓名: ";
            cin >> name;
            p = L->next;
            while (p != nullptr)
            {
                if (!strcmp(p->name, name.c_str()))
                {
                    if (!found) print_title();
                    print_one(p);
                    found = true;
                }
                p = p->next;
            }
            if (!found) cout << "该姓名不存在！" << endl;
            break;
        default:
            cout << "指令格式有误！" << endl;
            break;
    }
}

void update(list& L)
{
    system("cls");
    cout << "请输入考生的准考证号: ";
    string id;
    cin >> id;
    ptr p = find_id(L, id);
    if (p != nullptr)
    {
        cout << "该考生的当前信息如下: " << endl;
        print_title();
        print_one(p);
        system("pause");
        cout << "请输入考生的准考证号: ";
        string id, name, sex, age, major;
        cin >> id;
        if (id != string(p->id) && find_id(L, id) != nullptr)
        {
            cout << "该号码已存在！" << endl;
            return;
        }
        else if (!isNumeric(id) || id.length() != 5)
        {
            cout << "号码格式有误！" << endl;
            return;
        }
        cout << "请输入考生的姓名: ";
        cin >> name;
        cout << "请输入考生的性别: ";
        cin >> sex;
        if (sex == "男") sex = "m";
        else if (sex == "女") sex = "f";
        else
        {
            cout << "性别有误！" << endl;
            return;
        }
        cout << "请输入考生的年龄: ";
        cin >> age;
        if (!isNumeric(age))
        {
            cout << "年龄有误！" << endl;
            return;
        }
        cout << "请输入考生所要报考的专业: ";
        cin >> major;
        memcpy(p->id, id.c_str(), id.length());
        memcpy(p->name, name.c_str(), name.length());
        p->sex = sex[0];
        age = stoi(age);
        memcpy(p->major, major.c_str(), major.length());
        cout << "考生信息修改成功" << endl;
    }
    else cout << "该号码不存在！" << endl;
}
