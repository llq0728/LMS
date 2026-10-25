#ifndef LIBRARY_H
#define LIBRARY_H
#include "Resource.h"
#include "Reader.h"
#include "BorrowRecord.h"
#include "FileManager.h"
#include <string>
#include <vector>
#include <utility>
using namespace std;

class Library {
private:
    string libraryName;
    // 资源 vector，存放不同子类的资源指针（多态）
    vector<Resource*> resources;

    // 读者 vector，存放不同子类的读者指针（多态）
    vector<Reader*> readers;

    // 借阅记录，vector动态管理
    vector<BorrowRecord> records;

public:
    Library(string name);
    ~Library();

    // 资源相关
    void addResource(Resource* r);
    bool removeResource(string id);
    Resource* findResource(string id);
    void displayAllResources();
    vector<Resource*> searchResources(string keyword);

    // 读者相关
    void addReader(Reader* r);
    bool removeReader(string id);
    Reader* findReader(string id);
    void displayAllReaders();

    // 核心借阅、归还逻辑
    bool borrowBook(string readerId, string resId, string today);
    bool returnBook(string readerId, string resId, string today);

    // 查询借阅记录
    vector<BorrowRecord> getReaderBorrows(string rid);
    vector<BorrowRecord> getBorrowRecords();
    void showStatistics();

    vector<pair<string, int>> getTopBooks(int n);
    bool verifyAdmin(string pwd) const;

    // 文件持久化：保存全部数据到txt、从txt加载
    bool saveAllData();
    bool loadAllData();

    int getResourceCount() const;
    int getReaderCount() const;
    string getLibraryName() const;

    // 导出资源、读者列表给FileManager使用
    vector<Resource*> getAllResourceList();
    vector<Reader*> getAllReaderList();
};

#endif
