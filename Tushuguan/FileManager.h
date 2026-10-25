#ifndef FILEMANAGER_H
#define FILEMANAGER_H
#include "Resource.h"
#include "Reader.h"
#include "BorrowRecord.h"
#include <vector>
#include <string>
using namespace std;

// 文件管理类：负责把资源、读者、借阅记录保存到txt，从txt加载
class FileManager {
public:
    // 保存全部资源到文件
    static bool saveResources(const vector<Resource*>& list, const string& filename);
    // 从文件读取资源
    static vector<Resource*> loadResources(const string& filename);

    // 保存全部读者
    static bool saveReaders(const vector<Reader*>& list, const string& filename);
    // 读取读者
    static vector<Reader*> loadReaders(const string& filename);

    // 保存借阅记录
    static bool saveRecords(const vector<BorrowRecord>& list, const string& filename);
    // 读取借阅记录
    static vector<BorrowRecord> loadRecords(const string& filename);
};
#endif
