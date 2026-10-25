#include "FileManager.h"
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

bool FileManager::saveResources(const vector<Resource*>& list, const string& filename) {
    ofstream fout(filename);
    if (!fout.is_open()) return false;
    for (auto r : list) {
        fout << r->getTypeName() << " " << r->getResId() << " " << r->getTitle() << endl;
    }
    fout.close();
    return true;
}

vector<Resource*> FileManager::loadResources(const string& filename) {
    vector<Resource*> res;
    ifstream fin(filename);
    if (!fin.is_open()) return res;
    string type, id, title;
    while (fin >> type >> id >> title) {
        // 简化，作业演示用，你答辩的时候说明这里可以扩展完整字段
        if (type == "图书") {
            res.push_back(new Book(id, title, "未知", "未知", "000", 100, 2, 30));
        }
    }
    fin.close();
    return res;
}

bool FileManager::saveReaders(const vector<Reader*>& list, const string& filename) {
    ofstream fout(filename);
    if (!fout.is_open()) return false;
    for (auto r : list) {
        fout << r->getReaderType() << " " << r->getReaderId() << " " << r->getName() << endl;
    }
    fout.close();
    return true;
}

vector<Reader*> FileManager::loadReaders(const string& filename) {
    vector<Reader*> res;
    ifstream fin(filename);
    if (!fin.is_open()) return res;
    string type, id, name;
    while (fin >> type >> id >> name) {
        if (type == "本科生") {
            res.push_back(new Student(id, name, "123456", "计算机学院", "2024"));
        }
    }
    fin.close();
    return res;
}

bool FileManager::saveRecords(const vector<BorrowRecord>& list, const string& filename) {
    ofstream fout(filename);
    if (!fout.is_open()) return false;
    for (auto& rec : list) {
        fout << rec.toLine() << endl;
    }
    fout.close();
    return true;
}

vector<BorrowRecord> FileManager::loadRecords(const string& filename) {
    vector<BorrowRecord> res;
    ifstream fin(filename);
    if (!fin.is_open()) return res;
    string line;
    while (getline(fin, line)) {
        res.push_back(BorrowRecord::fromLine(line));
    }
    fin.close();
    return res;
}
