#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <algorithm>
#include <windows.h>
#include "ds.hpp"
#include "io.hpp"
#include "func.hpp"
#include "ui.hpp"
using namespace std;

int main()
{
    list L = new examinee();
    welcome();
    load(L);
    do showMenu();
    while (chooseFunc(L));
    save(L);
    return 0;
}
