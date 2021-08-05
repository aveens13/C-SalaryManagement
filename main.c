#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <conio.h>
#include<windows.h>
#include <ctype.h>

//structure definition
typedef struct {
    char name[20];
    int id;
    char position[20];
    float salary;
    char phoneno[10];
} employee;

//global variables
employee records[20];
char name[20];
char real_username[20] = "admin"; //username
char real_password[20] = "admin"; //password
int no_of_records;
float tax = 0.13;

//function declaration
void login();
void mainMenu();
void manageEmployees();
void addEmployees();
void appendToFile(employee*);
void readFromFile();
void generate_payment();
void searchEmployee();
void editEmployee();
void lowercase(char []);
void logs();
void gotoxy(int x, int y);

//main
int main()
{
    //system("cls");
    readFromFile();
    // printf("%s",records[0].name);
    login();
    mainMenu();
    return 0;
}

//login page
void login(){
    char username[20], password[20], input;
    printf("\n\n\n\t\t\tUsername: ");
    scanf("%s", username);
    printf("\n\t\t\tPassword: ");
    int i=0;
    do{
        password[i] = getch();
        if (password[i]!='\r') printf("*"); //masking the password
        i+=1;
    }while (password[i-1] != '\r');
    password[i-1]='\0';
    if (strcmp(username, real_username) == 0 && strcmp(password, real_password) == 0){
        system("cls");
        mainMenu();
    }else{
        system("cls");
        printf("\n\t\t\tInvalid Username or Password!");
        login();
    }
    
}

//main menu
void mainMenu(){
    int input;
    system("cls");
    printf("\n\n\n\n");
    printf("\t\t1. Generate Payment\n");
    printf("\t\t2. Manage Employees\n");
    printf("\t\t3. Edit the system\n");
    printf("\t\t4. Info\n");
    printf("\t\t5. Logs\n");
    printf("\t\t6. Exit\n");
    printf("\n\t\tInput: ");
    scanf("%d", &input);
    readFromFile(); //reading data from file
    switch (input){
    
    case 1:
        generate_payment();
        break;
    case 2:
        manageEmployees();
        break;
    case 3:
        //edit_system();
        break;
    case 4:
        //info();
        break;
    case 5:
        logs();
        break;
    case 6:
        exit(0);
        break;
    default:
        system("cls");
        printf("\n\tPlease enter a valid option!");
        mainMenu();
    }
    
}

//employee add, search, delete, edit
void manageEmployees(){
    char input;
    system("cls");
    printf("\n\n\n\n");
    printf("\t\t1. Add an employee\n");
    printf("\t\t2. Edit an employee\n");
    printf("\t\t3. Search an employee\n");
    printf("\t\t4. Remove an employee\n");
    printf("\t\t5. Back to main menu\n");
    printf("\n\t\tInput: ");
    scanf("%s", &input);

    switch (input){
    case '1':
        addEmployees();
        break;
    case '2':
        editEmployee();
        break;
    case '3':
        strcpy(name, "");
        system("cls");
        printf("Enter the name of employee: ");
        searchEmployee();
        break;
    case '4':
        //removeEmployee();
    case '5':
        mainMenu();
        break;
    default:
        manageEmployees();
    }
    
}

//employee add
void addEmployees() {
    employee new_record;
    char temp;
    printf("Enter the name of employee: ");
    scanf("%c", &temp);
    scanf("%[^\n]", new_record.name);
    printf("Enter the id: ");
    scanf("%d", &new_record.id);
    printf("Enter the position: ");
    scanf("%c", &temp);
    scanf("%[^\n]", new_record.position);
    printf("Enter the salary: ");
    scanf("%f", &new_record.salary);
    printf("Enter phone number: ");
    scanf("%c", &temp);
    scanf("%[^\n]", new_record.phoneno);
    
    appendToFile(&new_record);//adding the entered data to the file by calling another function
    mainMenu();
}

//adding new employee to the file
void appendToFile(employee* new_record){
    FILE *f = fopen("record.txt", "a");
    fprintf(f, "%s\n", new_record->name);
    fprintf(f, "%d\n", new_record->id);
    fprintf(f, "%s\n", new_record->position);
    fprintf(f, "%f\n", new_record->salary);
    fprintf(f, "%s\n", new_record->phoneno);
    fclose(f);
}

//reading from the file
void readFromFile(){
    int i=0;
    FILE *f;
    f= fopen("record.txt", "r");
    while (!feof(f)){
        fgets(records[i].name, 20, f);
        records[i].name[strlen(records[i].name)-1]='\0';
        fscanf(f, "%d\n", &records[i].id);
        fgets(records[i].position, 20, f);
        records[i].position[strlen(records[i].position)-1]='\0';
        fscanf(f, "%f\n", &records[i].salary);
        fgets(records[i].phoneno, 20, f);
        records[i].phoneno[strlen(records[i].phoneno)-1]='\0';
        i+=1;
    }
    no_of_records=i-1;
    fclose(f); 
}

//for employee search by name (id not done yet)
void searchEmployee(){
    char input = getch();
    if (input == '\b'){
        name[strlen(name)-1] = '\0';
    }else{
        strncat(name, &input, 1);
    }
    system("cls");
    printf("Enter the name of employee: %s\n\n", name);
    printf("\tID\t\tName\t\t\t\tPosition\tSalary\t\t\tPhone\n");
    for (int i=0; i<no_of_records; i++){
        char temp[20];
        strcpy(temp, records[i].name);
        lowercase(temp);
        lowercase(name);
        if (strstr(temp, name) != NULL){ 
            printf("\t%d\t\t%-20s\t\t%-s\t\t%-10.2f\t\t%-s\n", records[i].id, records[i].name, records[i].position, records[i].salary, records[i].phoneno);
        }else if (strcmp(name, "quit") == 0){
            manageEmployees();
        }
    }
    searchEmployee();
}

//to convert a whole string to lowercase
void lowercase(char temp[]){
    for (int i=0; i<strlen(temp); i++){
        temp[i]=tolower(temp[i]);
    }
}

//not completed but for editing employee data
void editEmployee(){
    strcpy(name, "");
    system("cls");
    printf("Enter the name of employee: ");
    searchEmployee();
}
void  generate_payment(){
    system("cls");
    int id_no,id;
    FILE *fp,*fp1;
    float amount,amount_after_tax;
    here:
    printf("\n\nInput the id no of the employee: ");
    scanf("%d",&id_no);
    for(int i=0;i<=no_of_records;i++){
        if(id_no == records[i].id){
            id = i;
        }
    }
    if(id_no == records[id].id){
        printf("\n\t\t\tThe payment will be generated to %s.",records[id].name);
        printf("\n\nAre you sure you want to pay %s?\n1. Yes\n2. No\n",records[id].name);
        scanf("%d",&id_no);
        if(id_no == 1){
            system("cls");
            printf("\n\n\t\tPlease note that each time you generate an amount to the employee, amount will be paid by deducting certain tax.");
            printf("\n\nEnter the amount: ");
            scanf("%f",&amount);
            // calculating the amount after tax 
            amount_after_tax = amount - tax*amount;
            records[id].salary += amount_after_tax;
            // Animation(if not relevant we can delete this)
            printf("\nProcessing");
            Sleep(300);printf(".");
            Sleep(300);printf(".");  
            Sleep(300);printf(".");
            Sleep(300);printf(".\n\n");
            printf("The amount of sum %f has been generated to the employee after deducting certain tax.",amount_after_tax);
            printf("\n\n\t\t\t\tUPDATED DETAILS...\n\n");
            printf("\n\nName:%s\t\tID:%d\t\tSalary:%f",records[id].name,records[id].id,records[id].salary);
            // Again opening file so to rewrite the updated details
            fp = fopen("record.txt","r");
            fflush(fp);
            fclose(fp);
            fp1 = fopen("record.txt","w");
            // this section rewrite the updated details
            for(int i=0;i<=no_of_records;i++){
                fprintf(fp1, "%s\n", records[i].name);
                fprintf(fp1, "%d\n", records[i].id);
                fprintf(fp1, "%s\n",records[i].position);
                fprintf(fp1, "%f\n", records[i].salary);
                fprintf(fp1, "%s\n", records[i].phoneno);
                fclose(fp1);

            }
            getch();
        }
        else if(id_no == 2){
            goto here;
        }
        else{
            printf("Invalid Input");
            goto here;
        }
    }
    else{
        printf("\n\n\tWe could not found the details related to that ID Number.\n\tPlease enter ID Number again.");
        goto here;
    }
}
//for the coordinates placement
void gotoxy(int x, int y){
    COORD A;
    A.X = x;
    A.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),A);
}
//view logs
void logs(){
    int i;
    system("cls");
    gotoxy(30,4);
    printf("===================================================================================");
    gotoxy(50,5);
    printf("\xB2\xB2\xB2\xB2\xB2\xB2 EMPLOYEE SALARY MANAGEMENT (LOGS)\xB2\xB2\xB2\xB2\xB2\xB2");
    gotoxy(30,6);
    printf("===================================================================================");
    gotoxy(3,8);
    printf("==================================================================================================================================");
    gotoxy(3,9);
    printf("ID");
    gotoxy(10,9);
    printf("NAME");
    gotoxy(33,9);
    printf("POSITION");
    gotoxy(56,9);
    printf("PHONE NO.");
    gotoxy(69,9);
    printf("SALARY");
    gotoxy(81,9);
    printf("BONUS");
    gotoxy(89,9);
    printf("TAX");
    gotoxy(97,9);
    printf("DEDUCTIONS");
    gotoxy(110,9);
    printf("NET EARNING");
    gotoxy(3,10);
    printf("==================================================================================================================================");

    for(i=0;i<no_of_records;i++){
        gotoxy(3,(i+11));
    printf("%-4d\t%-20s\t%-20s\t%-10s   %-.2f\t",records[i].id,records[i].name,records[i].position,records[i].phoneno,records[i].salary);

    }

    gotoxy(3,(i+11));
    printf("==================================================================================================================================\n\n");

    printf("\tTOTAL NO. OF EMPLOYEE=%d\n",no_of_records);
    gotoxy(50,(i+15));
    printf("Press any button to return to the main menu");
    getch();
    mainMenu();

    


}