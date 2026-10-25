#ifndef RESOURCE_H
#define RESOURCE_H
#include <string>
#include <iostream>
using namespace std;

// 资源基类，抽象类
class Resource {
protected:
    string resId;      // 资源编号
    string title;      // 标题
    string author;     // 作者
    string publisher;  // 出版社
    int borrowPeriod;  // 借阅天数
public:
    Resource();
    Resource(string id, string title, string author, string publisher, int borrowPeriod);
    virtual ~Resource();  // 虚析构，多态释放内存

    // 纯虚函数，子类必须自己实现，让Resource变成抽象类，不能直接new
    virtual void display() const = 0;
    virtual string getTypeName() const = 0;

    string getResId() const;
    string getTitle() const;
    int getBorrowPeriod() const;
    void setTitle(string title);
};

// 纸质资源中间类：图书、杂志继承它，有馆藏数量，可以借阅
class PaperResource : public Resource {
protected:
    int totalCount;     // 总馆藏
    int availableCount;  // 当前可借数量
public:
    PaperResource();
    PaperResource(string id, string title, string author, string publisher, int totalCount, int borrowPeriod);

    bool borrowOne();   // 借一本
    bool returnOne();   // 还一本
    bool isAvailable() const;

    int getAvailableCount() const;
};

// 图书子类
class Book : public PaperResource {
private:
    string isbn;
    int pages;
public:
    Book(string id, string title, string author, string publisher, string isbn, int pages, int totalCount, int borrowPeriod);
    void display() const override;
    string getTypeName() const override;
};

// 杂志子类
class Magazine : public PaperResource {
private:
    string issn;
    int issue;   // 期号
    int year;    // 出版年份
public:
    Magazine(string id, string title, string author, string publisher, string issn, int issue, int year, int totalCount, int borrowPeriod);
    void display() const override;
    string getTypeName() const override;
};

// 电子资源：不能外借，没有馆藏数量
class EResource : public Resource {
private:
    string format;    // 文件格式 PDF/EPUB
    double sizeMb;    // 文件大小
public:
    EResource(string id, string title, string author, string publisher, string format, double sizeMb, int borrowPeriod);
    void display() const override;
    string getTypeName() const override;
};

#endif
