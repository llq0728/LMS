#include "Book.h"
#include <iostream>
#include <cctype>

Book::Book() : bookId("B001"), isbn("9787302298229"),
bookName("C++程序设计"), author("谭浩强"),
publisher("清华大学出版社"),
totalCount(5), borrowCount(0) {
}

Book::Book(string id, string isbn, string name, string author,
    string publisher, int total)
    : bookId(id), isbn(isbn), bookName(name), author(author),
    publisher(publisher), totalCount(total), borrowCount(0) {
}

Book::Book(const Book& other)
    : bookId(other.bookId), isbn(other.isbn),
    bookName(other.bookName), author(other.author),
    publisher(other.publisher), totalCount(other.totalCount),
    borrowCount(other.borrowCount) {
}

Book::~Book() {}

void Book::display() const {
    cout << "编号:" << bookId
        << " | 书名:" << bookName
        << " | 作者:" << author
        << " | 出版社:" << publisher
        << " | 馆藏:" << totalCount << "本"
        << " | 可借:" << (totalCount - borrowCount) << "本";
}

bool Book::validateISBN() const {
    if (isbn.length() != 10 && isbn.length() != 13) return false;
    for (char c : isbn) {
        if (!isdigit(c)) return false;
    }
    return true;
}

bool Book::borrowOne() {
    if (borrowCount < totalCount) {
        borrowCount++;
        return true;
    }
    return false;
}

bool Book::returnOne() {
    if (borrowCount > 0) {
        borrowCount--;
        return true;
    }
    return false;
}

bool Book::isAvailable() const {
    return borrowCount < totalCount;
}

string Book::getBookId() const { return bookId; }
string Book::getBookName() const { return bookName; }
string Book::getAuthor() const { return author; }
string Book::getIsbn() const { return isbn; }
int Book::getTotalCount() const { return totalCount; }
int Book::getBorrowCount() const { return borrowCount; }
int Book::getAvailableCount() const { return totalCount - borrowCount; }

void Book::setBookId(string id) { bookId = id; }
void Book::setBookName(string name) { bookName = name; }
void Book::setTotalCount(int count) { totalCount = count; }
