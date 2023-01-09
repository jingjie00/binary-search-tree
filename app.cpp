#define _CRT_SECURE_NO_WARNINGS
#include	<iostream>
#include	<fstream>
#include	<cstdlib>
#include	<cstdio>
#include	<ctime>
#include	<string>
#include	<Windows.h>
#include	"BST.h"
#include    "Student.h"

using namespace std;

//We only edited BST.h(function declaration), BST.cpp(function definition) and app.cpp(question 7(menu) and question 1(readfile))
//We labelled every task we done by question1, question2... it is corresponding to task a, task b, task c...

bool readFile(const char*, BST*);
int menu();

int main() {
	//design
	system("color E0"); cout << "\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t      Welcome\n\t\t\t\t\t\t  Just a moment..\n\t\t\t\t\t      Checking the program...";
	Beep(2000, 100); Beep(1500, 120); Beep(2000, 80); Beep(1500, 100); Sleep(2000); system("cls"); system("color 70");

	//check all assignment related-file exist
	ifstream file1, file2;
	char f1, f2;
	file1.open("Layout_menu.txt"); file2.open("Layout_thanks.txt");
	file1 >> f1; file2 >> f2;
	if (!file1 || !file2 || f1 != '*' || f2 != '*') {
		system("color E0"); Beep(2000, 100); Beep(1500, 120); Beep(2000, 80); Beep(1500, 100);
		cout << "\n\n\n\n\n\n\n\n\t\t\t\t\tSystem detected missing / unable \n\t\t\t\t     to open some necesarry file as below" << endl << endl;
		if (!file1) cout << "\t\t\t\t\t\tLayout_menu.txt" << endl;
		if (!file2) cout << "\t\t\t\t\t\tLayout_thanks.txt" << endl;
		else cout << "Other abnormal situation occured. Please contact 011-3810 0852 for help" << endl;//cause by system error or compiler error. Normally would no happen
		cout << "\n\n\t\t\t\t Please included it for program able to run.\n\t\t\t\t  The program will terminated after 10 second...    " << endl << endl;
		Sleep(10000);
		return 0;
	}
	else {
		file1.close(); file2.close();
	}

	//here started*******************************************************************************************************************************

	string line;
	char* filename = new char[200], input[100], input2[100];
	int choice, order, source;
	bool error = true;
	ifstream file;
	BST* student = new BST;
	BST* t2;
	Student* stu;

	do {
		t2 = new BST; //make sure is empty
		stu = new Student; //make sure is empty
		choice = menu(); //function start here
		switch (choice) {
		case 1:
			cout << "\n\nRead data to BST\n";
			cout << "**If duplicate of student id is found,\nsystem will automatic update the record with the latest. \n\n";
			cout << "**If the student detail is incomplete, system will automatic drop the student. \n\n";
			cout << "Please enter the filename to be read ( eg:student.txt / selfmadestudent.txt / [any_name].txt )" << endl;
			cout << "Input------->";
			cin.ignore(); cin.getline(filename, 200, '\n'); cout << endl;
			if (!readFile(filename, student)) //function start here
				cout << "Fail to open the file" << endl;
			else
				cout << "\nCurrenly having total of " << student->count << " student." << endl;
			break;

		case 2:
			cout << "\n\nPrint deepest nodes\n\n";
			if (!student->deepestNodes()) //function start here
				cout << "The tree is empty!!!Please go through option<1> to read student record" << endl;
			break;

		case 3:
			cout << "\n\nDisplay student\n\n";
			do {
				if (!error)
					cout << "\nInvalid input!!!Please try again\n\n";
				cout << "Do you want to print the tree in ascending or descending order ( 0 - back to menu/ 1 - Ascending / 2 - Descending ): " << endl;
				cin >> input;
				if (strlen(input) < 2 && input[0] >= '0' && input[0] <= '2') {
					order = input[0] - '0';//minus the ascii value of 0 to get the number of that character represent like ((int)input[0])-((int)'0')
					if (order == 0)//enter 0 to return menu
						break;
					cout << "Where do you want display the output ( 0 - back to menu/ 1 - screen / 2 - file ): " << endl;
					cin >> input2;
					if (strlen(input2) < 2 && input2[0] >= '0' && input2[0] <= '2') {
						source = input2[0] - '0';//minus the ascii value of 0 to get the number of that character represent like ((int)input2[0])-((int)'0')
						if (source == 0)//enter 0 to return menu
							break;
						if (!student->display(order, source)) {//function start here
							cout << "\nThe tree is empty!!!Please go through option <1> to read student record" << endl;
							break;
						}
						else
							cout << "\nTotal of "<< student->count << " student(s) is successfully printed." << endl;
					}
					else error = false;
				}
				else error = false;
			} while (!error);
			error = true;
			break;

		case 4:
			cout << "\n\nClone Subtree\n\n";
			cout << "Will clone a subtree determined by the student ID you key-in(as a root)" << endl;
			cout << "You may return to menu by enter <0>" << endl;
			do {
				stu->id = 0;
				cout << "Please enter student ID that used to be cloned as root:";
				cin >> input;
				for (int i = 0; i < strlen(input); i++)
					if (!(int(input[i]) >= 48 && int(input[i] <= 57))) {//ascii method to validate
						stu->id = -1;
						cout << "\n\nInvalid input!!Please try again\n\n";
						break;
					}
					else
						stu->id = 10 * stu->id + int(input[i]) - 48;
			} while (stu->id == -1);
			if (!t2->CloneSubtree(*student, *stu))//student=t1 //function start here
				cout << "t1(student) is empty" << endl;
			else {
				cout << "\n\nOriginal tree (" << student->countNode() << " node): " << endl;
				student->preOrderPrint();//student=t1
				cout << "\n\n***********************************************************************************" << endl << endl;
				if (t2->empty())
					cout << "The entered student is not found in the tree" << endl;
				else {
					cout << "Cloned tree (" << t2->countNode() << " node) " << endl;
					cout << "Root of student ID : " << stu->id  << endl;
					t2->preOrderPrint();
				}
			}
			break;

		case 5:
			cout << "\n\nPrint Ancestor\n\n";
			do {
				stu->id = 0;
				cout << "Please enter the student ID:";
				cin >> input;
				for (int i = 0; i < strlen(input); i++)
					if (!(int(input[i]) >= 48 && int(input[i] <= 57))) {//ascii method to validate
						stu->id = -1;
						cout << "\n\nInvalid input!!Please try again\n\n";
						break;
					}
					else
						stu->id = 10 * stu->id + int(input[i]) - 48;
			} while (stu->id == -1);
			if (!student->printAncestor(*stu)) //function start here
				if (student->empty())
					cout << "The tree is empty!!! Please go through option <1> to read student record" << endl;
				else
					cout << "The student ID: " << stu->id << " not found in the tree. Thus no Ancestor for he or she." << endl;
			break;

		case 6:
			cout << "\n\nPrint Spiral\n\n";
			if (!student->printSpiral()) //function start here
				cout << "The tree is empty!!! Please go through option <1> to read student record" << endl;
			break;

		case 7:
			//design
			file.open("Layout_thanks.txt");
			if (file.is_open())
				while (!file.eof()) {
					getline(file, line);
					cout << line << endl;
				}
			file.close();
			cout << "                    Contact us if have any enquiry" << endl << "                  ";
			system("color E0"); Beep(2000, 100); Beep(1500, 120); Beep(2000, 80); Beep(1500, 100);
			break;

		default:
			cout << "\n\nInvalid input!!Please try again\n\n";
		}
		system("pause");
		delete t2; delete stu; t2 = NULL; stu = NULL;//remove and free the content
	} while (choice != 7);
	return 0;
}

/******************************************************************************************************************************************************************/
//Question 1
//use checkduplicate function created in BST.cpp
bool readFile(const char* filename, BST* t1)
{
	ifstream file(filename);
	char temp[1000]=" ";
	if (!file.is_open())
		return false;
	else
		while (!file.eof())
			if (!file.eof()) {
				Student stu;
				bool error = false, idError = false;
				//this loop for read a student from file
				while (1) {
					if (strcmp(temp, "StudentId") != 0)
						while (file >> temp)if (strcmp(temp, "StudentId") == 0)break; //arranged back to correct position if error happen
					error = true;//if break in the middle mean that error will continue true else it will rewrite by the end of this while loop
					if (file.eof())return true;//when already end of file

					if (file >> temp && strcmp(temp, "=") == 0)
						if (file.getline(temp, 30) && temp[0] == ' ')stu.id = stoi(temp);
						else { idError = true; break; }
					else { idError = true; break; }

					if (file >> temp && strcmp(temp, "Name") == 0)
						if (file >> temp && strcmp(temp, "=") == 0) {
							file.getline(temp, 31);
							if (stu.name[0] == ' ')
								for (int i = 0; i < 30; i++)
									stu.name[i] = temp[i + 1];
							else
								for (int i = 0; i < 30; i++)
									stu.name[i] = temp[i];
							stu.name[29] = '\0';
						}
						else break;
					else break;

					if (file >> temp && strcmp(temp, "Address") == 0)
						if (file >> temp && strcmp(temp, "=") == 0) {
							file.getline(temp, 101);
							if (stu.address[0] == ' ')
								for (int i = 0; i < 100; i++)
									stu.address[i] = temp[i + 1];
							else
								for (int i = 0; i < 100; i++)
									stu.address[i] = temp[i];
							stu.address[99] = '\0';
						}
						else break;
					else break;

					if (file >> temp && strcmp(temp, "DOB") == 0)
						if (file >> temp && strcmp(temp, "=") == 0) {
							file.getline(temp, 21);
							if (stu.DOB[0] == ' ')
								for (int i = 0; i < 20; i++)
									stu.DOB[i] = temp[i + 1];
							else
								for (int i = 0; i < 20; i++)
									stu.DOB[i] = temp[i];
							stu.DOB[19] = '\0';
						}
						else break;
					else break;

					if (file >> temp && strcmp(temp, "PhoneNumber") == 0)
						if (file >> temp && strcmp(temp, "=") == 0) {
							file.getline(temp, 11);
							if (stu.phone_no[0] == ' ')
								for (int i = 0; i < 10; i++)
									stu.phone_no[i] = temp[i + 1];
							else
								for (int i = 0; i < 10; i++)
									stu.phone_no[i] = temp[i];
							stu.phone_no[9] = '\0';
						}
						else break;
					else break;

					if (file >> temp && strcmp(temp, "Course") == 0)
						if (file >> temp && strcmp(temp, "=") == 0) {
							file.getline(temp, 6);
							if (stu.course[0] == ' ')
								for (int i = 0; i < 5; i++)
									stu.course[i] = temp[i + 1];
							else
								for (int i = 0; i < 5; i++)
									stu.course[i] = temp[i];
							stu.course[4] = '\0';
						}
						else break;
					else break;

					if (file >> temp && strcmp(temp, "CGPA") == 0)
						if (file >> temp && strcmp(temp, "=") == 0)
							if (file.getline(temp, 30) && strlen(temp) > 1)
								stu.cgpa = stod(temp);
							else stu.cgpa = 0;
						else break;
					else break;

					error = false; //return back to false mean that no error occur in this student
					break;//this while loop is just similar to goto function, but to avoid spagetti code, I use while loop
				}

				// check duplicate, if found will update with the latest information else normal insert
				if (!idError) {
					if (!t1->checkduplicate(stu)) {
						t1->insert(stu);//if not duplicate insert
						cout << "Student ID: " << stu.id << " successfully inserted" << endl;
					}
					else
						cout << "Duplicate found. ID:" << stu.id << " and the detail of this student will be updated with the latest get one." << endl;
				}
				//If error occur
				if (error && !idError)
					cout << "\nInconsistent format appear the text file when reading detail of student: " << stu.id << ". Partial detail of this student will be saved (before error occur)." << endl << endl;
				else if (idError)
					cout << "\nInconsistent format appear the text file when reading detail of student (ID error) thus all student related is dropped " << endl;
			}
	return true;
}

//Question 7
int menu() {
	string line;
	int choice;
	char input[100];
	system("cls");
	ifstream file("Layout_menu.txt");
	if (file.is_open())
		while (!file.eof()) {
			getline(file, line);
			cout << line << endl;
		}
	cout << "Input------->";
	cin >> input;
	if (strlen(input) < 2 && input[0] >= '0' && input[0] <= '7')//check if the input entered only one character and is a digit
		choice = input[0] - '0';//minus the ascii value of 0 to get the number of that character represent like ((int)input[0])-((int)'0')
	else
		choice = 0;
	file.close();
	system("cls");
	return choice;
}

