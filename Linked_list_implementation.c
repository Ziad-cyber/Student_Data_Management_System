#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void Linked_List(int n);
void dynamic_alloc(int N);


struct DateOf_Birth
{
   int year;
   int month;
   int day;
};

typedef struct student
{
   char Name[50];
   int ID;
   struct DateOf_Birth dateof_birth;
   int Score;
}Student;

typedef struct listnode
{
    struct listnode *next;
    Student entry;
}Listnode;

typedef struct list
{
    Listnode *head;
    Listnode *tail;
    int size;
}List;


void create_student(Student *ps)
{
    char str[50];
    printf (" Name: ");
    fflush(stdin);
    fgets(str,50,stdin);
    strcpy(ps->Name,str);
    printf ("\n ID: ");
    scanf("%d",&(ps->ID) );
    printf ("\n Score: ");
    scanf("%d",&(ps->Score));
    printf ("\n\n    Date of birth \n");
    printf(" Day : ");
    scanf("%d",&(ps->dateof_birth.day));
    printf ("\n Month : ");
    scanf("%d",&(ps->dateof_birth.month));
    printf ("\n Year : ");
    scanf("%d",&(ps->dateof_birth.year));
}

void create_list(List*pl)
{
    pl->size=0;
    pl->head=NULL;
    pl->tail=NULL;
}

void insert_list(int pos , const Student *ps , List *pl )
{
    Listnode *pe= (Listnode*) malloc(sizeof(Listnode));
    strcpy(pe->entry.Name,ps->Name);
    pe->entry.ID=ps->ID;
    pe->entry.Score=ps->Score;
    pe->entry.dateof_birth.day=ps->dateof_birth.day;
    pe->entry.dateof_birth.month=ps->dateof_birth.month;
    pe->entry.dateof_birth.year=ps->dateof_birth.year;
    if (pos==0)
        {
          if(pl->head==NULL)
          {
            pe->next=pl->head;
            pl->head=pe;
            pl->tail=pe;
          }
          else
          {
            pe->next=pl->head;
            pl->head=pe;
          }
        }
    else if(pos=pl->size)
        {
        pl->tail->next=pe;
        pe->next=NULL;
        pl->tail=pe;
        }
    else
        {
            Listnode* p_new=pl->head;
            for(int i=0;i<pos-1;i++)
            {
                p_new=p_new->next;
            }
            pe->next=p_new->next;
            p_new->next=pe;
        }
    pl->size++;
}

int size_of_students(List *pl)
{
     return pl->size;
}

struct student *students;
int n;


int main()
{
    int choice;
    printf("\t\t\t\t\t======================= Welcom! ===========================\nEnter number of students:");
    scanf("%d",&n);

    while(choice!=3)
        {
        printf("\n1-Dynamic allocation\n2-Linked List\n3-terminate program\n\n choice: ");
        scanf("%d",&choice);
        switch (choice)
            {
            case 1:
                {
                dynamic_alloc(n);
                break;
                }
            case 2:
                {
                Linked_List(n);
                break;
                }
            }

        }

    return 0;
}

void Linked_List(int n)
{

    int switch_var;
    Student s;
    List l;
    create_list(&l);
    int pos;
    int num=n;
    for(int i=0;i<num;i++)
        {
        create_student(&s);
        insert_list(i,&s ,&l);
        }
    printf("\nInsertion done\n");
    int sizee= size_of_students(&l);
    printf("\n         size of node is :%d\n",sizeof(Listnode));
    printf("\n         size of data structure is :%d\n",sizeof(Listnode)*sizee);
    while (1)
        {
        printf ("\n1-insert new student");
        printf ("\n2-terminate Linked list");
        scanf("%d",&switch_var);
        switch (switch_var)
            {
            case 1:
                {
                clock_t t;
                create_student(&s);
                printf("enter the position of the student which ranges from [0 : %d]\n",size_of_students(&l));
                printf(" where 0 is at Beginning and %d is at the end",size_of_students(&l));
                scanf("%d",&pos);
                t = clock();
                insert_list(pos,&s ,&l);
                printf("   Insertion Done!\n");
                t = clock() - t;
                double time_taken = ((double)t)/CLOCKS_PER_SEC;
                printf("inserting took %f seconds to execute \n", time_taken);
                break;
                }
            default:
                {
                break;
                }
            }

        if (switch_var==2)
            {
            break;
            }
        }
}


void dynamic_alloc(int n)
{
     students=(struct student*)(malloc(n*sizeof(struct student)));
     for(int i=0;i<n;i++)//Getting the data of students
        {
         printf("\n Name %d: ",i+1);
         fflush(stdin);
         fgets((students + i)->Name,50,stdin);
         printf("\n ID %d:",i+1);
         scanf("%d",&(students + i)->ID) ;
         printf("\n Score %d:",i+1);
         scanf("%d",&(students + i)->Score);
         printf ("\n\n    Date of birth \n");
         printf(" Day %d:",i+1);
         scanf("%d",&(students + i)->dateof_birth.day) ;
         printf("\n Month %d:",i+1);
         scanf("%d",&(students + i)->dateof_birth.month) ;
         printf("\n Year %d:",i+1);
         scanf("%d",&(students + i)->dateof_birth.year) ;
        }
    printf("\nTotal Size of this Data Structure is %d", n*sizeof(students)); //calculating size taken by structure
    clock_t t; //Identifying a variable to store time elapsed in it
    int choice;
    while(choice!=4)
        {
        printf("\n1-Insert From beginning\n2-Insert From middle\n3-Insert From end\n4-Terminate\n\nEnter your choice:");
        scanf("%d",&choice);
        switch (choice)
            {
            case 1:
                {
                 struct student *temp_student;
                 students=(struct student*)realloc(students, (n + 1) * sizeof(struct student));//Increasing the size of array by reallocation
                 temp_student=(struct student*)(malloc(sizeof(struct student))); //its an empty slot to store the data of new student
                 n++;
                 //getting the data of the new student & storing it in the empty slot
                 printf("\n Name: ");
                 fflush(stdin);
                 fgets((temp_student)->Name,50,stdin);
                 printf("\n ID: ");
                 scanf("%d",&(temp_student)->ID) ;
                 printf(" Score: ");
                 scanf("%d",&(temp_student)->Score);
                 printf ("\n\n    Date of birth \n");
                 printf(" Day : ");
                 scanf("%d",&(temp_student)->dateof_birth.day) ;
                 printf("\n Month: ");
                 scanf("%d",&(temp_student)->dateof_birth.month) ;
                 printf("\n Year: ");
                 scanf("%d",&(temp_student)->dateof_birth.year) ;
                 int i;
                 t=clock(); //start the timer to count elapsed period
                 for (i = n-1; i >0; i--) //start to move data by 1 place to empty room for the new data
                    {
                     strcpy((students + i)->Name,(students + i-1)->Name);
                    (students + i)->ID=(students + i-1)->ID;
                    (students + i)->Score=(students + i-1)->Score;
                    (students + i)->dateof_birth.day=(students + i-1)->dateof_birth.day;
                    (students + i)->dateof_birth.month=(students + i-1)->dateof_birth.month;
                    (students + i)->dateof_birth.year=(students + i-1)->dateof_birth.year;
                    }
                    //index will be equal to zero after loop(i=0), so we will copy the data of the new student from the temporary
                    //variable to the empty slot in the structure
                 strcpy((students + i)->Name,(temp_student)->Name);
                (students + i)->ID=(temp_student)->ID;
                (students + i)->Score=(temp_student)->Score;
                (students + i)->dateof_birth.day=(temp_student)->dateof_birth.day;
                (students + i)->dateof_birth.month=(temp_student)->dateof_birth.month;
                (students + i)->dateof_birth.year=(temp_student)->dateof_birth.year;
                 t=clock()-t; //calculating elapsed time by subtracting the start from the end
                 double Time_taken=((double)t)/CLOCKS_PER_SEC; //turning calculated time into seconds and storing it in a float variable
                 printf("\n         Time taken: %f\n\n",Time_taken); //print time
                 break;
                }
            //the same is repeated here but for middle insertion
            case 2:
                {
                struct student *temp_student;
                int index;
                printf("Enter Index you want to insert at:");
                scanf("%d",&index);
                students=(struct student*)realloc(students, (n + 1) * sizeof(struct student));
                temp_student=(struct student*)(malloc(sizeof(struct student)));
                n++;
                if(index<n)
                {
                    printf("\n Name: ");
                    fflush(stdin);
                    fgets((temp_student)->Name,50,stdin);
                    printf("\n ID: ");
                    scanf("%d",&(temp_student)->ID) ;
                    printf("\n Score: ");
                    scanf("%d",&(temp_student)->Score);
                    printf ("\n\n    Date of birth \n");
                    printf(" Day: ");
                    scanf("%d",&(temp_student)->dateof_birth.day) ;
                    printf("\n Month: ");
                    scanf("%d",&(temp_student)->dateof_birth.month) ;
                    printf("\n Year: ");
                    scanf("%d",&(temp_student)->dateof_birth.year) ;
                    int i;
                    t=clock();
                    for (i = n-1; i >index ; i--)
                    {
                        strcpy((students + i)->Name,(students + i-1)->Name);
                        (students + i)->ID=(students + i-1)->ID;
                        (students + i)->Score=(students + i-1)->Score;
                        (students + i)->dateof_birth.day=(students + i-1)->dateof_birth.day;
                        (students + i)->dateof_birth.month=(students + i-1)->dateof_birth.month;
                        (students + i)->dateof_birth.year=(students + i-1)->dateof_birth.year;
                    }
                     strcpy((students + i)->Name,(temp_student)->Name);
                    (students + i)->ID=(temp_student)->ID;
                    (students + i)->Score=(temp_student)->Score;
                    (students + i)->dateof_birth.day=(temp_student)->dateof_birth.day;
                    (students + i)->dateof_birth.month=(temp_student)->dateof_birth.month;
                    (students + i)->dateof_birth.year=(temp_student)->dateof_birth.year;
                     t=clock()-t;
                     double Time_taken=((double)t)/CLOCKS_PER_SEC;
                     printf("\n         Time taken: %f\n\n",Time_taken);
                }
                else
                    {
                        printf("Invalid index!");
                        exit(-1);
                    }
                break;
            }

            case 3:
                {
                struct student *temp_student;
                students=(struct student*)realloc(students, (n + 1) * sizeof(struct student));
                temp_student=(struct student*)(malloc(sizeof(struct student)));
                n++;
                printf("\n Name: ");
                fflush(stdin);
                fgets((temp_student)->Name,50,stdin);
                printf("\n ID: ");
                scanf("%d",&(temp_student)->ID) ;
                printf("\n Score: ");
                scanf("%d",&(temp_student)->Score);
                printf ("\n\n    Date of birth \n");
                printf(" Day: ");
                scanf("%d",&(temp_student)->dateof_birth.day) ;
                printf("\n Month: ");
                scanf("%d",&(temp_student)->dateof_birth.month) ;
                printf("\n Year: ");
                scanf("%d",&(temp_student)->dateof_birth.year) ;
                int i=n-1;
                t=clock();
                strcpy((students + i)->Name,(temp_student)->Name);
                (students + i)->ID=(temp_student)->ID;
                (students + i)->Score=(temp_student)->Score;
                (students + i)->dateof_birth.day=(temp_student)->dateof_birth.day;
                (students + i)->dateof_birth.month=(temp_student)->dateof_birth.month;
                (students + i)->dateof_birth.year=(temp_student)->dateof_birth.year;
                 t=clock()-t;
                 double Time_taken=((double)t)/CLOCKS_PER_SEC;
                 printf("\nTime taken: %f\n\n",Time_taken);
                 break;
                }
            }
        }
}



