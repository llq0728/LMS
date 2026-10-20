#ifndef LIBRARY_H
#define LIBRARY_H
#include "Resource.h"
#include "Reader.h"
#include <string>
using namespace std;

const int MAX_RESOURCES = 100;
const int MAX_READERS = 100;

class Library {
private:
    string libraryName;

    // 多态！基类指针数组管理所有类型资源
    Resource* resources[MAX_RESOURCES];
    int resourceCount;

    // 多态！基类指针数组管理所有类型读者
    Reader* readers[MAX_READERS];
    int readerCount;
public:
    Library(string name = "图书馆");
    ~Library(); // 虚析构函数配合，正确释放所有派生类对象

    // ========== 资源管理 ==========
    void addResource(Resource* res);   // 添加资源（多态参数）
    void displayAllResources() const;  // 多态显示
    Resource* findResource(string id);

    // ========== 读者管理 ==========
    void addReader(Reader* reader);    // 添加读者（多态参数）
    void displayAllReaders() const;    // 多态显示
    Reader* findReader(string id);

    // ========== 借阅功能 ==========
    bool borrowBook(string readerId, string resourceId);
    bool returnBook(string readerId, string resourceId);

    string getLibraryName() const;
};
#endif