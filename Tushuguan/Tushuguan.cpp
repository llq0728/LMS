#include <iostream>
#include "Resource.h"
#include "Reader.h"
using namespace std;

int main() {

    // ===== 1. 资源类继承演示 =====
    cout << "【资源类继承体系】" << endl;

    // 创建不同类型的资源对象
    Book book("B001", "C++程序设计", "谭浩强", "清华大学出版社",
        "9787302298229", 450, 5);
    Magazine mag("M001", "计算机学报", "中国计算机学会", "计算机学报出版社",
        "0254-4164", 6, 2024, 2);
    EResource eres("E001", "C++ Primer Plus", "Stephen Prata", "人民邮电出版社",
        "PDF", 45.6, 10);

    // 显示各类资源信息
    cout << "普通图书：" << endl;
    book.display(); cout << endl;

    cout << "\n杂志期刊：" << endl;
    mag.display(); cout << endl;

    cout << "\n电子资源：" << endl;
    eres.display(); cout << endl;

    // 验证继承的方法
    cout << "\n【继承方法验证】" << endl;
    cout << "调用基类方法 getTitle(): " << book.getTitle() << endl;
    cout << "调用子类方法 getIsbn(): " << book.getIsbn() << endl;
    cout << "Book的ISBN验证: " << (book.validateISBN() ? "合法" : "不合法") << endl;
    cout << endl;

    // ===== 2. 读者类继承演示 =====
    cout << "\n【读者类继承体系】" << endl;

    Student stu("2024001", "张三", "计算机学院", "2024级");
    Teacher tea("T001", "刘老师", "计算机学院", "副教授");

    cout << "学生：" << endl;
    stu.display(); cout << endl;

    cout << "\n教师：" << endl;
    tea.display(); cout << endl;

    // 验证不同借阅上限
    cout << "\n【不同类型读者的借阅上限】" << endl;
    cout << "学生最多借5本，教师最多借20本" << endl;
    cout << "学生借阅验证：";
    for (int i = 0; i < 7; i++) {
        if (stu.borrowBook()) {
            cout << "第" << i + 1 << "本成功 ";
        }
        else {
            cout << "第" << i + 1 << "本失败(达上限)";
            break;
        }
    }
    cout << "\n学生当前借阅数：" << stu.getCurrentBorrowed() << endl;
    cout << endl;

    // ===== 3. 借阅操作 =====
    cout << "\n【跨类借阅：学生借书】" << endl;

    // 学生借书（需要还几本腾出名额）
    for (int i = 0; i < 3; i++) stu.returnBook();

    if (book.borrowOne() && stu.borrowBook()) {
        cout << stu.getName() << " 成功借阅 《" << book.getTitle() << "》" << endl;
    }
    if (mag.borrowOne() && stu.borrowBook()) {
        cout << stu.getName() << " 成功借阅《" << mag.getTitle() << "》" << endl;
    }
    if (eres.borrowOne() && stu.borrowBook()) {
        cout << stu.getName() << " 成功借阅《" << eres.getTitle() << "》" << endl;
    }

    cout << "\n借阅后学生状态：" << endl;
    stu.display(); cout << endl;

    cout << "\n借阅后资源状态：" << endl;
    book.display(); cout << endl;
    mag.display(); cout << endl;
    eres.display(); cout << endl;

    return 0;
}
