#include <iostream>
#include <fstream>
#include <cstring>
#include <algorithm>
#include <windows.h>
#include "kmp.hpp"
#include "func.hpp"
#include "ui.hpp"
using namespace std;

int main()
{
    do showMenu();
    while (chooseFunc());
    return 0;
}
