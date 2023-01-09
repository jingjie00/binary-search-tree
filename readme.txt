Group Member 1:

Name: Tan Jing Jie
Student ID: 1804560
Course: Bachelor in Computer Science (Hons)
Practical Group: P 13
Practical Session: Tuesday, 4PM - 6PM
Tutor: 	Dr.Goh Chuan Meng


Group Member 2:

Name: Tan Wei Mun
Student ID: 1803705
Course: Bachelor in Computer Science (Hons)
Practical Group: P 13
Practical Session: Tuesday, 4PM - 6PM
Tutor: 	Dr.Goh Chuan Meng

********************************************************************************************************************************************************

**We labelled every task we done by question1, question2... it is corresponding to task a, task b, task c...
**Any question feel free to contact us by 011-3810 0852

********************************************************************************************************************************************************

Although the guildline say we no validation input is required,
 
BUT in some case some input will cause the program overflow,

Thus we have made some validation toward it. To prevent the program crashed.

********************************************************************************
**                     Some assumption and feature we made：                   **
********************************************************************************

Question 1
-We will no automatic read the file as the user may want to read other file as stated in the guildline
-We use student id as primary key, thus we allowed the name repeated(may be same name)
-Any duplicate happen we will update the node by the latest record
-We will prompt out all the duplicate detail

-Our program will automatic arranged back after some inconsistent format in student.txt. 
-So if inconsistent happened, only current student record is affected and other still work prerfectly
-The affected part will replaced by its default(NULL).

-System will prompt out inconsistent format in which student.

Eg.The student below will save to the text file with only his studentID and his name, others is null.
    System will not prompt our inconsistent in this case.
----------------------------file start---------------------------
StudentId = 19
Name = Alex Tan
Address = 
-----------------------------file end----------------------------

Eg. We only allow the correct format of text file
    (like "Name :" in following, StudentID and Address will be saved normally, BUT the name will be saved to null, because ":" is used 
    System will prompt out inconsistent record in this case.
----------------------------file start---------------------------
StudentId = 19
NAME : Alex Tan
Address = Helloworld 1234
-----------------------------file end----------------------------

Eg. We only allow the correct format of text file
    Name is missing, so system will only record the studentId, other detail will be it default(NULL),CGPA=0
    System will prompt out inconsistent record in this case.
----------------------------file start---------------------------
StudentId = 19
Address = Helloworld 1234
-----------------------------file end----------------------------

********************************************************************************************************************************************************
Question2
-print deepest node
-here we have the alternate method similar with alternate method(not use recursive but while loop) question 6,
-but it hard to be understand so here we only submit recursive method


********************************************************************************************************************************************************
Question3
-We will rewrite the output file once user repeat output to the outputfile


********************************************************************************************************************************************************
Question4
-As guildline we will list out original tree by preorder
-Then print the clone


********************************************************************************************************************************************************
Question5
-We will print out the target student detail first, followed by a line and his or her ancestor.


********************************************************************************************************************************************************
Question 6
-The question asked to print spiral, we printed it and for easier to look, we added a line after each level.
-The line can be removed at the for loop (we had make a comment there)
-We have think 2 solution. one is recursive and 1 is using while loop. We already make a comment there
-We use recursive method in this submission as more easier to be understand.

********************************************************************************************************************************************************
