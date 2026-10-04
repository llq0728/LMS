#ifndef BOOK_H
#define BOOK_H

#include <string>
using namespace std;

class Book {
private:
    string bookId;      // 图书编号
    string isbn;        // ISBN号
    string bookName;    // 书名
    string author;      // 作者
    string publisher;   // 出版社
    int totalCount;     // 馆藏总数
    int borrowCount;    // 已借出数量

public:
    Book();
    Book(string id, string isbn, string name, string author,
        string publisher, int total);

    Book(const Book& other);
    ~Book();

    // 基本操作
    void display() const;
    bool validateISBN() const;

    // 借还操作
    bool borrowOne();    // 借出一本
    bool returnOne();    // 归还一本
    bool isAvailable() const; // 是否可借

    // Getter & Setter
    string getBookId() const;
    string getBookName() const;
    string getAuthor() const;
    string getIsbn() const;
    int getTotalCount() const;
    int getBorrowCount() const;
    int getAvailableCount() const;

    void setBookId(string id);
    void setBookName(string name);
    void setTotalCount(int count);
};

#endif
