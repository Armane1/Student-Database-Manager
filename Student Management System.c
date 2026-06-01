#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Students
{
    int ID;
    char Name[50];
    int Age;
    float Grade;
};

void AddStudent()
{
    FILE *fpointer = fopen("shut.txt", "a");

    if (fpointer == NULL)
    {
        printf("Error: Could not open file.\n");
        return;
    }

    struct Students a;

    printf("Enter ID: ");
    scanf("%d", &a.ID);
    getchar();

    printf("Enter student name: ");
    fgets(a.Name, sizeof(a.Name), stdin);
    a.Name[strcspn(a.Name, "\n")] = '\0';

    printf("Enter age: ");
    scanf("%d", &a.Age);

    printf("Enter grade: ");
    scanf("%f", &a.Grade);

    fprintf(fpointer, "%d|%s|%d|%.2f\n", a.ID, a.Name, a.Age, a.Grade);

    fclose(fpointer);

    printf("Student added successfully.\n");
}

void ShowStudent()
{
    FILE *fpointer = fopen("shut.txt", "r");

    if (fpointer == NULL)
    {
        printf("Error: Could not open file.\n");
        return;
    }

    struct Students a;

    printf("\n---------- Students List ----------\n");

    while (fscanf(fpointer, "%d|%49[^|]|%d|%f",
                  &a.ID, a.Name, &a.Age, &a.Grade) == 4)
    {
        printf("ID: %d | Name: %s | Age: %d | Grade: %.2f\n",
               a.ID, a.Name, a.Age, a.Grade);
    }

    fclose(fpointer);
}

void RemoveStudent()
{
    int removeid;

    printf("Enter ID to remove: ");
    scanf("%d", &removeid);

    FILE *ff = fopen("shut.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    if (ff == NULL || temp == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    struct Students a;

    while (fscanf(ff, "%d|%49[^|]|%d|%f",
                  &a.ID, a.Name, &a.Age, &a.Grade) == 4)
    {
        if (a.ID != removeid)
        {
            fprintf(temp, "%d|%s|%d|%.2f\n",
                    a.ID, a.Name, a.Age, a.Grade);
        }
    }

    fclose(ff);
    fclose(temp);

    remove("shut.txt");
    rename("temp.txt", "shut.txt");

    printf("Student removed successfully.\n");
}

void SearchStudent()
{
    int searchID;
    int found = 0;

    printf("Enter ID to search: ");
    scanf("%d", &searchID);

    FILE *fpointer = fopen("shut.txt", "r");

    if (fpointer == NULL)
    {
        printf("Error: Could not open file.\n");
        return;
    }

    struct Students a;

    while (fscanf(fpointer, "%d|%49[^|]|%d|%f",
                  &a.ID, a.Name, &a.Age, &a.Grade) == 4)
    {
        if (a.ID == searchID)
        {
            printf("\nStudent Found:\n");
            printf("ID: %d\n", a.ID);
            printf("Name: %s\n", a.Name);
            printf("Age: %d\n", a.Age);
            printf("Grade: %.2f\n", a.Grade);

            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("Student not found.\n");
    }

    fclose(fpointer);
}

int main()
{
    int choose = 0;

    while (1)
    {
        printf("\n===== Student Management System =====\n");
        printf("1 - Add Student\n");
        printf("2 - Show Students\n");
        printf("3 - Remove Student\n");
        printf("4 - Search Student\n");
        printf("5 - Exit\n");
        printf("Choose: ");

        scanf("%d", &choose);

        if (choose == 1)
            AddStudent();
        else if (choose == 2)
            ShowStudent();
        else if (choose == 3)
            RemoveStudent();
        else if (choose == 4)
            SearchStudent();
        else if (choose == 5)
            exit(0);
        else
            printf("Invalid choice!\n");
    }

    return 0;
}