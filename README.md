# Banking-System-C
## 1. Project Description

The Bank Management System is a console-based application developed in the C programming language that performs essential banking operations. The system now stores account records in a singly linked list rather than directly accessing records from the file each time. This enables faster searching, dynamic insertion, and better memory utilization. Persistent storage is implemented through file handling (accounts.dat and history.txt) to ensure that data remains intact even after program termination.

The program demonstrates key concepts of data structures (linked lists), file I/O, dynamic memory allocation, modular programming, pointers, and real-time transactional updates.

## 2. Functionalities
Feature	Description

*Create Account	Adds a new account into a sorted linked list and saves to file.

*Deposit Amount	Adds funds to an account and logs the history.

*Withdraw Amount	Deducts balance after validation and logs the transaction.

*Transfer Amount	Transfers money between two accounts and records both sides of the transaction.

*Balance Enquiry	Displays the current account balance.

*Transaction History	Shows all transactions related to an account from history.txt.

*Show All Accounts	Displays all accounts sequentially from the linked list.

*Exit	Saves data and terminates the program safely.
## 3. Implementation Steps

Defined the AccountNode structure for dynamically storing account data using a linked list.

Loaded existing accounts from accounts.dat into a sorted linked list at startup (load_accounts()).

Implemented sorted insertion to always maintain ordered accounts (insert_account_sorted()).

Implemented search functionality for locating accounts efficiently (find_account()).

Implemented account operations such as deposit, withdrawal, transfer with real-time value updates.

Used save_accounts() to rewrite the updated linked list back to the file.

Created transaction logging using append_history() that records every activity in history.txt.

Designed a menu-driven UI, allowing repeated user interactions within the main loop.

Freed all allocated memory before exit using delete_list() to avoid memory leaks.

## 4. Breakdown of Contributions

### Team Member	Contribution

Aarya k bhat(IE2025004)    	       - Implemented linked list structure and file storage (load_accounts, save_accounts, insert_account_sorted)

T Lalith Srikanth(BA2025051)	     - Implemented account operations (deposit, withdraw, transfer),prepared documentation and UI menu

Tharun Srisanth(BA2025033)	       - Developed transaction logging, history display feature, testing and debugging

## 5. Function Descriptions (2–3 lines each)

### load_accounts()

Reads all stored accounts from accounts.dat and constructs a linked list. Each record is inserted into the list in sorted manner. Returns the head pointer of the list.

### save_accounts()

Writes the entire linked list of accounts to accounts.dat, ensuring persistent storage of updates. Returns 0 on success and -1 if file writing fails.

### create_node()

Dynamically allocates memory for a new account node and populates it with account number, name, and balance. Used internally during loading and creation of accounts.

### insert_account_sorted()

Inserts an account node in ascending order based on account number. Prevents duplicate entries and maintains a sorted linked list.

### find_account()

Searches through the linked list to find an account by account number. Returns a pointer to the node if found, otherwise returns NULL.

### delete_list()

Frees all memory allocations used in the linked list before program exit, preventing memory leaks.

### create_account()

Allows a user to register a new bank account. Validates for duplicates, inserts the account into the linked list, and updates the file.

### deposit_amount()

Deposits a specified amount into an account after validation, updates balance in memory and file, and logs the transaction in history.

### withdraw_amount()

Withdraws money after checking sufficient funds. Updates both linked list and file storage, and logs the event.

### transfer_amount()

Performs fund transfer from one account to another, checking existence and balance availability. Logs both debit and credit operations.

### balance_enquiry()

Displays the available balance of a specified account using find_account().

### append_history()

Records transaction details such as amount, updated balance, and status code (deposit, withdraw, transfer sent/received).

### check_history()

Reads history.txt and prints all matching transaction logs for a given account number.

### show_all_accounts()

Traverses through the linked list and prints complete account details.

### press_enter_to_continue()

Pauses execution until user input to improve user interface interaction.


## Files Included
### File	Purpose

bank_system.c	       - Main implementation of the banking system
accounts.dat	       - Binary storage for account records
history.txt	         - Text-based transaction log history
README.md	           - Project documentation
## Conclusion

This project effectively demonstrates real-time banking operations using linked lists and persistent file storage in C. Converting from direct file access to a linked list significantly improved efficiency and flexibility in managing account records. The program is modular, scalable, and capable of further enhancements such as passwords, admin login, interest calculations, and GUI front-end
