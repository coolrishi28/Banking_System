#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include <unistd.h>

typedef struct {
	char name[100];
	float balance;
	char password[100];
	char creationDate[100];
} User;

void creatorTag();
void optionPanel();
void createAccount();
void displayDetails(const char *username);
float getBalance(const char *username);
void deposit(const char *username);
void withdraw(const char *username);
int authenticateUser(const char *username);
int fileExists(const char *filename);
void logTransaction(const char *username, const char *type, float amount);
void clearScreen();
void showLoading(int dots, int delaySeconds);
void mainPage();

int main() {
	mainPage();
	return 0;
}

void mainPage() {
	int choice;
	char exitChoice;

	do {
		clearScreen();
		creatorTag();
		optionPanel();

		printf("\t\t\t\t-> ");
		scanf("%d", &choice);
		getchar();

		switch (choice) {
		case 1:
			createAccount();
			break;
		case 2:
		case 3:
		case 4: {
			char username[100];
			printf("\t\t\t\tEnter account name: ");
			fgets(username, sizeof(username), stdin);
			username[strcspn(username, "\n")] = '\0';

			if (!fileExists(username)) {
				printf("\t\t\t\tAccount does not exist.\n");
				//getchar();
				showLoading(3, 1);
				break;
			}

			if (!authenticateUser(username)) {
				printf("\t\t\t\tAuthentication failed.\n");
				//getchar();
				showLoading(3, 1);
				break;
			}

			if (choice == 2) deposit(username);
			else if (choice == 3) withdraw(username);
			else displayDetails(username);
			showLoading(3, 1);
			break;
		}
		case 5:
			printf("\t\t\t\tExiting...\n");
			return;
		default:
			printf("\t\t\t\tInvalid choice.\n");
			break;
		}

		printf("\t\t\t\tDo you want to exit? (y/n): ");
		exitChoice = getchar();
		getchar();

	} while (exitChoice == 'n' || exitChoice == 'N');
}

void creatorTag() {
	printf("\t\t\t\tBanking System\n");
	printf("\t\t\t\tBy: Shashwat Dwivedi\n\n");
}

void optionPanel() {
	printf("\t\t\t\t1. Create New Account\n");
	printf("\t\t\t\t2. Deposit\n");
	printf("\t\t\t\t3. Withdraw\n");
	printf("\t\t\t\t4. Display Account Details\n");
	printf("\t\t\t\t5. Exit\n");
}

void showLoading(int dots, int delaySeconds) {
	printf("\t\t\t\tLoading");
	fflush(stdout);

	for (int i = 0; i < dots; i++) {
		sleep(delaySeconds);
		printf(".");
		fflush(stdout);
	}
	printf("\n");
}

int fileExists(const char *username) {
	char filename[120];
	snprintf(filename, sizeof(filename), "%s.dat", username);
	FILE *file = fopen(filename, "rb");
	if (file) {
		fclose(file);
		return 1;
	}
	return 0;
}
