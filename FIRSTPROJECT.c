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

void Addstudent()
{
    FILE *fpointer = fopen("shut.txt" , "a");

    if(fpointer == NULL)
    {
        printf("The operation has been exited with an error  : \n");
        return;
    }
  
    struct Students a;
    
    printf("Enter The ID : \n");
    scanf("%d" , &a.ID);
    getchar();

    printf("Enter the name of the studetn : \n");
    fgets(a.Name, sizeof(a.Name), stdin);
    a.Name[strcspn(a.Name, "\n")] = '\0';

    printf("Enter The Age : \n");
    scanf("%d" , &a.Age);

    printf("Enter The Grade : \n");
    scanf("%f" , &a.Grade);


    fprintf(fpointer, "%d|%s|%d|%.2f\n" , a.ID ,a.Name, a.Age , a.Grade);

    fclose(fpointer);
}


void ShowStudent()
{
    FILE *fpointer = fopen("shut.txt" , "r");

    if(fpointer == NULL)
    {
        printf("The programm has exited with an error : \n ");
        return;
    }

    struct Students a;

    printf("---------- Students list ---------- \n");
    while(fscanf(fpointer, "%d|%49[^|]|%d|%f",
&a.ID,
a.Name,
&a.Age,
&a.Grade) == 4)
{
    printf("ID : %d | Name : %s | Age : %d | Grade : %.2f\n",
    a.ID,
    a.Name,
    a.Age,
    a.Grade);
}
    fclose(fpointer);
}


void RemoveStudent()
{
    int removeid;

    printf("Enter the Id u want to remove : \n");
    scanf("%d" , &removeid);
    
    FILE *ff = fopen("shut.txt" , "r");
    FILE *x = fopen("uu.txt" , "w");

    struct Students a;

    while (fscanf(ff,
        "%d|%49[^|]|%d|%f",
        &a.ID,
        a.Name,
        &a.Age,
        &a.Grade) == 4)
    {
        if(a.ID != removeid)
        {
            fprintf(x,
            "%d|%s|%d|%.2f\n",
            a.ID,
            a.Name,
            a.Age,
            a.Grade);
        }
    }

    fclose(x);
    fclose(ff);

    remove("shut.txt");
    rename("uu.txt", "shut.txt");
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
        printf("Error opening file\n");
        return;
    }

    struct Students a;

    while (fscanf(fpointer,
    "%d|%49[^|]|%d|%f",
    &a.ID,
    a.Name,
    &a.Age,
    &a.Grade) == 4)
    {
        if (a.ID == searchID)
        {
            printf("Student Found:\n");
            printf("ID : %d\n", a.ID);
            printf("Name : %s\n", a.Name);
            printf("Age : %d\n", a.Age);
            printf("Grade : %.2f\n", a.Grade);
            printf("\n");

            found = 1;
            break;
        }
    }

    if (found == 0)
    {
        printf("Student not found\n");
    }

    fclose(fpointer);
}




int main()
{
   int choose = 0;

    while(1)
    {
    printf("Choose one between those : \n");
    printf("1- Add Student : \n");
    printf("2- Show Students : \n");
    printf("3- Remove Student \n");
    printf("4- Search Student \n");
    printf("5- Exit \n");
    scanf("%d" , &choose);

    if(choose == 1)
    {
        Addstudent();
    }

    else if(choose == 2)
    {
        ShowStudent();
    }

    else if(choose == 3)
    {
        RemoveStudent();
    }

    else if (choose == 4 ){
        SearchStudent();
    }
    
    else if (choose == 5){
        exit(0);
    }

    else{
        printf("U Entered a invalid choice : \n");
    }
}

return 0;

}