/*
 * ==============================================
 *     实验一：类与对象 —— 主程序
 * ==============================================
 *
 * 演示内容：
 * 1. 使用默认构造函数创建对象
 * 2. 使用重载构造函数创建对象
 * 3. 使用拷贝构造函数创建对象
 * 4. 调用成员函数操作对象
 * 5. ISBN合法性验证
 * 6. 借书/还书操作
 */

#include <iostream>
#include "Book.h"
using namespace std;

int main() {
    cout << "===== 实验一：类与对象 演示 =====" << endl << endl;

    // ===== 1. 默认构造函数 =====
    cout << "【1】使用默认构造函数创建图书：" << endl;
    Book book1;
    book1.display();
    cout << endl;

    // ===== 2. 重载构造函数 =====
    cout << "【2】使用重载构造函数创建图书：" << endl;
    Book book2("B002", "9787302147510", "数据结构",
        "严蔚敏", "清华大学出版社", 39.0, 380);
    book2.display();
    cout << endl;

    // ===== 3. 拷贝构造函数 =====
    cout << "【3】使用拷贝构造函数创建图书副本：" << endl;
    Book book3 = book2; // 调用拷贝构造
    book3.setBookId("B003"); // 修改副本编号
    book3.display();
    cout << endl;

    // ===== 4. 修改数据成员 =====
    cout << "【4】修改图书信息：" << endl;
    book1.setBookName("C++程序设计（第五版）");
    book1.setPrice(59.9);
    book1.setPages(520);
    cout << "修改后：" << book1.getBookName()
        << "，价格：¥" << book1.getPrice()
        << "，页数：" << book1.getPages() << "页" << endl;
    cout << endl;

    // ===== 5. ISBN 验证 =====
    cout << "【5】ISBN 合法性验证：" << endl;
    Book bookBad("B999", "12345", "测试书", "作者", "出版社", 10, 100);
    cout << "book2 ISBN(" << book2.getIsbn() << ")："
        << (book2.validateISBN() ? "合法" : "不合法") << endl;
    cout << "bookBad ISBN(" << bookBad.getIsbn() << ")："
        << (bookBad.validateISBN() ? "合法" : "不合法") << endl;
    cout << endl;

    // ===== 6. 借书/还书操作 =====
    cout << "【6】借阅操作演示：" << endl;
    cout << "第一次借阅：" << endl;
    book1.borrowBook();
    cout << "第二次借阅：" << endl;
    book1.borrowBook(); // 应该失败
    cout << "归还图书：" << endl;
    book1.returnBook();
    cout << "再次借阅：" << endl;
    book1.borrowBook(); // 应该成功
    cout << endl;

    cout << "===== 演示结束 =====" << endl;
    return 0;
}
