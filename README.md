# Library-Management
Small library management project to showcase C programming language skills.
The application used to create the file: Turbo C++

**There are 4 modules contained in this project:**
1. Student
2. Teacher
3. Book
4. Transaction

In Starting the program run it asked for the admin id and password. if it does not find password-related data then the program asked to generate a password first as admin.
then the user discovers the above modules.

The introduction of modules is as follows:-

**1.	Student Module:-**
--> In this module student detail will be maintained. This section, it includes the student id, name, course, semester, and gender.
--> In this module we include the following Function:-
◦	Insert:-This operation is used to enter data for a new student in the student section’s database. In this section, the student id will automatically be generated. 
◦	Delete:- This operation is used to delete the data of student which leaves the college. In this section it just wants the student id to delete the particular student detail.
◦	Update:-This operation is used to modify the data like the semester of student and degree of the student and view the student id and name.
◦	Search:-This operation is used to search particular student records. In this section student records can be searched by student id and it will also searched by the student name.
  	
**2.	Teacher Module:-**
-->In this module, teacher detail will be maintained. This section, includes the teacher's id, name, Department, and gender.
-->In this module, we include the following Function:-
◦	Insert:-This operation is used to enter data for a new teacher in the teacher section’s database. In this section, teacher id will automatically be generated and the teacher's name, department, and gender detail will be included. 
◦	Delete:- This operation is used to delete the data of a teacher who leaves the college. In this section, it required the teacher id to delete the particular record.
◦	Update:-This operation is used to modify the data like the degree of the teacher and it displays the teacher id and name of the teacher.
◦	Search:-This operation is used to search particular teacher records. In this section search can be done in two ways first it will search by id and second it will be searched by name also.


**3.	Book Module:-**
-->In this module's book detail will be maintained. In this Module book id, name, publisher, author, and price of the book will be Maintained.
-->In this module we include the following Function:-
o	Insert:-This operation is used to enter data for a new book which parched new into the library. In this section it included book name, publisher, author, price and book id is automatically generated. 
o	Delete:- This operation is used to delete the data of a particular book using book id.
o	Update:-This operation is used to modify the data like book author name, price, and publisher using provided book id.
o	Search:-This operation is used to search particular book records. In this section search can be done by id and by name also.

**4.	Transaction Module:-**
-->In the transaction student and teacher can issue the book and return the book. Using the transaction module librarian can track the book states and easily maintain the book record.
-->In the transaction module we included the following Function:-
◦	Issue Function
◦	Return Function

1. Issue Function:-In this function it takes the user id and book id and checks into the database if the book is available it issues that book to that user.
2. Return Function:-In This function takes the book id and user id and book states will change and done available.
