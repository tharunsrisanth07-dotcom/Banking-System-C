<u># Banking-System-C</u>
<u>##1. Project Description</u>
The Bank Management System is a console-based application developed in the C programming language. It provides basic banking operations such as creating an account, depositing and withdrawing funds, transferring money between accounts, checking account balance, viewing transaction history, and displaying all stored accounts. The system uses file handling to store account details and transaction logs permanently, ensuring that data is retained even after the program ends.
This project demonstrates key concepts of C programming including structures, pointers, file operations, modular programming, and user-driven menu execution.

<u>##2. Functionalities in the Project</u>
The system supports the following features:

*Create Account – Registers a new customer with a unique account number and name.
*Deposit Amount – Adds money to an account and updates balance.
*Withdraw Amount – Deducts requested funds if sufficient balance is available.
*Transfer Amount – Moves funds between two accounts and updates records.
*Balance Enquiry – Displays the current balance of an account.
*Transaction History – Shows previous transactions stored with type and updated balance.
*Show All Accounts – Displays a list of all accounts created.
*Exit – Allows the user to safely exit the system.

<u>##3. Implementation Steps</u>
Step-by-step Implementation:

1. Defined structures for storing account details and transaction log structure.
2. Used file handling (accounts.dat, history.txt) to store account information and transaction history.
3. Implemented account creation, validating unique account numbers and writing to the account file.
4. Developed deposit and withdrawal functions, updating balances directly in the binary file.
5. Implemented fund transfer, checking validity of both accounts and updating balances accordingly.
6. Logged all transactions in history.txt using the log_history() function.
7. Implemented menu-driven UI inside main() to allow users to interact repeatedly.
8. Built supporting features such as history display and full account list output.

<u>##4. Breakdown of Contributions</u>
Team Member	Contribution
Tharun srisanth(BA2025033)	   Implemented account creation, deposit, withdrawal features and Report writing
Aarya k bhat(IE2025004)        Developed fund transfer logic, balance enquiry and project documentation
T Lalith Srikanth(BA2025051)	 Implemented transaction logging, history display and debugging


<u>##5. Function Descriptions</u>
###create_account()
Creates a new bank account by taking account number and name as input. Checks for duplicates before storing data. Initializes balance to zero and writes details to accounts.dat.

###deposit_amount()
Lets the user deposit funds into an existing account by updating the stored balance in the file. Records the transaction in history.txt and displays the new balance.

###withdraw_amount()
Withdraws money after validating sufficient balance. Updates the account record in the binary file and logs the transaction for future reference.

###transfer_amount()
Transfers money between two accounts after validating both accounts and balance availability. Updates both accounts’ records and logs debit and credit actions separately.

###balance_enquiry()
Displays the current balance of a specified account by reading from accounts.dat.

###check_history()
Reads from history.txt to show all past transactions associated with a given account number.

###show_all_accounts()
Displays all existing accounts with account number, name, and balance.

###log_history()
Stores transaction details such as amount, new balance, and type (deposit/withdraw/transfer) into history.txt

<u>##Files in Project</u>
File	Description
main.c	            Source code for the banking system
accounts.dat	      Binary file containing stored account information
history.txt        	Text file maintaining transaction history
README.md	          Project report & documentation

<u>##Conclusion</u>
This project successfully implements a functioning bank management system with essential operations and persistent file storage. It demonstrates the practical application of C structures, file handling, condition checking, loops, and menu-driven design.
