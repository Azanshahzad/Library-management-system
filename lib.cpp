#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>

using namespace std;

class Book
{
public:
    void addBook()
    {
        int id, qty;
        string title, author;

        cout << "\nEnter Book ID: ";
        cin >> id;
        cin.ignore();

        cout << "Enter Title: ";
        getline(cin, title);

        cout << "Enter Author: ";
        getline(cin, author);

        cout << "Enter Quantity: ";
        cin >> qty;

        ofstream file("books.txt", ios::app);
        file << id << "|" << title << "|" << author << "|" << qty << endl;
        file.close();

        cout << "Book Added Successfully!\n";
    }

void viewBooks()
{
    ifstream file("books.txt");

    if (!file)
    {
        cout << "\nNo Books Found!\n";
        return;
    }

    string line;

    cout << "\n============================== BOOK LIST ==============================\n\n";

    cout << left
         << setw(10) << "ID"
         << setw(30) << "TITLE"
         << setw(25) << "AUTHOR"
         << setw(10) << "QTY" << endl;

    cout << string(75, '=') << endl;

    while (getline(file, line))
    {
        stringstream ss(line);

        string id, title, author, qty;

        getline(ss, id, '|');
        getline(ss, title, '|');
        getline(ss, author, '|');
        getline(ss, qty);

        cout << left
             << setw(10) << id
             << setw(30) << title
             << setw(25) << author
             << setw(10) << qty
             << endl;
    }

    file.close();
}

    void searchBook()
    {
        int id;
        cout << "\nEnter Book ID: ";
        cin >> id;

        ifstream file("books.txt");
        string line;
        bool found = false;

        while (getline(file, line))
        {
            stringstream ss(line);
            string sid;

            getline(ss, sid, '|');

            if (stoi(sid) == id)
            {
                cout << "\nBook Found:\n" << line << endl;
                found = true;
                break;
            }
        }

        file.close();

        if (!found)
            cout << "Book Not Found!\n";
    }

    void deleteBook()
    {
        int id;
        cout << "\nEnter Book ID to Delete: ";
        cin >> id;

        ifstream file("books.txt");
        ofstream temp("temp.txt");

        string line;
        bool found = false;

        while (getline(file, line))
        {
            stringstream ss(line);
            string sid;

            getline(ss, sid, '|');

            if (stoi(sid) != id)
                temp << line << endl;
            else
                found = true;
        }

        file.close();
        temp.close();

        remove("books.txt");
        rename("temp.txt", "books.txt");

        if (found)
            cout << "Book Deleted!\n";
        else
            cout << "Book Not Found!\n";
    }

    void issueBook()
    {
        int bookId, memberId;

        cout << "\nEnter Book ID: ";
        cin >> bookId;

        cout << "Enter Member ID: ";
        cin >> memberId;

        ofstream file("issued.txt", ios::app);
        file << bookId << "|" << memberId << endl;
        file.close();

        cout << "Book Issued Successfully!\n";
    }

    void returnBook()
    {
        int bookId, memberId;

        cout << "\nEnter Book ID: ";
        cin >> bookId;

        cout << "Enter Member ID: ";
        cin >> memberId;

        ifstream file("issued.txt");
        ofstream temp("temp.txt");

        string line;
        bool found = false;

        while (getline(file, line))
        {
            stringstream ss(line);
            string b, m;

            getline(ss, b, '|');
            getline(ss, m);

            if (stoi(b) == bookId && stoi(m) == memberId)
                found = true;
            else
                temp << line << endl;
        }

        file.close();
        temp.close();

        remove("issued.txt");
        rename("temp.txt", "issued.txt");

        if (found)
            cout << "Book Returned Successfully!\n";
        else
            cout << "Record Not Found!\n";
    }
};

class Member
{
public:
    void addMember()
    {
        int id;
        string name;

        cout << "\nEnter Member ID: ";
        cin >> id;
        cin.ignore();

        cout << "Enter Name: ";
        getline(cin, name);

        ofstream file("members.txt", ios::app);
        file << id << "|" << name << endl;
        file.close();

        cout << "Member Added Successfully!\n";
    }

    void viewMembers()
    {
        ifstream file("members.txt");
        string line;

        cout << "\n===== MEMBER LIST =====\n";

        while (getline(file, line))
            cout << line << endl;

        file.close();
    }

    void searchMember()
    {
        int id;
        cout << "\nEnter Member ID: ";
        cin >> id;

        ifstream file("members.txt");
        string line;
        bool found = false;

        while (getline(file, line))
        {
            stringstream ss(line);
            string sid;

            getline(ss, sid, '|');

            if (stoi(sid) == id)
            {
                cout << "\nMember Found:\n" << line << endl;
                found = true;
                break;
            }
        }

        file.close();

        if (!found)
            cout << "Member Not Found!\n";
    }
};

int main()
{
    Book b;
    Member m;

    int choice;

    do
    {
        cout << "\n\n===== LIBRARY SYSTEM =====\n";
        cout << "1. Add Book\n";
        cout << "2. View Books\n";
        cout << "3. Search Book\n";
        cout << "4. Delete Book\n";
        cout << "5. Issue Book\n";
        cout << "6. Return Book\n";
        cout << "7. Add Member\n";
        cout << "8. View Members\n";
        cout << "9. Search Member\n";
        cout << "10. Exit\n";

        cout << "\nEnter Choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1: b.addBook(); break;
        case 2: b.viewBooks(); break;
        case 3: b.searchBook(); break;
        case 4: b.deleteBook(); break;
        case 5: b.issueBook(); break;
        case 6: b.returnBook(); break;
        case 7: m.addMember(); break;
        case 8: m.viewMembers(); break;
        case 9: m.searchMember(); break;
        }

    } while (choice != 10);

    return 0;
}