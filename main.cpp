#include <iostream>
#include "Book.h"
#include "Users.h"
#include <fstream>
#include <string>
#include <vector>
#include <string>
#include <iomanip>

ostream& operator << (ostream& out, const Book& b)
{
    out << b.GetDetailInfo();
    return out;
}
ostream& operator << (ostream& out, const User& current)
{
    out << current.GetUsername();
    return out;
}
void ReadLibraryFile(vector <Book> &list, int &last_ID, bool &file_exist, string filename) {
    ifstream ifile(filename);
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
            string status;
            while (ch != ';') {
                ch = line[letterIterator];

                if (ch != '|') {
                    item.push_back(ch);
                }
                else {


                    if (type == 0) {
                        id = item;

                        //cout << "this is the id " << id << endl;
                        
                        integerID = stoi(id);                     
                        type++;

                    }
                    else if (type == 1) {
                        bookname = item;
                        //cout << bookname << endl;
                        type++;
                    }
                    else if (type == 2) {
                        authorname = item;
                        type++;
                    }
                    else if (type == 3) {
                        status = item;
                        type = 0;
                    }

                    item = "";

                    ch = ' ';
                }
                letterIterator++;
                
            }

            //cout << "id: " << id << " bookname: " << bookname << " authorname: "<< authorname << endl;
            
            Book current = { integerID, bookname, authorname, status };
            list.push_back(current);
            booknumber++;
            

            //cout << list[booknumber].GetDetailInfo() << endl;

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

void ReadUsersFile(vector <User> &userslist, int &lastUserNum, bool &file_exist) {
    ifstream ifile("users.txt");    
    if (ifile) {        
        file_exist = true;
        int usernum = 0;
        
        while (!ifile.eof()) {
            
            string line;
            
            getline(ifile, line);
            if (line == "") {
                if (userslist.size() == 0)
                    file_exist = false;
                break;
            }
            int type = 0;
            string item;
            string username;
            int numbooks = 0;
            vector <int> bookIndexes;
            
            char letter;
            for (int ch = 0; ch < line.size(); ch++) {
                letter = line[ch];
                if (letter != '|' && type != 2) {
                    item.push_back(letter);
                }
                else if (type == 2) {
                    if (letter != ',') {
                        item.push_back(letter);
                    }
                    else {
                        //cout << "Item as a Book index: " + item << endl;
                        bookIndexes.push_back(stoi(item));
                        item = "";
                    }
                }
                else {
                    if (type == 0) {
                        username = item;
                        item = "";
                        type++;
                    }
                    else if (type == 1){
                        // << item + "item 1" << endl;
                        numbooks = stoi(item);
                        item = "";
                        type++;
                        //cout << type << "is type\n";
                    }
                }
            }
            
            //cout << "username: " + username << " numbooks: " << numbooks << endl;
            //for (int book = 0; book < bookIndexes.size(); book++) {
            //    cout << bookIndexes[book] << " ";
            //}
            //cout << endl;
            
            //New stuff
            bool sameuser = false;
            for (int user = 0; user < userslist.size(); user++) {
                if (username == userslist[user].GetUsername()) {
                    sameuser = true;
                }
            }
            if (sameuser == false) {
                if (bookIndexes.size() != 0) {
                    User current = User(username, numbooks, bookIndexes);
                    userslist.push_back(current);
                    usernum++;
                }
                else {
                    User current = User(username, numbooks);
                    userslist.push_back(current);
                    usernum++;
                }
            }

        } //while.eof

        if (usernum == 0) {
            lastUserNum = 1;
        }
        else {
            lastUserNum = usernum;

        }
    
    }
}

vector<Book> Enterbook() {

    vector <Book> list;
    int last_ID = 0;
    bool file_exist = false;
    ReadLibraryFile(list, last_ID, file_exist, "newascii.txt");
    //cout << "Last ID: " << last_ID << endl;

    ofstream file;
    file.open("newascii.txt", ios_base::app);
    int numbooks;
    string endline;

    cout << "How many books would you like to enter?" << endl;
    cin >> numbooks;
    cin.ignore(); // done to flush out the endl that existed after entering the int



    for (int booknum = 0; booknum < numbooks; booknum++) {

        string bookname, authorname;
        cout << "Enter book name:" << endl;
        getline(cin, bookname);


        cout << "Enter " << bookname << "'s author:\n";
        getline(cin, authorname);

        Book b = { booknum + last_ID, bookname, authorname, "in" };
        list.push_back(b);


        if (file_exist) {
            file << "\n" << b;
        }
        else {
            file << b;
        }



    }
    file.close();
    return list;
    
}

void CreateUser(vector <User> &userslist) {
    int lastUserNum = 0;
    bool file_exist = false;
    
    ReadUsersFile(userslist, lastUserNum, file_exist);

    ofstream file;
    file.open("users.txt", ios_base::app);
    string username;
    cout << "Enter new username:" << endl;
    
    getline(cin, username);
    
    User current = username;
    userslist.push_back(current);

    if (file_exist) {
        file << "\n" << username + "|0|";
    }
    else {
        file << username + "|0|";
    }

    file.close();
}

int FIND(vector <Book> list, int type, string searchQuery) {
    
    int booknum = -1;
    bool bookfound = false;
    for (int book = 0; book < list.size(); book++) {  
        if (list[book].GetSpecificInfo(type) == searchQuery) {
            cout << "\n\nUsing " << searchQuery << " Found " << list[book] << "\n\n";
            bookfound = true;
            booknum = book;
            
        }  
    }
    return booknum;
}
void Delete(vector <Book>& list, int bookID /*to delete with*/) {
    cout << list[bookID] << " has been erased. :(" << endl;
    list.erase(list.begin() + bookID);
    ofstream file;
    file.open("newascii.txt");
    for (int i = 0; i < list.size(); i++) {
        if (i != list.size() - 1) {
            file << list[i] << endl;
            //file << list[i].GetSpecificInfo(0) + "|" + list[i].GetSpecificInfo(1) + "|" + list[i].GetSpecificInfo(2) + "|" + "in" + "|" + ";" << endl;
        }
        else {
            file << list[i];
            //file << list[i].GetSpecificInfo(0) + "|" + list[i].GetSpecificInfo(1) + "|" + list[i].GetSpecificInfo(2) + "|" + "in" + "|" + ";";
        }
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

bool Login(vector <User> userslist, int &currentUser) {
    cout << "Login ID:\n";
    string tried_username;
    getline(cin, tried_username);
    
    //cout << "Real Usernames" << endl;
    
    for (int user = 0; user < userslist.size(); user++) {

        //cout << userslist[user].GetUsername() << endl;
        
        if (userslist[user].GetUsername() == tried_username) {
        cout << "Welcome " << userslist[user] << "!!!\n";
        currentUser = user;
        return true;
        }
    }
    cout << "Please Try Again" << endl;
    return false;
}

void TakeoutTakeIn(bool takeout, vector <Book>& list, vector <User>& userslist, int currentUser) {
    int type;
    cout << "Enter type of search required" << endl;
    cout << "0- Search by id\n1-Search by book name\n2-Search by author name" << endl;
    cin >> type;
    string searchtkQuery;
    cout << "Enter search and take out query: " << endl;
    cin.ignore();
    getline(cin, searchtkQuery);
    bool rewrite = false;
    int bookIndex = FIND(list, type, searchtkQuery);
    if (bookIndex != -1) {
        if (takeout && list[bookIndex].GetSpecificInfo(3) == "in") {
            list[bookIndex].ChangeSpecificInfo(3, "out");
            //Changes user's number of books taken out and vector of books
            string tempid = list[bookIndex].GetSpecificInfo(0);
            userslist[currentUser].BooksTakenOut(true, tempid);
            rewrite = true;
            cout << "\n\nBook taken out successfully.\n\n" << endl;

        }
        else if (!takeout && list[bookIndex].GetSpecificInfo(3) == "out") {
            list[bookIndex].ChangeSpecificInfo(3, "in");
            //Changes user's number of books taken out and vector of books
            string tempid = list[bookIndex].GetSpecificInfo(0);
            userslist[currentUser].BooksTakenOut(false, tempid);
            rewrite = true;
            cout << "\n\nBook returned out succefully.\n\n" << endl;
        }
        else {
            cout << "This action cannot be done at this time due to status of book.\n\n" << endl;
        }

        cout << "Number of books in current user: " + userslist[currentUser].GetNumBooks() << endl;

        if (rewrite) {
            ofstream userfile;
            userfile.open("users.txt", 'w');
            for (int user = 0; user < userslist.size(); user++) {
                if (user != userslist.size() - 1) {

                    userfile << userslist[user].GetUsername() + '|' + userslist[user].GetNumBooks() + '|' + userslist[user].GetBookIndexes() << endl; //change to also save vector of taken out
                    //cout << userslist[user].GetUsername() + '|' + userslist[user].GetNumBooks() + '|' + userslist[user].GetBookIndexes() << endl;
                }
                else {
                    userfile << userslist[user].GetUsername() + '|' + userslist[user].GetNumBooks() + '|' + userslist[user].GetBookIndexes(); //change to also save vector of taken out
                    //cout << userslist[user].GetUsername() + '|' + userslist[user].GetNumBooks() + '|' + userslist[user].GetBookIndexes();
                }
            }
            userfile.close();

            cout << "\nBook Status : [" << list[bookIndex] << "]\n" << endl;
            ofstream file;
            file.open("newascii.txt");
            for (int i = 0; i < list.size(); i++) {
                if (i != list.size() - 1) {
                    file << list[i] << endl;
                }
                else {
                    file << list[i];
                }
            }
            file.close();
        }
    }
    else {
        cout << "Book was not found" << endl;
    }

}



int main() {
    clock_t start, end;
    
    int currentUser;
    int lastUserNum = 0;
    bool file_exist = false;
    vector <User> userslist;
    ReadUsersFile(userslist, lastUserNum, file_exist);
    if (userslist.size() == 0) {
        cout << "Please create a user" << endl;
        CreateUser(userslist);
    }
    bool LoggedIn = false;
    while (!LoggedIn) {
        LoggedIn = Login(userslist, currentUser);
    }

    //cout << "Current Username = " + userslist[currentUser].GetUsername() << " booknumber: " + userslist[currentUser].GetNumBooks() << endl;

    vector <Book> LibraryList = Enterbook();
    bool exit = false;
    while (exit == false) {
        int choice;
        cout << "Please Pick One of the Following options:" << endl;
        cout << "1- Find a book" << endl;
        cout << "2- Delete a book" << endl;
        cout << "3- Print all books" << endl;
        cout << "4- Enter a new book" << endl;
        cout << "5- Create a new user" << endl;
        cout << "6- Take-out/Put-back a book" << endl;
        cout << "0- Exist Program" << endl;
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
            start = clock();
            
            int bookIndex = FIND(LibraryList, type, searchQuery);
            if (bookIndex != -1) {
                Delete(LibraryList, bookIndex);
            }
            else {
                cout << "Book was not found.\n" << endl;
            }
            end = clock();
            double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
            cout << "\n Time taken for find function:" << fixed << time_taken << setprecision(5) << endl;

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
            if (bookIndex != -1) {
                Delete(LibraryList, bookIndex);
            }
            else {
                cout << "Book was not found and could not be deleted." << endl;
            }
        }

        else if (choice == 3) {
            PrintBooks(LibraryList);
        }
        else if (choice == 4) {
            LibraryList = Enterbook();
        }
        else if (choice == 5) {
            cin.ignore();
            CreateUser(userslist);
        }
        else if (choice == 6) {
            string uinput;
            cout << "1-Take out\n2-Bring Back" << endl;
            cin >> uinput;
            if (uinput == "1") {
                TakeoutTakeIn(true, LibraryList, userslist, currentUser);
            }
            else {
                TakeoutTakeIn(false, LibraryList, userslist, currentUser);
            }
            
        }

        else{
            break;
        }
    }
    // std::cout << b << std::endl;

    // std::ofstream file;
    // file.open("mylibrary.txt");

    // file << b << std::endl;
    // file.close();
}