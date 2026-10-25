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

    virtual string getReaderType() const = 0;
    virtual void displayBase() const;
    virtual void display() const = 0;

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
    ~Student() override;
    string getReaderType() const override;
    void display() const override;
};

class Teacher : public Reader {
private:
    string title;
public:
    Teacher();
    Teacher(string id, string name, string dept, string title);
    ~Teacher() override;
    string getReaderType() const override;
    void display() const override;
};
#endif
