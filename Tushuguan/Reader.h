/*
 * 读者类 —— 也使用虚函数实现多态
 */
#ifndef READER_H
#define READER_H
#include <string>
#include <iostream>
using namespace std;

class Reader {
protected:
    string readerId;
    string name;
    string department;
    int maxBorrowCount;
    int currentBorrowed;
public:
    Reader();
    Reader(string id, string name, string dept, int maxBorrow);
    virtual ~Reader();
    //纯虚函数，头文件这里加上override
    virtual string getReaderType() const = 0;
    virtual void displayBase() const;
    virtual void display() const;

    bool borrowBook();
    bool returnBook();
    bool canBorrowMore() const;
    string getReaderId() const;
    string getName() const;
    int getCurrentBorrowed() const;
    int getMaxBorrowCount() const;
};

class Student : public Reader {
private:
    string grade;
public:
    Student();
    Student(string id, string name, string dept, string grade);
    ~Student();
    // 头文件这里加override，cpp里面不能写
    string getReaderType() const override;
    void display() const;
};

class Teacher : public Reader {
private:
    string title;
public:
    Teacher();
    Teacher(string id, string name, string dept, string title);
    ~Teacher();
    string getReaderType() const override;
    void display() const;
};

#endif