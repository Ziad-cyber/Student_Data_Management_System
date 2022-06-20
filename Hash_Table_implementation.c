#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define N 211
#include <math.h>

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
    int size;
}List;

Student arr[N];
List Hash_Table [N];
int Linear=0;

void create_list(List*pl)
{
    pl->size=0;
    pl->head=NULL;
}

void insert_list(const Student *ps , List *pl )
{
    Listnode *pe= (Listnode*) malloc(sizeof(Listnode));
    Listnode *q=pl->head;
    strcpy(pe->entry.Name,ps->Name);
    pe->entry.ID=ps->ID;
    pe->entry.Score=ps->Score;
    pe->entry.dateof_birth.day=ps->dateof_birth.day;
    pe->entry.dateof_birth.month=ps->dateof_birth.month;
    pe->entry.dateof_birth.year=ps->dateof_birth.year;
    if (pl->size==0){
        pe->next=pl->head;
        pl->head=pe;
    }
    else
    {
        for (int i=0 ; i!=pl->size-1 ; i++)
        {
            q=q->next;
        }
        pe->next=q->next;
        q->next=pe;
    }
    pl->size++;
}

void create_student(Student *ps)
{
    char str[50];
    printf ("\n\n name : ");
    fflush(stdin);
    fgets(str,50,stdin);
    strcpy(ps->Name,str);
    printf ("\n ID : ");
    scanf("%d",&(ps->ID) );
    printf ("\n Score : ");
    scanf("%d",&(ps->Score));
    printf ("\n\n    Date of birth \n");
    printf(" Day : ");
    scanf("%d",&(ps->dateof_birth.day));
    printf ("\n Month : ");
    scanf("%d",&(ps->dateof_birth.month));
    printf ("\n Year : ");
    scanf("%d",&(ps->dateof_birth.year));
}

unsigned long pre_hash(Student *ps)
{
    char name[50];
    unsigned long x=0;
    int num=0;
    strcpy(name,ps->Name);
    for (int i=0;i<strlen(name)-1;i++)
        {
        if (name[i]!=32){
            num=name[i]-'a';
            x=x+(num*(pow(2,(i+1))));
        }
    }
    return x;
}
unsigned long pre_hash2(char *ps)
{
    char name[50];
    unsigned long x=0;
    int num=0;
    strcpy(name,ps);
    for (int i=0;i<strlen(name)-1;i++)
        {
        if (name[i]!=32)
        {
            num=name[i]-'a';
            x=x+(num*(pow(2,(i+1))));
        }
    }
    return x;
}

void search_list(List *ph,char *ptr_name,int ID)
{
    char name2[50];
    Listnode *q;
    strcpy(name2,ptr_name);
    long pre_hash=pre_hash2(name2);
    int hashpos = hash_func(pre_hash);
    ph+=hashpos;
    if (ph->size!=0)
    {
        q=ph->head;
        for (int i=0;i<=(ph->size)-1;i++)
        {
            if(ID==q->entry.ID)
            {
                printf("\n\nName :\t%s\n",q->entry.Name);
                printf ("ID :\t%d\n",q->entry.ID);
                printf ("Score :\t%d\n",q->entry.Score);
                printf("Date of birth :%d / %d / %d\t\n\n\n",q->entry.dateof_birth.day,q->entry.dateof_birth.month,q->entry.dateof_birth.year);
                break;
            }
            else if ((q->next)!=NULL)
            {
                q=q->next;
            }
            else
            {
                printf("\n\n    Student not found! \n\n");
            }
        }
    }
    else
    {
        printf("\n\n    Student not found! \n\n");
    }
}

void delete_list(List *ph,char *ptr_name,int ID)
{
    char name2[50];
    Listnode *q;
    Listnode *z;
    strcpy(name2,ptr_name);
    unsigned long pre_hash=pre_hash2(name2);
    int hashpos = hash_func(pre_hash);
    ph+=hashpos;
    if (ph->size!=0)
    {
        q=ph->head;
        z=ph->head;
        for (int i=0;i<=(ph->size)-1;i++)
        {
            if(ID==q->entry.ID)
            {
                if (i==0)
                {
                    ph->head=q->next;
                    free(q);
                    ph->size--;
                    printf("\n\n    Successfully Deleted!\n");
                }
                else
                {
                    z+=(i-1);
                    z->next=q->next;
                    free (q);
                    ph->size--;
                    printf("\n\n    Successfully Deleted!\n");
                }
                break;
            }
            else if ((q->next)!=NULL){
                q=q->next;
            }
            else
            {
                printf("\n\n    Student not found! \n\n");
            }
        }
    }
    else
    {
        printf("\n\n    Student not found! \n\n");
    }
}

int size_of_students(List *ph)
{
    int student_size=0;
    for (int i=0;i<N;i++)
    {
        student_size+= ph->size;
        printf("\n at arr[%d] the size is :%d \n\n",i,ph->size);
        ph++;
    }
    return student_size;
}

void init_hashtable()
{
    for (int i=0;i<=N;i++)
        {
            create_list(&Hash_Table[i]);
        }
}

void pre_insert_list()
{
    Student s;
    unsigned long prehash;
    int hash_pos;
    create_student(&s);
    prehash=pre_hash(&s);
    hash_pos = hash_func(prehash);
    printf("\n Inserted at index: %d\n\n",hash_pos);
    insert_list(&s,&Hash_Table[hash_pos]);
    printf("\n\n     Successfully inserted \n");
}

void pre_search_list()
{
    char std_name[50];
    int std_ID;
    printf("\n Name: ");
    fflush(stdin);
    fgets(std_name,50,stdin);
    fflush(stdin);
    printf("\n ID: ");
    scanf("%d",&std_ID);
    fflush(stdin);
    search_list(Hash_Table,std_name,std_ID);
}

void pre_delete_list()
{
    char std_name[50];
    int std_ID;
    printf("\n Name: ");
    fflush(stdin);
    fgets(std_name,50,stdin);
    fflush(stdin);
    printf("\n ID: ");
    scanf("%d",&std_ID);
    fflush(stdin);
    delete_list(Hash_Table,std_name,std_ID);
}

void iterated_insertion()
{
    int num;
    printf("Insert the number of students you wish to insert: ");
    scanf("%d",&num);
    for(int i=0;i<num;i++)
    {
        pre_insert_list();
    }
}




int hash_func (unsigned long  x)
{
    int value ;
    value=((((20 *x)+(500)) % 7919) % N);
    return value;
}

int Hash_function(int day ,int month,int year)
{
    int index=0;
   return index=(day+month+year)%N;
}

int search_student(int i,Student *s)
{
    if(Linear)
        Linear=0;
        for(;i<N;i++)
            if(s->ID==arr[i].ID)
                if((s->dateof_birth.day==arr[i].dateof_birth.day) && (s->dateof_birth.month==arr[i].dateof_birth.month) && (s->dateof_birth.year==arr[i].dateof_birth.year))
                      return i;
    else
    {
        int index=i;
        for(int j=0;j<N;j++)
        {
            index=i+j*j;
            if(index<N)
               if(s->ID==arr[index].ID)
                    if((s->dateof_birth.day==arr[index].dateof_birth.day)&&(s->dateof_birth.month==arr[index].dateof_birth.month)&&(s->dateof_birth.year==arr[index].dateof_birth.year))
                      return index;
        }

    }

    return -1;
}

void Linearmultiple_insertions()
{
    int num;
    printf("Insert the number of students you wish to insert: ");
    scanf("%d",&num);
    for(int i=0;i<num;i++)
    {
        Linearlyinsert_student();
    }
}

void Quadraticmultiple_insertions()
{
    int num;
    printf("Insert the number of students you wish to insert: ");
    scanf("%d",&num);
    for(int i=0;i<num;i++)
    {
        Quadraticlyinsert_student();
    }
}


void Linearlyinsert_student()
{
    Student s;
    create_student(&s);
    int index=Hash_function(s.dateof_birth.day,s.dateof_birth.month,s.dateof_birth.year);
    if (arr[index].dateof_birth.day ==0)
    {
        strcpy(arr[index].Name,s.Name);
        arr[index].ID=s.ID;
        arr[index].Score=s.Score;
        arr[index].dateof_birth.day=s.dateof_birth.day;
        arr[index].dateof_birth.month=s.dateof_birth.month;
        arr[index].dateof_birth.year=s.dateof_birth.year;
        printf("\n\n     Successfully inserted \n");
        printf(" Inserted at index: %d\n\n",index);
    }
    else
    {
        int i=index;
        for(;i<N;i++)
        {
            if (arr[i].dateof_birth.day ==0)
            {
                strcpy(arr[i].Name,s.Name);
                arr[i].ID=s.ID;
                arr[i].Score=s.Score;
                arr[i].dateof_birth.day=s.dateof_birth.day;
                arr[i].dateof_birth.month=s.dateof_birth.month;
                arr[i].dateof_birth.year=s.dateof_birth.year;
                printf("\n\n      Successfully inserted \n");
                printf(" Inserted at index: %d\n\n",i);
                break;
            }
        }
        if(i==N)
        {
            printf("\n\n    Insertion failed! \n\n");
        }
    }
}

void Quadraticlyinsert_student()
{
    Student s;
    create_student(&s);
    int index=Hash_function(s.dateof_birth.day,s.dateof_birth.month,s.dateof_birth.year);
    if (arr[index].dateof_birth.day ==0)
    {
        strcpy(arr[index].Name,s.Name);
        arr[index].ID=s.ID;
        arr[index].Score=s.Score;
        arr[index].dateof_birth.day=s.dateof_birth.day;
        arr[index].dateof_birth.month=s.dateof_birth.month;
        arr[index].dateof_birth.year=s.dateof_birth.year;
        printf("\n\n  Successfully inserted \n");
        printf(" Inserted at index: %d",index);
    }
    else
    {
        int i;
        for(int j=1;j<N;j++)
        {
            i=index+j*j;
            if(i<N)
            {
                if (arr[i].dateof_birth.day ==0)
                {
                    strcpy(arr[i].Name,s.Name);
                    arr[i].ID=s.ID;
                    arr[i].Score=s.Score;
                    arr[i].dateof_birth.day=s.dateof_birth.day;
                    arr[i].dateof_birth.month=s.dateof_birth.month;
                    arr[i].dateof_birth.year=s.dateof_birth.year;
                    printf("\n\n  successfully inserted \n");
                    printf(" Inserted at index: %d",index);
                    break;
                }
            }
            else
            {
                printf("\n\n    Insertion failed! \n\n");
                break;
            }
        }
    }
}

void Display(int location)
{
    printf("\n\tName\n\t%s\n",arr[location].Name);
    printf("\tID\tscore\tDate_of_birth\n\t%d\t%d",arr[location].ID,arr[location].Score);
    printf("\t%d / %d / %d\n", arr[location].dateof_birth.day,arr[location].dateof_birth.month,arr[location].dateof_birth.year);
}

void Linear_Probing()
{
    int choice=0;
    printf("\n\n          Total structure size: %d\n\n",sizeof(Student)*N);
    while (1)
    {
        printf("\n1-insert new student\n2-delete a student\n3-search for a student\n4-terminate linear probing\n\n\n");
        printf("choice: ");
        fflush(stdin);
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:
                {
                    Linearmultiple_insertions();
                    break;
                }
            case 2:
                {
                    Student s;
                    printf ("\n ID : ");
                    scanf("%d",&(s.ID) );
                    printf ("\n\n    Date of birth \n");
                    printf(" Day : ");
                    scanf("%d",&(s.dateof_birth.day));
                    printf ("\n Month : ");
                    scanf("%d",&(s.dateof_birth.month));
                    printf ("\n Year : ");
                    scanf("%d",&(s.dateof_birth.year));
                    int index=Hash_function(s.dateof_birth.day,s.dateof_birth.month,s.dateof_birth.year);
                    Linear=1;
                    int location = search_student(index,&s);
                    if(location==-1)
                        printf("\n\n    Student not found! \n\n");
                    else
                    {
                        arr[location].dateof_birth.day=0;
                        printf("\n     Student deleted.\n\n");
                    }
                    break;
                }
            case 3:
                {
                    Student s;
                    printf ("\n ID : ");
                    scanf("%d",&(s.ID) );
                    printf ("\n\n    Date of birth \n");
                    printf(" Day : ");
                    scanf("%d",&(s.dateof_birth.day));
                    printf ("\n Month : ");
                    scanf("%d",&(s.dateof_birth.month));
                    printf ("\n Year : ");
                    scanf("%d",&(s.dateof_birth.year));
                    int index=Hash_function(s.dateof_birth.day,s.dateof_birth.month,s.dateof_birth.year);
                    Linear=1;
                    int location = search_student(index,&s);
                    if(location==-1)
                        printf("\n\n    Student not found!\n\n");
                    else
                        Display(location);
                    break;
                }
            case 4:
                break;
            default:
                printf("\n\n     invalid choice!\n\n please choose from the options.\n\n");
        }
        if (choice==4)
            break;
    }


}

void Quadratic_Probing()
{
    int choice=0;
    printf("\n\n          Total structure size: %d\n\n",sizeof(Student)*N);
    while (1)
    {
        printf("\n1-insert new student\n2-delete a student\n3-search for a student\n4-terminate Quadratic probing\n\n\n");
        printf("choice: ");
        fflush(stdin);
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:
                {
                    Quadraticmultiple_insertions();
                    break;
                }
            case 2:
                {
                    Student s;
                    printf ("\n ID : ");
                    scanf("%d",&(s.ID) );
                    printf ("\n\n    Date of birth \n");
                    printf(" Day : ");
                    scanf("%d",&(s.dateof_birth.day));
                    printf ("\n Month : ");
                    scanf("%d",&(s.dateof_birth.month));
                    printf ("\n Year : ");
                    scanf("%d",&(s.dateof_birth.year));
                    int index=Hash_function(s.dateof_birth.day,s.dateof_birth.month,s.dateof_birth.year);
                    int location = search_student(index,&s);
                    if(location==-1)
                        printf("\n\n    Student not found! \n\n");
                    else
                    {
                        arr[location].dateof_birth.day=0;
                        printf("\n     Student deleted.\n\n");
                    }
                    break;
                }
            case 3:
                {
                    Student s;
                    printf ("\n ID : ");
                    scanf("%d",&(s.ID) );
                    printf ("\n\n    Date of birth \n");
                    printf(" Day : ");
                    scanf("%d",&(s.dateof_birth.day));
                    printf ("\n Month : ");
                    scanf("%d",&(s.dateof_birth.month));
                    printf ("\n Year : ");
                    scanf("%d",&(s.dateof_birth.year));
                    int index=Hash_function(s.dateof_birth.day,s.dateof_birth.month,s.dateof_birth.year);
                    int location = search_student(index,&s);
                    if(location==-1)
                        printf("\n\n    Student not found!\n\n");
                    else
                        Display(location);
                    break;
                }
            case 4:
                break;
            default:
                printf("\n\n     invalid choice!\n\n please choose from the options.\n\n");
        }
        if (choice==4)
            break;
    }
}

void init()
{
    for(int i=0;i<N;i++)
        arr[i].dateof_birth.day=0;
}


void chained_hashing()
{
    int switch_var;
    init_hashtable();
    while (1)
    {
        printf ("1-insert new student\n");
        printf ("2-search for a student\n");
        printf ("3-delete a student\n");
        printf ("4-terminate chained hashing\n");
        printf ("\nchoice: ");
        scanf("%d",&switch_var);
        switch (switch_var)
        {
            case 1:
                iterated_insertion();
                break;
            case 2:
                pre_search_list();
                break;
            case 3:
                pre_delete_list();
                break;
            case 4:
                break;
            default:
                printf("\n\n     invalid choice!\n\n please choose from the options.\n\n");
                break;
        }
        if (switch_var==4)
        {
            return;
        }
   }

}

void closed_hashing()
{
    while(1)
    {
        int choice=0;
        printf("\n1-linear propping\n2-quadratic propping\n3-terminate closed hashing\n\n");
        printf("choice: ");
        fflush(stdin);
        scanf(" %d",&choice);
        switch(choice)
        {
            case 1:
                {
                    Linear_Probing();
                    break;
                }
            case 2:
                {
                    Quadratic_Probing();
                    break;
                }
            case 3:
                break;
            default:
                printf("\n\n     invalid choice!\n\n please choose from the options\n\n");
        }
        if(choice==3)
          return ;
    }
}


int main()
{
    init();//a function in case compiler doesn't initialize global variable by zero
    printf("======================= Welcom! ===========================\n\n");
    printf("choose the hashing you want\n");
    while(1)
    {
        int choice=0;
        printf ("1-chained hashing\n");
        printf ("2-closed hashing\n");
        printf ("3-terminate program\n\n");
        printf("choice: ");
        fflush(stdin);
        scanf(" %d",&choice);
        switch(choice)
        {
            case 1:
                chained_hashing();
                break;
            case 2:
                closed_hashing();
                break;
            case 3:
                break;
            default:
                printf("\n\n     invalid choice!\n\n please choose from the options\n\n");
                break;
        }
        if(choice==3)
          return 0;

    }
    return 0;
}