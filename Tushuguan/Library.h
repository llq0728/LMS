#ifndef LIBRARY_H
#define LIBRARY_H
#include "Resource.h"
#include "Reader.h"
#include <string>
using namespace std;

const int MAX_RESOURCES = 100;
const int MAX_READERS = 100;

class Library {
private:
    string libraryName;
    Resource* resources[MAX_RESOURCES];
    int resourceCount;
    Reader* readers[MAX_READERS];
    int readerCount;
public:
    Library(string name = "图书馆");
    virtual ~Library();

    void addResource(Resource* res);
    void displayAllResources() const;
    Resource* findResource(string id);

    void addReader(Reader* reader);
    void displayAllReaders() const;
    Reader* findReader(string id);

    bool borrowBook(string readerId, string resourceId);
    bool returnBook(string readerId, string resourceId);

    string getLibraryName() const;
};
#endif
