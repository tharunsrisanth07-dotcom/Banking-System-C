#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ACC_FILE "accounts.dat"
#define HISTORY_FILE "history.txt"
#define NAME_LEN 50

typedef struct AccountNode {
    int acc_no;
    char name[NAME_LEN];
    float balance;
    struct AccountNode *next;
} AccountNode;

AccountNode* createNode(int acc_no, const char *name, float balance) {
    AccountNode *n = (AccountNode *) malloc(sizeof(AccountNode));
    if (!n) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    n->acc_no = acc_no;
    strncpy(n->name, name, NAME_LEN - 1);
    n->name[NAME_LEN - 1] = '\0';
    n->balance = balance;
    n->next = NULL;
    return n;
}

AccountNode* insertAccountSorted(AccountNode *head, AccountNode *node) {
    if (!head || node->acc_no < head->acc_no) {
        node->next = head;
        return node;
    }
    AccountNode *cur = head;
    while (cur->next && cur->next->acc_no < node->acc_no) {
        cur = cur->next;
    }
    if (cur->acc_no == node->acc_no) {
        free(node);
        return head;
    }
    if (cur->next && cur->next->acc_no == node->acc_no) {
        free(node);
        return head;
    }
    node->next = cur->next;
    cur->next = node;
    return head;
}

AccountNode* findAccount(AccountNode *head, int acc_no) {
    AccountNode *cur = head;
    while (cur) {
        if (cur->acc_no == acc_no) return cur;
        cur = cur->next;
    }
    return NULL;
}

void deleteList(AccountNode *head) {
    AccountNode *cur = head;
    while (cur) {
        AccountNode *tmp = cur;
        cur = cur->next;
        free(tmp);
    }
}

void appendHistory(int acc_no, float amount, float new_balance, int status) {
    FILE *hf = fopen(HISTORY_FILE, "a");
    if (!hf) return;
    fprintf(hf, "%d %.2f %.2f %d\n", acc_no, amount, new_balance, status);
    fclose(hf);
}

int saveAccounts(AccountNode *head) {
    FILE *f = fopen(ACC_FILE, "wb");
    if (!f) {
        printf("Error opening accounts file for writing.\n");
        return -1;
    }

    AccountNode *cur = head;
    while (cur) {
        fwrite(&cur->acc_no, sizeof(int), 1, f);
        fwrite(cur->name, sizeof(char), NAME_LEN, f);
        fwrite(&cur->balance, sizeof(float), 1, f);
        cur = cur->next;
    }

    fclose(f);
    return 0;
}

AccountNode* loadAccounts() {
    FILE *f = fopen(ACC_FILE, "rb");
    if (!f) return NULL;

    AccountNode *head = NULL;
    while (1) {
        int acc_no;
        char name[NAME_LEN];
        float balance;

        if (fread(&acc_no, sizeof(int), 1, f) != 1) break;
        if (fread(name, sizeof(char), NAME_LEN, f) != NAME_LEN) break;
        if (fread(&balance, sizeof(float), 1, f) != 1) break;

        name[NAME_LEN - 1] = '\0';

        AccountNode *node = createNode(acc_no, name, balance);
        head = insertAccountSorted(head, node);
    }

    fclose(f);
    return head;
}

void createAccount(AccountNode **head_ptr) {
    int acc_no;
    char name[NAME_LEN];

    printf("\n--- Create Account ---\n");
    printf("Enter Account Number: ");
    scanf("%d", &acc_no);

    if (findAccount(*head_ptr, acc_no)) {
        printf("Account number already exists.\n");
        return;
    }

    printf("Enter Name (no spaces): ");
    scanf("%s", name);  

    AccountNode *node = createNode(acc_no, name, 0.0f);
    *head_ptr = insertAccountSorted(*head_ptr, node);

    if (saveAccounts(*head_ptr) == 0)
        printf("Account created successfully.\n");
}

void depositAmount(AccountNode **head_ptr) {
    int acc_no;
    float amount;

    printf("\n--- Deposit ---\n");
    printf("Enter Account number: ");
    scanf("%d", &acc_no);
    printf("Enter amount to be deposited: ");
    scanf("%f", &amount);

    if (amount <= 0.0f) {
        printf("Amount must be positive.\n");
        return;
    }

    AccountNode *acc = findAccount(*head_ptr, acc_no);
    if (!acc) {
        printf("Account not found.\n");
        return;
    }

    acc->balance += amount;

    if (saveAccounts(*head_ptr) == 0) {
        appendHistory(acc_no, amount, acc->balance, 1);
        printf("%.2f deposited successfully\nNew balance is %.2f\n", amount, acc->balance);
    }
}

void withdrawAmount(AccountNode **head_ptr) {
    int acc_no;
    float amount;

    printf("\n--- Withdraw ---\n");
    printf("Enter Account number: ");
    scanf("%d", &acc_no);
    printf("Enter amount to be withdrawn: ");
    scanf("%f", &amount);

    if (amount <= 0.0f) {
        printf("Amount must be positive.\n");
        return;
    }

    AccountNode *acc = findAccount(*head_ptr, acc_no);
    if (!acc) {
        printf("Account not found.\n");
        return;
    }

    if (acc->balance < amount) {
        printf("Insufficient balance!\n");
        return;
    }

    acc->balance -= amount;

    if (saveAccounts(*head_ptr) == 0) {
        appendHistory(acc_no, amount, acc->balance, 0);
        printf("%.2f withdrawn successfully\nNew balance is %.2f\n", amount, acc->balance);
    }
}

void transferAmount(AccountNode **head_ptr) {
    int from, to;
    float amt;

    printf("\n--- Transfer ---\n");
    printf("Enter sender account number: ");
    scanf("%d", &from);
    printf("Enter receiver account number: ");
    scanf("%d", &to);
    printf("Enter amount to transfer: ");
    scanf("%f", &amt);

    if (from == to) {
        printf("Cannot transfer to the same account!\n");
        return;
    }
    if (amt <= 0.0f) {
        printf("Amount must be positive.\n");
        return;
    }

    AccountNode *acc_f = findAccount(*head_ptr, from);
    AccountNode *acc_t = findAccount(*head_ptr, to);

    if (!acc_f) {
        printf("Sender account not found!\n");
        return;
    }
    if (!acc_t) {
        printf("Receiver account not found!\n");
        return;
    }
    if (acc_f->balance < amt) {
        printf("Insufficient balance!\n");
        return;
    }

    acc_f->balance -= amt;
    acc_t->balance += amt;

    if (saveAccounts(*head_ptr) == 0) {
        appendHistory(from, amt, acc_f->balance, 2);
        appendHistory(to, amt, acc_t->balance, 3);
        printf("Transfer successful!\n");
    }
}

void balanceEnquiry(AccountNode *head) {
    int accno;

    printf("\n--- Balance Enquiry ---\n");
    printf("Enter Account Number: ");
    scanf("%d", &accno);

    AccountNode *acc = findAccount(head, accno);
    if (!acc) {
        printf("Account not found.\n");
        return;
    }

    printf("Your current balance is: %.2f\n", acc->balance);
}

void checkHistory() {
    int acc_no;

    printf("\n--- Transaction History ---\n");
    printf("Enter your account number: ");
    scanf("%d", &acc_no);

    FILE *hf = fopen(HISTORY_FILE, "r");
    if (!hf) {
        printf("No history file found!\n");
        return;
    }

    int acc;
    float amount, bal;
    int status;
    int found = 0;

    printf("\n--- Transaction History for Account %d ---\n", acc_no);
    while (fscanf(hf, "%d %f %f %d", &acc, &amount, &bal, &status) == 4) {
        if (acc == acc_no) {
            found = 1;
            if (status == 1) printf("Deposited %.2f | New Balance = %.2f\n", amount, bal);
            else if (status == 0) printf("Withdrawn %.2f | New Balance = %.2f\n", amount, bal);
            else if (status == 2) printf("Transferred OUT %.2f | New Balance = %.2f\n", amount, bal);
            else if (status == 3) printf("Received %.2f | New Balance = %.2f\n", amount, bal);
        }
    }

    if (!found) printf("No transaction history found for this account.\n");
    fclose(hf);
}

void showAllAccounts(AccountNode *head) {
    printf("\n--- All Accounts ---\n");
    if (!head) {
        printf("No accounts found.\n");
        return;
    }

    AccountNode *cur = head;
    while (cur) {
        printf("Account Number: %d, Name: %s, Balance: %.2f\n",
               cur->acc_no, cur->name, cur->balance);
        cur = cur->next;
    }
}

int main() {
    AccountNode *head = loadAccounts();
    int choice;
    while (1) {
        printf("\n BANK MANAGEMENT SYSTEM\n");
        printf(" 1. Create Account\n");
        printf(" 2. Deposit Amount\n");
        printf(" 3. Withdraw Amount\n");
        printf(" 4. Transfer Amount\n");
        printf(" 5. Balance Enquiry\n");
        printf(" 6. Check History\n");
        printf(" 7. Exit\n");
        printf(" 8. Show All Accounts\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: createAccount(&head); break;
            case 2: depositAmount(&head); break;
            case 3: withdrawAmount(&head); break;
            case 4: transferAmount(&head); break;
            case 5: balanceEnquiry(head); break;
            case 6: checkHistory(); break;
            case 7:
                printf("Exiting...\n");
                deleteList(head);
                return 0;
            case 8: showAllAccounts(head); break;
            default: printf("Invalid choice. Please try again.\n"); break;
        }
    }
}