/*
 * 图书馆类 —— 与Book类形成组合关系
 *
 * 组合关系体现：
 * - Library 包含 Book 对象数组（has a 关系）
 * - Library 整体，Book 部分
 * - Library 负责管理所有Book对象的生命周期
 * - Book对象不能脱离Library独立存在（逻辑上）
 */

#ifndef LIBRARY_H
#define LIBRARY_H

#include "Book.h"
#include <string>
using namespace std;

const int MAX_BOOKS = 100; // 最大图书种类数

class Library {
private:
    string libraryName;
    Book books[MAX_BOOKS];  // 组合关系：对象数组
    int bookCount;          // 当前图书种类数

public:
    Library(string name = "图书馆");
    ~Library();

    // ===== 组合关系：图书馆管理图书 =====
    bool addBook(const Book& book);   // 添加图书
    bool removeBook(string bookId);   // 删除图书
    Book* findBook(string bookId);    // 查找图书
    void displayAllBooks() const;     // 显示所有图书

    string getLibraryName() const;
    int getBookCount() const;
};

#endif
