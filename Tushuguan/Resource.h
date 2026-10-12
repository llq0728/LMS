#ifndef RESOURCE_H
#define RESOURCE_H
#include <iostream>
#include <string>
using namespace std;

//资源基类
class Resource
{
protected:
    string resId;
    string title;
    string author;
    string publisher;
    int totalCount;
    int availableCount;
    int borrowPeriod;
public:
    Resource();
    Resource(string id, string title, string author, string publisher,
        int totalCount, int borrowPeriod);
    virtual ~Resource();

    void displayBase() const;
    virtual void display() const = 0; //纯虚函数，Resource抽象类

    bool borrowOne();
    bool returnOne();
    bool isAvailable() const;

    string getResId() const;
    string getTitle() const;
    int getAvailableCount() const;
    int getBorrowPeriod() const;

    void setTitle(string title);
    void addCount(int num);
};

//图书子类
class Book : public Resource
{
protected:
    string isbn;
    int pages;
public:
    Book();
    Book(string id, string title, string author, string publisher,
        string isbn, int pages, int totalCount);
    ~Book();

    void display() const override;
    bool validateISBN() const;
    string getIsbn() const;
    int getPages() const;
};

//杂志子类
class Magazine : public Resource
{
protected:
    string issn;
    int issueNumber;
    int publishYear;
public:
    Magazine();
    Magazine(string id, string title, string author, string publisher,
        string issn, int issue, int year, int totalCount);
    ~Magazine();

    void display() const override;
    string getIssn() const;
    int getIssueNumber() const;
    int getPublishYear() const;
};

//电子资源子类
class EResource : public Resource
{
protected:
    string format;
    double fileSize;
public:
    EResource();
    EResource(string id, string title, string author, string publisher,
        string format, double fileSize, int totalCount);
    ~EResource();

    void display() const override;
    string getFormat() const;
    double getFileSize() const;
};

#endif
