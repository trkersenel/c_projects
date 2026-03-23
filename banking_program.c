#include <stdio.h>
#include <string.h>

#define MAX_ACC 50
#define MAX_STR 100

struct Account {
    char owner[MAX_STR];
    int accNumber;
    double balance;
};

struct Bank {
    struct Account accounts[MAX_ACC];
    int countAccounts;
};

void add_account(struct Bank *bank){
    if(bank->countAccounts >= MAX_ACC){
        printf("Bank account limit reached!\n");
        return;
    }

    getchar(); /* clear buffer */

    printf("Owner name: ");
    fgets(bank->accounts[bank->countAccounts].owner, MAX_STR, stdin);
    bank->accounts[bank->countAccounts].owner[
        strcspn(bank->accounts[bank->countAccounts].owner, "\n")] = 0;

    printf("Account number: ");
    scanf("%d", &bank->accounts[bank->countAccounts].accNumber);

    printf("Initial balance: ");
    scanf("%lf", &bank->accounts[bank->countAccounts].balance);

    bank->countAccounts++;
    printf("Account created!\n");
}

void display_accounts(struct Bank bank){
    if(bank.countAccounts == 0){
        printf("No accounts found.\n");
        return;
    }

    for(int i=0; i<bank.countAccounts; i++){
        printf("%d) %s | Acc #%d | Balance: %.2lf\n",
               i+1,
               bank.accounts[i].owner,
               bank.accounts[i].accNumber,
               bank.accounts[i].balance);
    }
}

void search_account(struct Bank bank){
    int num;
    printf("Enter account number to search: ");
    scanf("%d", &num);

    for(int i=0; i<bank.countAccounts; i++){
        if(bank.accounts[i].accNumber == num){
            printf("Found → %s | Acc #%d | Balance: %.2lf\n",
                   bank.accounts[i].owner,
                   bank.accounts[i].accNumber,
                   bank.accounts[i].balance);
            return;
        }
    }

    printf("Account not found.\n");
}

void delete_account(struct Bank *bank){
    int num;
    printf("Enter account number to delete: ");
    scanf("%d", &num);

    for(int i=0; i<bank->countAccounts; i++){
        if(bank->accounts[i].accNumber == num){

            /* shift left */
            for(int j=i; j < bank->countAccounts - 1; j++){
                bank->accounts[j] = bank->accounts[j+1];
            }

            bank->countAccounts--;
            printf("Account deleted.\n");
            return;
        }
    }

    printf("Account not found.\n");
}

void deposit(struct Bank *bank){
    int num;
    double amount;
    printf("Enter account number: ");
    scanf("%d", &num);

    for(int i=0; i<bank->countAccounts; i++){
        if(bank->accounts[i].accNumber == num){
            printf("Amount to deposit: ");
            scanf("%lf", &amount);
            if(amount <= 0){
                printf("Amount must be positive.\n");
                return;
            }
            bank->accounts[i].balance += amount;
            printf("Deposited %.2lf -> New balance: %.2lf\n",
                   amount, bank->accounts[i].balance);
            return;
        }
    }
    printf("Account not found.\n");
}

void withdraw(struct Bank *bank){
    int num;
    double amount;
    printf("Enter account number: ");
    scanf("%d", &num);

    for(int i=0; i<bank->countAccounts; i++){
        if(bank->accounts[i].accNumber == num){
            printf("Amount to withdraw: ");
            scanf("%lf", &amount);
            if(amount <= 0){
                printf("Amount must be positive.\n");
                return;
            }
            if(amount > bank->accounts[i].balance){
                printf("Insufficient funds! Balance: %.2lf\n",
                       bank->accounts[i].balance);
                return;
            }
            bank->accounts[i].balance -= amount;
            printf("Withdrew %.2lf -> New balance: %.2lf\n",
                   amount, bank->accounts[i].balance);
            return;
        }
    }
    printf("Account not found.\n");
}

void save_file(struct Bank bank){
    FILE *file = fopen("accounts.txt", "w");
    if(file==NULL){
        printf("Cannot open file!\n");
        return;
    }

    for(int i=0; i<bank.countAccounts; i++){
        fprintf(file, "%s,%d,%.2lf\n",
                bank.accounts[i].owner,
                bank.accounts[i].accNumber,
                bank.accounts[i].balance);
    }

    fclose(file);
    printf("Accounts saved.\n");
}

void load_file(struct Bank *bank){
    FILE *file = fopen("accounts.txt", "r");
    if(file==NULL){
        printf("No file found.\n");
        return;
    }

    bank->countAccounts = 0;

    while(fscanf(file, "%99[^,],%d,%lf\n",
                 bank->accounts[bank->countAccounts].owner,
                 &bank->accounts[bank->countAccounts].accNumber,
                 &bank->accounts[bank->countAccounts].balance) == 3){

        bank->countAccounts++;

        if(bank->countAccounts >= MAX_ACC)
            break;
    }

    fclose(file);
    printf("Accounts loaded.\n");
}

void show_menu(){
    printf("\n--- BANK ACCOUNT MANAGER ---\n");
    printf("1. Create Account\n");
    printf("2. List Accounts\n");
    printf("3. Search Account\n");
    printf("4. Delete Account\n");
    printf("5. Deposit Money\n");
    printf("6. Withdraw Money\n");
    printf("7. Save to File\n");
    printf("8. Load from File\n");
    printf("9. Exit\n");
    printf("Choice: ");
}

int main(){
    struct Bank bank;
    bank.countAccounts = 0;
    int choice;

    do{
        show_menu();
        scanf("%d", &choice);

        switch(choice){
            case 1:
                add_account(&bank);
                break;
            case 2:
                display_accounts(bank);
                break;
            case 3:
                search_account(bank);
                break;
            case 4:
                delete_account(&bank);
                break;
            case 5:
                deposit(&bank);
                break;
            case 6:
                withdraw(&bank);
                break;
            case 7:
                save_file(bank);
                break;
            case 8:
                load_file(&bank);
                break;
            case 9:
                printf("Exiting...\n");
                break;
            default:
                printf("Enter a number 1-9.\n");
        }

    } while(choice != 9);

    return 0;
}