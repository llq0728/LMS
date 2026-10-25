#include "Library.h"
#include <iostream>
#include <algorithm>
#include <fstream>

Library::Library(string name)
    : libraryName(name), resourceCount(0), readerCount(0)
{
    // 初始化为空指针
    for (int i = 0; i < MAX_RESOURCES; i++)
        resources[i] = nullptr;
    for (int i = 0; i < MAX_READERS; i++)
        readers[i] = nullptr;
}

Library::~Library()
{
    // 释放所有资源对象
    for (int i = 0; i < resourceCount; i++)
    {
        delete resources[i];
    }
    // 释放所有读者对象
    for (int i = 0; i < readerCount; i++)
    {
        delete readers[i];
    }
    // records是BorrowRecord对象，vector自动销毁，不需要手动delete
}

void Library::addResource(Resource* r)
{
    if (resourceCount < MAX_RESOURCES)
    {
        resources[resourceCount++] = r;
    }
}

bool Library::removeResource(string id)
{
    for (int i = 0; i < resourceCount; i++)
    {
        if (resources[i]->getResId() == id)
        {
            delete resources[i];
            // 后面元素往前移动覆盖
            for (int j = i; j < resourceCount - 1; j++)
            {
                resources[j] = resources[j + 1];
            }
            resources[resourceCount - 1] = nullptr;
            resourceCount--;
            return true;
        }
    }
    return false;
}

Resource* Library::findResource(string id)
{
    for (int i = 0; i < resourceCount; i++)
    {
        if (resources[i]->getResId() == id)
            return resources[i];
    }
    return nullptr;
}

void Library::displayAllResources()
{
    cout << "\n全部资源列表：" << endl;
    for (int i = 0; i < resourceCount; i++)
    {
        resources[i]->display();
        cout << endl;
    }
}

vector<Resource*> Library::searchResources(string keyword)
{
    vector<Resource*> res;
    for (int i = 0; i < resourceCount; i++)
    {
        // 标题包含关键字就匹配
        if (resources[i]->getTitle().find(keyword) != string::npos)
        {
            res.push_back(resources[i]);
        }
    }
    return res;
}

void Library::addReader(Reader* r)
{
    if (readerCount < MAX_READERS)
    {
        readers[readerCount++] = r;
    }
}

bool Library::removeReader(string id)
{
    for (int i = 0; i < readerCount; i++)
    {
        if (readers[i]->getReaderId() == id)
        {
            delete readers[i];
            for (int j = i; j < readerCount - 1; j++)
            {
                readers[j] = readers[j + 1];
            }
            readers[readerCount - 1] = nullptr;
            readerCount--;
            return true;
        }
    }
    return false;
}

Reader* Library::findReader(string id)
{
    for (int i = 0; i < readerCount; i++)
    {
        if (readers[i]->getReaderId() == id)
            return readers[i];
    }
    return nullptr;
}

void Library::displayAllReaders()
{
    cout << "\n全部读者列表：" << endl;
    for (int i = 0; i < readerCount; i++)
    {
        readers[i]->display();
        cout << endl;
    }
}

bool Library::borrowBook(string readerId, string resId, string today)
{
    Reader* rd = findReader(readerId);
    Resource* rs = findResource(resId);
    if (!rd || !rs)
        return false;

    // 判断是不是纸质资源，电子资源不能借
    PaperResource* pr = dynamic_cast<PaperResource*>(rs);
    if (!pr)
        return false;

    // 判断读者还能不能借、书还有库存
    if (!rd->canBorrowMore() || !pr->borrowOne())
        return false;

    // 添加一条借阅记录，到期日期这里简化写
    BorrowRecord newRec(readerId, resId, today, "到期简化");
    records.push_back(newRec);
    rd->borrowBook();
    return true;
}

bool Library::returnBook(string readerId, string resId, string today)
{
    Reader* rd = findReader(readerId);
    Resource* rs = findResource(resId);
    if (!rd || !rs)
        return false;

    PaperResource* pr = dynamic_cast<PaperResource*>(rs);
    if (!pr)
        return false;

    // 找到这条没归还的记录
    for (auto& rec : records)
    {
        if (rec.getReaderId() == readerId && rec.getResourceId() == resId && !rec.getIsReturned())
        {
            rec.doReturn(today, 0);
            pr->returnOne();
            rd->returnBook();
            return true;
        }
    }
    return false;
}

vector<BorrowRecord> Library::getReaderBorrows(string rid)
{
    vector<BorrowRecord> ret;
    for (auto& r : records)
    {
        if (r.getReaderId() == rid)
            ret.push_back(r);
    }
    return ret;
}

vector<BorrowRecord> Library::getBorrowRecords()
{
    return records;
}

void Library::showStatistics()
{
    cout << "\n====图书馆统计信息====" << endl;
    cout << "资源总数：" << resourceCount << endl;
    cout << "读者总数：" << readerCount << endl;
    cout << "借阅记录总数：" << records.size() << endl;
}

vector<pair<string, int>> Library::getTopBooks(int n)
{
    vector<pair<string, int>> tmp;
    return tmp;
}

bool Library::verifyAdmin(string pwd) const
{
    return pwd == "admin123";
}

int Library::getResourceCount() const
{
    return resourceCount;
}

int Library::getReaderCount() const
{
    return readerCount;
}

string Library::getLibraryName() const
{
    return libraryName;
}

// 把所有资源放到vector，给FileManager调用
vector<Resource*> Library::getAllResourceList()
{
    vector<Resource*> list;
    for (int i = 0; i < resourceCount; i++)
    {
        list.push_back(resources[i]);
    }
    return list;
}

// 把所有读者放到vector，给FileManager调用
vector<Reader*> Library::getAllReaderList()
{
    vector<Reader*> list;
    for (int i = 0; i < readerCount; i++)
    {
        list.push_back(readers[i]);
    }
    return list;
}

// 一次性保存三类数据到txt文件
bool Library::saveAllData()
{
    bool s1 = FileManager::saveResources(getAllResourceList(), "resources.txt");
    bool s2 = FileManager::saveReaders(getAllReaderList(), "readers.txt");
    bool s3 = FileManager::saveRecords(records, "records.txt");
    return s1 && s2 && s3;
}

// 从txt加载数据
bool Library::loadAllData()
{
    vector<Resource*> resList = FileManager::loadResources("resources.txt");
    for (auto r : resList)
    {
        addResource(r);
    }

    vector<Reader*> rdList = FileManager::loadReaders("readers.txt");
    for (auto r : rdList)
    {
        addReader(r);
    }

    records = FileManager::loadRecords("records.txt");
    return true;
}
