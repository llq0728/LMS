#ifndef RESOURCE_H
#define RESOURCE_H
#include <string>
#include <iostream>
using namespace std;

// ===== 顶层资源抽象基类（移除馆藏相关成员，所有资源通用属性）=====
class Resource {
protected:
    string resId;
    string title;
    string author;
    string publisher;
    int borrowPeriod;   // 借阅期限（所有资源都有）
public:
    Resource();
    Resource(string id, string title, string author, string publisher,
        int borrowPeriod);

    // 虚析构函数！重要！
    // 用基类指针删除派生类对象时，确保派生类析构函数被调用
    virtual ~Resource();

    // ===== 纯虚函数 =====
    // 使Resource成为抽象类，不能实例化
    // 子类必须实现，统一接口
    virtual string getTypeName() const = 0;

    // ===== 虚函数 =====
    virtual void displayBase() const; // 新增：输出所有资源公共基础信息，代码复用
    virtual void display() const;

    // Getter
    string getResId() const;
    string getTitle() const;
    int getBorrowPeriod() const;

    void setTitle(string title);
};

// =====【新增中间纸质资源类 PaperResource】=====
// 继承Resource，存放馆藏、借阅相关属性与方法
// Book、Magazine继承这个类；EResource直接继承Resource，不带馆藏
class PaperResource : public Resource {
protected:
    int totalCount;
    int availableCount;
public:
    PaperResource();
    PaperResource(string id, string title, string author, string publisher,
        int borrowPeriod, int totalCount);

    virtual ~PaperResource() {}

    bool borrowOne();
    bool returnOne();
    bool isAvailable() const;

    int getAvailableCount() const;
    int getTotalCount() const;

    void display() const override;
};

// ===== 普通图书 =====
class Book : public PaperResource {
private:
    string isbn;
    int pages;
public:
    Book();
    Book(string id, string title, string author, string publisher,
        string isbn, int pages, int totalCount, int borrowPeriod);
    ~Book();
    // override 显式标记重写（C++11）
    string getTypeName() const override;
    void display() const override;

    bool validateISBN() const;
};

// ===== 杂志期刊 =====
class Magazine : public PaperResource {
private:
    string issn;
    int issueNumber;
    int publishYear;
public:
    Magazine();
    Magazine(string id, string title, string author, string publisher,
        string issn, int issue, int year, int totalCount, int borrowPeriod);
    ~Magazine();
    string getTypeName() const override;
    void display() const override;
};

// ===== 电子资源 =====
class EResource : public Resource {
private:
    string format;
    double fileSize;
public:
    EResource();
    EResource(string id, string title, string author, string publisher,
        string format, double fileSize, int borrowPeriod);
    ~EResource();
    string getTypeName() const override;
    void display() const override;
};
#endif