#include "Book.h"

string Book::GetDetailInfo() const {
	return to_string(id_) + ":" + name_ + ":" + author_ + ":" + ";";
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
}

string Book::Details() {
    string namestatement = " Book name : ";

    return "Book ID: " + id_ + namestatement + name_ + " Author name: " + author_;
}


