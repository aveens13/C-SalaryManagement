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
float tax = 0.13;
sys det[2];
//function declaration
void login();//Ankit
void mainMenu();//Ankit
void manageEmployees();//Ankit
void addEmployees();//Ankit
void appendToFile(employee*);//Ankit
void readFromFile();//Ankit
void generate_payment();//Avinav
void searchEmployee();//Ankit
void removeEmployee();//Avinav
void removeEmployee1(int);//Avinav
void editEmployee();//Avinav
void edit_system();//Nishit
void writesysfile();//Nishit
void readsysfile();//Nishit
void info();//Nishit
void lowercase(char []);//Ankit
void logs();//Sulav
void gotoxy(int x, int y);//Sulav

//main
int main()
{    
    readsysfile();
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
        edit_system();
        break;
    case 4:
        info();
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
    char password[20];int i=0;
    printf("\nProcessing");
    Sleep(300);printf(".");
    Sleep(300);printf(".");  
    Sleep(300);printf(".");
    Sleep(300);printf(".\n\n");
    for(int j=3;j>0;j--){
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
    printf("\n\n\t\t\tEnter the percentage of Provident fund to be deducted: ");
    scanf("%f",&det[0].provident_fund);
    fprintf(fp,"%f",det[0].provident_fund);
    fprintf(fp,"\n%f",det[0].tax);
    fclose(fp);
    readsysfile();
}
void readsysfile(){
    FILE *fp;
    fp = fopen("sys.txt","r");
    fscanf(fp,"%f",&det[1].provident_fund);
    fscanf(fp,"%f",&det[1].tax);
}
//information of a certain employee
void info(){
      system("CLS");
    char rate[10];
    float num, per;
    FILE *fp;
    fp=fopen("sys.txt","r");
    fgets(rate, 10, fp);//provident fund
    num=atof(rate); //change string from file into float
    per=num*100; //change into percentage
    printf("The current provident fund rate is %2.f%. \n", per);
    fgets(rate, 10, fp);//tax rate
    num=atof(rate);
    per=num*100;
    printf("The current tax rate is %2.f%. \n", per);
    fclose(fp);

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
    FILE *fp,*fp1;
    char change[20],temp;
    int j,id_no;
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
    printf("\n\n\t\t1.Position\n\t\t2.Phone Number\n");
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
    default:
        printf("Invalid choice");
        Sleep(1000);
        editEmployee();
        break;
    }
    
    
}
void  generate_payment(){
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
            break;
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
            printf("Enter any key to go to main menu.");
            getch();
            mainMenu();
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