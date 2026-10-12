#include "Reader.h"

// ==================== Reader 基类 ====================
Reader::Reader()
    : readerId(""), name(""), department(""),
    maxBorrowCount(5), currentBorrowed(0)
{
}

Reader::Reader(string id, string name, string dept, int maxBorrow)
    : readerId(id), name(name), department(dept),
    maxBorrowCount(maxBorrow), currentBorrowed(0)
{
}

Reader::~Reader()
{
}

void Reader::display() const
{
    cout << "编号:" << readerId
        << " | 姓名:" << name
        << " | 院系:" << department
        << " | 已借:" << currentBorrowed << "/" << maxBorrowCount << "本";
}

bool Reader::borrowBook()
{
    if (canBorrowMore())
    {
        currentBorrowed++;
        return true;
    }
    return false;
}

bool Reader::returnBook()
{
    if (currentBorrowed > 0)
    {
        currentBorrowed--;
        return true;
    }
    return false;
}

bool Reader::canBorrowMore() const
{
    return currentBorrowed < maxBorrowCount;
}

string Reader::getReaderId() const { return readerId; }
string Reader::getName() const { return name; }
int Reader::getCurrentBorrowed() const { return currentBorrowed; }
int Reader::getMaxBorrowCount() const { return maxBorrowCount; }

// ==================== Student 子类 ====================
Student::Student() : Reader(), grade("")
{
    // 删掉原来 maxBorrowCount =5; 父类构造已经初始化
}

Student::Student(string id, string name, string dept, string grade)
    : Reader(id, name, dept, 5), grade(grade)
{
}

Student::~Student()
{
}

void Student::display() const
{
    Reader::display();
    cout << " | 年级:" << grade << endl;
}

string Student::getGrade() const
{
    return grade;
}

// ==================== Teacher 子类 ====================
Teacher::Teacher() : Reader(), title("")
{
    // 删掉原来 maxBorrowCount =20;
}

Teacher::Teacher(string id, string name, string dept, string title)
    : Reader(id, name, dept, 20), title(title)
{
}

Teacher::~Teacher()
{
}

void Teacher::display() const
{
    Reader::display();
    cout << " | 职称:" << title << endl;
}

string Teacher::getTitle() const
{
    return title;
}
