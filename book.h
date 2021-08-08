#pragma once

#include <string>
#include <iostream>

using namespace std;

class Book {
    int id_;
    string name_;
    string author_;
    string status_;

public:
    Book(int id, string name, string author, string status) :
        id_(id), name_(name), author_(author), status_(status)
    {}

    string GetDetailInfo() const;
    string GetSpecificInfo(int InfoType);
    string Details();
    void ChangeSpecificInfo(int InfoType, string change);

};