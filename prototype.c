#include<time.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>
// I changed here 
// and ankit changed here xD
// Sulav commit here
// nishit ko comment
//aba chai push garna aayo
//again push
//last push
float interest_rate=0.06;
void delay(){
    int i,j;
    for(i=0;i<31567;i++){
    for(j=0;j<31567;j++){}
    }
}
void edit();
void details();
void deposit(int);
typedef struct
{
    char name[50];
    int id;
    int age;
    float salary;
}employee;
typedef struct
{
    char name[20];
    int id,age;
    float salary,interest;
}detail;

detail a[20];

int main(){
    FILE *p;
    int cp,usr_choice;
    char name1[20],name[20] = "admin";
    char password1[10],password[10]="admin";
    p = fopen("main.txt","r");
    int i=0,len;
    while(!feof(p)){
        fgets(a[i].name,20,p);
        fscanf(p,"\n%d",&a[i].id);
        fscanf(p,"\n%d",&a[i].age);
        fscanf(p,"\n%f",&a[i].salary);
        fscanf(p,"\n%f\n",&a[i].interest);
        i++; 
    }
    len = i;
    system("cls");
    printf("\n\n\t\t\t\t\t\t|||||||| Salary Management ||||||||\n\n");
    printf("\t\t\t\t\tThis is admin panel of salary management system.\n \t\t\tYou need to login to view the details of the employees, edit the details, provde salary to the desired employee.\n\n");
    printf("\n\n\n\n\t\t\t\t\t\tEnter Username: ");
    scanf("%s",name1);
    printf("\n\t\t\t\t\t\tEnter your password: ");
    scanf("%s",password1);
    cp = strcmp(name,name1);
    if(cp==0){
        printf("\nProcessing");
        delay();printf(".");
        delay();printf(".");
        delay();printf(".");
        delay();printf(".");
        system("cls");
        printf("\n\tUsername and Password Bypassed\n\n\n");
        here:
        printf("\t\t\t\t\t\t1.View Employee Details\n\t\t\t\t\t\t2.Edit the system\n\t\t\t\t\t\t3.Deposit Salary to a employee\n\t\t\t\t\t\t4.Deduct the Liabilities lost from Employee's account\n\t\t\t\t\t\t5.Provide Bonus to the employee\n\n\t\t\t\t\t\tEnter your choice here:");
        scanf("%d",&usr_choice);
        switch (usr_choice)
        {
        case 1:
            details();
            break;
        case 2:
            edit();
            break;
        case 3:
            deposit(len);
            break;
        case 4:
            // deduct();
            break;
        case 5:
            // bonus();
            break;
        default:
            printf("\n\nInvalid Choice.\n\n");
            goto here;
            break;
        }
    }
    else{
        printf("\nIncorrect Username or password");
        printf("\n\nEnter any key to go to main menu.");
        getch();
        main();
    }

    return 0;
}
void edit(){
    FILE *p;
    float interest;
    employee *emp;
    emp = (employee *)malloc(20*sizeof(employee));
    int usr_choice;
    char temp;
    here:
    printf("\n\t\t\t\t\t\t1.Add an employee\n\t\t\t\t\t\t2.Remove an employee\n\t\t\t\t\t\t3.Edit the system details\n\nEnter your choice here:");
    scanf("%d",&usr_choice);
    system("cls");
    switch (usr_choice)
    {
    case 1:
        printf("\nProcessing");
        delay();printf(".");
        delay();printf(".");
        delay();printf(".");
        delay();printf(".");
        p = fopen("main.txt","a");
        printf("Enter the name of employee:");
        scanf("%c",&temp); 
        scanf("%[^\n]",emp[0].name);
        printf("Enter the employee's id:");
        scanf("%d",&emp[0].id);
        printf("Enter the employee's age:");
        scanf("%d",&emp[0].age);
        printf("Enter the employee's salary:");
        scanf("%f",&emp[0].salary);
        interest = interest_rate * emp->salary;
        fputs(emp->name,p);
        fprintf(p,"\n%d",emp->id);
        fprintf(p,"\n%d",emp->age);
        fprintf(p,"\n%f",emp->salary);
        fprintf(p,"\n%f",interest);
        fclose(p);
        printf("Enter any key to go to main menu.");
        getch();
        main();
        break;
    case 2:
        /* code */
        break;
    case 3:
        /* code */
        break;
    default:
    printf("Invalid Choice");
    goto here;
        break;
    }
}
void details(){
    int id,ch;
    system("cls");
    printf("\nInput the id no of the employee:");
    scanf("%d",&ch);
    for(int i=0;i<20;i++){
        if(ch == a[i].id){
            id = i;
            }
    }
    printf("\nProcessing");
    delay();printf(".");
    delay();printf(".");  
    delay();printf(".");
    delay();printf(".\n\n");

    printf("\t\t\t\t\t\tName:%s\t\t\t\t\t\tID:%d\n\t\t\t\t\t\tAge:%d\n\t\t\t\t\t\tSalary:$%.2f\n\t\t\t\t\t\tInterest Acquired:%.2f",a[id].name,a[id].id,a[id].age,a[id].salary,a[id].interest);
    printf("\nEnter any key to go to main menu. ");
    getch();
    main();
}
void deposit(int len){
    int id_no,j,res;
    FILE *fp,*fp1,*fp2;
    float salary,deposited_amt;
    here:
    system("cls");
    printf("\t\t\t\t\t\tHere you can provide the salary to specific employee.\n\n");
    printf("Enter the Id no of the employee: ");
    scanf("%d",&j);
    for(int i=0;i<20;i++){
        if(j == a[i].id){
            id_no = i;
            }
    }
    printf("\nProcessing");
    delay();printf(".");
    delay();printf(".");  
    delay();printf(".");
    delay();printf(".\n\n");
    printf("The name of the employee is %s\n",a[id_no].name);
    printf("\nAre you sure you want to deposit to %s\n1. Yes\n2. No\n");
    scanf("%d",&res);
    switch (res)
    {
    case 1:
        salary = a[id_no].salary+a[id_no].interest;
        printf("\n\t\t\t\t\t\tName: %s\n\t\t\t\t\t\tCurrent Balance with interest: $%f",a[id_no].name,salary);
        printf("\nEnter the amount you want to deposit: ");
        scanf("%f",&deposited_amt);
        a[id_no].salary = salary+deposited_amt;
        a[id_no].interest = interest_rate * a[id_no].salary;
        printf("\nProcessing");
        delay();printf(".");
        delay();printf(".");  
        delay();printf(".");
        delay();printf(".\n\n");
        printf("\n\t\t\t\t\t\tName: %s\n\t\t\t\t\t\tUpdated Balance: $%f",a[id_no].name,a[id_no].salary);
        fp1 = fopen("main.txt","r");
        fflush(fp1);
        fclose(fp1);
        fp = fopen("main.txt","w");
        int i=0;
        for(i=0;i<len;i++){
            fputs(a[i].name,fp);
            fprintf(fp,"%d",a[i].id);
            fprintf(fp,"\n%d",a[i].age);
            fprintf(fp,"\n%f",a[i].salary);
            fprintf(fp,"\n%f\n",a[i].interest);
        }
        fclose(fp);
        printf("\n\n\t\t\t\t\t\tPress any key to go to main menu");
        getch();
        main();        
        break;
    case 2:
        goto here;
        break;
    default:
        printf("Invalid input.");
        goto here;
        break;
    }
}