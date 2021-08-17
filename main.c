#include <stdio.h>
//#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <ctype.h>
#include "color.h"

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
void generate_payment();//Ankit (done)
void searchEmployee();//Ankit (done)
void removeEmployee();//Avinav
void removeEmployee1(int);//Avinav
void editEmployee();//Avinav
void edit_system();//Nishit
void writesysfile();//Nishit
void info();//Nishit
void lowercase(char []);//Ankit (done)
void logs();//Sulav
void gotoxy(int x, int y);//Sulav
void printPaySlip(int); //Ankit (done)
void displayDetails(int); //Ankit (done)

//main
int main()
{    
    color_init();
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

    fg_color(COLOR_GREEN | COLOR_BRIGHT);
    printf("\n\n\n\t\t\tUsername: ");
    color_reset();

    scanf("%s", username);
    
    fg_color(COLOR_GREEN | COLOR_BRIGHT);
    printf("\n\t\t\tPassword: ");
    color_reset();
    
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
        fg_color(COLOR_RED | COLOR_BRIGHT);
        printf("\n\t\t\tInvalid Username or Password!");
        color_reset();
        login();
    }
    
}

//main menu
void mainMenu(){
    int input;
    system("cls");
    printf("\n\n\n\n");
    fg_color(COLOR_YELLOW | COLOR_BRIGHT);
    printf("\t\t1. Generate Payment\n");
    printf("\t\t2. Manage Employees\n");
    printf("\t\t3. Edit the system\n");
    printf("\t\t4. Info\n");
    printf("\t\t5. Logs\n");
    printf("\t\t6. Exit\n");
    color_reset();

    fg_color(COLOR_GREEN | COLOR_BRIGHT);
    printf("\n\t\tInput: ");
    color_reset();

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
    fg_color(COLOR_YELLOW | COLOR_BRIGHT);
    printf("\t\t1. Add an employee\n");
    printf("\t\t2. Edit an employee\n");
    printf("\t\t3. Search an employee\n");
    printf("\t\t4. Remove an employee\n");
    printf("\t\t5. Back to main menu\n");
    color_reset();
    fg_color(COLOR_GREEN | COLOR_BRIGHT);
    printf("\n\t\tInput: ");
    color_reset();

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
        fg_color(COLOR_YELLOW | COLOR_BRIGHT);
        printf("\tEnter the name of employee: ");
        color_reset();
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
    fg_color(COLOR_YELLOW | COLOR_BRIGHT);
    printf("\n\nEnter the name of employee: ");
    color_reset();
    scanf("%c", &temp);
    scanf("%[^\n]", new_record.name);
    fg_color(COLOR_YELLOW | COLOR_BRIGHT);
    printf("Enter the id: ");
    color_reset();
    scanf("%d", &new_record.id);
    fg_color(COLOR_YELLOW | COLOR_BRIGHT);
    printf("Enter the position: ");
    color_reset();
    scanf("%c", &temp);
    scanf("%[^\n]", new_record.position);
    fg_color(COLOR_YELLOW | COLOR_BRIGHT);
    printf("Enter the salary: ");
    color_reset();
    scanf("%f", &new_record.salary);
    fg_color(COLOR_YELLOW | COLOR_BRIGHT);
    printf("Enter phone number: ");
    color_reset();
    scanf("%s", new_record.phoneno);
    appendToFile(new_record); //adding the entered data to the file by calling another function
    fg_color(COLOR_GREEN | COLOR_BRIGHT);
    printf("\nDo you want to add more? (y/n): ");
    color_reset();
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
   fg_color(COLOR_YELLOW | COLOR_BRIGHT);
   printf("\tEnter the id no. of the employee: ");
   color_reset();
   scanf("%d",&id_no);
   for(int i=0;i<=no_of_records;i++){
        if(id_no == records[i].id){
            j = i;
        }
    }
    if(j!=9999){
        fg_color(COLOR_GREEN | COLOR_BRIGHT);
        printf("\tDo you want to remove %s from the employee records?(y/n) ",records[j].name);
        color_reset();
        usr_res = getch();
        if(usr_res == 'y'){
            removeEmployee1(j);}
        else {
            removeEmployee();}
    }
    else{
        fg_color(COLOR_RED | COLOR_BRIGHT);
        printf("\tWe could not find the user with %d",id_no);
        printf("\tEnter any key to repeat the process");getch();
        color_reset();
        removeEmployee();
    }
}
void removeEmployee1(int id_no){
    FILE *fp,*fp1;
    fg_color(COLOR_RED | COLOR_BRIGHT);
    printf("\n\n\tClearing User Info");
    Sleep(300);printf(".");
    Sleep(300);printf(".");  
    Sleep(300);printf(".");
    Sleep(300);printf(".\n\n");
    color_reset();
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
    fg_color(COLOR_CYAN | COLOR_BRIGHT);
    printf("\n\n\tProcessing");
    Sleep(300);printf(".");
    Sleep(300);printf(".");  
    Sleep(300);printf(".");
    Sleep(300);printf(".\n\n");
    color_reset();
    for(int j=3;j>0;j--){
        int i = 0;
        system("cls");
        fg_color(COLOR_YELLOW | COLOR_BRIGHT);
        printf("\n\n\t\tYou are accessing the admin-panel, you are required to enter the password again.");
        color_reset();
        fg_color(COLOR_GREEN | COLOR_BRIGHT);
        printf("\n\n\t\t\t\tPassword: ");
        color_reset();
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
            fg_color(COLOR_RED | COLOR_BRIGHT);
            printf("\n\n\t\tYou have provided the wrong password");
            printf("\n\n\t\tEnter any key to try again");
            printf("\n\n\t\tYou have %d tries left",j-1);
            getch();
            color_reset();
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
    fg_color(COLOR_YELLOW | COLOR_BRIGHT);
    printf("\n\n\t\t\tEnter the new tax rate in percentage : ");
    color_reset();
    scanf("%f",&det[0].tax);
    fg_color(COLOR_YELLOW | COLOR_BRIGHT);
    printf("\n\n\t\t\tEnter the new Provident Fund percentage : ");
    color_reset();
    scanf("%f",&det[0].provident_fund);
    fprintf(fp,"%f",det[0].tax);
    fprintf(fp,"\n%f",det[0].provident_fund);
    fclose(fp);
}

/*void readsysfile(){`
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
    fg_color(COLOR_YELLOW | COLOR_BRIGHT);
    printf("\n\n\t\t\tThe current tax rate is %.2f%%. \n", num);
    fscanf(fp,"%f",&num);//Tax rate
    printf("\n\n\t\t\tThe current provident fund rate is %.2f%%. \n", num);
    color_reset();
    fclose(fp);
    fg_color(COLOR_GREEN |  COLOR_BRIGHT);
    printf("\n\n\t\t\tEnter any character to go to main menu...");
    getch();
    color_reset();
    mainMenu();

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
    fg_color(COLOR_YELLOW | COLOR_BRIGHT);
    printf("\tEnter the name of employee: ");
    color_reset();
    printf("%s\n\n", name);
    fg_color(COLOR_GREEN | COLOR_BRIGHT);
    printf("\tID\t\tName\t\t\t\tPosition\t\t\tSalary\t\t\t\tPhone\n\n");
    color_reset();
    for (int i=0; i<no_of_records; i++){
        char temp[20], id_str[10], temp_position[20];
        strcpy(temp, records[i].name);
        strcpy(temp_position, records[i].position);
        lowercase(temp);
        lowercase(temp_position);
        lowercase(name);
        itoa(records[i].id, id_str, 10);
        if (strstr(temp, name) != NULL || strstr(id_str, name) != NULL || strstr(temp_position,name) != NULL){ 
            fg_color(COLOR_CYAN | COLOR_BRIGHT);        
            printf("\t%d\t\t%-20s\t\t%-20s\t\t%-20.2f\t\t%-20s\n\n", records[i].id, records[i].name, records[i].position, records[i].salary, records[i].phoneno);
            color_reset();
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
    fg_color(COLOR_YELLOW | COLOR_BRIGHT);
    printf("\n\tEnter the id no of employee: ");
    color_reset();
    scanf("%d",&id_no);
    for(int i=0;i<=no_of_records;i++){
        if(id_no == records[i].id){
            j = i;
        }
    }
    system("cls");
    fg_color(COLOR_GREEN | COLOR_BRIGHT);
    printf("\n\t\tWhat do you want to edit for %s?",records[j].name);
    color_reset();
    fg_color(COLOR_YELLOW | COLOR_BRIGHT);
    printf("\n\n\t\t1.Position\n\t\t2.Phone Number\n\t\t3.Name\n\t\t4.Id Number\n");
    color_reset();
    scanf("%d",&usr_choice);
    switch (usr_choice)
    {
    case 1:
        system("cls");
        fg_color(COLOR_YELLOW | COLOR_BRIGHT);
        printf("\n\t\tCurrent Position of %s is %s.",records[j].name,records[j].position);
        color_reset();
        fg_color(COLOR_GREEN | COLOR_BRIGHT);
        printf("\n\nPlease enter the new position: ");
        color_reset();
        scanf("%c",&temp);
        scanf("%[^\n]",change);
        strcpy(records[j].position , change);
        fg_color(COLOR_CYAN | COLOR_BRIGHT);
        printf("\nProcessing");
        Sleep(300);printf(".");
        Sleep(300);printf(".");  
        Sleep(300);printf(".");
        Sleep(300);printf(".\n\n");
        color_reset();
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
        fg_color(COLOR_YELLOW | COLOR_BRIGHT);
        printf("\n\n\t\tSucessfully changed the position for %s",records[j].name);
        printf("\n\nEnter any key to go to main menu");
        color_reset();
        getch();
        mainMenu();
        break;
    case 2:
        system("cls");
        fg_color(COLOR_YELLOW | COLOR_BRIGHT);
        printf("\n\t\tCurrent Phone Number of %s is %s.",records[j].name,records[j].phoneno);
        color_reset();
        fg_color(COLOR_GREEN | COLOR_BRIGHT);
        printf("\n\nPlease enter the new Phone Number: ");
        color_reset();
        scanf("%c",&temp);
        scanf("%[^\n]",change);
        strcpy(records[j].phoneno , change);
        fg_color(COLOR_CYAN | COLOR_BRIGHT);
        printf("\nProcessing");
        Sleep(300);printf(".");
        Sleep(300);printf(".");  
        Sleep(300);printf(".");
        Sleep(300);printf(".\n\n");
        color_reset();
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
        fg_color(COLOR_YELLOW | COLOR_BRIGHT);
        printf("\n\n\t\tSucessfully changed the phone number of %s",records[j].name);
        printf("\n\nEnter any key to go to main menu");
        getch();
        color_reset();
        mainMenu();

        break;
    case 3:
        system("cls");
        fg_color(COLOR_YELLOW | COLOR_BRIGHT);
        printf("\n\t\tCurrent Name is %s.",records[j].name);
        color_reset();
        fg_color(COLOR_GREEN | COLOR_BRIGHT);
        printf("\n\nPlease enter the new Name: ");
        color_reset();
        scanf("%c",&temp);
        scanf("%[^\n]",change);
        strcpy(records[j].name , change);
        fg_color(COLOR_CYAN | COLOR_BRIGHT);
        printf("\nProcessing");
        Sleep(300);printf(".");
        Sleep(300);printf(".");  
        Sleep(300);printf(".");
        Sleep(300);printf(".\n\n");
        color_reset();
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
        fg_color(COLOR_YELLOW | COLOR_BRIGHT);
        printf("\n\n\t\tSucessfully changed the name as %s",records[j].name);
        printf("\n\nEnter any key to go to main menu");
        getch();
        color_reset();
        mainMenu();

        break;
    case 4:
        
        system("cls");
        fg_color(COLOR_YELLOW | COLOR_BRIGHT);
        printf("\n\t\tCurrent Id Number of %s is %d.",records[j].name,records[j].id);
        color_reset();    
        fg_color(COLOR_GREEN | COLOR_BRIGHT);
        printf("\n\nPlease enter the new ID Number: ");
        color_reset();
        scanf("%d",&idd);
        // scanf("%[^\n]",change);
        // strcpy(records[j].phoneno , change);
        records[j].id = idd;
        fg_color(COLOR_CYAN | COLOR_BRIGHT);
        printf("\nProcessing");
        Sleep(300);printf(".");
        Sleep(300);printf(".");  
        Sleep(300);printf(".");
        Sleep(300);printf(".\n\n");
        color_reset();
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
        fg_color(COLOR_YELLOW | COLOR_BRIGHT);
        printf("\n\n\t\tSucessfully changed the Id number of %s",records[j].name);
        color_reset();
        fg_color(COLOR_CYAN | COLOR_BRIGHT);
        printf("\n\nEnter any key to go to main menu");
        getch();
        color_reset();
        mainMenu();

        break;
    default:
        fg_color(COLOR_RED | COLOR_BRIGHT);
        printf("Invalid choice");
        color_reset();
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
    fg_color(COLOR_YELLOW | COLOR_BRIGHT);
    printf("\n\t\tPlease enter id of the employee: ");
    color_reset();
    scanf("%d", &id);
    for (int i=0; i<no_of_records; i++){
        if (id==records[i].id) {
            displayDetails(i);
            fg_color(COLOR_GREEN | COLOR_BRIGHT);
            printf("\n\n\t\tDo you want to pay %s? (y/n): ", records[i].name);
            choice = getch();
            color_reset();
            if (choice =='y') {
                FILE *f = fopen("deposit.txt", "r");
                while (!feof(f)){
                    fscanf(f, "%d\n", &done_id);
                    if (done_id==id){
                        fg_color(COLOR_RED | COLOR_BRIGHT);
                        printf("\n\n\t\tYou have already paid %s!", records[i].name);
                        printf("\n\n\t\tPress any button to continue...");
                        getch();
                        color_reset();
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
    fg_color(COLOR_RED | COLOR_BRIGHT);
    printf("\n\n\t------------------------------------------------\n");
    color_reset();
    fg_color(COLOR_YELLOW | COLOR_BRIGHT);
    printf("\n\t\tName: ");
    color_reset();
    printf("%s\n", records[i].name);
    fg_color(COLOR_YELLOW | COLOR_BRIGHT);
    printf("\n\t\tID: ");
    color_reset();
    printf("%d\n", records[i].id);
    fg_color(COLOR_YELLOW | COLOR_BRIGHT);
    printf("\n\t\tPosition: ");
    color_reset();
    printf("%s\n", records[i].position);
    fg_color(COLOR_YELLOW | COLOR_BRIGHT);
    printf("\n\t\tSalary: ");
    color_reset();
    printf("%.2f\n", records[i].salary);
    fg_color(COLOR_YELLOW | COLOR_BRIGHT);
    printf("\n\t\tPhone Number: ");
    color_reset();
    printf("%s\n", records[i].phoneno);
    fg_color(COLOR_RED | COLOR_BRIGHT);
    printf("\n\t------------------------------------------------");
    color_reset();
}

void printPaySlip(int i){
    float total, provident_fund, tax, bonus;
    char choice;
    fg_color(COLOR_YELLOW | COLOR_BRIGHT);
    printf("\n\n\t\tAmount of Bonus: ");
    color_reset();
    scanf("%f", &bonus);
    FILE *f = fopen("sys.txt", "r");
    while (!feof(f)){
        fscanf(f, "%f\n", &tax);
        fscanf(f, "%f\n", &provident_fund);
    }
    fclose(f);
    total = records[i].salary - (tax/100*records[i].salary) - (provident_fund/100*records[i].salary) + bonus;
    system("cls");
    fg_color(COLOR_RED | COLOR_BRIGHT);
    printf("\n\n\t---------------------------------------------------------------------\n\n");
    color_reset();
    fg_color(COLOR_GREEN | COLOR_BRIGHT);
    printf("\t\tName: ");
    color_reset();
    printf("%s\t\t\t\t", records[i].name);
    fg_color(COLOR_GREEN | COLOR_BRIGHT);
    printf("ID: ");
    color_reset();
    printf("%d\n\n\t\t", records[i].id);
    fg_color(COLOR_GREEN | COLOR_BRIGHT);
    printf("Salary: ");
    color_reset();
    printf("Rs. %.2f\t\t\t", records[i].salary);
    fg_color(COLOR_GREEN | COLOR_BRIGHT);
    printf("Tax: ");
    color_reset();
    printf("Rs. %.2f\n\n\t\t",(tax/100*records[i].salary));
    fg_color(COLOR_GREEN | COLOR_BRIGHT);
    printf("Provident Fund: ");
    color_reset();
    printf("Rs. %.2f\t\t", (provident_fund/100*records[i].salary));
    fg_color(COLOR_GREEN | COLOR_BRIGHT);
    printf("Bonus: ");
    color_reset();
    printf("Rs. %.2f\n\n\n\t\t\t\t", bonus);
    fg_color(COLOR_GREEN | COLOR_BRIGHT);
    printf("Total: ");
    color_reset();
    printf("Rs. %.2f",total); 
    fg_color(COLOR_RED | COLOR_BRIGHT);
    printf("\n\n\t---------------------------------------------------------------------");
    color_reset();
    fg_color(COLOR_YELLOW | COLOR_BRIGHT);
    printf("\n\n\tDo you want to deposit ");
    color_reset();
    fg_color(COLOR_GREEN | COLOR_BRIGHT);
    printf("Rs. %.2f", total);
    color_reset();
    fg_color(COLOR_YELLOW | COLOR_BRIGHT);
    printf(" to ");
    color_reset();
    fg_color(COLOR_GREEN | COLOR_BRIGHT);
    printf("%s", records[i].name);
    color_reset();
    fg_color(COLOR_YELLOW | COLOR_BRIGHT);
    printf("'s account? (y/n): ");
    color_reset();
    choice = getch();
    if (choice=='y'){
        FILE *f = fopen("deposit.txt", "a");
        fprintf(f, "%d\n", records[i].id);
        fclose(f);
        fg_color(COLOR_CYAN | COLOR_BRIGHT);
        printf("\n\n\tDone!\n");
        printf("\n\tPress any key to go back to Main Menu...");
        color_reset();
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
    gotoxy(45,5);
    fg_color(COLOR_YELLOW | COLOR_BRIGHT);
    printf("\xB2\xB2\xB2\xB2\xB2\xB2 EMPLOYEE SALARY MANAGEMENT (LOGS)\xB2\xB2\xB2\xB2\xB2\xB2");
    color_reset();
    gotoxy(30,6);
    printf("===================================================================================");
    gotoxy(30,8);
    printf("=======================================================================================");
    gotoxy(30,9);
    fg_color(COLOR_GREEN | COLOR_BRIGHT);
    printf("ID");
    gotoxy(37,9);
    printf("NAME");
    gotoxy(60,9);
    printf("POSITION");
    gotoxy(83,9);
    printf("PHONE NO.");
    gotoxy(106,9);
    printf("SALARY");
    gotoxy(30,10);
    color_reset();
    printf("=======================================================================================");

    for(i=0;i<no_of_records;i++){
        gotoxy(30,(i+11));
        fg_color(COLOR_CYAN | COLOR_BRIGHT);
    printf("%-4d   %-20s   %-20s   %-20s   %-.2f\t",records[i].id,records[i].name,records[i].position,records[i].phoneno,records[i].salary);
        color_reset();
    }

    gotoxy(30,(i+11));
    printf("=======================================================================================\n\n");
    fg_color(COLOR_GREEN | COLOR_BRIGHT);
    printf("\t\t\t\tTOTAL NO. OF EMPLOYEES = %d\n",no_of_records);
    gotoxy(50,(i+15));
    color_reset();
    fg_color(COLOR_YELLOW | COLOR_BRIGHT);
    printf("Press any button to return to the main menu");
    color_reset();
    getch();
    mainMenu();
}