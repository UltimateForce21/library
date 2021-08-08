#pragma once

#include <string>
#include <iostream>
#include <vector>
using namespace std;

class User {
    string user_;
    int numBooksOut_ = 0;
    vector <int> bookIndexes_;
    


public:
    User(string user, int numBooksOut = 0) :
        user_(user), numBooksOut_(numBooksOut)
    {}
    User() :
        user_("")
    {}
    User(string user, int numBooksOut, vector <int> bookIndexes) :
        user_(user), numBooksOut_(numBooksOut), bookIndexes_(bookIndexes)
    {}

    string GetUsername() const;
    string GetNumBooks() const;
    string GetBookIndexes() const;
    void pushIndexes(vector <int> bookIndexes);
    void BooksTakenOut(bool takeout, string tempid);

};