#include <iostream>
#include "Book.h"
#include "Student.h"
#include "Library.h"
using namespace std;

int main() {
    cout << "实验二：组合关系与依赖关系 演示" << endl << endl;

    // ===== 1. 组合关系演示 =====
    cout << "【组合关系演示】Library 组合 Book" << endl;
    Library lib("西南科技大学图书馆");

    // 添加图书（组合关系：图书馆包含图书）
    lib.addBook(Book("B001", "9787302298229", "C++程序设计",
        "谭浩强", "清华大学出版社", 5));
    lib.addBook(Book("B002", "9787302147510", "数据结构",
        "严蔚敏", "清华大学出版社", 3));
    lib.addBook(Book("B003", "9787111407010", "算法导论",
        "Thomas H.Cormen", "机械工业出版社", 2));

    lib.displayAllBooks();
    cout << endl;

    // ===== 2. 依赖关系演示 =====
    cout << "【依赖关系演示】Student 依赖 Book（传指针）" << endl;
    Student stu1("2024001", "张三", "计算机学院", 5);
    Student stu2("2024002", "李四", "计算机学院", 5);

    cout << "\n--- 学生信息 ---" << endl;
    stu1.display(); cout << endl;
    stu2.display(); cout << endl;

    // 通过图书馆找到图书（组合 + 依赖的联动）
    cout << "\n--- 借书操作 ---" << endl;
    Book* book1 = lib.findBook("B001");
    Book* book2 = lib.findBook("B002");
    Book* book3 = lib.findBook("B003");

    // 张三借书（依赖关系：Student.use(Book)）
    stu1.borrowBook(book1);  // 传指针 —— 地址传递
    stu1.borrowBook(book2);
    stu1.borrowBook(book3);

    // 李四借书
    stu2.borrowBook(book1);
    stu2.borrowBook(book1);
    stu2.borrowBook(book3);  // 算法导论只有2本，应该被借完了

    cout << "\n--- 借阅后的图书状态 ---" << endl;
    lib.displayAllBooks();

    cout << "\n--- 借阅后的学生状态 ---" << endl;
    stu1.display(); cout << endl;
    stu2.display(); cout << endl;

    // 还书操作
    cout << "\n--- 还书操作 ---" << endl;
    stu1.returnBook(book2);
    stu2.borrowBook(book2);  // 李四现在能借到了

    cout << "\n--- 最终状态 ---" << endl;
    lib.displayAllBooks();
    stu1.display(); cout << endl;
    stu2.display(); cout << endl;

    // ===== 3. 删除图书演示 =====
    cout << "\n【删除图书演示】" << endl;
    lib.removeBook("B002");
    lib.displayAllBooks();

    cout << "\n演示结束" << endl;

    return 0;
}
