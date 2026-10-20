#include "Resource.h"
#include <cctype>
#include <iostream>
using namespace std;

// ==================== Resource 顶层基类（所有资源通用，移除馆藏相关） ====================
Resource::Resource()
    : resId(""), title(""), author(""), publisher(""), borrowPeriod(30) {
}

Resource::Resource(string id, string title, string author, string publisher, int borrowPeriod)
    : resId(id), title(title), author(author), publisher(publisher), borrowPeriod(borrowPeriod) {
}

Resource::~Resource() {}

// 基类公共信息输出（displayBase：只输出全部资源都有的基础信息）
void Resource::displayBase() const {
    cout << "编号:" << resId
        << " | 标题:" << title
        << " | 作者:" << author
        << " | 出版社:" << publisher
        << " | 借阅期限:" << borrowPeriod << "天";
}

// 纯虚函数，子类重写display实现多态
void Resource::display() const {
    displayBase();
}

string Resource::getResId() const { return resId; }
string Resource::getTitle() const { return title; }
int Resource::getBorrowPeriod() const { return borrowPeriod; }
void Resource::setTitle(string title) { this->title = title; }

// ==================== PaperResource 中间纸质资源类【新增！】====================
// 继承Resource，专门管理馆藏、借阅归还（只有图书、杂志继承它）
PaperResource::PaperResource()
    : Resource(), totalCount(0), availableCount(0) {
}

PaperResource::PaperResource(string id, string title, string author, string publisher, int borrowPeriod, int totalCount)
    : Resource(id, title, author, publisher, borrowPeriod), totalCount(totalCount)
{
    availableCount = totalCount;
}

bool PaperResource::borrowOne() {
    if (availableCount > 0) {
        availableCount--;
        return true;
    }
    return false;
}

bool PaperResource::returnOne() {
    if (availableCount < totalCount) {
        availableCount++;
        return true;
    }
    return false;
}

bool PaperResource::isAvailable() const {
    return availableCount > 0;
}

int PaperResource::getAvailableCount() const { return availableCount; }
int PaperResource::getTotalCount() const { return totalCount; }

void PaperResource::display() const {
    Resource::displayBase();
    cout << " | 馆藏:" << totalCount << "本"
        << " | 可借:" << availableCount << "本";
}

// ==================== Book 子类：继承 PaperResource（不再直接继承Resource） ====================
Book::Book() : PaperResource(), isbn(""), pages(0) {}

Book::Book(string id, string title, string author, string publisher,
    string isbn, int pages, int totalCount, int borrowPeriod)
    : PaperResource(id, title, author, publisher, borrowPeriod, totalCount),
    isbn(isbn), pages(pages) {
}

Book::~Book() {}

string Book::getTypeName() const {
    return "普通图书";
}

void Book::display() const {
    PaperResource::display();
    cout << " | ISBN:" << isbn << " | 页数:" << pages << "页";
}

bool Book::validateISBN() const {
    if (isbn.length() != 10 && isbn.length() != 13) return false;
    for (char c : isbn) {
        if (!isdigit(c)) return false;
    }
    return true;
}

// ==================== Magazine 子类：继承 PaperResource ====================
Magazine::Magazine() : PaperResource(), issn(""), issueNumber(0), publishYear(0) {}

Magazine::Magazine(string id, string title, string author, string publisher,
    string issn, int issue, int year, int totalCount, int borrowPeriod)
    : PaperResource(id, title, author, publisher, borrowPeriod, totalCount),
    issn(issn), issueNumber(issue), publishYear(year) {
}

Magazine::~Magazine() {}

string Magazine::getTypeName() const {
    return "杂志期刊";
}

void Magazine::display() const {
    PaperResource::display();
    cout << " | ISSN:" << issn << " | 第" << issueNumber << "期"
        << " | " << publishYear << "年";
}

// ==================== EResource 子类：直接继承Resource，**无馆藏** ====================
EResource::EResource() : Resource(), format(""), fileSize(0) {}

EResource::EResource(string id, string title, string author, string publisher,
    string format, double fileSize, int borrowPeriod)
    : Resource(id, title, author, publisher, borrowPeriod),
    format(format), fileSize(fileSize) {
}

EResource::~EResource() {}

string EResource::getTypeName() const {
    return "电子资源";
}

void EResource::display() const {
    Resource::displayBase();
    cout << " | 格式:" << format << " | 大小:" << fileSize << "MB";
}