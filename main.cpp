#include <iostream>
#include "Book.h"
#include <fstream>

#include <string>
#include <vector>
using namespace std;

ostream& operator << (ostream& out, const Book& b)
{
    out << b.GetDetailInfo();
    return out;
}
void ReadLibraryFile(vector <Book> &list, int &last_ID, bool &file_exist) {
    ifstream ifile("bookLibrary.txt");
    if (ifile) {
        file_exist = true;


        string line;
        int booknumber = 0;
        int type = 0;
        int integerID = 0;

        // while (!ifile.eof())
        while (!ifile.eof()) {
            getline(ifile, line);
            if (line == "") {
                break;
            }

            char ch = ' ';
            string item = " ";
            int letterIterator = 0;
            int type = 0;
            string id;
            string bookname;
            string authorname;
            while (ch != ';') {
                ch = line[letterIterator];

                if (ch != ':') {
                    item.push_back(ch);
                }
                else {
                    if (type == 0) {
                        id = item;
                        //cout << id <<endl;
                        integerID = stoi(id);
                        type++;

                    }
                    else if (type == 1) {
                        bookname = item;
                        type++;
                    }
                    else if (type == 2) {
                        authorname = item;
                        type = 0;
                    }

                    item = "";

                    ch = ' ';
                }
                letterIterator++;
                
            }

            //cout << "id: " << id << " bookname: " << bookname << " authorname: "<< authorname << endl;
            Book current = { integerID, bookname, authorname };
            list.push_back(current);

            //cout << list[booknumber].GetDetailInfo() << endl;

            booknumber++;



            ch = ' ';
            //cout << endl;
        }
        if (booknumber == 0) {
            last_ID = 1;
        }
        else {
            last_ID = booknumber;
        }
        ifile.close();

        //cout << "\n";
    }
}

vector<Book> Enterbook() {

    vector <Book> list;
    int last_ID = 0;
    bool file_exist = false;
    ReadLibraryFile(list, last_ID, file_exist);
    //cout << "Last ID: " << last_ID << endl;

    ofstream file;
    file.open("bookLibrary.txt", ios_base::app);
    int numbooks;
    string endline;

    cout << "How many books?" << endl;
    cin >> numbooks;
    cin.ignore(); // done to flush out the endl that existed after entering the int



    for (int booknum = 0; booknum < numbooks; booknum++) {

        string bookname, authorname;
        cout << "Enter book name:" << endl;
        getline(cin, bookname);


        cout << "Enter " << bookname << "'s author:\n";
        getline(cin, authorname);

        Book b = { booknum + last_ID, bookname, authorname };
        list.push_back(b);


        if (file_exist) {
            file << "\n" << b;
        }
        else {
            file << b << endl;
        }



    }
    file.close();
    return list;
}

int FIND(vector <Book> list, int type, string searchQuery) {
    
    int booknum;
    bool bookfound = false;
    for (int book = 0; book < list.size(); book++) {  
        if (list[book].GetSpecificInfo(type) == searchQuery) {
            cout << "Using " << searchQuery << " Found " << list[book] << "\n\n";
            bookfound = true;
            booknum = book;
            return booknum;
        }  
    }
    if (bookfound == false) {
        cout << "Using search query: " << searchQuery << " book was not found.\n\n";
    }
}
void Delete(vector <Book>& list, int bookID /*to delete with*/) {
    cout << list[bookID] << " has been erased. :(" << endl;
    list.erase(list.begin() + bookID);
    ofstream file;
    file.open("bookLibrary.txt");
    for (int i = 0; i < list.size(); i++) {
        if (i != list.size() - 1)
            file << list[i] << endl;
        else
            file << list[i];
    }


    //file << b << std::endl;
    file.close();

}
void PrintBooks(vector <Book>& list) {
    
    cout << "\n\n";
    for (int i = 0; i < list.size(); i++) {
        cout << list[i] << endl;
    }
    cout << "\n\n";
}



int main() {
    vector <Book> LibraryList = Enterbook();
    bool exit = false;
    while (exit == false) {
        int choice;
        cout << "Please Pick One of the Following options:" << endl;
        cout << "1- Find a book" << endl;
        cout << "2- Delete a book" << endl;
        cout << "3- Print all books" << endl;
        cout << "4- Exist Program" << endl;
        cin >> choice;

        if (choice == 1) {
            int type;
            cout << "Enter type of search" << endl;
            cout << "0- Search by id\n1-Search by book name\n2-Search by author name" << endl;
            cin >> type;
            string searchQuery;
            cout << "Enter search query: " << endl;
            cin.ignore();
            getline(cin, searchQuery);
            FIND(LibraryList, type, searchQuery);


        }
        else if (choice == 2) {
            int type;
            cout << "Enter type of search required to delete book" << endl;
            cout << "0- Search and delete by id\n1-Search and delete by book name\n2-Search and delete by author name" << endl;
            cin >> type;
            string searchDeleteQuery;
            cout << "Enter search and delete query: " << endl;
            cin.ignore();
            getline(cin, searchDeleteQuery);
            int bookIndex = FIND(LibraryList, type, searchDeleteQuery);
            Delete(LibraryList, bookIndex);
        }

        else if (choice == 3) {
            PrintBooks(LibraryList);
        }


        

        else if (choice == 4) {
            break;
        }
    }
    // std::cout << b << std::endl;

    // std::ofstream file;
    // file.open("mylibrary.txt");

    // file << b << std::endl;
    // file.close();
}