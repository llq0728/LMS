#include <iostream>
#include "Library.h"
using namespace std;
int main() {
    cout << "===== 实验四：多态性与虚函数 演示 =====" << endl << endl;
    Library lib("西南科技大学图书馆");

    // ===== 1. 添加不同类型资源（多态参数）=====
    cout << "【添加资源】（基类指针接收不同子类对象）" << endl;
    // Book构造：id,标题,作者,出版社,isbn,页数,馆藏数,借阅期限(30天)
    lib.addResource(new Book("B001", "C++程序设计", "谭浩强", "清华大学出版社",
        "9787302298229", 450, 5, 30));
    lib.addResource(new Book("B002", "数据结构", "严蔚敏", "清华大学出版社",
        "9787302147510", 380, 3, 30));
    // Magazine构造：id,标题,作者,出版社,issn,期号,年份,馆藏数,借阅期限(14天)
    lib.addResource(new Magazine("M001", "计算机学报", "中国计算机学会",
        "计算机学报出版社", "0254-4164", 6, 2024, 2, 14));
    // EResource构造：id,标题,作者,出版社,格式,文件大小,借阅期限(7天)，不再传馆藏
    lib.addResource(new EResource("E001", "C++ Primer Plus", "Stephen Prata",
        "人民邮电出版社", "PDF", 45.6, 7));
    // ===== 2. 多态显示 =====
    cout << "\n【多态显示】同一display()调用，不同类型输出不同内容" << endl;
    lib.displayAllResources();
    // ===== 3. 添加不同类型读者 =====
    cout << "\n【添加读者】" << endl;
    lib.addReader(new Student("2024001", "张三", "计算机学院", "2024级"));
    lib.addReader(new Student("2024002", "李四", "计算机学院", "2024级"));
    lib.addReader(new Teacher("T001", "刘老师", "计算机学院", "副教授"));

    lib.displayAllReaders();
    // ===== 4. 多态借阅 =====
    cout << "\n【多态借阅】不同类型读者借阅不同类型资源" << endl;
    cout << "--------------------------------" << endl;

    // 学生借普通图书
    lib.borrowBook("2024001", "B001");
    // 学生借杂志
    lib.borrowBook("2024001", "M001");
    // 学生尝试借电子资源，会提示电子资源不可外借
    lib.borrowBook("2024001", "E001");
    // 教师借多本
    lib.borrowBook("T001", "B001");
    lib.borrowBook("T001", "B002");
    lib.borrowBook("T001", "M001");
    // 教师尝试借电子资源，同样禁止
    lib.borrowBook("T001", "E001");

    cout << "\n【借阅后的资源状态】" << endl;
    lib.displayAllResources();

    cout << "\n【借阅后的读者状态】" << endl;
    lib.displayAllReaders();
    // ===== 5. 还书 =====
    cout << "\n【还书操作】" << endl;
    lib.returnBook("2024001", "B001");
    lib.returnBook("T001", "B002");

    cout << "\n【最终状态】" << endl;
    lib.displayAllResources();
    cout << "\n===== 演示结束 =====" << endl;
    return 0;
}