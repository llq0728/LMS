#include "Library.h"
#include <iostream>

Library::Library(string name) : libraryName(name), bookCount(0) {}

Library::~Library() {}

bool Library::addBook(const Book& book) {
    if (bookCount >= MAX_BOOKS) {
        cout << "图书馆已满，无法添加新图书！" << endl;
        return false;
    }

    // 检查是否已存在
    for (int i = 0; i < bookCount; i++) {
        if (books[i].getBookId() == book.getBookId()) {
            cout << "图书编号已存在！" << endl;
            return false;
        }
    }

    books[bookCount] = book; // 赋值操作
    bookCount++;
    cout << "成功添加图书：" << book.getBookName() << endl;
    return true;
}

bool Library::removeBook(string bookId) {
    for (int i = 0; i < bookCount; i++) {
        if (books[i].getBookId() == bookId) {
            cout << "删除图书：" << books[i].getBookName() << endl;
            // 后面的往前移
            for (int j = i; j < bookCount - 1; j++) {
                books[j] = books[j + 1];
            }
            bookCount--;
            return true;
        }
    }
    cout << "未找到编号为 " << bookId << " 的图书！" << endl;
    return false;
}

Book* Library::findBook(string bookId) {
    for (int i = 0; i < bookCount; i++) {
        if (books[i].getBookId() == bookId) {
            return &books[i]; // 返回指针
        }
    }
    return nullptr;
}

void Library::displayAllBooks() const {
    cout << "\n===== " << libraryName << " 图书目录（共"
        << bookCount << "种）=====" << endl;
    for (int i = 0; i < bookCount; i++) {
        cout << "[" << i + 1 << "] ";
        books[i].display();
        cout << endl;
    }
    cout << "==========================================" << endl;
}

string Library::getLibraryName() const { return libraryName; }
int Library::getBookCount() const { return bookCount; }
