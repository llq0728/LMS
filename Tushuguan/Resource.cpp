#include "Resource.h"
#include <cctype>
Resource::Resource()
    : resId(""), title(""), author(""), publisher(""),
    totalCount(0), availableCount(0), borrowPeriod(30) {
}

Resource::Resource(string id, string title, string author, string publisher,
    int totalCount, int borrowPeriod)
    : resId(id), title(title), author(author), publisher(publisher),
    totalCount(totalCount), borrowPeriod(borrowPeriod) {
    availableCount = totalCount;
}

Resource::~Resource() {}

void Resource::displayBase() const {
    cout << "编号:" << resId
        << " | 标题:" << title
        << " | 作者:" << author
        << " | 出版社:" << publisher
        << " | 馆藏:" << totalCount << "本"
        << " | 可借:" << availableCount << "本"
        << " | 借阅期:" << borrowPeriod << "天";
}

bool Resource::borrowOne() {
    if (availableCount > 0) {
        availableCount--;
        return true;
    }
    return false;
}

bool Resource::returnOne() {
    if (availableCount < totalCount) {
        availableCount++;
        return true;
    }
    return false;
}

bool Resource::isAvailable() const {
    return availableCount > 0;
}

string Resource::getResId() const { return resId; }
string Resource::getTitle() const { return title; }
int Resource::getAvailableCount() const { return availableCount; }
int Resource::getBorrowPeriod() const { return borrowPeriod; }

void Resource::setTitle(string title) { this->title = title; }
void Resource::addCount(int num) {
    totalCount += num;
    availableCount += num;
}

// ==================== Book 子类 ====================

Book::Book() : Resource(), isbn(""), pages(0) {
    borrowPeriod = 30; // 图书借阅30天
}

Book::Book(string id, string title, string author, string publisher,
    string isbn, int pages, int totalCount)
    : Resource(id, title, author, publisher, totalCount, 30),
    isbn(isbn), pages(pages) {
}

Book::~Book() {}

void Book::display() const {
    cout << "[普通图书] ";
    displayBase(); // 调用基类方法
    cout << " | ISBN:" << isbn
        << " | 页数:" << pages << "页";
}

bool Book::validateISBN() const {
    if (isbn.length() != 10 && isbn.length() != 13) return false;
    for (char c : isbn) {
        if (!isdigit(c)) return false;
    }
    return true;
}

string Book::getIsbn() const { return isbn; }
int Book::getPages() const { return pages; }

// ==================== Magazine 子类 ====================

Magazine::Magazine() : Resource(), issn(""), issueNumber(0), publishYear(0) {
    borrowPeriod = 14; // 杂志借阅14天
}

Magazine::Magazine(string id, string title, string author, string publisher,
    string issn, int issue, int year, int totalCount)
    : Resource(id, title, author, publisher, totalCount, 14),
    issn(issn), issueNumber(issue), publishYear(year) {
}

Magazine::~Magazine() {}

void Magazine::display() const {
    cout << "[杂志期刊] ";
    displayBase();
    cout << " | ISSN:" << issn
        << " | 第" << issueNumber << "期"
        << " | " << publishYear << "年";
}

string Magazine::getIssn() const { return issn; }
int Magazine::getIssueNumber() const { return issueNumber; }
int Magazine::getPublishYear() const { return publishYear; }

// ==================== EResource 子类 ====================

EResource::EResource() : Resource(), format(""), fileSize(0) {
    borrowPeriod = 7; // 电子资源借阅7天
}

EResource::EResource(string id, string title, string author, string publisher,
    string format, double fileSize, int totalCount)
    : Resource(id, title, author, publisher, totalCount, 7),
    format(format), fileSize(fileSize) {
}

EResource::~EResource() {}

void EResource::display() const {
    cout << "[电子资源] ";
    displayBase();
    cout << " | 格式:" << format
        << " | 大小:" << fileSize << "MB";
}

string EResource::getFormat() const { return format; }
double EResource::getFileSize() const { return fileSize; }
