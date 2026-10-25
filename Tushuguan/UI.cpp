#include "UI.h"
#include "Library.h"
#include "BorrowRecord.h"
#include <iostream>
#include <string>
using namespace std;

Library* lib = nullptr;
Reader* currentReader = nullptr;

string input(string tip)
{
    cout << tip;
    string s;
    cin >> s;
    return s;
}
void pause()
{
    cout << "\n按回车继续...";
    cin.ignore();
    cin.get();
}
string getCurrentDate()
{
    return "2026-10-25";
}

void UI::readerMenu()
{
    while (true)
    {
        system("cls");
        cout << "===== 读者菜单 =====" << endl;
        cout << "1. 查询资源" << endl;
        cout << "2. 借阅资源" << endl;
        cout << "3. 归还资源" << endl;
        cout << "4. 我的借阅记录" << endl;
        cout << "0. 退出登录" << endl;
        string op = input("请输入选项：");
        if (op == "1")
            readerSearchRes();
        else if (op == "2")
            readerBorrowBook();
        else if (op == "3")
            readerReturnBook();
        else if (op == "4")
            readerMyBorrows();
        else if (op == "0")
        {
            currentReader = nullptr;
            break;
        }
        else
        {
            cout << "输入错误！";
            pause();
        }
    }
}

void UI::readerSearchRes()
{
    string key = input("输入关键词搜索标题：");
    auto resList = lib->searchResources(key);
    cout << "\n===== 搜索结果（共" << resList.size() << "条）=====" << endl;
    for (auto p : resList)
    {
        p->display();
        cout << endl;
    }
    pause();
}

void UI::readerBorrowBook()
{
    string rid = input("输入要借阅的资源编号：");
    bool ok = lib->borrowBook(currentReader->getReaderId(), rid, getCurrentDate());
    if (ok)
    {
        cout << "借阅成功！" << endl;
    }
    else
    {
        cout << "借阅失败！（电子资源不可外借或无库存/达到借阅上限）" << endl;
    }
    pause();
}

void UI::readerReturnBook()
{
    string rid = input("输入要归还的资源编号：");
    bool ok = lib->returnBook(currentReader->getReaderId(), rid, getCurrentDate());
    if (ok)
    {
        cout << "归还成功！" << endl;
    }
    else
    {
        cout << "归还失败，检查是否借过这本书！" << endl;
    }
    pause();
}

void UI::readerMyBorrows()
{
    vector<BorrowRecord> records = lib->getReaderBorrows(currentReader->getReaderId());
    cout << "\n===== 我的借阅记录（共" << records.size() << "条）=====" << endl;
    for (size_t i = 0; i < records.size(); i++)
    {
        BorrowRecord r = records[i];
        Resource* res = lib->findResource(r.getResourceId());
        string title = res ? res->getTitle() : "未知资源";
        cout << "[" << i + 1 << "] " << title;
        if (r.getIsReturned())
        {
            cout << " 【已归还】";
        }
        else
        {
            cout << " 【在借】";
        }
        cout << endl;
    }
    pause();
}

void UI::adminMenu()
{
    while (true)
    {
        system("cls");
        cout << "===== 管理员菜单 =====" << endl;
        cout << "1. 添加资源" << endl;
        cout << "2. 删除资源" << endl;
        cout << "3. 添加读者" << endl;
        cout << "4. 删除读者" << endl;
        cout << "5. 查看全部资源" << endl;
        cout << "6. 查看全部读者" << endl;
        cout << "7. 查看所有借阅记录" << endl;
        cout << "8. 保存数据" << endl;
        cout << "9. 加载数据" << endl;
        cout << "10. 修改资源" << endl;
        cout << "11. 修改读者" << endl;
        cout << "0. 退出登录" << endl;
        string op = input("请输入选项：");
        if (op == "1")
            adminAddResource();
        else if (op == "2")
            adminDelResource();
        else if (op == "3")
            adminAddReader();
        else if (op == "4")
            adminDelReader();
        else if (op == "5")
            lib->displayAllResources();
        else if (op == "6")
            lib->displayAllReaders();
        else if (op == "7")
            adminShowAllRecords();
        else if (op == "8")
        {
            if (lib->saveAllData())
                cout << "保存成功！" << endl;
            else
                cout << "保存失败！" << endl;
            pause();
        }
        else if (op == "9")
        {
            if (lib->loadAllData())
                cout << "加载成功！" << endl;
            else
                cout << "加载失败！" << endl;
            pause();
        }
        else if (op == "10")
            adminEditResource();
        else if (op == "11")
            adminEditReader();
        else if (op == "0")
        {
            break;
        }
        else
        {
            cout << "输入错误！";
            pause();
        }
    }
}

void UI::adminAddResource()
{
    cout << "\n【新增资源】1-图书 2-杂志 3-电子资源" << endl;
    string t = input("选择类型：");
    if (t == "1")
    {
        string id, title, auth, pub, isbn;
        int pages, totalCnt, period;
        id = input("资源编号：");
        title = input("书名：");
        auth = input("作者：");
        pub = input("出版社：");
        isbn = input("ISBN：");
        cout << "页数："; cin >> pages;
        cout << "馆藏总数："; cin >> totalCnt;
        cout << "借阅期限(天)："; cin >> period;
        lib->addResource(new Book(id, title, auth, pub, isbn, pages, totalCnt, period));
        cout << "添加图书成功！";
    }
    else if (t == "2")
    {
        string id, title, auth, pub, issn;
        int issue, year, totalCnt, period;
        id = input("资源编号：");
        title = input("刊名：");
        auth = input("主办：");
        pub = input("出版社：");
        issn = input("ISSN：");
        cout << "期号："; cin >> issue;
        cout << "出版年份："; cin >> year;
        cout << "馆藏总数："; cin >> totalCnt;
        cout << "借阅期限(天)："; cin >> period;
        lib->addResource(new Magazine(id, title, auth, pub, issn, issue, year, totalCnt, period));
        cout << "添加杂志成功！";
    }
    else if (t == "3")
    {
        string id, title, auth, pub, format;
        double sizeMb;
        int period;
        id = input("资源编号：");
        title = input("名称：");
        auth = input("作者：");
        pub = input("发布方：");
        format = input("文件格式(PDF/EPUB)：");
        cout << "文件大小(MB)："; cin >> sizeMb;
        cout << "借阅期限(天)："; cin >> period;
        lib->addResource(new EResource(id, title, auth, pub, format, sizeMb, period));
        cout << "添加电子资源成功！";
    }
    else
    {
        cout << "类型错误！";
    }
    pause();
}

void UI::adminAddReader()
{
    cout << "\n【新增读者】1-本科生 2-研究生 3-教师" << endl;
    string t = input("选择类型：");
    string id, name, pwd, dept;
    id = input("读者编号：");
    name = input("姓名：");
    pwd = input("登录密码：");
    dept = input("院系：");

    if (t == "1")
    {
        string grade = input("年级：");
        lib->addReader(new Student(id, name, pwd, dept, grade));
        cout << "添加本科生读者成功！";
    }
    else if (t == "2")
    {
        string major = input("专业：");
        string sup = input("导师：");
        lib->addReader(new Postgraduate(id, name, pwd, dept, major, sup));
        cout << "添加研究生读者成功！";
    }
    else if (t == "3")
    {
        string title = input("职称：");
        lib->addReader(new Teacher(id, name, pwd, dept, title));
        cout << "添加教师读者成功！";
    }
    else
    {
        cout << "类型错误！";
    }
    pause();
}

void UI::adminDelResource()
{
    string id = input("输入要删除的资源编号：");
    if (lib->removeResource(id))
        cout << "删除成功！";
    else
        cout << "未找到该资源！";
    pause();
}

void UI::adminDelReader()
{
    string id = input("输入要删除的读者编号：");
    if (lib->removeReader(id))
        cout << "删除成功！";
    else
        cout << "未找到该读者！";
    pause();
}

void UI::adminShowAllRecords()
{
    vector<BorrowRecord> records = lib->getBorrowRecords();
    cout << "\n===== 全部借阅记录（共" << records.size() << "条）=====" << endl;
    for (size_t i = 0; i < records.size(); i++)
    {
        BorrowRecord r = records[i];
        Reader* rd = lib->findReader(r.getReaderId());
        Resource* res = lib->findResource(r.getResourceId());

        string rName = rd ? rd->getName() : "未知读者";
        string rTitle = res ? res->getTitle() : "未知资源";
        string status = r.getIsReturned() ? "已归还" : "借阅中";

        cout << "[" << i + 1 << "] 读者：" << rName
            << "  资源：" << rTitle
            << "  借出日期：" << r.getBorrowDate()
            << "  归还日期：" << r.getReturnDate()
            << "  状态：" << status << endl;
    }
    pause();
}

// 修改资源：按编号找到后改标题
void UI::adminEditResource()
{
    string id = input("输入要修改的资源编号：");
    Resource* res = lib->findResource(id);
    if (!res)
    {
        cout << "未找到该资源！";
        pause();
        return;
    }
    cout << "当前标题：" << res->getTitle() << endl;
    string newTitle = input("输入新标题：");
    res->setTitle(newTitle);   // 复用 Resource 已有的 setTitle
    cout << "修改成功！";
    pause();
}

// 修改读者：按编号找到后改姓名和密码
void UI::adminEditReader()
{
    string id = input("输入要修改的读者编号：");
    Reader* rd = lib->findReader(id);
    if (!rd)
    {
        cout << "未找到该读者！";
        pause();
        return;
    }
    cout << "当前姓名：" << rd->getName() << endl;
    string newName = input("输入新姓名：");
    string newPwd = input("输入新密码：");
    rd->setName(newName);       // Reader 已有 setName
    rd->setPassword(newPwd);    // Reader 已有 setPassword
    cout << "修改成功！";
    pause();
}

void UI::init(Library* l)
{
    lib = l;
}
void UI::showMain()
{
    while (true)
    {
        system("cls");
        cout << "===== 图书馆管理系统 =====" << endl;
        cout << "1. 读者登录" << endl;
        cout << "2. 管理员登录" << endl;
        cout << "0. 退出系统" << endl;
        string op = input("请选择：");
        if (op == "1")
        {
            string id = input("读者编号：");
            string pwd = input("读者密码：");
            Reader* r = lib->findReader(id);
            if (r && r->checkPassword(pwd))
            {
                currentReader = r;
                readerMenu();
            }
            else
            {
                cout << "编号或密码错误！";
                pause();
            }
        }
        else if (op == "2")
        {
            string pwd = input("管理员密码：");
            if (lib->verifyAdmin(pwd))
            {
                adminMenu();
            }
            else
            {
                cout << "密码错误！";
                pause();
            }
        }
        else if (op == "0")
        {
            cout << "系统退出" << endl;
            break;
        }
        else
        {
            cout << "输入错误！";
            pause();
        }
    }
}
