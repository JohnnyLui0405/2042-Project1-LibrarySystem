#include <iostream>
#include <iomanip>
#include <fstream> // for file input/output
#include <string>
#include <algorithm>
#include <sstream>
#include <cstdlib>
using namespace std;

// Common functions
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

// If input is "exit", "quit", or "q", return true
bool isExit(string input)
{
	return input == "exit" || input == "quit" || input == "q";
}

// If Contact Number is valid, return true
bool isValidContactNum(string contactNum)
{
	return (contactNum[0] == '2' || contactNum[0] == '3' || contactNum[0] == '5' || contactNum[0] == '6' || contactNum[0] == '9');
}

// to convert string to lowercase
string toLower(string str)
{
	for (int i = 0; i < (int)str.size(); i++)
	{
		str[i] = tolower(str[i]);
	}
	return str;
}

// to convert string to uppercase
string toUpper(string str)
{
	for (int i = 0; i < (int)str.size(); i++)
	{
		str[i] = toupper(str[i]);
	}
	return str;
}

// class DateTime
// {
// public:
// 	void printTime()
// 	{
// 		cout << setfill('0') << setw(2) << hour << ":" << setw(2) << minute << ":" << setw(2) << second << " " << setw(2) << day << "/" << setw(2) << month << "/" << setw(4) << year << endl;
// 	}
// 	void setTimeNow()
// 	{
// 		// time(0) get Unix Time (seconds since 1 Jan 1970)
// 		// tm is a structure that contains the time components
// 		// localtime() convert Unix Time to local Time Zone
// 		time_t now = time(0);
// 		tm *ltm = localtime(&now);
// 		hour = ltm->tm_hour;
// 	}
// 	void getDueDay()
// 	{
// 		hour
// 	}

// private:
// 	int hour, minute, second, day, month, year;
// };

// DateTime getDueDate()
// {
// 	DateTime dueDate;
// 	dueDate.setTimeNow();
// 	dueDate.day += 7;
// 	if (dueDate.day > 30)
// 	{
// 		dueDate.day -= 30;
// 		dueDate.month++;
// 		if (dueDate.month > 12)
// 		{
// 			dueDate.month -= 12;
// 			dueDate.year++;
// 		}
// 	}
// 	return dueDate;
// }

void systemExit()
{
	char choice;
	cout << "Are you sure you want to exit? (Y/n): ";
	cin >> choice;
	if (choice == 'Y' || choice == 'y')
	{
		cout << "Exiting..." << endl;
		exit(0);
	}
	else if (choice == 'N' || choice == 'n')
	{
		cout << "Back to main menu." << endl;
	}
	else
	{
		cout << "Invalid input. Back to main menu." << endl;
	}
}

void mainMenu();
class Book
{
public:
	string ID;
	string title;
	string author;
	string publisher;
	string year;
	// DateTime dueDate;
	bool isAvailable;

	Book()
	{
		isAvailable = true;
	}
};
class Borrower
{
public:
	string borrowerID;
	string lastName;
	string firstName;
	string fullName;
	string contactNum;
	Book *borrowedBooks;
	int numBorrowedBooks;

	Borrower()
	{
		numBorrowedBooks = 0;
		borrowedBooks = new Book[5];
	}
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

	// if book is available, return true
	bool isBorrowed(string bookID, Borrower borrower)
	{
		for (int i = 0; i < borrower.numBorrowedBooks; i++)
		{
			if (borrower.borrowedBooks[i].ID == bookID)
			{
				return true;
			}
		}
		return false;
	}

	// sort Book list using Bubble Sort
	void sortBookList()
	{
		int i, j;
		for (i = 0; i < numBooks - 1; i++)
		{
			for (j = 0; j < numBooks - i - 1; j++)
			{
				if (bookList[j].title > bookList[j + 1].title)
				{
					Book temp = bookList[j];
					bookList[j] = bookList[j + 1];
					bookList[j + 1] = temp;
				}
			}
		}
	}

	// sort Borrower list using Bubble Sort
	void sortBorrowerList()
	{
		int i, j;
		for (i = 0; i < numBorrowers - 1; i++)
		{
			for (j = 0; j < numBorrowers - i - 1; j++)
			{
				if (borrowerList[j].lastName > borrowerList[j + 1].lastName)
				{
					Borrower temp = borrowerList[j];
					borrowerList[j] = borrowerList[j + 1];
					borrowerList[j + 1] = temp;
				}
			}
		}
	}

	// add book to bookList
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
		// cout << "Book added" << endl;
	}

	// remove book from bookList
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
				cout << "Are you sure you want to remove this book? (Y/n): ";
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
			}
		}
		cout << "Book not found or not available" << endl;
	}

	// add book to bookList by user
	void addBookByUser()
	{
		string ID, title, author, publisher;
		int year;
		cout << "=====================================================================================================" << endl;
		cout << "To add a book to the system, the you needs to provide the following details :" << endl;
		cout << "- ID(a string with maximum 10 characters, has to be unique)" << endl;
		cout << "- Title(a string with maximum 100 characters)" << endl;
		cout << "- Author(a string with maximum 50 characters, may contains multiple names separated by semi-colon ‘;’)" << endl;
		cout << "- Publisher(a string with maximum 50 characters)" << endl;
		cout << "- Year(a positive integer)" << endl;
		cout << "type 'exit' to exit" << endl;
		cout << "=====================================================================================================" << endl;

		while (true)
		{

			cout
				<< "Enter book ID: ";
			cin >> ID;
			if (isExit(ID))
			{
				return;
			}

			if (ID.size() > 10)
			{
				cout << "Only string with maximum 10 characters is allowed" << endl;
			}
			else if (validateBook(ID) != -1)
			{
				cout << "Book ID already exists" << endl;
			}
			else
			{
				break;
			}
		}

		while (true)
		{
			cout << "Enter book title: ";
			cin.ignore();
			getline(cin, title);
			if (isExit(title))
			{
				return;
			}
			if (title.size() > 100)
			{
				cout << "Only string with maximum 100 characters is allowed" << endl;
			}
			else
			{
				break;
			}
		}

		while (true)
		{
			cout << "Enter book author: ";
			getline(cin, author);
			if (isExit(author))
			{
				return;
			}
			if (author.size() > 50)
			{
				cout << "Only string with maximum 50 characters is allowed" << endl;
			}
			else
			{
				break;
			}
		}

		while (true)
		{
			cout << "Enter book publisher: ";
			getline(cin, publisher);
			if (isExit(publisher))
			{
				return;
			}
			if (publisher.size() > 50)
			{
				cout << "Only string with maximum 50 characters is allowed" << endl;
			}
			else
			{
				break;
			}
		}

		while (true)
		{
			cout << "Enter book year: ";
			cin >> year;
			if (isExit(to_string(year)))
			{
				return;
			}
			if (cin.fail())
			{						   // check whether last input was failed
				cin.clear();		   // Reset the input error status to no error
				cin.ignore(255, '\n'); // ignore maximum of 255 characters,
									   // or reached the end of line.
			}
			if (year <= 0)
			{
				cout << "Only positive integer is allowed" << endl;
			}
			else
			{
				break;
			}
		}
		addBook(ID, title, author, publisher, to_string(year));
		sortBookList();
		cout << "Book added" << endl;
	}

	// check if borrowerID exist in borrowerList, and return the index using linear search
	int validateBorrower(string borrowerID, int low, int high)
	{
		for (int i = 0; i < numBorrowers; i++)
		{
			if (borrowerList[i].borrowerID == borrowerID)
			{
				return i;
			}
		}

		return -1;
	}

	// check if bookID exist in bookList, and return the index using linear search
	int validateBook(string bookID)
	{
		for (int i = 0; i < numBooks; i++)
		{
			if (bookList[i].ID == bookID)
			{
				return i;
			}
		}
		return -1;
	}

	int randomBook()
	{
		int bookIndex = rand() % (numBooks);
		return bookIndex;
	}

	// displayBookList
	void displayBooks()
	{
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

	// searchBook by keywords
	void searchBook()
	{
		cout << "=====================================================================================================" << endl;
		cout << "To search for a book, the user needs to provide the following details :" << endl;
		cout << "Single keyword or multiple keywords separated by space" << endl;
		cout << "The system will display all books that contain the keyword(s) in their title, author, or publisher" << endl;
		cout << "If the keyword is qutoed, the system will display all books that contain the exact keyword" << endl;
		cout << "=====================================================================================================" << endl;
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
					// convert to lowercase
					keywords[j] = toLower(keywords[j]);
					title = toLower(title);
					author = toLower(author);
					publisher = toLower(publisher);
					ID = toLower(ID);
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

	void displayBookInfo(int bookIndex)
	{
		cout << "Book details:" << endl;
		cout << "Title: " << bookList[bookIndex].title << endl;
		cout << "Author: " << bookList[bookIndex].author << endl;
		cout << "Publisher: " << bookList[bookIndex].publisher << endl;
		cout << "Year of publication: " << bookList[bookIndex].year << endl;
		return;
	}

	void addBorrower(string lastName, string firstName, string contactNum)
	{
		Borrower borrower;
		borrower.borrowerID = "HKCC" + string(4 - to_string(numBorrowers + 1).size(), '0') + to_string(numBorrowers + 1);
		borrower.lastName = lastName;
		borrower.firstName = firstName;
		borrower.fullName = lastName + " " + firstName;
		borrower.contactNum = contactNum;
		borrowerList[numBorrowers] = borrower;
		numBorrowers++;
		// cout << "Borrower added " << borrower.borrowerID << endl;
	}

	void displayBorrowers()
	{
		cout << "sorting" << endl;
		size_t headerWidth[4] = {11, 43, 20, 20};
		cout << left << setw(headerWidth[0]) << "borrowerID"
			 << setw(headerWidth[1]) << "Name"
			 << setw(headerWidth[2]) << "Contact Number"
			 << setw(headerWidth[3]) << "Number of books borrowed"
			 << endl;

		for (int i = 0; i < numBorrowers; i++)
		{
			cout << left << setw(headerWidth[0]) << borrowerList[i].borrowerID
				 << setw(headerWidth[1]) << borrowerList[i].lastName + " " + borrowerList[i].firstName
				 << setw(headerWidth[2]) << borrowerList[i].contactNum
				 << setw(headerWidth[3]) << borrowerList[i].numBorrowedBooks
				 << endl;
		}
	}

	void searchBorrower()
	{
		string borrowerID;
		cout << "Enter borrowerID: ";
		cin >> borrowerID;
		if (borrowerID.size() > 10)
		{
			cout << "Only string with maximum 10 characters is allowed" << endl;
			return;
		}

		int index = validateBorrower(borrowerID, 0, numBorrowers - 1);

		if (index == -1)
		{
			cout << "Borrower not found" << endl;
			return;
		}
		else
		{
			size_t headerWidth[4] = {11, 43, 20, 20};
			cout << left << setw(headerWidth[0]) << "borrowerID"
				 << setw(headerWidth[1]) << "Name"
				 << setw(headerWidth[2]) << "Contact Number"
				 << setw(headerWidth[3]) << "Number of books borrowed"
				 << endl;

			cout << left << setw(headerWidth[0]) << borrowerList[index].borrowerID
				 << setw(headerWidth[1]) << borrowerList[index].fullName
				 << setw(headerWidth[2]) << borrowerList[index].contactNum
				 << setw(headerWidth[3]) << borrowerList[index].numBorrowedBooks
				 << endl;

			cout << "List of books borrowed: " << endl;

			if (borrowerList[index].numBorrowedBooks > 0)
			{
				cout << left << setw(headerWidth[0]) << "bookID"
					 << setw(headerWidth[1]) << "Title"
					 << setw(headerWidth[2]) << "Author"
					 << setw(headerWidth[3]) << "Publisher"
					 << endl;
				for (int i = 0; i < borrowerList[index].numBorrowedBooks; i++)
				{
					cout << left << setw(headerWidth[0]) << borrowerList[index].borrowedBooks[i].ID
						 << setw(headerWidth[1]) << borrowerList[index].borrowedBooks[i].title
						 << setw(headerWidth[2]) << borrowerList[index].borrowedBooks[i].author
						 << setw(headerWidth[3]) << borrowerList[index].borrowedBooks[i].publisher
						 << endl;
				}
			}
			else
			{
				cout << "No books borrowed" << endl;
			}
		}
	}

	void addBorrowerByUser()
	{
		string lastName, firstName, contactNum;
		cout << "=====================================================================================================" << endl;
		cout << "To add a borrower to the system, the you needs to provide the following details :" << endl;
		cout << "-lastName(a string with maximum 10 characters)" << endl;
		cout << "-firstName(a string with maximum 30 characters)" << endl;
		cout << "-contactNumber(an 8-digit number, begins with 2, 3, 5, 6, or 9)" << endl;
		cout << "=====================================================================================================" << endl;

		cout << "Enter Last Name: ";
		cin.ignore();
		getline(cin, lastName);
		while (lastName.size() > 10)
		{
			cout << "Only string with maximum 10 characters is allowed" << endl;
			getline(cin, lastName);
			if (isExit(lastName))
				return;
		}

		// to upper case
		for (int i = 0; i < lastName.size(); i++)
		{
			lastName[i] = toupper(lastName[i]);
		}

		cout << "Enter First Name: ";
		getline(cin, firstName);
		while (firstName.size() > 30)
		{
			cout << "Only string with maximum 30 characters is allowed" << endl;
			getline(cin, firstName);
			if (isExit(firstName))
				return;
		}

		cout << "Enter Contact Number: ";
		getline(cin, contactNum);
		while (contactNum.size() != 8 || !isValidContactNum(contactNum))
		{
			cout << "Only integer with an 8-digit number, begins with 2, 3, 5, 6, or 9 is allowed" << endl;
			cout << "Enter Contact Number: ";
			getline(cin, contactNum);
			if (isExit(contactNum))
				return;
		}

		lastName = toUpper(lastName);
		int numofwords = 0;
		string *firstNameWords = split(firstName, ' ', &numofwords);
		for (int i = 0; i < numofwords; i++)
		{
			firstNameWords[i][0] = toupper(firstNameWords[i][0]);
			cout << firstNameWords[i] << endl;
		}
		firstName = "";
		for (int i = 0; i < numofwords; i++)
		{
			firstName += firstNameWords[i];
			if (i != numofwords - 1)
				firstName += " ";
		}
		addBorrower(lastName, firstName, contactNum);
		sortBorrowerList();
	}

	void removeBorrowerByUser()
	{
		string borrowerID;
		cout << "Enter borrower ID: ";
		cin >> borrowerID;
		int index = validateBorrower(borrowerID, 0, numBorrowers - 1);
		if (index == -1 || borrowerList[index].numBorrowedBooks > 0)
			cout << "Borrower not found or has books borrowed" << endl;
		else
		{
			// display the borrower
			size_t headerWidth[4] = {11, 43, 20, 20};
			cout << left << setw(headerWidth[0]) << "borrowerID"
				 << setw(headerWidth[1]) << "Name"
				 << setw(headerWidth[2]) << "Contact Number"
				 << setw(headerWidth[3]) << "Number of books borrowed"
				 << endl;
			cout << left << setw(headerWidth[0]) << borrowerList[index].borrowerID
				 << setw(headerWidth[1]) << borrowerList[index].fullName
				 << setw(headerWidth[2]) << borrowerList[index].contactNum
				 << setw(headerWidth[3]) << borrowerList[index].numBorrowedBooks
				 << endl;
			// confirm
			string choice;
			cout << "Are you sure you want to remove this borrower? (Y/n): ";
			cin >> choice;
			if (choice == "Y" || choice == "y")
			{
				for (int i = index; i < numBorrowers - 1; i++)
				{
					borrowerList[i] = borrowerList[i + 1];
				}
				numBorrowers--;
				cout << "Borrower removed" << endl;
			}
			else
				cout << "Borrower not removed" << endl;
		}
	}

	void borrowBooks()
	{
		string borrowerID;
		string valid = "HKCC";
		string bookID;
		bool flag = true;
		cout << "************************************ Borrow Book(s) ***************************************" << endl;
		cout << "To borrow book(s), you should provide the following details: " << endl;
		cout << "Borrower ID (HKCCXXXX e.g. HKCC0001)" << endl;
		cout << "Book ID" << endl;
		cout << "You can borrow at most 5 books." << endl;
		cout << "If the quota is used up, you cannot borrow more books until some books have been returned." << endl;
		cout << "*******************************************************************************************" << endl;

		cin.ignore(1);
		while (flag == true)
		{
			cout << "Enter Borrower ID: ";
			getline(cin, borrowerID);
			if (isExit(borrowerID))
				return;
			if ((borrowerID.size() != 8))
			{
				cout << "Invalid Borrower ID length. Please enter again." << endl;
			}
			else if (borrowerID.substr(0, 4) != valid.substr(0, 4))
			{
				cout << "Invalid Borrower ID format. Please enter again." << endl;
			}
			else
			{
				// find borrower ID
				if ((validateBorrower(borrowerID, 0, numBorrowers - 1)) == -1)
				{
					cout << "Borrower ID not found. Please enter again." << endl;
				}
				else
					flag = false;
			}
		}

		int borrowerIndex = validateBorrower(borrowerID, 0, numBorrowers - 1);

		flag = true;
		while (flag == true)
		{
			cout << "Enter Book ID (press [N/n] if you don't want to borrow more books): ";
			getline(cin, bookID);
			if (isExit(bookID))
				return;
			if ((bookID == "N") || (bookID == "n"))
			{
				cout << "End of Book ID input." << endl;
				flag = false;
				break;
			}
			else if (bookID.size() > 10)
			{
				cout << "Invalid Book ID length. Please enter again." << endl;
			}
			else
			{
				int bookIndex = validateBook(bookID);
				if (bookIndex == -1)
				{
					cout << "Book ID not found. Please enter again." << endl;
				}
				else
				{
					// update book availability
					// number of books borrowed++
					if (bookList[bookIndex].isAvailable && borrowerList[borrowerIndex].numBorrowedBooks != 5)
					{
						borrowerList[borrowerIndex].borrowedBooks[borrowerList[borrowerIndex].numBorrowedBooks] = bookList[bookIndex];
						borrowerList[borrowerIndex].numBorrowedBooks++;
						bookList[bookIndex].isAvailable = false;
						// bookList[bookIndex].dueDate = getDueDate();
						cout << "Book borrowed successfully." << endl;
						cout << "Number of books borrowed: " << borrowerList[borrowerIndex].numBorrowedBooks << endl;
						if (borrowerList[borrowerIndex].numBorrowedBooks == 5)
						{
							cout << "You have reached the maximum number of books you can borrow." << endl;
							cout << "Please return some books before borrowing more." << endl;
							return;
						}
					}
					else if (bookList[bookIndex].isAvailable == false)
					{
						cout << "This book has already been borrowed." << endl;
					}
					else
					{
						cout << "You have reached the maximum number of books you can borrow." << endl;
						cout << "Please return some books before borrowing more." << endl;
					}
				}
			}
		}

		cout << "End of borrowing process. Back to main menu." << endl;
		return;
	}

	void returnBooks()
	{
		string borrowerID;
		string valid = "HKCC";
		string bookID;
		bool flag = true;
		cout << "************************************ Return Book(s) ***************************************" << endl;
		cout << "To return book(s), you should provide the following details: " << endl;
		cout << "Borrower ID (HKCCXXXX e.g. HKCC0001)" << endl;
		cout << "Book ID" << endl;
		cout << "You can borrow at most 5 books." << endl;
		cout << "If the quota is used up, you cannot borrow more books until some books have been returned." << endl;
		cout << "*******************************************************************************************" << endl;

		cin.ignore(1);
		while (flag == true)
		{
			cout << "Enter Borrower ID: ";
			getline(cin, borrowerID);
			if (isExit(borrowerID))
				return;
			if ((borrowerID.size() != 8))
			{
				cout << "Invalid Borrower ID length. Please enter again." << endl;
			}
			else if (borrowerID.substr(0, 4) != valid.substr(0, 4))
			{
				cout << "Invalid Borrower ID format. Please enter again." << endl;
			}
			else
			{
				// find borrower ID
				if ((validateBorrower(borrowerID, 0, numBorrowers - 1)) == -1)
				{
					cout << "Borrower ID not found. Please enter again." << endl;
				}
				else
					flag = false;
			}
		}

		int borrowerIndex = validateBorrower(borrowerID, 0, numBorrowers - 1);

		flag = true;
		while (flag == true)
		{
			cout << "Enter Book ID (press [N/n] if you don't want to return more books): ";
			getline(cin, bookID);
			if (isExit(bookID))
				return;
			if ((bookID == "N") || (bookID == "n"))
			{
				cout << "End of Book ID input." << endl;
				flag = false;
				break;
			}
			else if (bookID.size() > 10)
			{
				cout << "Invalid Book ID length. Please enter again." << endl;
			}
			else
			{
				int bookIndex = validateBook(bookID);
				if (bookIndex == -1)
				{
					cout << "Book ID not found. Please enter again." << endl;
				}
				else
				{
					// update book availability
					// number of books borrowed--
					if (isBorrowed(bookID, borrowerList[borrowerIndex]) && borrowerList[borrowerIndex].numBorrowedBooks != 0)
					{
						borrowerList[borrowerIndex].numBorrowedBooks--;
						bookList[bookIndex].isAvailable = true;
						cout << "Book returned successfully." << endl;
					}
					else if (isBorrowed(bookID, borrowerList[borrowerIndex]) == false)
					{
						cout << "You have not borrowed this book." << endl;
					}
					else
					{
						cout << "You have not borrowed any books." << endl;
						return;
					}
				}
			}
		}

		cout << "End of returning process. Back to main menu." << endl;
		return;
	}

	void randomBookRecommend()
	{
		string bookID;
		int bookIndex;
		char input;
		cout << "Having no idea to read which book? Here is an available book recommended for you!" << endl;
		while (true)
		{
			while (true)
			{
			bookIndex = randomBook();
			if (bookList[bookIndex].isAvailable)
			{
			cout << "ID of the recommended book: " << bookList[bookIndex].ID << endl;
			displayBookInfo(bookIndex);
			break;
			}
			else bookIndex = randomBook();
			}

			cout << "Would you like to get another book recommendation? (Y/n)" << endl;
			cin >> input;
			if (input != 'Y' && input != 'y' && input != 'N' && input != 'n')
			{
				cout << "Invalid input. Please enter again." << endl;
			}
			else if (input == 'N' || input == 'n')
			{
				break;
			}
		}
		cout << "Back to main menu." << endl;
		return;
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

		if (type == "book") // Add book
			library.addBook(fields[0], fields[1], fields[2], fields[3], fields[4]);
		else if (type == "borrower") // Add borrower
			library.addBorrower(fields[0], fields[1], fields[2]);
		countRecords++;
	}
	// cout << countRecords << " Record(s) imported.\n";
	inFile.close();
}

// R0 File Import Process
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
			cout << "Importing book list . . . ";
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
			cout << "Importing borrower list . . . ";
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

	library.sortBookList();
	library.sortBorrowerList();

	cout << "Welcome to Library Management System" << endl;
}

void manageBorrowers()
{
	int option;
	cout << "*** Manage Borrowers ***" << endl;
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
	manageBooks();
}

void membersList()
{
	cout << "******************************************" << endl;
	cout << setw(15) << "Group #12" << setw(20) << "Member List" << endl;
	cout << "Name:" << setw(20) << "HUNG Ho Yin" << setw(12) << "22160123A" << setw(5) << "203C" << endl;
	cout << "Name:" << setw(20) << "KAN Wing Yi" << setw(12) << "22144320A" << setw(5) << "203C" << endl;
	cout << "Name:" << setw(20) << "KU Ka Ho" << setw(12) << "22150222A" << setw(5) << "203A" << endl;
	cout << "Name:" << setw(20) << "LUI Chun Shing" << setw(12) << "22075684A" << setw(5) << "203D" << endl;
	cout << "Name:" << setw(20) << "*MAK Ka Wah Andrew" << setw(12) << "22079450A" << setw(5) << "203C" << endl;
	cout << "Name:" << setw(20) << "YUEN Kin Man" << setw(12) << "22153666A" << setw(5) << "203C" << endl;
	cout << "******************************************" << endl;
	cout << "\nEnd of display. Back to main menu.\n";
	return;
}

void mainMenu()
{
	int option;
	cout << "******* Library Management System *******" << endl;
	cout << "[1] Manage books" << endl;
	cout << "[2] Manage borrowers" << endl;
	cout << "[3] Borrow book(s)" << endl;
	cout << "[4] Return book(s)" << endl;
	cout << "[5] Random available book recommendation" << endl;
	cout << "[6] Member List" << endl;
	cout << "[7] Exit" << endl;
	cout << "*****************************************" << endl;
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
		library.borrowBooks();
		break;
	case 4:
		// Return book(s)
		library.returnBooks();
		break;
	case 5:
		// Useful feature(s) added
		library.randomBookRecommend();
		break;
	case 6:
		// Member List
		membersList();
		break;
	case 7:
		// Exit
		systemExit();
		break;
	default:
		// Invalid input
		cout << "Invalid input. Please enter again." << endl;
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
