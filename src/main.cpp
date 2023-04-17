#include <iostream>
#include <iomanip>
#include <fstream> // for file input/output
#include <string>
using namespace std;

class Book
{
public:
	string ID;
	string title;
	string author;
	string publisher;
	string year;
};

class Borrower
{
public:
	string borrowerID;
	string lastName;
	string firstName;
	string contractNum;
};

class Library
{
public:
	int numBooks;
	Book bookList[1000];
	int numBorrowers;
	Borrower borrowerList[1000];

	Library()
	{
		numBooks = 0;
		numBorrowers = 0;
	}

	void addBook(string ID, string title, string author, string publisher, string year)
	{
		Book book;
		book.ID = ID;
		book.title = title;
		book.author = author;
		book.publisher = publisher;
		book.year = year;
		bookList[numBooks] = book;
		numBooks++;
		cout << "Book added" << endl;
	}

	void addBorrower(string lastName, string firstName, string contractNum)
	{
		Borrower borrower;
		borrower.lastName = lastName;
		borrower.firstName = firstName;
		borrower.contractNum = contractNum;
		borrowerList[numBorrowers] = borrower;
		numBorrowers++;
		cout << "Borrower added" << borrower.borrowerID << endl;
	}

	void displayBooks()
	{
		size_t headerWidth[5] = {10, 100, 50, 50, 10};
		cout << left << setw(headerWidth[0]) << "ID"
			 << setw(headerWidth[1]) << "Title"
			 << setw(headerWidth[2]) << "Author"
			 << setw(headerWidth[3]) << "Publisher"
			 << setw(headerWidth[4]) << "Year" << endl;
		for (int i = 0; i < numBooks; i++)
		{
			cout << left << setw(headerWidth[0]) << bookList[i].ID
				 << setw(headerWidth[1]) << bookList[i].title
				 << setw(headerWidth[2]) << bookList[i].author
				 << setw(headerWidth[3]) << bookList[i].publisher
				 << setw(headerWidth[4]) << bookList[i].year << endl;
		}
	}
	// cout << bookList[i].ID << " " << bookList[i].title << " " << bookList[i].author << " " << bookList[i].publisher << " " << bookList[i].year << endl;
};

Library library;

int extractFields(string line, char fields[][101])
{
	/*
	 *	Suggested algorithm:
	 *	1. Use loop to check every char of string
	 *	2. Handle when it is " or ,
	 *	3. Copy the content char into 2D array fields
	 *	4. Count the number of fields
	 */
	int numFields = 0, i = 0, j = 0;

	// **********
	// Implement your code to extract fields from the line
	// **********
	cout << line << endl;
	while (i <= line.length())
	{
		if (line[i] == ',')
		{
			fields[numFields][j] = '\0';
			numFields++;
			j = 0;
		}
		else
		{
			fields[numFields][j] = line[i];
			j++;
		}
		i++;
	}
	return numFields;
}

void readCSV(string filename, string type)
{
	fstream inFile;			   // for handling file
	string line;			   // for storing 1 line in a file
	char fields[10][101] = {}; // for storing extracted fields (assume max. 10 fields per line, each field has max. 100 char)
	int numFields;			   // for storing number of fields per line
	int countRecords = 0;	   // for counting the number of records in csv file

	inFile.open(filename);
	if (!inFile.is_open())
	{
		cout << "Cannot open file \"" << filename << "\"\n";
		return;
	}

	while (getline(inFile, line, '\n'))
	{											 // read line by line until end of file
		numFields = extractFields(line, fields); // call function to extract fields from the line

		for (int i = 0; i <= numFields; i++)
		{											// *** display the fields of this line
			cout << i << ": " << fields[i] << endl; // *** you should modify this code for fields processing
		}
		if (type == "book") // Add book
			library.addBook(fields[0], fields[1], fields[2], fields[3], fields[4]);
		else if (type == "borrower") // Add borrower
			library.addBorrower(fields[0], fields[1], fields[2]);
		countRecords++;
	}

	cout << countRecords << " Record(s) imported.\n";
	inFile.close();
}

void importFile()
{
	string filename;
	char isImport;

	cout << "Import book list from file? [Y/N] ";
	cin >> isImport;
	if (isImport == 'Y')
	{
		cin.ignore();
		cout << "Path of book list file: ";
		// getline(cin, filename); // Path with space is allowed
		filename = "G:\\Code\\Github\\2042-Project\\src\\BookList.csv";
		cout << "Importing book list . . . " << filename;
		readCSV(filename, "book");
		cout << "Done" << endl;
		cout << "Import borrower list from file? [Y/N] ";
		cin >> isImport;
		if (isImport == 'Y')
		{
			cin.ignore();
			cout << "Path of borrower list file: ";
			// getline(cin, filename); // Path with space is allowed
			filename = "G:\\Code\\Github\\2042-Project\\src\\BorrowerList.csv";
			cout << "Importing book list . . . ";
			readCSV(filename, "borrower");
			cout << "Done" << endl;

			cout << "Welcome to the Library Management System";
		}
		else if (isImport == 'N')
		{
			cout << "No borrower list is imported";
		}
		else
		{
			cout << "Invalid input";
		}
	}
	else if (isImport == 'N')
	{
		cout << "No book list is imported";
	}
	else
	{
		cout << "Invalid input";
	}
}

void manageBooks()
{
	int option;
	cout << "*** Manage Books ***" << endl;
	cout << "[1] Display books" << endl;
	cout << "[2] Search book" << endl;
	cout << "[3] Add book" << endl;
	cout << "[4] Remove book" << endl;
	cout << "[5] Back" << endl;
	cout << "*******************" << endl;
	cout << "Option (1 - 5): ";

	cin >> option;
	switch (option)
	{
	case 1:
		// Display books
		library.displayBooks();
		break;
	case 2:
		// Search book
		break;
	case 3:
		// Add book
		break;
	case 4:
		// Remove book
		break;
	case 5:
		// Back
		break;
	default:
		cout << "Invalid input" << endl;
		break;
	}
}

void mainMenu()
{
	int option;
	cout << "*** Library Management System ***" << endl;
	cout << "[1] Manage books" << endl;
	cout << "[2] Manage borrowers" << endl;
	cout << "[3] Borrow book(s)" << endl;
	cout << "[4] Return book(s)" << endl;
	cout << "[5] Useful feature(s) added" << endl;
	cout << "[6] Member List" << endl;
	cout << "[7] Exit" << endl;
	cout << "*********************************" << endl;
	cout << "Option (1 - 7): ";

	cin >> option;
	switch (option)
	{
	case 1:
		// Manage books
		manageBooks();
		break;
	case 2:
		// Manage borrowers
		break;
	case 3:
		// Borrow book(s)
		break;
	case 4:
		// Return book(s)
		break;
	case 5:
		// Useful feature(s) added
		break;
	case 6:
		// Member List
		break;
	case 7:
		// Exit
		break;
	default:
		// Invalid input
		break;
	}
}

int main()
{
	string filename;
	importFile();
	mainMenu();

	// cout << "Input path to CSV file: ";
	// getline(cin, filename); // Path with space is allowed
	// readCSV(filename);

	return 0;
}