#include <iostream>
#include <iomanip>
#include <fstream> // for file input/output
#include <string>
#include <algorithm>
using namespace std;

class Book
{
public:
	string ID;
	string title;
	string author;
	string publisher;
	string year;
	bool isAvailable;

	Book()
	{
		isAvailable = true;
	}
};

string *split(string str, char del, int *numKeywords)
{
	string *keywords = new string[50];
	string temp = "";
	bool isQuoted = false;
	for (int i = 0; i < (int)str.size(); i++)
	{
		if (str[i] == '"')
		{
			isQuoted = !isQuoted;
		}
		if (str[i] != del || isQuoted)
		{
			temp += str[i];
		}
		else
		{
			keywords[*numKeywords] = temp;
			*numKeywords = *numKeywords + 1;
			;
			temp = "";
		}
	};
	keywords[*numKeywords] = temp;
	*numKeywords = *numKeywords + 1;
	return keywords;
}

class Borrower
{
public:
	string borrowerID;
	string lastName;
	string firstName;
	string contactNum;
};

class Library
{
public:
	int numBooks;
	Book bookList[1000];
	int numBorrowers;
	Borrower borrowerList[500];

	Library()
	{
		numBooks = 0;
		numBorrowers = 0;
	}

	void sortBookList()
	{
		sort(bookList, bookList + numBooks, [](Book a, Book b)
			 { return a.title < b.title; });
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

	void removeBookByUser()
	{
		string ID;
		cout << "Enter book ID: ";
		cin >> ID;
		for (int i = 0; i < numBooks; i++)
		{
			if (bookList[i].ID == ID && bookList[i].isAvailable)
			{
				size_t headerWidth[5] = {13, 103, 53, 53, 10};
				string isAvailableText = bookList[i].isAvailable ? "Yes" : "No";
				cout << left << setw(headerWidth[0]) << "ID"
					 << setw(headerWidth[1]) << "Book Details"
					 << setw(headerWidth[4]) << "Availibility" << endl;
				cout << left << setw(headerWidth[0]) << bookList[i].ID
					 << setw(headerWidth[1]) << bookList[i].title
					 << setw(10) << isAvailableText << endl;
				cout << setw(headerWidth[0]) << ""
					 << setw(headerWidth[1]) << bookList[i].author
					 << setw(headerWidth[4]) << ""
					 << "\n"
					 << setw(headerWidth[0]) << ""
					 << setw(headerWidth[1]) << bookList[i].publisher + "(" + bookList[i].year + ")"
					 << endl;
				cout << "Are you sure you want to remove this book? (Y/N): ";
				string choice;
				cin >> choice;
				if (choice == "Y" || choice == "y")
				{
					for (int j = i; j < numBooks - 1; j++)
					{
						bookList[j] = bookList[j + 1];
					}
					numBooks--;
					cout << "Book removed" << endl;
					return;
				}
				else
				{
					cout << "Book not removed" << endl;
					return;
				}

				// for (int j = i; j < numBooks - 1; j++)
				// {
				// 	bookList[j] = bookList[j + 1];
				// }
				// numBooks--;
				// cout << "Book removed" << endl;
				// return;
			}
		}
		cout << "Book not found or not available" << endl;
	}

	void addBookByUser()
	{
		string ID, title, author, publisher;
		int year;
		cout << "=====================================================================================================" << endl;
		cout << "To add a book to the system, the you needs to provide the following details :" << endl;
		cout << "-ID(a string with maximum 10 characters, has to be unique)" << endl;
		cout << "-Title(a string with maximum 100 characters)" << endl;
		cout << "-Author(a string with maximum 50 characters, may contains multiple names separated by semi-colon ‘;’)" << endl;
		cout << "-Publisher(a string with maximum 50 characters)" << endl;
		cout << "-Year(a positive integer)" << endl;
		cout << "=====================================================================================================" << endl;

		cout
			<< "Enter book ID: ";
		cin >> ID;
		if (ID.size() > 10)
		{
			cout << "Only string with maximum 10 characters is allowed" << endl;
			return;
		}
		for (int i = 0; i < numBooks; i++)
		{
			if (bookList[i].ID == ID)
			{
				cout << "Book ID already exists" << endl;
				return;
			}
		}

		cout << "Enter book title: ";
		cin.ignore();
		getline(cin, title);
		if (title.size() > 100)
		{
			cout << "Only string with maximum 100 characters is allowed" << endl;
			return;
		}

		cout << "Enter book author: ";
		getline(cin, author);
		if (author.size() > 50)
		{
			cout << "Only string with maximum 50 characters is allowed" << endl;
			return;
		}

		cout << "Enter book publisher: ";
		getline(cin, publisher);
		if (publisher.size() > 50)
		{
			cout << "Only string with maximum 50 characters is allowed" << endl;
			return;
		}

		cout << "Enter book year: ";
		cin >> year;
		if (cin.fail())
		{						   // check whether last input was failed
			cin.clear();		   // Reset the input error status to no error
			cin.ignore(255, '\n'); // ignore maximum of 255 characters,
								   // or reached the end of line.
		}
		if (year <= 0)
		{
			cout << "Only positive integer is allowed" << endl;
			return;
		}
		addBook(ID, title, author, publisher, to_string(year));
	}

	void displayBooks()
	{
		sortBookList();
		size_t headerWidth[5] = {13, 103, 53, 53, 10};
		cout << left << setw(headerWidth[0]) << "ID"
			 << setw(headerWidth[1]) << "Book Details"
			 << setw(headerWidth[4]) << "Availibility" << endl;
		for (int i = 0; i < numBooks; i++)
		{
			string isAvailableText = bookList[i].isAvailable ? "Yes" : "No";
			cout << left << setw(headerWidth[0]) << bookList[i].ID
				 << setw(headerWidth[1]) << bookList[i].title
				 << setw(10) << isAvailableText << endl;
			cout << setw(headerWidth[0]) << ""
				 << setw(headerWidth[1]) << bookList[i].author
				 << setw(headerWidth[4]) << ""
				 << "\n"
				 << setw(headerWidth[0]) << ""
				 << setw(headerWidth[1]) << bookList[i].publisher + "(" + bookList[i].year + ")"
				 << endl;
		}
	}

	void searchBook()
	{
		string keyword;
		cin.ignore();
		cout << "Enter keyword: ";
		getline(cin, keyword);
		if (keyword.size() > 50)
		{
			cout << "Only string with maximum 50 characters is allowed" << endl;
			return;
		}

		int numKeywords = 0;
		string *keywords = split(keyword, ' ', &numKeywords);

		sortBookList();
		size_t headerWidth[5] = {13, 103, 53, 53, 10};
		cout << left << setw(headerWidth[0]) << "ID"
			 << setw(headerWidth[1]) << "Book Details"
			 << setw(headerWidth[4]) << "Availibility" << endl;
		for (int i = 0; i < numBooks; i++)
		{
			string title = bookList[i].title;
			string author = bookList[i].author;
			string publisher = bookList[i].publisher;
			string ID = bookList[i].ID;

			for (int j = 0; j < numKeywords; j++)
			{
				if (keywords[j][0] == '"' && keywords[j][keywords[j].size() - 1] == '"')
				{
					keywords[j] = keywords[j].substr(1, keywords[j].size() - 2);
				}
				else
				{
					transform(title.begin(), title.end(), title.begin(), ::tolower);
					transform(author.begin(), author.end(), author.begin(), ::tolower);
					transform(publisher.begin(), publisher.end(), publisher.begin(), ::tolower);
					transform(ID.begin(), ID.end(), ID.begin(), ::tolower);
					transform(keywords[j].begin(), keywords[j].end(), keywords[j].begin(), ::tolower);
				}

				if (title.find(keywords[j]) != string::npos || author.find(keywords[j]) != string::npos || publisher.find(keywords[j]) != string::npos || ID.find(keywords[j]) != string::npos)
				{
					string isAvailableText = bookList[i].isAvailable ? "Yes" : "No";
					cout << left << setw(headerWidth[0]) << bookList[i].ID
						 << setw(headerWidth[1]) << bookList[i].title
						 << setw(10) << isAvailableText << endl;
					cout << setw(headerWidth[0]) << ""
						 << setw(headerWidth[1]) << bookList[i].author
						 << setw(headerWidth[4]) << ""
						 << "\n"
						 << setw(headerWidth[0]) << ""
						 << setw(headerWidth[1]) << bookList[i].publisher + "(" + bookList[i].year + ")"
						 << endl;
					break;
				}
			}
		}
	}

	void sortBorrowerList()
	{
		sort(borrowerList, borrowerList + numBorrowers, [](Borrower a, Borrower b)
			 { return a.lastName < b.lastName; });
	}

	void addBorrower(string lastName, string firstName, string contactNum)
	{
		Borrower borrower;
		borrower.lastName = lastName;
		borrower.firstName = firstName;
		borrower.contactNum = contactNum;
		borrowerList[numBorrowers] = borrower;
		numBorrowers++;
		cout << "Borrower added" << borrower.borrowerID << endl;
	}

	void displayBorrowers()
	{

	}

	void searchBorrower()
	{

	}

	void addBorrowerByUser()
	{

	}

	void removeBorrowerByUser()
	{
	}
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
	bool isQuote = false;

	// **********
	// Implement your code to extract fields from the line
	// **********
	cout << line << endl;
	while (i <= line.length())
	{
		if (line[i] == '"' && line[i + 1] != '"')
		{
			isQuote = !isQuote;
		}
		else if (line[i] == '"' && line[i + 1] == '"')
		{
			fields[numFields][j] = line[i];
			j++;
			i++;
		}
		else if (line[i] == ',' && !isQuote)
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
	string isImport;
	while (true)
	{
		cout << "Import book list from file? [Y/n] ";
		getline(cin, isImport);
		if (isImport == "Y" || isImport == "y")
		{
			cout << "Path of book list file: ";
			// getline(cin, filename); // Path with space is allowed
			filename = "BookList.csv";
			cout << "Importing book list . . . " << filename;
			readCSV(filename, "book");
			cout << "Done" << endl;
			break;
		}
		else if (isImport == "N" || isImport == "n")
		{
			break;
		}
		else
		{
			cout << "Invalid input. Please try again." << endl;
		}
	}

	while (true)
	{
		cout << "Import borrower list from file? [Y/n] ";
		getline(cin, isImport);
		if (isImport == "Y" || isImport == "y")
		{
			cout << "Path of borrower list file: ";
			// getline(cin, filename); // Path with space is allowed
			filename = "BorrowerList.csv";
			cout << "Importing book list . . . ";
			readCSV(filename, "borrower");
			cout << "Done" << endl;
			break;
		}
		else if (isImport == "N" || isImport == "n")
		{
			break;
		}
		else
		{
			cout << "Invalid input. Please try again." << endl;
		}
	}
}

void manageBorrowers()
{
	int option;
	cout << "*** Manage Books ***" << endl;
	cout << "[1] Display borrowers" << endl;
	cout << "[2] Search borrower" << endl;
	cout << "[3] Add borrower" << endl;
	cout << "[4] Remove borrower" << endl;
	cout << "[5] Back" << endl;
	cout << "*******************" << endl;
	cout << "Option (1 - 5): ";

	cin >> option;
	if (cin.fail())
	{						   // check whether last input was failed
		cin.clear();		   // Reset the input error status to no error
		cin.ignore(255, '\n'); // ignore maximum of 255 characters,
							   // or reached the end of line.
	}
	switch (option)
	{
	case 1:
		// Display books
		library.displayBorrowers();
		break;
	case 2:
		// Search book
		library.searchBorrower();
		break;
	case 3:
		// Add book
		library.addBorrowerByUser();
		break;
	case 4:
		// Remove book
		library.removeBorrowerByUser();
		break;
	case 5:
		// Back
		return;
		break;
	default:
		cout << "Invalid input" << endl;
		break;
	}
	manageBorrowers();
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
	if (cin.fail())
	{						   // check whether last input was failed
		cin.clear();		   // Reset the input error status to no error
		cin.ignore(255, '\n'); // ignore maximum of 255 characters,
							   // or reached the end of line.
	}
	switch (option)
	{
	case 1:
		// Display books
		library.displayBooks();
		break;
	case 2:
		// Search book
		library.searchBook();
		break;
	case 3:
		// Add book
		library.addBookByUser();
		break;
	case 4:
		// Remove book
		library.removeBookByUser();
		break;
	case 5:
		// Back
		return;
		break;
	default:
		cout << "Invalid input" << endl;
		break;
	}
	manageBorrowers();
}

void borrowBooks(){
	string borrowerID;
	string valid = "HKCC";
	string bookID;
	bool flag = true;
	cout << "*************************************Borrow Book(s)****************************************" << endl;
	cout << "To borrow book(s), you should provide the following details: " << endl;
	cout << "Borrower ID" << endl;
	cout << "Book ID" << endl;
	cout << "You can borrow at most 5 books." << endl;
	cout << "If the quota is used up, you cannot borrow more books until some books have been returned." << endl;
	cout << "*******************************************************************************************" << endl;

	while (flag = true){
		cout << "Enter Borrower ID: ";
		getline(cin, borrowerID);
		if ((borrowerID.size() != 8) ){
			cout << "Invalid Borrower ID length. Please enter again." << endl;
		}
		else if (borrowerID.substr(0,4) != valid.substr(0,4)){
			cout << "Invalid Borrower ID format. Please enter again." << endl;
		}
		// else {
			// find borrower ID
			// if (not found){
				// cout << "Borrower ID not found. Please enter again." << endl;
			// }
			// else flag = false;
		// }
	}
	
	// if (){
		// check quota
	// }
	// else {
		// cout << "Out of quota." << endl;
		// break;
	// }
	

	flag = true;
	while (flag = true){
		cout << "Enter Book ID (enter N/n when finish input): ";
		getline(cin,bookID);
		if ((bookID == "N") || (bookID == "n")){
			cout << "End of Book ID input." << endl;
			flag = false;
			break;
		}
		else if (bookID.size() > 10){
			cout << "Invalid Book ID length. Please enter again." << endl;
		}
		// else {
			// search book ID
			// if (found){
				// update book availability
				// quota++
				// break;
			// }
		// }
		// if (out of quota){
			// cout << "Out of quota." << endl;
			// flag = false;
		// }
	}

	cout << "End of borrowing process. Back to main menu." << endl;
	mainMenu();
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
	if (cin.fail())
	{						   // check whether last input was failed
		cin.clear();		   // Reset the input error status to no error
		cin.ignore(255, '\n'); // ignore maximum of 255 characters,
							   // or reached the end of line.
	}
	switch (option)
	{
	case 1:
		// Manage books
		manageBooks();
		break;
	case 2:
		// Manage borrowers
		manageBorrowers();
		break;
	case 3:
		// Borrow book(s)
		borrowBooks();
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
		return;
		break;
	default:
		// Invalid input
		break;
	}
	mainMenu();
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