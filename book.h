#pragma once

#include <string>
#include <iostream>

using namespace std;

class Book {
    int id_;
    string name_;
    string author_;

public:
    Book(int id, string name, string author) :
        id_(id), name_(name), author_(author)
    {}

    string GetDetailInfo() const;
    string GetSpecificInfo(int InfoType);
    string Details();
};