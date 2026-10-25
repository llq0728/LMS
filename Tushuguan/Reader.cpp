#include "Reader.h"

// ========== Reader 基类 ==========
Reader::Reader()
    : readerId(""), name(""), password(""), department(""), maxBorrowCount(5), currentBorrowed(0), fine(0) {
}

Reader::Reader(string id, string name, string pwd, string dept, int maxBorrow)
    : readerId(id), name(name), password(pwd), department(dept), maxBorrowCount(maxBorrow), currentBorrowed(0), fine(0) {
}

Reader::~Reader() {}

void Reader::display() const {
    cout << "编号:" << readerId
        << " 姓名:" << name
        << " 院系:" << department
        << " 已借:" << currentBorrowed << "/" << maxBorrowCount
        << " 待缴罚款:" << fine;
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

bool Reader::checkPassword(string pwd) const {
    return password == pwd;
}
void Reader::setPassword(string pwd) {
    password = pwd;
}
bool Reader::payFine(double money) {
    if (money <= 0 || money > fine)
        return false;
    fine -= money;
    return true;
}

string Reader::getReaderId() const { return readerId; }
string Reader::getName() const { return name; }
string Reader::getDepartment() const { return department; }
int Reader::getCurrentBorrowed() const { return currentBorrowed; }
int Reader::getMaxBorrowCount() const { return maxBorrowCount; }
double Reader::getFine() const { return fine; }

void Reader::setName(string newName) { name = newName; }
void Reader::setDepartment(string newDept) { department = newDept; }
void Reader::addFine(double f) { fine += f; }

// ========== Student ==========
Student::Student(string id, string name, string pwd, string dept, string grade)
    : Reader(id, name, pwd, dept, 5), grade(grade) {
}
string Student::getReaderType() const { return "本科生"; }
void Student::display() const {
    Reader::display();
    cout << " 年级:" << grade;
}

// ========== Postgraduate ==========
Postgraduate::Postgraduate(string id, string name, string pwd, string dept, string major, string sup)
    : Reader(id, name, pwd, dept, 8), major(major), supervisor(sup) {
}
string Postgraduate::getReaderType() const { return "研究生"; }
void Postgraduate::display() const {
    Reader::display();
    cout << " 专业:" << major << " 导师:" << supervisor;
}

// ========== Teacher ==========
Teacher::Teacher(string id, string name, string pwd, string dept, string title)
    : Reader(id, name, pwd, dept, 10), title(title) {
}
string Teacher::getReaderType() const { return "教师"; }
void Teacher::display() const {
    Reader::display();
    cout << " 职称:" << title;
}
