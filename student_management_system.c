#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void addstudent();
void viewallstudents();
void searchstudent();
void updatestudent();
void deletestudent();
void createadmin();
int adminlogin();
void changeadminpassword();

struct admin
{
    char username[50];
    char password[50];
};

struct student
{
    int roll;
    char name[50];
    int sub;
    float cgpa;
    float sgpa;
    int sem;
    float marks;
};

// Student Management System
int main()
{
    createadmin();
    printf("----------STUDENT MANAGEMENT SYSTEM----------\n");
    if(!adminlogin())
    {
        printf("Access Denied.\n");
        printf("Exiting the program........\n-----THANK YOU-----\n");
        return 0;
    }
    int choice;
    do
    {
        printf("----------MAIN MENU----------\n");
        printf("1 -> Add Student\n");
        printf("2 -> View All Students\n");
        printf("3 -> Search Student\n");
        printf("4 -> Update Student\n");
        printf("5 -> Delete Student\n");
        printf("6 -> Exit\n");
        printf("7 -> Admin Login\n");
        printf("8 -> Change Admin Password\n");
        printf("--------------------------------\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            adminlogin();
            addstudent();
            break;
        case 2:
            viewallstudents();
            break;
        case 3:
            searchstudent();
            break;
        case 4:
            adminlogin();
            updatestudent();
            break;
        case 5:
            adminlogin();
            deletestudent();
            break;
        case 6:
            printf("Exiting the program........\n-----THANK YOU-----\n");
            break;
        case 7:
            adminlogin();
            break;
        case 8:
            adminlogin();
            changeadminpassword();
            break;          
        default:
            printf("Invalid choice---\n");
            break;
        }
    } while (choice != 6);
    return 0;
}

// Adding Students
void addstudent()
{
    FILE *fp;
    struct student s, temp;
    int count = 0;
    printf("Enter roll no of student\n");
    scanf("%d", &s.roll);
    // to check if duplicate rollno exist or not
    fp = fopen("students.dat", "rb");
    if (fp != NULL)
    {
        while (fread(&temp, sizeof(temp), 1, fp))
        {
            if (temp.roll == s.roll)
            {
                count = 1;
                break;
            }
        }
        fclose(fp);
    }
    if (count)
    {
        printf("Roll no already exist.\n");
        printf("Cannot add student.\n");
        return;
    }
    printf("Enter name of student\n");
    scanf(" %[^\n]", s.name);
    printf("Enter student's semester\n");
    scanf("%d", &s.sem);
    printf("Enter total no of subjects in %d semester\n", s.sem);
    scanf("%d", &s.sub);
    printf("Enter student's total marks out of %d00\n", s.sub);
    scanf("%f", &s.marks);
    printf("Enter the SGPA \n");
    scanf("%f", &s.sgpa);
    // for invalid sgpa and cgpa
    while (s.sgpa < 0 || s.sgpa > 10)
    {
        printf("Invalid SGPA\n");
        printf("Please Enter again\n");
        scanf("%f", &s.sgpa);
    }
    printf("Enter the CGPA\n");
    scanf("%f", &s.cgpa);
    while (s.cgpa < 0 || s.cgpa > 10)
    {
        printf("Invalid CGPA\n");
        printf("Please Enter again\n");
        scanf("%f", &s.cgpa);
    }
    fp = fopen("students.dat", "ab");
    if (fp == NULL)
    {
        printf("ERROR IN FILE\n");
        return;
    }
    fwrite(&s, sizeof(s), 1, fp);
    fclose(fp);
    printf("---Student Added Successfully---\n");
}

// Viewing All Students
void viewallstudents()
{
    FILE *fp = fopen("students.dat", "rb");
    struct student s;

    if (fp == NULL)
    {
        printf("ERROR IN FILE\n");
        return;
    }
    printf("\nROLLNO\tNAME\t\tSEMESTER TOTAL SUBJECT\tTOTAL MARKS\tSGPA\tCGPA\n");
    printf("---------------------------------------------------------------------------\n");
    while (fread(&s, sizeof(s), 1, fp))
    {
        printf(" %d\t %s \t\t %d \t\t %d \t %.2f \t %.2f \t %.2f\n", s.roll, s.name, s.sem, s.sub, s.marks, s.sgpa, s.cgpa);
    }
    fclose(fp);
}

// Searching Student
void searchstudent()
{
    FILE *fp = fopen("students.dat", "rb");
    struct student s;
    int Roll;
    int found = 0;

    if (fp == NULL)
    {
        printf("ERROR IN FILE\n");
        return;
    }
    printf("Enter rollnoof student to be searched\n");
    scanf("%d", &Roll);
    while (fread(&s, sizeof(s), 1, fp))
    {
        if (s.roll == Roll)
        {
            printf("Student found\n");
            printf("ROLL NO\tNAME\tSEMESTER\tTOTAL SUBJECT\tTOTAL MARKS\tSGPA\tCGPA\n");
            printf("%d\t%s\t%d\t%d\t%.2f\t%.2f\t%.2f\n", s.roll, s.name, s.sem, s.sub, s.marks, s.sgpa, s.cgpa);
            found = 1;
            break;
        }
    }
    if (!found)
    {
        printf("Student not fount--\n");
    }
    fclose(fp);
}

// To Update Student
void updatestudent()
{
    FILE *fp = fopen("students.dat", "rb+");
    struct student s;
    int ROLL;
    int found = 0;

    if (fp == NULL)
    {
        printf("ERROR IN FILE\n");
        return;
    }
    printf("Enter rollno of student to be updated\n");
    scanf("%d", &ROLL);
    while (fread(&s, sizeof(s), 1, fp))
    {
        if (s.roll == ROLL)
        {
            printf("Enter new name\n");
            scanf(" %[^\n]", s.name);
            printf("Enter student's new semester\n");
            scanf("%d", &s.sem);
            printf("Enter new total no of subjects in %d semester\n", s.sem);
            scanf("%d", &s.sub);
            printf("Enter student's new total marks out of %d00\n", s.sub);
            scanf("%f", &s.marks);
            printf("Enter new the SGPA \n");
            scanf("%f", &s.sgpa);
            while (s.sgpa < 0 || s.sgpa > 10)
            {
                printf("Invalid SGPA\n");
                printf("Please Enter again\n");
                scanf("%f", &s.sgpa);
            }
            printf("Enter new the CGPA\n");
            scanf("%f", &s.cgpa);
            while (s.cgpa < 0 || s.cgpa > 10)
            {
                printf("Invalid CGPA\n");
                printf("Please Enter again\n");
                scanf("%f", &s.cgpa);
            }
            fseek(fp, -sizeof(s), SEEK_CUR);
            fwrite(&s, sizeof(s), 1, fp);
            found = 1;
            printf("Record Updated Successfully--\n");
            break;
        }
    }
    if (!found)
    {
        printf("Student Not Found\n");
    }
    fclose(fp);
}

// To Delete Student
void deletestudent()
{
    FILE *fp = fopen("students.dat", "rb");
    FILE *temp = fopen("temp.dat", "wb");
    struct student s;
    int roll;
    int found = 0;
    if (fp == NULL || temp == NULL)
    {
        printf("ERROR IN FILE\n");
        return;
    }
    printf("Enter rollno of student which has to delete\n");
    scanf("%d", &roll);
    while (fread(&s, sizeof(s), 1, fp))
    {
        if (s.roll != roll)
        {
            fwrite(&s, sizeof(s), 1, temp);
        }
        else
        {
            found = 1;
        }
    }
    fclose(fp);
    fclose(temp);
    remove("students.dat");
    rename("temp.dat", "students.dat");
    if (found)
    {
        printf("Student deleted successfully--\n");
    }
    else
    {
        printf("Student Not Found--\n");
    }
}
void createadmin()
{
    FILE *fp = fopen("admin.dat", "rb");
    struct admin a;
    if (fp != NULL)
    {
        fclose(fp);
        return;
    }
    fclose(fp);
    fp = fopen("admin.dat", "wb");
    if (fp == NULL)
    {
        printf("ERROR IN FILE\n");
        return;
    }
    printf("Create Admin Account\n");
    printf("Enter username: ");
    scanf(" %[^\n]", a.username);
    printf("Enter password: ");
    scanf(" %[^\n]", a.password);
    fwrite(&a, sizeof(a), 1, fp);
    fclose(fp);
    printf("Admin account created successfully--\n");
}
int adminlogin()
{
    FILE *fp = fopen("admin.dat", "rb");
    struct admin a;
    char username[50];
    char password[50];
    if (fp == NULL)
    {
        printf("ERROR IN FILE\n");
        return 0;
    }
    fread(&a, sizeof(a), 1, fp);
    fclose(fp);
    printf("Admin Login\n");
    printf("Enter username: ");
    scanf(" %[^\n]", username);
    printf("Enter password: ");
    scanf(" %[^\n]", password);
    if (strcmp(username, a.username) == 0 && strcmp(password, a.password) == 0)
    {
        printf("Login Successful--\n");
        return 1;
    }
    else
    {
        printf("Invalid username or password--\n");
        return 0;
    }
}
void changeadminpassword()
{
    FILE *fp = fopen("admin.dat", "rb+");
    struct admin a;
    char newpassword[50];
    if (fp == NULL)
    {
        printf("ERROR IN FILE\n");
        return;
    }
    fread(&a, sizeof(a), 1, fp);
    printf("Enter new password: ");
    scanf(" %[^\n]", newpassword);
    strcpy(a.password, newpassword);
    fseek(fp, 0, SEEK_SET);
    fwrite(&a, sizeof(a), 1, fp);
    fclose(fp);
    printf("Password changed successfully--\n");
}