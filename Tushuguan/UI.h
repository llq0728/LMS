#ifndef UI_H
#define UI_H
#include "Library.h"
#include "BorrowRecord.h"
#include <vector>
class UI
{
public:
    static void init(Library* l);
    static void showMain();
private:
    static void readerMenu();
    static void readerSearchRes();
    static void readerBorrowBook();
    static void readerReturnBook();
    static void readerMyBorrows();

    static void adminMenu();
    static void adminAddResource();
    static void adminDelResource();
    static void adminEditResource();   // 修改资源（改标题）
    static void adminAddReader();
    static void adminDelReader();
    static void adminEditReader();     // 修改读者（改姓名/密码）
    static void adminShowAllRecords();
};
#endif
