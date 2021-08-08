#include "Users.h"

string User::GetUsername () const{
	return user_;

}

string User::GetNumBooks() const {
	return to_string(numBooksOut_);

}

string User::GetBookIndexes() const {
	string entirething;
	for (int i = 0; i < bookIndexes_.size(); i++) {
		entirething += to_string(bookIndexes_[i]) + ",";
	}
	//cout << "Entire thing: " + entirething << endl;
	return entirething;
}

void User::BooksTakenOut(bool takeout, string tempid) {
	cout << "Original number of books under current user: " + to_string(numBooksOut_) << endl;
	int temp = stoi(tempid);
	if (takeout) {
		numBooksOut_++;
		
		//cout << "Temp: " << temp << endl;
		bookIndexes_.push_back(temp);
		//cout << "Added temp in Book: " << bookIndexes_.back() << endl;

	}
	else {
		numBooksOut_--;
		for (int i = 0; i < bookIndexes_.size(); i++) {
			if (temp == bookIndexes_[i]) {
				bookIndexes_.erase(bookIndexes_.begin()+i);
			}
		}
	}
	cout << "New number of books under current user: " + to_string(numBooksOut_) << endl;
}



