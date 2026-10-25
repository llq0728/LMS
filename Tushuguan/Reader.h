#ifndef READER_H
#define READER_H
#include <string>
#include <iostream>
using namespace std;

// 读者抽象基类
class Reader {
protected:
    string readerId;
    string name;
    string password;
    string department;
    int maxBorrowCount;   // 最多能借几本
    int currentBorrowed;  // 现在已经借了几本
    double fine;          // 罚款
public:
    Reader();
    Reader(string id, string name, string pwd, string dept, int maxBorrow);
    virtual ~Reader();

    virtual string getReaderType() const = 0; // 纯虚函数，抽象类
    virtual void display() const;

    bool borrowBook();
    bool returnBook();
    bool canBorrowMore() const;

    bool checkPassword(string pwd) const;
    void setPassword(string pwd);
    bool payFine(double money);

    string getReaderId() const;
    string getName() const;
    string getDepartment() const;
    int getCurrentBorrowed() const;
    int getMaxBorrowCount() const;
    double getFine() const;

    void setName(string newName);
    void setDepartment(string newDept);
    void addFine(double f);
};

// 本科生
class Student : public Reader {
private:
    string grade; // 年级
public:
    Student(string id, string name, string pwd, string dept, string grade);
    string getReaderType() const override;
    void display() const override;
};

// 研究生
class Postgraduate : public Reader {
private:
    string major;
    string supervisor; // 导师
public:
    Postgraduate(string id, string name, string pwd, string dept, string major, string sup);
    string getReaderType() const override;
    void display() const override;
};

// 教师
class Teacher : public Reader {
private:
    string title; // 职称
public:
    Teacher(string id, string name, string pwd, string dept, string title);
    string getReaderType() const override;
    void display() const override;
};

#endif
