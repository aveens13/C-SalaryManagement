#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <conio.h>
#include <windows.h>
#include <ctype.h>

//structure definition
typedef struct {
    char name[20];
    int id;
    char position[20];
    float salary;
    char phoneno[10];
} employee;

typedef struct{
    float provident_fund;
    float tax;
}sys;


//global variables
employee records[20];
char name[20];
char real_username[20] = "admin"; //username
char real_password[20] = "admin"; //password
int no_of_records;

//float tax = 0.13;
sys det[2];

//function declaration
void login();//Ankit (done)
void mainMenu();//Ankit (done)
void manageEmployees();//Ankit (done)
void addEmployees();//Ankit (done)
void appendToFile(employee);//Ankit (done)
void readFromFile();//Ankit (done)
void generate_payment();//Avinav
void searchEmployee();//Ankit 
void removeEmployee();//Avinav
void removeEmployee1(int);//Avinav
void editEmployee();//Avinav
void edit_system();//Nishit
void writesysfile();//Nishit
void readsysfile();//Nishit
void info();//Nishit
void lowercase(char []);//Ankit (done)
void logs();//Sulav
void gotoxy(int x, int y);//Sulav
void printPaySlip(int); //Ankit
void displayDetails(int); //Ankit

//main
int main()
{    
    //readsysfile();
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
    int i=0, value1, value2;
    do{
        password[i] = getch();
        if (password[i]!='\r') printf("*"); //masking the password
        i+=1;
    }while (password[i-1] != '\r');
    password[i-1]='\0';
    value1 = strcmp(username, real_username);
    value2 = strcmp(password, real_password);
    if (value1 == 0 && value2 == 0){
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
        edit_system();
        break;
    case 4:
        info();
        break;
    case 5:
        logs();
        break;
    case 6:
        printf("\n");
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
        removeEmployee();
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
    char option;
    system("cls");
    printf("\n\nEnter the name of employee: ");
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
    scanf("%s", new_record.phoneno);
    appendToFile(new_record); //adding the entered data to the file by calling another function
    printf("\nDo you want to add more? (y/n): ");
    scanf("%c", &temp);
    scanf("%c", &option);
    tolower(option);
    if (option == 'y') addEmployees();
    else mainMenu();
}

//adding new employee to the file
void appendToFile(employee new_record){
    FILE *f = fopen("record.txt", "a");
    fprintf(f, "%s\n", new_record.name);
    fprintf(f, "%d\n", new_record.id);
    fprintf(f, "%s\n", new_record.position);
    fprintf(f, "%f\n", new_record.salary);
    fprintf(f, "%s\n", new_record.phoneno);
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
// removing an employee
void removeEmployee(){
    int id_no,j=9999;
    char usr_res;
   system("cls");
   printf("Enter the id no. of the employee: ");
   scanf("%d",&id_no);
   for(int i=0;i<=no_of_records;i++){
        if(id_no == records[i].id){
            j = i;
        }
    }
    if(j!=9999){
        printf("Do you want to remove %s from the employee records?",records[j].name);
        usr_res = getch();
        if(usr_res == 'y'){
            removeEmployee1(j);}
        else {
            removeEmployee();}
    }
    else{
        printf("We could not find the user with %d",id_no);
        printf("Enter any key to repeat the process");getch();
        removeEmployee();
    }
}
void removeEmployee1(int id_no){
    FILE *fp,*fp1;
    printf("\nClearing User Info");
    Sleep(300);printf(".");
    Sleep(300);printf(".");  
    Sleep(300);printf(".");
    Sleep(300);printf(".\n\n");
    fp = fopen("record.txt","r");
    fflush(fp);
    fclose(fp);
    fp1 = fopen("record.txt","w");
    // this section rewrite the updated details
    for(int i=0;i<no_of_records;i++){
        if(i!=id_no){
            fprintf(fp1, "%s\n", records[i].name);
            fprintf(fp1, "%d\n", records[i].id);
            fprintf(fp1, "%s\n",records[i].position);
            fprintf(fp1, "%f\n", records[i].salary);
            fprintf(fp1, "%s\n", records[i].phoneno);
        }    
    }
    fclose(fp1);
}
// system edit
void edit_system(){
    char password[20];
    printf("\nProcessing");
    Sleep(300);printf(".");
    Sleep(300);printf(".");  
    Sleep(300);printf(".");
    Sleep(300);printf(".\n\n");
    for(int j=3;j>0;j--){
        int i = 0;
        system("cls");
        printf("\n\n\t\tYou are accessing the admin-panel, you are required to enter the password again.");
        printf("\n\n\t\t\t\tPassword: ");
        do{
            password[i] = getch();
            if(password[i] != 13) printf("*");
            i++;
        }
        while(password[i-1] != 13 );
        password[i-1] = '\0';
        if(strcmp(password,real_password)==0){
            system("cls");
            writesysfile();
            break;
        }
        else{
            printf("\n\nYou have provided the wrong password");
            printf("\n\n\t\t\tEnter any key to try again");
            printf("\n\n\t\t\tYou have %d tries left",j-1);
            getch();
        }
    }

}
void writesysfile(){
    FILE *fp;
    fp =fopen("sys.txt","r");
    fflush(fp);
    fclose(fp);
    fp=fopen("sys.txt","w");
    system("cls");
    printf("\n\n\t\t\tEnter the new tax rate: ");
    scanf("%f",&det[0].tax);
    printf("\n\n\t\t\tEnter the new Provident Fund percentage: ");
    scanf("%f",&det[0].provident_fund);
    fprintf(fp,"%f",det[0].tax);
    fprintf(fp,"\n%f",det[0].provident_fund);
    fclose(fp);
}

/*void readsysfile(){
    FILE *fp;
    fp = fopen("sys.txt","r");
    fscanf(fp,"%f",&det[1].tax);
    fscanf(fp,"%f",&det[1].provident_fund);
}*/

//information of a certain employee
void info(){
    system("cls");
    float num, per;
    FILE *fp;
    fp=fopen("sys.txt","r");
    fscanf(fp,"%f",&num);//provident fund
    per=num*100; //change into percentage
    printf("\n\n\t\t\tThe current provident fund rate is %.2f%. \n", per);
    fscanf(fp,"%f",&num);//Tax rate
    per=num*100;
    printf("\n\n\t\t\tThe current tax rate is %.2f%. \n", per);
    fclose(fp);

}
//search employee
void searchEmployee(){
    char input = getch();
    if (input == '\b'){
        name[strlen(name)-1] = '\0';
    }else{
        strncat(name, &input, 1);
    }
    system("cls");
    printf("Enter the name of employee: %s\n\n", name);
    printf("\tID\t\tName\t\t\t\tPosition\t\t\tSalary\t\t\t\tPhone\n");
    for (int i=0; i<no_of_records; i++){
        char temp[20], id_str[10], temp_position[20];
        strcpy(temp, records[i].name);
        strcpy(temp_position, records[i].position);
        lowercase(temp);
        lowercase(temp_position);
        lowercase(name);
        itoa(records[i].id, id_str, 10);
        if (strstr(temp, name) != NULL || strstr(id_str, name) != NULL || strstr(temp_position,name) != NULL){ 
            printf("\t%d\t\t%-20s\t\t%-20s\t\t%-20.2f\t\t%-20s\n", records[i].id, records[i].name, records[i].position, records[i].salary, records[i].phoneno);
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
FILE *fp,*fp1;
    char change[20],temp;
    int j,id_no;
    int idd;
    int usr_choice;
    strcpy(name, "");
    system("cls");
    printf("Enter the id no of employee: ");
    scanf("%d",&id_no);
    for(int i=0;i<=no_of_records;i++){
        if(id_no == records[i].id){
            j = i;
        }
    }
    system("cls");
    printf("\n\t\tWhat do you want to edit for %s?",records[j].name);
    printf("\n\n\t\t1.Position\n\t\t2.Phone Number\n\t\t3.Name\n\t\t4.Id Number\n");
    scanf("%d",&usr_choice);
    switch (usr_choice)
    {
    case 1:
        system("cls");
        printf("\n\t\tCurrent Position of %s is %s.",records[j].name,records[j].position);
        printf("\n\nPlease enter the new position: ");
        scanf("%c",&temp);
        scanf("%[^\n]",change);
        strcpy(records[j].position , change);
        printf("\nProcessing");
        Sleep(300);printf(".");
        Sleep(300);printf(".");  
        Sleep(300);printf(".");
        Sleep(300);printf(".\n\n");
        fp = fopen("record.txt","r");
        fflush(fp);
        fclose(fp);
        fp1 = fopen("record.txt","w");
        // this section rewrite the updated details
        for(int i=0;i<no_of_records;i++){
            fprintf(fp1, "%s\n", records[i].name);
            fprintf(fp1, "%d\n", records[i].id);
            fprintf(fp1, "%s\n",records[i].position);
            fprintf(fp1, "%f\n", records[i].salary);
            fprintf(fp1, "%s\n", records[i].phoneno);
            
        }
        fclose(fp1);
        printf("\n\n\t\tSucessfully changed the position for %s",records[j].name);
        printf("\n\nEnter any key to go to main menu");
        getch();
        mainMenu();
        break;
    case 2:
        system("cls");
        printf("\n\t\tCurrent Phone Number of %s is %s.",records[j].name,records[j].phoneno);
        printf("\n\nPlease enter the new Phone Number: ");
        scanf("%c",&temp);
        scanf("%[^\n]",change);
        strcpy(records[j].phoneno , change);
        printf("\nProcessing");
        Sleep(300);printf(".");
        Sleep(300);printf(".");  
        Sleep(300);printf(".");
        Sleep(300);printf(".\n\n");
        fp = fopen("record.txt","r");
        fflush(fp);
        fclose(fp);
        fp1 = fopen("record.txt","w");
        // this section rewrite the updated details
        for(int i=0;i<no_of_records;i++){
            fprintf(fp1, "%s\n", records[i].name);
            fprintf(fp1, "%d\n", records[i].id);
            fprintf(fp1, "%s\n",records[i].position);
            fprintf(fp1, "%f\n", records[i].salary);
            fprintf(fp1, "%s\n", records[i].phoneno);
            
        }
        fclose(fp1);
        printf("\n\n\t\tSucessfully changed the phone number of %s",records[j].name);
        printf("\n\nEnter any key to go to main menu");
        getch();
        mainMenu();

        break;
    case 3:
        system("cls");
        printf("\n\t\tCurrent Name is %s.",records[j].name);
        printf("\n\nPlease enter the new Name: ");
        scanf("%c",&temp);
        scanf("%[^\n]",change);
        strcpy(records[j].name , change);
        printf("\nProcessing");
        Sleep(300);printf(".");
        Sleep(300);printf(".");  
        Sleep(300);printf(".");
        Sleep(300);printf(".\n\n");
        fp = fopen("record.txt","r");
        fflush(fp);
        fclose(fp);
        fp1 = fopen("record.txt","w");
        // this section rewrite the updated details
        for(int i=0;i<no_of_records;i++){
            fprintf(fp1, "%s\n", records[i].name);
            fprintf(fp1, "%d\n", records[i].id);
            fprintf(fp1, "%s\n",records[i].position);
            fprintf(fp1, "%f\n", records[i].salary);
            fprintf(fp1, "%s\n", records[i].phoneno);
            
        }
        fclose(fp1);
        printf("\n\n\t\tSucessfully changed the name as %s",records[j].name);
        printf("\n\nEnter any key to go to main menu");
        getch();
        mainMenu();

        break;
    case 4:
        
        system("cls");
        printf("\n\t\tCurrent Id Number of %s is %d.",records[j].name,records[j].id);
        printf("\n\nPlease enter the new ID Number: ");
        scanf("%d",&idd);
        // scanf("%[^\n]",change);
        // strcpy(records[j].phoneno , change);
        records[j].id = idd;
        printf("\nProcessing");
        Sleep(300);printf(".");
        Sleep(300);printf(".");  
        Sleep(300);printf(".");
        Sleep(300);printf(".\n\n");
        fp = fopen("record.txt","r");
        fflush(fp);
        fclose(fp);
        fp1 = fopen("record.txt","w");
        // this section rewrite the updated details
        for(int i=0;i<no_of_records;i++){
            fprintf(fp1, "%s\n", records[i].name);
            fprintf(fp1, "%d\n", records[i].id);
            fprintf(fp1, "%s\n",records[i].position);
            fprintf(fp1, "%f\n", records[i].salary);
            fprintf(fp1, "%s\n", records[i].phoneno);
            
        }
        fclose(fp1);
        printf("\n\n\t\tSucessfully changed the Id number of %s",records[j].name);
        printf("\n\nEnter any key to go to main menu");
        getch();
        mainMenu();

        break;
    default:
        printf("Invalid choice");
        Sleep(1000);
        editEmployee();
        break;
    }
    
    
}
/*void  generate_payment(){
    system("cls");
    int id_no,id;
    FILE *fp,*fp1;
    float amount,amount_after_tax,amount_after_pf;
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
            printf("\n\n\t\tPlease note that each time you generate an amount to the employee, amount will be paid by deducting certain tax and certain percentage goes to Provident Fund.");
            printf("\n\nEnter the amount: ");
            scanf("%f",&amount);
            // calculating the amount after tax 
            amount_after_tax = amount - det[1].tax*amount;
            amount_after_pf = amount_after_tax - det[1].provident_fund*amount_after_tax;
            records[id].salary += amount_after_pf;
            // Animation(if not relevant we can delete this)
            printf("\nProcessing");
            Sleep(300);printf(".");
            Sleep(300);printf(".");  
            Sleep(300);printf(".");
            Sleep(300);printf(".\n\n");
            printf("The amount of sum %f has been generated to the employee after deducting certain tax and some percentage of the amount was updated as Provident fund.",amount_after_pf);
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
            }
            fclose(fp1);
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
*/

void generate_payment(){
    int id, done_id;
    char choice;
    system("cls");
    printf("\n\t\tPlease enter id of the employee: ");
    scanf("%d", &id);
    for (int i=0; i<no_of_records; i++){
        if (id==records[i].id) {
            displayDetails(i);
            printf("\n\n\t\tDo you want to pay %s? (y/n):", records[i].name);
            choice = getch();
            if (choice =='y') {
                FILE *f = fopen("deposit.txt", "r");
                while (!feof(f)){
                    fscanf(f, "%d\n", &done_id);
                    if (done_id==id){
                        printf("\n\n\t\tYou have already paid %s!", records[i].name);
                        printf("\n\n\t\tPress any button to continue...");
                        getch();
                        mainMenu();
                    }
                }
                 
                fclose(f);
                printPaySlip(i);
            }
            else mainMenu();
            break;
            } 
    }
}

void displayDetails(int i){
    printf("\n\n\t------------------------------------------------\n");
    printf("\n\t\tName: %s\n", records[i].name);
    printf("\n\t\tID: %d\n", records[i].id);
    printf("\n\t\tPosition: %s\n", records[i].position);
    printf("\n\t\tSalary: %.2f\n", records[i].salary);
    printf("\n\t\tPhone Number: %s\n", records[i].phoneno);
    printf("\n\t------------------------------------------------");
}

void printPaySlip(int i){
    float total, provident_fund, tax, bonus;
    char choice;
    FILE *f = fopen("sys.txt", "r");
    while (!feof(f)){
        fscanf(f, "%f\n", &tax);
        fscanf(f, "%f\n", &provident_fund);
    }
    fclose(f);
    bonus = 10000;
    total = records[i].salary - (tax/100*records[i].salary) - (provident_fund/100*records[i].salary) + bonus;
    system("cls");
    printf("\n\n\t---------------------------------------------------------------------\n\n");
    printf("\t\tName: %s\t\t\t\tID:%d\n\n\t\tSalary: Rs. %.2f\t\t\tTax: Rs. %.2f\n\n\t\tProvident Fund: Rs. %.2f\t\tBonus: Rs. %.2f\n\n\n\t\t\t\tTotal: Rs. %.2f", records[i].name, records[i].id, records[i].salary, (tax/100*records[i].salary), (provident_fund/100*records[i].salary), bonus, total);
    printf("\n\n\t---------------------------------------------------------------------");
    printf("\n\n\tDo you want to deposit Rs. %.2f to %s's account? (y/n): ", total, records[i].name);
    choice = getch();
    if (choice=='y'){
        FILE *f = fopen("deposit.txt", "a");
        fprintf(f, "%d\n", records[i].id);
        fclose(f);
        printf("\n\n\tDone!\n");
        printf("\n\tPress any key to go back to Main Menu...");
        getch();
    }
    mainMenu();
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