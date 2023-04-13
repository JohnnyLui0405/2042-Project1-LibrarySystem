#include <iostream>
#include <fstream> // for file input/output
#include <string>
using namespace std;

class 
void mainMenu();
void manageBookMenu();
void manageBorrowerMenu();
void borrowBooksMenu();
void returnBooksMenu();

class BookList
{
public:
	BookList();
 	void displayBookList();
	void searchBook();
	void addBook();
	void removeBook();
	void back();
private:
int ID, Bookdetails, availability;
}

class BorrowerList
{
public:
	BorrowerList()
	void displayBorrowerList();
	void serachBook();
	void addBorrower();
	void removeBorrower();
	void back()
private:
int ID, Name, Contactnumber, Numberofbooksborrowed;
 }


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

	while (i < line.length())
	{
		if (line[i] == ',' || line[i] == '\"')
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

	fields[numFields][j] = '\0';
	numFields++;

	return numFields;
}

void readCSV(string filename)
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

		for (int i = 0; i < numFields; i++)			// *** display the fields of this line
			cout << i << ": " << fields[i] << endl; // *** you should modify this code for fields processing
		cout << "\n\n";								// *** e.g. assign fields to data members of an object

		countRecords++;
	}

	cout << countRecords << " Record(s) imported.\n";
	inFile.close();
}

// R0 Ask Whether the user want to import the book and the borrower list from a file
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
		getline(cin, filename); // Path with space is allowed
		cout << "Importing book list . . . " << filename;
		readCSV(filename);
		cout << "Done" << endl;

		cout << "Import borrower list from file? [Y/N] ";
		cin >> isImport;
		if (isImport == 'Y')
		{
			cout << "Path of borrower list file: ";
			cin >> filename;
			getline(cin, filename); // Path with space is allowed
			cout << "Importing book list . . . ";
			readCSV(filename);
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

void mainOptionController(int option)
{
	switch (option)
	{
	case 1:
		// Manage books
		manageBookMenu()
		break;
	case 2:
		// Manage borrowers
		manageBorrowerMenu()
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

void manageBookOptionController(int option)
{
	switch (option)
	{
	case 1:
		// Display books
		BookList.displayBooklist()
		break;
	case 2:
		// Search book
		BookList.searchBook()
		break;
	case 3:
		// Add book
		BookList.addBook()
		break;
	case 4:
		// Remove book
		BookList.removeBook()
		break;
	case 5:
		// Back
		BookList.back()
		break;
	default:
		// Invalid input
		break;
	}
}

void manageBorrowersOptionController(int option)
{
	switch (option)
	{
	case 1:
		// Display borrowers
		BorrowerList.displayBooklist()
		break;
	case 2:
		// Add borrowers
		BorrowerList.searchBorrower()
		break;
	case 3:
		// Add book
		BorrowerList.addBorrower()
		break;
	case 4:
		// Remove book
		BorrowerList.removeBorrower()
		break;
	case 5:
		// Back
		BorrowerList.back()
		break;
	default:
		// Invalid input
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
	mainOptionController(option);
}

void manageBookMenu()
{
	int option;
	cout << "*** Manage Books ***" << endl;
	cout << "[1] Display books" << endl;
	cout << "[2] Search book" << endl;
	cout << "[3] Add book" << endl;
	cout << "[4] Remove book" << endl;
	cout << "[5] Back" << endl;
	cout << "********************" << endl;
	cout << "Option (1 - 5): ";

	cin >> option;
	manageBookOptionController(option);
}

void manageBorrowerMenu()
{
	int option;
	cout << "*** Manage Borrowers ***" << endl;
	cout << "[1] Display borrowers" << endl;
	cout << "[2] Search borrower" << endl;
	cout << "[3] Add borrower" << endl;
	cout << "[4] Remove borrower" << endl;
	cout << "[5] Back" << endl;
	cout << "********************" << endl;
	cout << "Option (1 - 5): ";

	cin >> option;
	manageBookOptionController(option);
}


void returnBooksMenu();


int main()
{
	importFile();
	// mainMenu();
	// string filename;

	// cout << "Input path to CSV file: ";
	// getline(cin, filename); // Path with space is allowed
	// readCSV(filename);
	return 0;
}