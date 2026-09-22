/*
 * 学生类 —— 与Book类形成依赖关系
 *
 * 依赖关系体现：
 * - Student的borrowBook函数参数是 Book*（指针传递）
 * - 学生借书时，会修改Book对象的状态（借出数量+1）
 * - 同时修改Student自身的状态（已借数量+1）
 * - 这是典型的 use a 关系
 */

#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include "Book.h"
using namespace std;

class Student {
private:
    string studentId;     // 学号
    string name;          // 姓名
    string department;    // 院系
    int maxBorrowCount;   // 最大借阅数量
    int currentBorrowed;  // 当前已借数量

public:
    Student();
    Student(string id, string name, string dept, int maxBorrow);
    Student(const Student& other);
    ~Student();

    // 基本操作
    void display() const;

    // ===== 依赖关系：学生借书（传Book指针）=====
    // 参数用指针是因为需要修改Book对象的状态
    bool borrowBook(Book* book);   // 借书
    bool returnBook(Book* book);   // 还书

    // Getter & Setter
    string getStudentId() const;
    string getName() const;
    int getCurrentBorrowed() const;
    int getMaxBorrowCount() const;
    bool canBorrowMore() const; // 是否还能借书
};

#endif
