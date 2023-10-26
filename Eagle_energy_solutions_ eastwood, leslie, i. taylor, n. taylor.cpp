/*
Programming 2 Project
Eastwood, Leslie, I. Taylor, N. Taylor
March 12, 2023

Eagle Energy JA, maintenance and automation system
*/

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include<conio.h>

using namespace std;
// Define constants
#define clientdata 1
#define creditdata 1
#define salesdata 1
#define USERNAME "user"
#define PASSWORD "userpass"
#define MAX_ATTEMPTS 3
#define MAX_COMPANIES 1
#define COMPANY_FILENAME "company_data.txt"
#define MAX_EMPLOYEES 1

//structure for the date
typedef struct{
	int day;
	char month[20];
	int year;
}DATE;

//structure for the clients credit data
typedef struct{
	int creditID;
	int companyID;
	char companyName[50];
	char contactPerson[50];
	char email[50];
	char telephone[20];
	int companyCode;
	int personalID;
	char petrolType[15];
	float gallons;
	float clientCreditAm;
	DATE dateOfTransaction;
	float totalCompanyCredit;
}PREMIUM_CLIENT;

// Structure to hold company data
typedef struct{
    int companyID;
    char companyName[50];
    char contactPerson[50];
    char contactEmail[50];
    char contactPhoneNumber[20];
} Company;

struct client_data{
    char IDtype [20];
    char clientname[30];
    int company_id;
    int company_code; 
    int personal_idnum;
};

//stores employee data for the future records
struct employee {
    char name[50];
    char job_title[50];
    char username[50];
    char passcode[15];
};

int checkCredentials(const char* username, const char* password); //function to verify login 
void menu(void); //function prototype for menu options (possible tasks to complete within the system)
void sellPetrol(void); //funtion prototype to carry out sale
PREMIUM_CLIENT readCreditData(void); //function prototype to read data into client (credit purchase) variable
void printReceipt(PREMIUM_CLIENT premiumClient); //function prototype to print receipt info after client's purchase
void exit(void); //function prototype to exit the program
void displayReports(void); //function to display credit, petrol sales and client reports
void addAndUpdateEmployees(void); //Allow for the user to Add or update employee data
void searchCompanies(void); //Function prototype for company search

//declaring variables in the global scope
Company companies = {0, "", "", "", ""};
struct employee employees = {"", "", "", 0};
float petrolRate = 1.10; //constants for the price point of each petrol type
struct client_data x={"","",0,0,0,};
PREMIUM_CLIENT premiumClient;
int saleID, eagleEnergyID = 876, pumpNo;

int main(){
	
	char username[50]; // Variable to store username
    char password[50]; // Variable to store password
    int loginAttempts = 0;

    // Welcome Message
    printf("Hello, Welcome to Eagle Energy Jamaica!\n\n");
    
    puts("\n__________________________________________________________________________________________");

    // While the maximum number of login attempts has not been reached
    while (loginAttempts < MAX_ATTEMPTS) {
        // Prompt the user for their username and password
        printf("Please enter your username: ");
        scanf("%s", username);
        printf("Please enter your password: ");
        scanf("%s", password);

        // If the credentials are correct, break the loop
        if (checkCredentials(username, password)) {
            printf("\nLogin successful!\n\n"); // Print successful message
            break;
        }
        // If the credentials are incorrect, increment the number of login attempts
        else {
            printf("\nInvalid username or password. Please try again!\n\n"); // Print error message
            loginAttempts++;
        }
    }

    // If the maximum number of login attempts was reached, print an error message
    if (loginAttempts == MAX_ATTEMPTS) {
        printf("\nSIKE! Access denied! Maximum number of login attempts reached!\n\n"); // Print error message
    }
	
	puts("\n__________________________________________________________________________________________\n");
    
    // Load the company data
    FILE *ccPtr; 

	cout<<"*******ENTER REQUIRED INFORMATION**********";
	printf("\n");

	if((ccPtr = fopen ("company_data.txt", "a")) == NULL){
		printf("Could not open file.");
	} else {
		for(int i=0; i<MAX_COMPANIES; i++){
			printf("\n");
		
			printf("Enter company ID #: ");
			scanf("%d", &companies.companyID);
		
			printf("Enter company name: ");
			scanf("%s", companies.companyName);
		
			printf("Enter company contact person: ");
			scanf("%s", companies.contactPerson);
		
			printf("Enter company email: ");
			scanf("%s", companies.contactEmail);
		
			printf("Enter company telephone number: ");
			scanf("%s", companies.contactPhoneNumber);
		}
	
		fprintf(ccPtr, "%s\n\n", "COMPANY DATA");
	
		for(int i=0; i<MAX_COMPANIES; i++){
    
        	fprintf(ccPtr,
			"Company ID #: %d\n"
			"Company Name: %s\n"
			"Company Contact Person: %s\n"
			"Company Email: %s\n"
			"Company Telephone: %s", companies.companyID, companies.companyName, companies.contactPerson, companies.contactEmail, companies.contactPhoneNumber);
        	fputs("\n__________________________________________________________________________________________\n", ccPtr);
        }
         
        fclose(ccPtr);    
	}
    
    puts("\n__________________________________________________________________________________________\n");
    
    FILE *cdfptr;
    
    cout<<"*******ENTER REQUIRED INFORMATION**********";
    printf("\n");
        
    if((cdfptr=fopen("client_data.txt","a"))==NULL)
    printf("File cannot be accessed!");
    else{
        
        for(int i=0; i<clientdata; i++){
            printf("\n");
            
            printf("Enter client ID type: ");
            scanf("%s",x.IDtype);
        
            printf("Enter client name: ");
            scanf("%s",x.clientname);
            
            printf("Enter company ID #: ");
            scanf("%d",&x.company_id);
            
            printf("Enter company code: ");
            scanf("%d",&x.company_code);
            
            printf("Enter personal id#: ");
            scanf("%d",&x.personal_idnum);
        }
        
        fprintf(cdfptr, "%s\n\n", "CLIENT DATA");
            
        for(int i=0; i<clientdata; i++){
    
        fprintf(cdfptr,
		"Client Name: %s\n"
		"Company ID #: %d\n"
		"Company Code: %d\n"
		"Personal ID #: %d",x.clientname,x.company_id,x.company_code,x.personal_idnum);
        fputs("\n__________________________________________________________________________________________\n", cdfptr);
        }
         
        fclose(cdfptr);    
    }
    
    puts("\n__________________________________________________________________________________________");
    
    menu(); //function call for the menu
    
	return 0;
}

int checkCredentials(const char* username, const char* password) {
    // If the username and password match the predefined ones, return 1 (true)
    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        return 1;
    }
    // Otherwise, return 0 (false)
    else {
        return 0;
    }
}

//function definition for the menu
void menu(void){
	int option;
	
	puts("\nEAGLE ENERGY JAMAICA");
	puts("\nWhat would you like to do? Here are some options: " //display menu
			"\n1. Sell Petrol"
			"\n2. Display reports"
					"\n\t- Credit Report"
					"\n\t- Petrol Sales"
					"\n\t- Client Sales"
			"\n3. Search Companies"
			"\n4. Add & Update Employees"
			"\n5. Exit");
	printf("\nPlease enter option: ");
	scanf("%d", &option); //read user option
	puts("\n__________________________________________________________________________________________");
	
	//function calls to carry out tasks respective to menu option entered
	switch(option){
		case 1:
			sellPetrol();
			break;
		case 2:
			displayReports();
			break;
		case 3:
			searchCompanies();
			break;
		case 4: 
			addAndUpdateEmployees();
			break;
		case 5:
			exit();
			break;
		default:
			printf("Invalid choice.\n");
	}
}

//function definition for menu option 1, petrol sales
void sellPetrol(void){
	puts("\nYou may go ahead with the sale!");
		
	PREMIUM_CLIENT premiumClient;
	FILE *nPtr;
	
	if((nPtr = fopen ("credit_data.txt", "a")) == NULL){
		puts("File could not be opened.");
	} else {
		premiumClient = readCreditData(); //function call to collect client purchase info
		printReceipt(premiumClient); //function to print receipt after purchase
		
		fprintf(nPtr, "%s\n\n", "CREDIT DATA");
		
		for(int i=0; i<creditdata; i++){
			fprintf(nPtr, 
			"Credit ID#: %d\n"
			"Company ID #: %d\n"
			"Company Name: %s\n"
			"Company Contact Person: %s\n"
			"Company Email: %s\n"
			"Company Telephone: %s\n"
			"Personal ID #: %d\n"
			"Petrol Type: %s\n"
			"Gallons: %.1f\n"
			"Client Credit Amount: $%.2f\n"
			"Date of Transaction: %d/%s/%d\n"
			"Total Company Credit: $%.2f\n", premiumClient.creditID, premiumClient.companyID, premiumClient.companyName, premiumClient.contactPerson, 
			premiumClient.email, premiumClient.telephone, premiumClient.personalID, premiumClient.petrolType, premiumClient.gallons, premiumClient.clientCreditAm,
			premiumClient.dateOfTransaction.day, premiumClient.dateOfTransaction.month, premiumClient.dateOfTransaction.year, premiumClient.totalCompanyCredit); //write to the file
			fputs("\n__________________________________________________________________________________________\n", nPtr);
		}
		
		//user will have to manually calculate the accumulated company credit (to be paid at the end of the month) based on info in this file
		
		fclose(nPtr); //close the file
	}
	
	puts("\n__________________________________________________________________________________________\n");	
	
	//sales data 
	FILE *sPtr;
	
	if((sPtr = fopen ("sales_data.txt", "a")) == NULL){
		puts("File could not be opened.");
	} else {
		printf("\nPlease enter the sale ID # and the pump #: ");
		scanf("%d%d", &saleID, &pumpNo);
		
		fprintf(sPtr, "%s\n\n", "SALES DATA");
		
		for(int i=0; i<salesdata; i++){
			fprintf(sPtr, 
			"Sale ID #: %d\n"
			"Eagle Energy ID #: %d\n"
			"Company Code: %d\n"
			"Personal ID #: %d\n"
			"Petrol Type: %s\n"
			"Pump #: %d\n"
			"Gallons: %.1f\n"
			"Cost Per Gallon: $%.2f\n"
			"Client Credit Amount/ Value of Sale: $%.2f\n"
			"Date of Sale: %d/%s/%d\n", saleID, eagleEnergyID, premiumClient.companyCode, premiumClient.personalID, premiumClient.petrolType, pumpNo, premiumClient.gallons,
			petrolRate, premiumClient.clientCreditAm, premiumClient.dateOfTransaction.day, premiumClient.dateOfTransaction.month, premiumClient.dateOfTransaction.year); //write to the file
			fputs("\n__________________________________________________________________________________________\n", sPtr);
		}
		
		//user will have to manually calculate the total petrol sales for each type based on info in this file
		
		fclose(sPtr);
		
		puts("\nTransaction complete. Thank You!");
		
		menu(); //function call for the menu
	}
}

//function definition to read data into client (credit purchase) variable
PREMIUM_CLIENT readCreditData(void){
	printf("\nPlease enter credit ID #: ");
	scanf("%d", &premiumClient.creditID);
	
	printf("\nPlease enter company ID #: ");
	scanf("%d", &premiumClient.companyID);
	
	printf("\nPlease enter company name: ");
	scanf("%s", premiumClient.companyName);
	
	printf("\nPlease enter company contact person: ");
	scanf("%s", premiumClient.contactPerson);
	
	printf("\nPlease enter company email: ");
	scanf("%s", premiumClient.email);
	
	printf("\nPlease enter company telephone number: ");
	scanf("%s", premiumClient.telephone);
	
	printf("\nPlease enter client's company code: ");
	scanf("%d", &premiumClient.companyCode);
	
	printf("\nPlease enter client's personal ID #: ");
	scanf("%d", &premiumClient.personalID);
	
	printf("\nPlease enter petrol type: ");
	scanf("%s", premiumClient.petrolType);
	
	printf("\nPlease enter gallons: ");
	scanf("%f", &premiumClient.gallons);
	
	premiumClient.clientCreditAm = premiumClient.gallons * petrolRate;
	
	printf("\nPlease enter date of transaction - day, in numbers: ");
	scanf("%d", &premiumClient.dateOfTransaction.day);
	
	printf("\nPlease enter date of transaction - month, in letters: ");
	scanf("%s", premiumClient.dateOfTransaction.month);
	
	printf("\nPlease enter date of transaction - year, in numbers: ");
	scanf("%d", &premiumClient.dateOfTransaction.year);
	
	printf("\nPlease enter total company credit: ");
	scanf("%f", &premiumClient.totalCompanyCredit);
	
	return premiumClient;
}

//function definition to print receipt info after client's purchase
void printReceipt(PREMIUM_CLIENT premiumClient){
	puts("\n__________________________________________________________________________________________");
	puts("\nThanks for the support! Here is your receipt: ");
	
	printf("\nClient Personal ID #: %d", premiumClient.personalID);
	printf("\nPetrol Type: %s", premiumClient.petrolType);
	printf("\nGallons: %.1f", premiumClient.gallons);
	printf("\nCost per Gallon: $%.2f", petrolRate);
	printf("\nClient Credit Amount/ Value of Sale: $%.2f", premiumClient.clientCreditAm);
	printf("\nDate of Transaction: %d/%s/%d", premiumClient.dateOfTransaction.day, premiumClient.dateOfTransaction.month, premiumClient.dateOfTransaction.year);
}

//function definition for exit option
void exit(void){
	puts("\nThank you for using Eagle Energy services!");
}

//function to display reports
void displayReports(void){
	FILE *nPtr,*sPtr;
    
    if ((nPtr=fopen("credit_data.txt","rb+"))==NULL)
    printf("\a\tFile cannot be accessed!!!");
    else{
    	printf("\n%s\n\n", "CREDIT REPORT");
        printf("%s \t\t %s \t\t %s\n", "Personal ID", "Client Credit Amount", "Total Company Credit");
		fscanf(nPtr, "%d %f %f", &premiumClient.personalID, &premiumClient.clientCreditAm, &premiumClient.totalCompanyCredit); 
		printf("%d \t\t\t $%.2f \t\t\t $%.2f\n", premiumClient.personalID, premiumClient.clientCreditAm, premiumClient.totalCompanyCredit);
        printf("\n*************************************************************************\n");
    }
    
    if ((sPtr=fopen("sales_data.txt","rb+"))==NULL)
    printf("\a\tFile cannot be accessed!!!");
    else{
    	printf("\n%s\n\n", "PETROL SALES REPORT");
        printf("%s \t\t %s \t\t %s \t\t %s\n", "Petrol Type", "Pump No.", "Gallons", "Cost per Gallon");
		fscanf(sPtr, "%s %d %f %f", premiumClient.petrolType, &pumpNo, &premiumClient.gallons, &petrolRate);
		printf("%s \t\t\t %d \t\t\t %.1f \t\t\t $%.2f\n", premiumClient.petrolType, pumpNo, premiumClient.gallons, petrolRate);
		printf("\n*************************************************************************\n");
    }
    
    if((nPtr=fopen("credit_data.txt","rb+"))==NULL)
    printf("\a\tFile cannot be accessed!!!");
    else{
        printf("\n%s\n\n", "CLIENT SALES REPORT");
        printf("%s \t\t %s \t\t %s \t\t %s\n", "Company Code", "Personal ID", "Total Gallons", "Client Credit Amount");
        fscanf(nPtr, "%d %d %f %f", &premiumClient.companyCode, &premiumClient.personalID, &premiumClient.gallons, &premiumClient.clientCreditAm);
        printf("%d \t\t\t %d \t\t\t %.1f \t\t\t $%.2f\n", premiumClient.companyCode, premiumClient.personalID, premiumClient.gallons, premiumClient.clientCreditAm);
		printf("\n*************************************************************************\n");
    }
    
    fclose(sPtr);
    
    fclose(nPtr);
    
    puts("\nHere are the reports. Thank You!");
    
    menu(); //function call for the menu
}

void addAndUpdateEmployees(void){
	FILE *ePtr; 

	cout<<"*******ENTER REQUIRED INFORMATION**********";
	printf("\n");

	if((ePtr = fopen ("employee_data.txt", "a+")) == NULL){
		printf("Could not open file.");
	} else {
		for(int i=0; i<MAX_EMPLOYEES; i++){
			printf("\n");
			
			printf("Enter employee name: ");
			scanf("%s", &employees.name);
		
			printf("Enter employee job title: ");
			scanf("%s", employees.job_title);
		
			printf("Enter assigned employee username: ");
			scanf("%s", employees.username);
		
			printf("Enter assigned employee password: ");
			scanf("%s", &employees.passcode);
		}
	
		fprintf(ePtr, "%s\n\n", "EMPLOYEE DATA");
	
		for(int i=0; i<MAX_EMPLOYEES; i++){
    
        	fprintf(ePtr,
			"Employee Name: %s\n"
			"Employee Job Title: %s\n"
			"Employee Username: %s\n"
			"Employee Password: %s", employees.name, employees.job_title, employees.username, &employees.passcode);
        	fputs("\n__________________________________________________________________________________________\n", ePtr);
        }
	}
        
	fclose(ePtr); 
	
	puts("\nUpdate Complete. Thank You!");
	
	menu(); //function call for the menu
}

// Function definition for search
void searchCompanies(void){
    FILE *ccPtr;
    
    if ((ccPtr=fopen("company_data.txt","rb+"))==NULL)
    printf("\a\tFile cannot be accessed!!!");
    else{
    	printf("\n%s\n\n", "ALL COMPANIES IN SYSTEM");
        printf("%d \t\t %s \t\t %s \t\t %s \t\t %s\n", "Company ID", "Company Name", "Contact Person", "Company Email", "Company Telephone");
		fscanf(ccPtr, "%d %s %s %s", &companies.companyID, companies.companyName, companies.contactPerson, companies.contactEmail, companies.contactPhoneNumber);
		printf("%d \t\t\t %s \t\t\t %s \t\t\t %s \t\t\t %s\n", companies.companyID, companies.companyName, companies.contactPerson, companies.contactEmail, companies.contactPhoneNumber);
        printf("\n*************************************************************************\n");
    }
    
    fclose(ccPtr);
    
    puts("\nSearch Complete. Thank You!");
    
    menu(); //function call for the menu
}
