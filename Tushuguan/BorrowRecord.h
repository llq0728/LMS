#ifndef BORROWRECORD_H
#define BORROWRECORD_H
#include <string>
using namespace std;

// 借阅记录类：保存一条借书、还书信息
class BorrowRecord {
private:
    string readerId;
    string resId;
    string borrowDate;
    string dueDate;
    string returnDate;
    bool isReturned;
    double fine;
public:
    BorrowRecord();
    BorrowRecord(string rid, string rsid, string bDate, string dDate);

    void doReturn(string retDate, double f);

    string getReaderId() const;
    string getResourceId() const;
    string getBorrowDate() const;
    string getDueDate() const;
    string getReturnDate() const;
    bool getIsReturned() const;
    double getFine() const;

    // 用于读写文件，拼接成一行字符串
    string toLine() const;
    // 从一行文本还原记录
    static BorrowRecord fromLine(const string& line);
};
#endif
