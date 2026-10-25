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

const int MAX_RESOURCES = 100;
const int MAX_READERS = 100;

class Library {
private:
    string libraryName;
    // 资源数组，存放不同子类的资源指针（多态）
    Resource* resources[MAX_RESOURCES];
    int resourceCount;

    // 读者数组，存放不同子类的读者指针（多态）
    Reader* readers[MAX_READERS];
    int readerCount;

    // 借阅记录，vector动态管理，不再用指针
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
