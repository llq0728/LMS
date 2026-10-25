#include <iostream>
#include "UI.h"
#include "Library.h"
using namespace std;

// 程序入口，运行整个系统
int main() {
    Library* lib = new Library("我的图书馆");
    UI::init(lib);
    UI::showMain();
    delete lib;
    return 0;
}
