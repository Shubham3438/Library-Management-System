#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;
class Person {
public:
    string name;

    void inputName(string role) {
        cout << "Enter " << role << " Name: ";
        getline(cin, name);
    }
};

class Teacher : public Person {
public:
    void issueBookRecord(int bookID, string studentName, vector<string>& issuedRecords) {
        string record = "Teacher: " + name + " issued Book ID: " + to_string(bookID) + " to Student: " + studentName;
        issuedRecords.push_back(record);
        cout << "Record: " << record << endl;
    }

    void returnBookRecord(int bookID, string studentName, vector<string>& issuedRecords) {
        string record = "Teacher: " + name + " received Book ID: " + to_string(bookID) + " from Student: " + studentName;
        issuedRecords.push_back(record);
        cout << "Record: " << record << endl;
    }
};

class Student : public Person {
public:
    string regNo;

    void inputStudent() {
        cout << "Enter Student Registration No: ";
        getline(cin, regNo);
        inputName("Student");
    }
};

class Book {
public:
    int bookID;
    string title;
    string author;
    bool isIssued;

    void inputBook() {
        cout << "Enter Book UID: ";
        cin >> bookID;
        cin.ignore();
        cout << "Enter Book Title: ";
        getline(cin, title);
        cout << "Enter Author Name: ";
        getline(cin, author);
        isIssued = false;
    }

    void displayBook() {
        cout << "\nUID: " << bookID
             << "\nTitle: " << title
             << "\nAuthor: " << author
             << "\nStatus: " << (isIssued ? "Issued" : "Available")
             << "\n-------------------------------\n";
    }
};

vector<Book> books = {
    {1, "Don Quixote", "Miguel de Cervantes", false},
    {2, "Alice's Adventures in Wonderland", "Lewis Carroll", false},
    {3, "The Adventures of Huckleberry Finn", "Mark Twain", false},
    {4, "The Adventures of Tom Sawyer", "Mark Twain", false},
    {5, "Treasure Island", "Robert Louis Stevenson", false},
    {6, "Pride and Prejudice", "Jane Austen", false},
    {7, "Wuthering Heights", "Emily Brontë", false},
    {8, "Jane Eyre", "Charlotte Brontë", false},
    {9, "Moby Dick", "Herman Melville", false},
    {10, "The Scarlet Letter", "Nathaniel Hawthorne", false},
    {11, "Gulliver's Travels", "Jonathan Swift", false},
    {12, "The Pilgrim's Progress", "John Bunyan", false},
    {13, "A Christmas Carol", "Charles Dickens", false},
    {14, "David Copperfield", "Charles Dickens", false},
    {15, "A Tale of Two Cities", "Charles Dickens", false},
    {16, "Little Women", "Louisa May Alcott", false},
    {17, "Great Expectations", "Charles Dickens", false},
    {18, "The Hobbit", "J.R.R. Tolkien", false},
    {19, "Frankenstein", "Mary Shelley", false},
    {20, "Oliver Twist", "Charles Dickens", false},
    {21, "Uncle Tom's Cabin", "Harriet Beecher Stowe", false},
    {22, "Crime and Punishment", "Fyodor Dostoyevsky", false},
    {23, "Madame Bovary", "Gustave Flaubert", false},
    {24, "The Return of the King", "J.R.R. Tolkien", false},
    {25, "Dracula", "Bram Stoker", false},
    {26, "The Three Musketeers", "Alexandre Dumas", false},
    {27, "Brave New World", "Aldous Huxley", false},
    {28, "War and Peace", "Leo Tolstoy", false},
    {29, "To Kill a Mockingbird", "Harper Lee", false},
    {30, "The Wizard of Oz", "L. Frank Baum", false},
    {31, "Les Misérables", "Victor Hugo", false},
    {32, "The Secret Garden", "Frances Hodgson Burnett", false},
    {33, "Animal Farm", "George Orwell", false},
    {34, "The Great Gatsby", "F. Scott Fitzgerald", false},
    {35, "The Little Prince", "Antoine de Saint-Exupéry", false},
    {36, "The Call of the Wild", "Jack London", false},
    {37, "20,000 Leagues Under the Sea", "Jules Verne", false},
    {38, "Anna Karenina", "Leo Tolstoy", false},
    {39, "The Wind in the Willows", "Kenneth Grahame", false},
    {40, "The Picture of Dorian Gray", "Oscar Wilde", false},
    {41, "The Grapes of Wrath", "John Steinbeck", false},
    {42, "Sense and Sensibility", "Jane Austen", false},
    {43, "The Last of the Mohicans", "James Fenimore Cooper", false},
    {44, "Tess of the d'Urbervilles", "Thomas Hardy", false},
    {45, "Harry Potter and the Sorcerer's Stone", "J.K. Rowling", false},
    {46, "Heidi", "Johanna Spyri", false},
    {47, "Ulysses", "James Joyce", false},
    {48, "The Complete Sherlock Holmes", "Arthur Conan Doyle", false},
    {49, "The Count of Monte Cristo", "Alexandre Dumas", false},
    {50, "The Old Man and the Sea", "Ernest Hemingway", false}
};

void createBookListFile() {
    ofstream fout("booklist.txt");
    fout << "UID\tTitle\tAuthor\n";
    for (Book &b : books) {
        fout << b.bookID << "\t" << b.title << "\t" << b.author << "\n";
    }
    fout.close();
    cout << "\n booklist.txt created with all book records.\n";
}

void addBook() {
    Book b;
    b.inputBook();
    books.push_back(b);
    cout << "\n Book added successfully!\n";
}

void displayBooks() {
    if (books.empty()) {
        cout << "\n No books found.\n";
        return;
    }
    for (Book &b : books) {
        b.displayBook();
    }
}

void issueBook(Teacher &teacher, vector<string>& issuedRecords) {
    Student student;
    student.inputStudent();

    int id;
    cout << "Enter Book UID to issue: ";
    cin >> id;

    bool found = false;

    for (Book &b : books) {
        if (b.bookID == id && !b.isIssued) {
            b.isIssued = true;
            teacher.issueBookRecord(id, student.name, issuedRecords);
            cout << "\n Book issued successfully to " << student.name << "!\n";
            found = true;
            break;
        }
    }

    if (!found)
        cout << "\n Book not found or already issued.\n";
}

void returnBook(Teacher &teacher, vector<string>& issuedRecords) {
    Student student;
    student.inputStudent();

    int id;
    cout << "Enter Book UID to return: ";
    cin >> id;

    bool found = false;

    for (Book &b : books) {
        if (b.bookID == id && b.isIssued) {
            b.isIssued = false;
            teacher.returnBookRecord(id, student.name, issuedRecords);
            cout << "\n Book returned successfully by " << student.name << "!\n";
            found = true;
            break;
        }
    }

    if (!found)
        cout << "\n Book not found or not issued.\n";
}

void viewIssuedRecords(vector<string>& issuedRecords) {
    if (issuedRecords.empty()) {
        cout << "\n No issued records found.\n";
        return;
    }

    cout << "\n=== Issued Records ===\n";
    for (string record : issuedRecords) {
        cout << record << endl;
    }
}

int main() {
    int choice;
    vector<string> issuedRecords;

    // Create booklist.txt on program start
    createBookListFile();

    Teacher teacher;
    teacher.inputName("Teacher");

    while (true) {
        cout << "\n======= LIBRARY MANAGEMENT SYSTEM =======\n";
        cout << "1. Add New Book\n";
        cout << "2. View All Books\n";
        cout << "3. Issue Book\n";
        cout << "4. Return Book\n";
        cout << "5. View Issued Records\n";
        cout << "6. Exit\n";
        cout << "=========================================\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: addBook(); break;
            case 2: displayBooks(); break;
            case 3: issueBook(teacher, issuedRecords); break;
            case 4: returnBook(teacher, issuedRecords); break;
            case 5: viewIssuedRecords(issuedRecords); break;
            case 6: cout << "\n Exiting... Thank you!\n"; return 0;
            default: cout << "\n Invalid option. Try again.\n";
        }

        cout << "\n";
        system("pause");
    }
}
