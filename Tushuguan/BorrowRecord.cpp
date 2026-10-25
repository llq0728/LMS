#include "BorrowRecord.h"
#include <sstream>
using namespace std;

BorrowRecord::BorrowRecord()
    : readerId(""), resId(""), borrowDate(""), dueDate(""), returnDate(""), isReturned(false), fine(0) {
}

BorrowRecord::BorrowRecord(string rid, string rsid, string bDate, string dDate)
    : readerId(rid), resId(rsid), borrowDate(bDate), dueDate(dDate), returnDate(""), isReturned(false), fine(0) {
}

void BorrowRecord::doReturn(string retDate, double f) {
    returnDate = retDate;
    isReturned = true;
    fine = f;
}

string BorrowRecord::getReaderId() const { return readerId; }
string BorrowRecord::getResourceId() const { return resId; }
string BorrowRecord::getBorrowDate() const { return borrowDate; }
string BorrowRecord::getDueDate() const { return dueDate; }
string BorrowRecord::getReturnDate() const { return returnDate; }
bool BorrowRecord::getIsReturned() const { return isReturned; }
double BorrowRecord::getFine() const { return fine; }

string BorrowRecord::toLine() const {
    stringstream ss;
    ss << readerId << " " << resId << " " << borrowDate << " " << dueDate << " "
        << returnDate << " " << isReturned << " " << fine;
    return ss.str();
}

BorrowRecord BorrowRecord::fromLine(const string& line) {
    stringstream ss(line);
    string rid, rsid, bDate, dDate, rDate;
    bool retFlag;
    double f;
    ss >> rid >> rsid >> bDate >> dDate >> rDate >> retFlag >> f;
    BorrowRecord rec(rid, rsid, bDate, dDate);
    rec.returnDate = rDate;
    rec.isReturned = retFlag;
    rec.fine = f;
    return rec;
}
