#include "Reader.h"
// ==================== Reader 基类 ====================
Reader::Reader()
    : readerId(""), name(""), department(""),
    maxBorrowCount(5), currentBorrowed(0) {
}
Reader::Reader(string id, string name, string dept, int maxBorrow)
    : readerId(id), name(name), department(dept),
    maxBorrowCount(maxBorrow), currentBorrowed(0) {
}
Reader::~Reader() {}

void Reader::displayBase() const {
    cout << "编号:" << readerId
        << " | 姓名:" << name
        << " | 院系:" << department
        << " | 已借:" << currentBorrowed << "/" << maxBorrowCount << "本";
}

void Reader::display() const {
    displayBase();
}

bool Reader::borrowBook() {
    if (canBorrowMore()) {
        currentBorrowed++;
        return true;
    }
    return false;
}
bool Reader::returnBook() {
    if (currentBorrowed > 0) {
        currentBorrowed--;
        return true;
    }
    return false;
}
bool Reader::canBorrowMore() const {
    return currentBorrowed < maxBorrowCount;
}
string Reader::getReaderId() const { return readerId; }
string Reader::getName() const { return name; }
int Reader::getCurrentBorrowed() const { return currentBorrowed; }
int Reader::getMaxBorrowCount() const { return maxBorrowCount; }

// ==================== Student 子类 ====================
Student::Student() : Reader(), grade("") {
    maxBorrowCount = 5;
}
Student::Student(string id, string name, string dept, string grade)
    : Reader(id, name, dept, 5), grade(grade)
{
}
Student::~Student() {}
// 重点！cpp实现这里，删掉override！！
string Student::getReaderType() const {
    return "学生";
}
void Student::display() const
{
    Reader::displayBase();
    cout << " | 年级:" << grade;
}

// ==================== Teacher 子类 ====================
Teacher::Teacher() : Reader(), title("") {
    maxBorrowCount = 20;
}
Teacher::Teacher(string id, string name, string dept, string title)
    : Reader(id, name, dept, 20), title(title)
{
}
Teacher::~Teacher() {}
// 重点！cpp实现这里，删掉override！！
string Teacher::getReaderType() const {
    return "教师";
}
void Teacher::display() const
{
    Reader::displayBase();
    cout << " | 职称:" << title;
}