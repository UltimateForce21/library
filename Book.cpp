#include "Book.h"

string Book::GetDetailInfo() const {
	return to_string(id_) + "|" + name_ + "|" + author_ + "|" + status_ + "|" +";";
}

string Book::GetSpecificInfo(int InfoType) {
    if (InfoType == 0) {
        return to_string(id_);
    }
    else if (InfoType == 1) {
        return name_;
    }
    else if (InfoType == 2) {
        return author_;
    }
    else if (InfoType == 3) {
        return status_;
    }
}

string Book::Details() {
    string namestatement = " Book name : ";

    return "Book ID: " + id_ + namestatement + name_ + " Author name: " + author_;
}

void Book::ChangeSpecificInfo(int InfoType, string change) {
    if (InfoType == 0) {
        id_ = stoi(change);
    }
    else if (InfoType == 1) {
        name_ = change;
    }
    else if (InfoType == 2) {
        author_;
    }
    else if (InfoType == 3) {
        status_ = change;
    }
}
 

