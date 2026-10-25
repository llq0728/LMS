#include "Library.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <cstdlib>

// ========== 日期工具：把 "YYYY-MM-DD" 拆成 年/月/日 ==========
static void splitDate(const string& s, int& y, int& m, int& d) {
    y = atoi(s.substr(0, 4).c_str());
    m = atoi(s.substr(5, 2).c_str());
    d = atoi(s.substr(8, 2).c_str());
}

// 平年每月天数
static int monthDays(int y, int m) {
    int days[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    // 闰年二月 29 天
    if ((y%4==0 && y%100!=0) || y%400==0) days[1] = 29;
    return days[m-1];
}

// 今天 today 加 n 天，返回新的 "YYYY-MM-DD"
static string addDays(const string& today, int n) {
    int y, m, d;
    splitDate(today, y, m, d);
    d += n;
    // 天数超出当月就滚到下个月
    while (d > monthDays(y, m)) {
        d -= monthDays(y, m);
        m++;
        if (m > 12) { m = 1; y++; }
    }
    // 用 stringstream 拼成 "YYYY-MM-DD"
    stringstream ss;
    ss << y << "-" << (m < 10 ? "0" : "") << m << "-" << (d < 10 ? "0" : "") << d;
    return ss.str();
}

// 算 d2 - d1 相差几天（d2 晚于 d1 时为正）
static int daysBetween(const string& d1, const string& d2) {
    int y1,m1,dd1, y2,m2,dd2;
    splitDate(d1, y1, m1, dd1);
    splitDate(d2, y2, m2, dd2);
    // 先按整年数粗算
    int diff = (y2 - y1) * 365;
    for (int y = y1; y < y2; y++)
        if ((y%4==0 && y%100!=0) || y%400==0) diff++; // 闰年补一天
    // 再算年内天数差
    for (int m = 1; m < m1; m++) diff -= monthDays(y1, m);
    diff -= dd1;
    for (int m = 1; m < m2; m++) diff += monthDays(y2, m);
    diff += dd2;
    return diff;
}

Library::Library(string name)
    : libraryName(name)
{
}

Library::~Library()
{
    // 释放所有资源对象
    for (auto r : resources) delete r;
    // 释放所有读者对象
    for (auto r : readers) delete r;
    // records是BorrowRecord对象，vector自动销毁
}

void Library::addResource(Resource* r)
{
    resources.push_back(r);
}

bool Library::removeResource(string id)
{
    for (auto it = resources.begin(); it != resources.end(); ++it)
    {
        if ((*it)->getResId() == id)
        {
            delete *it;
            resources.erase(it);
            return true;
        }
    }
    return false;
}

Resource* Library::findResource(string id)
{
    for (auto r : resources)
    {
        if (r->getResId() == id) return r;
    }
    return nullptr;
}

void Library::displayAllResources()
{
    cout << "\n全部资源列表：" << endl;
    for (auto r : resources)
    {
        r->display();
        cout << endl;
    }
}

vector<Resource*> Library::searchResources(string keyword)
{
    vector<Resource*> res;
    for (auto r : resources)
    {
        if (r->getTitle().find(keyword) != string::npos)
            res.push_back(r);
    }
    return res;
}

void Library::addReader(Reader* r)
{
    readers.push_back(r);
}

bool Library::removeReader(string id)
{
    for (auto it = readers.begin(); it != readers.end(); ++it)
    {
        if ((*it)->getReaderId() == id)
        {
            delete *it;
            readers.erase(it);
            return true;
        }
    }
    return false;
}

Reader* Library::findReader(string id)
{
    for (auto r : readers)
    {
        if (r->getReaderId() == id) return r;
    }
    return nullptr;
}

void Library::displayAllReaders()
{
    cout << "\n全部读者列表：" << endl;
    for (auto r : readers)
    {
        r->display();
        cout << endl;
    }
}

bool Library::borrowBook(string readerId, string resId, string today)
{
    Reader* rd = findReader(readerId);
    Resource* rs = findResource(resId);
    if (!rd || !rs)
        return false;

    // 电子资源不能借
    PaperResource* pr = dynamic_cast<PaperResource*>(rs);
    if (!pr)
        return false;

    if (!rd->canBorrowMore() || !pr->borrowOne())
        return false;

    // 根据资源借阅期限算到期日
    string due = addDays(today, rs->getBorrowPeriod());
    BorrowRecord newRec(readerId, resId, today, due);
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

    for (auto& rec : records)
    {
        if (rec.getReaderId() == readerId && rec.getResourceId() == resId && !rec.getIsReturned())
        {
            // 计算逾期罚款：超过到期日每天 0.1 元
            double fine = 0;
            int overdue = daysBetween(rec.getDueDate(), today);
            if (overdue > 0) fine = overdue * 0.1;

            rec.doReturn(today, fine);
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
    cout << "资源总数：" << resources.size() << endl;
    cout << "读者总数：" << readers.size() << endl;
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
    return (int)resources.size();
}

int Library::getReaderCount() const
{
    return (int)readers.size();
}

string Library::getLibraryName() const
{
    return libraryName;
}

vector<Resource*> Library::getAllResourceList()
{
    return resources;
}

vector<Reader*> Library::getAllReaderList()
{
    return readers;
}

bool Library::saveAllData()
{
    bool s1 = FileManager::saveResources(resources, "resources.txt");
    bool s2 = FileManager::saveReaders(readers, "readers.txt");
    bool s3 = FileManager::saveRecords(records, "records.txt");
    return s1 && s2 && s3;
}

bool Library::loadAllData()
{
    vector<Resource*> resList = FileManager::loadResources("resources.txt");
    for (auto r : resList) resources.push_back(r);

    vector<Reader*> rdList = FileManager::loadReaders("readers.txt");
    for (auto r : rdList) readers.push_back(r);

    records = FileManager::loadRecords("records.txt");
    return true;
}
