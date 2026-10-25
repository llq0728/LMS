#include "Resource.h"

// ========== Resource 基类 ==========
Resource::Resource()
    : resId(""), title(""), author(""), publisher(""), borrowPeriod(30) {
}

Resource::Resource(string id, string title, string author, string publisher, int borrowPeriod)
    : resId(id), title(title), author(author), publisher(publisher), borrowPeriod(borrowPeriod) {
}

Resource::~Resource() {}

string Resource::getResId() const { return resId; }
string Resource::getTitle() const { return title; }
int Resource::getBorrowPeriod() const { return borrowPeriod; }
void Resource::setTitle(string title) { this->title = title; }

// ========== PaperResource 纸质中间类 ==========
PaperResource::PaperResource()
    : Resource(), totalCount(0), availableCount(0) {
}

PaperResource::PaperResource(string id, string title, string author, string publisher, int totalCount, int borrowPeriod)
    : Resource(id, title, author, publisher, borrowPeriod), totalCount(totalCount), availableCount(totalCount) {
}

bool PaperResource::borrowOne() {
    if (availableCount > 0) {
        availableCount--;
        return true;
    }
    return false;
}
bool PaperResource::returnOne() {
    availableCount++;
    return true;
}
bool PaperResource::isAvailable() const {
    return availableCount > 0;
}
int PaperResource::getAvailableCount() const {
    return availableCount;
}

// ========== Book 图书 ==========
Book::Book(string id, string title, string author, string publisher, string isbn, int pages, int totalCount, int borrowPeriod)
    : PaperResource(id, title, author, publisher, totalCount, borrowPeriod), isbn(isbn), pages(pages) {
}

void Book::display() const {
    cout << "[图书] 编号:" << resId
        << " 标题:" << title
        << " 作者:" << author
        << " 出版社:" << publisher
        << " ISBN:" << isbn
        << " 页数:" << pages
        << " 馆藏:" << totalCount
        << " 可借:" << availableCount
        << " 借阅期限:" << borrowPeriod << "天";
}
string Book::getTypeName() const {
    return "图书";
}

// ========== Magazine 杂志 ==========
Magazine::Magazine(string id, string title, string author, string publisher, string issn, int issue, int year, int totalCount, int borrowPeriod)
    : PaperResource(id, title, author, publisher, totalCount, borrowPeriod), issn(issn), issue(issue), year(year) {
}

void Magazine::display() const {
    cout << "[杂志] 编号:" << resId
        << " 标题:" << title
        << " 作者:" << author
        << " 出版社:" << publisher
        << " ISSN:" << issn
        << " " << year << "年第" << issue << "期"
        << " 馆藏:" << totalCount
        << " 可借:" << availableCount
        << " 借阅期限:" << borrowPeriod << "天";
}
string Magazine::getTypeName() const {
    return "杂志";
}

// ========== EResource 电子资源 ==========
EResource::EResource(string id, string title, string author, string publisher, string format, double sizeMb, int borrowPeriod)
    : Resource(id, title, author, publisher, borrowPeriod), format(format), sizeMb(sizeMb) {
}

void EResource::display() const {
    cout << "[电子资源] 编号:" << resId
        << " 标题:" << title
        << " 作者:" << author
        << " 出版社:" << publisher
        << " 格式:" << format
        << " 大小:" << sizeMb << "MB"
        << " 不可外借";
}
string EResource::getTypeName() const {
    return "电子资源";
}
