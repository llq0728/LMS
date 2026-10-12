#ifndef READER_H
#define READER_H

#include <string>
#include <iostream>
using namespace std;

// 读者基类
class Reader
{
protected:
    string readerId;      // 编号
    string name;          // 姓名
    string department;    // 院系
    int maxBorrowCount;   // 最大借阅数
    int currentBorrowed;  // 当前已借数

public:
    Reader();
    Reader(string id, string name, string dept, int maxBorrow);
    virtual ~Reader();   // 虚析构

    virtual void display() const;  // 虚函数，子类重写

    bool borrowBook();
    bool returnBook();
    bool canBorrowMore() const;

    string getReaderId() const;
    string getName() const;
    int getCurrentBorrowed() const;
    int getMaxBorrowCount() const; // 补上这个函数声明，cpp里用到
};

// 学生类（公有继承 Reader）
class Student : public Reader
{
private:
    string grade;     // 年级
public:
    Student();
    Student(string id, string name, string dept, string grade);
    ~Student();

    void display() const override;  // 重写虚函数
    string getGrade() const;
};

// 教师类（公有继承 Reader）
class Teacher : public Reader
{
private:
    string title;     // 职称
public:
    Teacher();
    Teacher(string id, string name, string dept, string title);
    ~Teacher();

    void display() const override;  // 重写虚函数
    string getTitle() const;
};

#endif
