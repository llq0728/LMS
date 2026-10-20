#include "Library.h"
#include <iostream>
Library::Library(string name)
    : libraryName(name), resourceCount(0), readerCount(0) {
    for (int i = 0; i < MAX_RESOURCES; i++) resources[i] = nullptr;
    for (int i = 0; i < MAX_READERS; i++) readers[i] = nullptr;
}
Library::~Library() {
    // 释放所有资源对象（虚析构确保正确释放派生类部分）
    for (int i = 0; i < resourceCount; i++) {
        delete resources[i];  // 多态释放：因为Resource有虚析构函数
    }
    // 释放所有读者对象
    for (int i = 0; i < readerCount; i++) {
        delete readers[i];
    }
}
void Library::addResource(Resource* res) {
    if (resourceCount < MAX_RESOURCES) {
        resources[resourceCount++] = res;
        cout << "添加" << res->getTypeName() << "：" << res->getTitle() << endl;
    }
}
void Library::displayAllResources() const {
    cout << "\n===== " << libraryName << " 资源目录（共"
        << resourceCount << "种）=====" << endl;
    // 多态调用：不同类型资源显示不同内容
    for (int i = 0; i < resourceCount; i++) {
        cout << "[" << i + 1 << "] [" << resources[i]->getTypeName() << "] ";
        resources[i]->display();  // 虚函数调用！
        cout << endl;
    }
    cout << "==========================================" << endl;
}
Resource* Library::findResource(string id) {
    for (int i = 0; i < resourceCount; i++) {
        if (resources[i]->getResId() == id) {
            return resources[i];
        }
    }
    return nullptr;
}
void Library::addReader(Reader* reader) {
    if (readerCount < MAX_READERS) {
        readers[readerCount++] = reader;
        cout << "添加" << reader->getReaderType() << "：" << reader->getName() << endl;
    }
}
void Library::displayAllReaders() const {
    cout << "\n===== 读者列表（共" << readerCount << "人）=====" << endl;
    for (int i = 0; i < readerCount; i++) {
        cout << "[" << i + 1 << "] [" << readers[i]->getReaderType() << "] ";
        readers[i]->display();  // 虚函数调用！
        cout << endl;
    }
    cout << "========================================" << endl;
}
Reader* Library::findReader(string id) {
    for (int i = 0; i < readerCount; i++) {
        if (readers[i]->getReaderId() == id) {
            return readers[i];
        }
    }
    return nullptr;
}
bool Library::borrowBook(string readerId, string resourceId) {
    Reader* reader = findReader(readerId);
    Resource* resource = findResource(resourceId);

    if (!reader || !resource) {
        cout << "错误：读者或资源不存在！" << endl;
        return false;
    }

    // 动态类型转换：只有PaperResource纸质资源才支持借阅
    PaperResource* paperRes = dynamic_cast<PaperResource*>(resource);
    if (paperRes == nullptr)
    {
        cout << "错误：电子资源不可外借！" << endl;
        return false;
    }

    if (!reader->canBorrowMore()) {
        cout << "错误：" << reader->getName() << " 已达借阅上限！" << endl;
        return false;
    }

    if (!paperRes->isAvailable()) {
        cout << "错误：《" << resource->getTitle() << "》已全部借出！" << endl;
        return false;
    }

    paperRes->borrowOne();
    reader->borrowBook();
    cout << reader->getName() << " 成功借阅《" << resource->getTitle() << "》"
        << "（" << resource->getTypeName() << "）" << endl;
    return true;
}
bool Library::returnBook(string readerId, string resourceId) {
    Reader* reader = findReader(readerId);
    Resource* resource = findResource(resourceId);

    if (!reader || !resource)
    {
        cout << "错误：读者或资源不存在！" << endl;
        return false;
    }

    PaperResource* paperRes = dynamic_cast<PaperResource*>(resource);
    if (paperRes == nullptr)
    {
        cout << "错误：电子资源不需要归还！" << endl;
        return false;
    }

    // 还书逻辑
    if (paperRes->returnOne() && reader->returnBook())
    {
        cout << reader->getName() << " 归还《" << resource->getTitle() << "》" << endl;
        return true;
    }
    else
    {
        cout << "错误：还书失败！" << endl;
        return false;
    }
}
string Library::getLibraryName() const { return libraryName; }