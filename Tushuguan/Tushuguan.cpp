#include <iostream>
#include "UI.h"
#include "Library.h"
using namespace std;

// 程序入口，运行整个系统
int main() {
    Library* lib = new Library("我的图书馆");

    // ===== 预置几个测试资源，方便一进来就能演示 =====
    lib->addResource(new Book("B001", "C++程序设计", "谭浩强", "清华大学出版社",
        "9787302298229", 450, 5, 30));
    lib->addResource(new Book("B002", "数据结构", "严蔚敏", "清华大学出版社",
        "9787302147510", 380, 3, 30));
    lib->addResource(new Magazine("M001", "计算机学报", "中国计算机学会", "计算机学报出版社",
        "0254-4164", 6, 2026, 2, 14));

    // ===== 预置几个测试读者：编号 / 密码 =====
    lib->addReader(new Student("2024001", "张三", "123456", "计算机学院", "2024级"));
    lib->addReader(new Teacher("T001", "刘老师", "123456", "计算机学院", "副教授"));

    UI::init(lib);
    UI::showMain();
    delete lib;
    return 0;
}
