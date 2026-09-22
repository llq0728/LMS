#include "Student.h"
#include <iostream>

Student::Student()
    : studentId("2024001"), name("张三"),
    department("计算机学院"), maxBorrowCount(5),
    currentBorrowed(0) {
}

Student::Student(string id, string name, string dept, int maxBorrow)
    : studentId(id), name(name), department(dept),
    maxBorrowCount(maxBorrow), currentBorrowed(0) {
}

Student::Student(const Student& other)
    : studentId(other.studentId), name(other.name),
    department(other.department),
    maxBorrowCount(other.maxBorrowCount),
    currentBorrowed(other.currentBorrowed) {
}

Student::~Student() {}

void Student::display() const {
    cout << "学号:" << studentId
        << " | 姓名:" << name
        << " | 院系:" << department
        << " | 已借:" << currentBorrowed << "/" << maxBorrowCount << "本";
}

// ===== 依赖关系核心：借书 =====
// 传Book指针，修改Book对象状态 —— 典型的依赖关系
bool Student::borrowBook(Book* book) {
    // 判断学生是否还能借
    if (!canBorrowMore()) {
        cout << "[" << name << "] 借阅失败：已达最大借阅数量！" << endl;
        return false;
    }

    // 判断图书是否可借
    if (!book->isAvailable()) {
        cout << "[" << name << "] 借阅失败：《" << book->getBookName()
            << "》已全部借出！" << endl;
        return false;
    }

    // 双方状态都改变
    if (book->borrowOne()) {
        currentBorrowed++;
        cout << "[" << name << "] 成功借阅《" << book->getBookName() << "》" << endl;
        return true;
    }

    return false;
}

bool Student::returnBook(Book* book) {
    if (currentBorrowed <= 0) {
        cout << "[" << name << "] 归还失败：没有借阅任何图书！" << endl;
        return false;
    }

    book->returnOne();
    currentBorrowed--;
    cout << "[" << name << "] 成功归还《" << book->getBookName() << "》" << endl;
    return true;
}

string Student::getStudentId() const { return studentId; }
string Student::getName() const { return name; }
int Student::getCurrentBorrowed() const { return currentBorrowed; }
int Student::getMaxBorrowCount() const { return maxBorrowCount; }

bool Student::canBorrowMore() const {
    return currentBorrowed < maxBorrowCount;
}
