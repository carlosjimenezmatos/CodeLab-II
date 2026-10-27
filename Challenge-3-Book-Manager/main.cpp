
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <limits>
using namespace std;

// Book class stores information about each book
class Book {
public:
    string title, author, id;
    int pages;
    bool borrowed;

    Book(string t, string a, int p, string i, bool b)
        : title(t), author(a), pages(p), id(i), borrowed(b) {}

    void display() const {
        cout << "\nID: " << id
             << "\nTitle: " << title
             << "\nAuthor: " << author
             << "\nPages: " << pages
             << "\nStatus: " << (borrowed ? "Borrowed" : "Available")
             << "\n";
    }
};

// Read books from the supplied text file
vector<Book> loadBooks() {
    vector<Book> books;
    ifstream file("bookData.txt");
    string line;

    if (!file) {
        cout << "Error: Cannot open bookData.txt\n";
        return books;
    }

    while (getline(file, line)) {
        stringstream ss(line);
        string title, author, pages, id, status;

        if (getline(ss, title, ',') &&
            getline(ss, author, ',') &&
            getline(ss, pages, ',') &&
            getline(ss, id, ',') &&
            getline(ss, status)) {
            try {
                books.emplace_back(title, author, stoi(pages),
                                   id, status == "true");
            } catch (...) {
                cout << "Skipping invalid book record.\n";
            }
        }
    }
    return books;
}

// Save updated borrowing information
void saveBooks(const vector<Book>& books) {
    ofstream file("bookData.txt");

    if (!file) {
        cout << "Error: Could not save book data.\n";
        return;
    }

    for (const Book& book : books) {
        file << book.title << "," << book.author << ","
             << book.pages << "," << book.id << ","
             << (book.borrowed ? "true" : "false") << "\n";
    }
}

// Find a book using its ID
Book* findBook(vector<Book>& books, const string& id) {
    for (Book& book : books) {
        if (book.id == id) {
            return &book;
        }
    }
    return nullptr;
}

int main() {
    vector<Book> books = loadBooks();

    if (books.empty()) {
        cout << "No books loaded. Check bookData.txt.\n";
        return 1;
    }

    int choice;
    string id;

    while (true) {
        cout << "\n===== LIBRARY BOOK MANAGER =====\n";
        cout << "1. View all books\n";
        cout << "2. View individual book\n";
        cout << "3. Borrow a book\n";
        cout << "4. Return a book\n";
        cout << "5. Exit\n";
        cout << "Choose an option: ";

        if (!(cin >> choice)) {
            cout << "Invalid input. Enter a number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (choice == 5) {
            cout << "Goodbye!\n";
            break;
        }

        if (choice == 1) {
            for (const Book& book : books) {
                book.display();
            }
        }
        else if (choice >= 2 && choice <= 4) {
            cout << "Enter book ID: ";
            cin >> id;

            Book* book = findBook(books, id);

            if (book == nullptr) {
                cout << "Book not found.\n";
                continue;
            }

            if (choice == 2) {
                book->display();
            }
            else if (choice == 3) {
                if (book->borrowed) {
                    cout << "This book is already borrowed.\n";
                } else {
                    book->borrowed = true;
                    saveBooks(books);
                    cout << "Book borrowed successfully!\n";
                }
            }
            else if (choice == 4) {
                if (!book->borrowed) {
                    cout << "This book is already available.\n";
                } else {
                    book->borrowed = false;
                    saveBooks(books);
                    cout << "Book returned successfully!\n";
                }
            }
        }
        else {
            cout << "Invalid option. Please try again.\n";
        }
    }

    return 0;
}
