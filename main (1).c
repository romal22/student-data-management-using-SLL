#include <stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct student{
    int rollno;
    char name[20];
    float marks;
    struct student *next;
}sll;

void add_new_record(sll **);
void delete_a_record(sll **);
void show_the_file(sll **);
void modify_the_record(sll **);
void save(sll *);
void sort_the_list(sll **);
void reverse_the_file(sll **);
void delete_all_record(sll **);
int count_node(sll *);
void sort_name(sll *);
void sort_marks(sll *);
void sort_rollno(sll *);

int main()
{
    sll *hpointer=0;
    char op;
    while(1)
    {
    printf("********student record menu**********\n");
    printf("        a/A:add new record\n");
    printf("        d/D:delete a record\n");
    printf("        s/S:show the file\n");
    printf("        m/M:modify a record\n");
    printf("        v/V:save\n");
    printf("        e/E:exit\n");
    printf("        t/T:sort the list\n");
    printf("        l/L:delete all the records\n");
    printf("        r/R:reverse the file\n");
    printf("\nenter your choice=");
    scanf(" %c",&op);
    
    switch(op)
    {
        case 'a':
        case 'A':add_new_record(&hpointer);
                 break;
        case 'd':
        case 'D':delete_a_record(&hpointer);
                 break;
        case 's':
        case 'S':show_the_file(&hpointer);
                 break;
        case 'm':
        case 'M':modify_the_record(&hpointer);
                 break;
        case 'v':
        case 'V':save(hpointer);
                 break; 
        case 'e':
        case 'E':exit(0);
        case 't':
        case 'T':sort_the_list(&hpointer);
                 break;
        case 'l':
        case 'L':delete_all_record(&hpointer);
                 break;
        case 'r':
        case 'R':reverse_the_file(&hpointer);
                 break;
        default :
                 printf("invalid input\n");
                 break;
    }
    }
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////
void add_new_record(sll **ptr)
{
    sll *new;
    
    int flag=0,m=1,d=count_node(*ptr);
    new=malloc(sizeof(sll));
    printf("****enter the data****\n");
    scanf(" %s %f",new->name,&new->marks);
    int a[d];
    sll *temp=*ptr,*temp1=*ptr;
    flag=0;
    int i=0,j;
    while(i<d)
    {
        a[i]=temp->rollno;
        temp=temp->next;
        i++;
    }
    for (m=1;m<=d+1;m++) {
        flag=0;
        for(i=0;i<d;i++) 
        {
            if(a[i]==m) 
            {
                flag=1;
                break;
            }
        }
        if(flag==0) 
        {
            new->rollno=m;
            break;
        }
    }
    new->next=*ptr;
    *ptr=new;
    
}
///////////////////////////////////////////////////////////////////////////////////
void show_the_file(sll **ptr)
{
    sll *new,*last;
    FILE *fp=fopen("student.txt","r");
    static int flag=0;
    if(fp==0)
    {
        printf("error in file opening\n");
        return;
    }
    if(flag==0)
    {
    while(1)
    {
        new=(sll *)malloc(sizeof(sll));
        if((fscanf(fp,"%d%s%f",&new->rollno,new->name,&new->marks))==EOF)
        {
            free(new);
            break;
        }
        new->next=0;
        if(*ptr==0)
        *ptr=new;
        else
        {
            last=*ptr;
            while(last->next)
            last=last->next;
            last->next=new;
        }
    }
    flag=1;
    }
    sll *temp=*ptr;
    if(temp==0)
    {
        printf("**********************************\n");
        printf("no data found!\n");
        printf("**********************************\n");
        return;
    }
    while(temp)
    {
        printf("%d %s %f\n",temp->rollno,temp->name,temp->marks);
        temp=temp->next;
    }
}
///////////////////////////////////////////////////////////////////////////////////
void delete_a_record(sll **ptr)
{
    if(*ptr == 0)
    {
        printf("**** no data found ****\n");
        return;
    }
    char c[20];
    char op;
    printf("select the choice\nR/r based on rollno\nN/nenter a name to delete\n");
    scanf(" %c",&op);
    int r;
    sll *del=*ptr,*prev;
    switch(op)
    {
        case 'R':
        case 'r':
                printf("ener a roll no to delete the data");
                scanf("%d",&r);
                while(del)
                {
                if((del->rollno)==r)
                {
                    if(del==(*ptr))
                    (*ptr)=del->next;
                    else
                    prev->next=del->next;
                    free(del);
                    return;
                }
                    prev=del;
                    del=del->next;
                }
                break;
        case 'N':
        case 'n':
                printf("enter a name to delete=");
                scanf("%s",c);
                while(del)
                {
                if((strcmp(del->name,c))==0)
                {
                    if(del==(*ptr))
                    (*ptr)=del->next;
                    else
                    prev->next=del->next;
                    free(del);
                    return;
                }
                    prev=del;
                    del=del->next;
                }
                break;
        default : printf("invalid input\n");
    }
}
//////////////////////////////////////////////////////////////////////////////////
void modify_the_record(sll **ptr)
{
    if(*ptr == 0)
    {
        printf("**** no data found ****\n");
        return;
    }
    int n,flag=0,r;
    char c[20],op,d[20];
    float m,k;
    sll *temp=*ptr;
    printf("enter which record to search for modification\nR/r based on rollno\nN/nenter a name\nP/p marks based\n");
    scanf(" %c",&op);
    switch(op)
    {
        case 'R':
        case 'r':printf("enter a rollno\n");
                 scanf("%d",&n);
                 r=count_node(*ptr);
                 if(n>r)
                 {
                    printf("invalid rollno\n");
                    return;
                 }
                printf("enter name and marks wants to modify%d",n);
                scanf("%s %f",d,&k);
    
                while(temp)
                {
                    if((temp->rollno)==n)
                    {
                        strcpy(temp->name,d);
                        temp->marks=k;
                        flag=1;
                        break;
                    }
                    temp=temp->next;
                }
                break;
        
        case 'N':
        case 'n':
                printf("enter a name\n");
                scanf(" %s",c);
                printf("enter name and marks wants to modify on %s",c);
                scanf("%s %f",d,&k);
                while(temp)
                {
                    if((strcmp(temp->name,c))==0)
                    {
                        strcpy(temp->name,d);
                        temp->marks=k;
                        flag=1;
                        break;
                    }
                    temp=temp->next;
                }
                break;
        
        case 'P':
        case 'p':
                printf("enter a marks and rollno\n");
                scanf("%f %d",&m,&n);
                printf("enter name and marks wants to modify on %d",n);
                scanf("%s %f",d,&k);
                while(temp)
                {
                    if( ((temp->marks)==m) && ((temp->rollno)==n))
                    {
                        strcpy(temp->name,d);
                        temp->marks=k;
                        flag=1;
                       break;
                    }
                    temp=temp->next;
                }
                break;
        
        default :
                printf("invalid input\n");
                break;
    
    }
    if(flag==0)
    printf("***no such type of data found!***\n");
    else
    printf("***data modified successfully***\n");
}
//////////////////////////////////////////////////////////////////////////////////
void save(sll *ptr)
{
    
    int n;
    char op;
    printf("1) save and exit 2)exit without saving");
    scanf(" %d",&n);
    if(n==1)
    {
        FILE *fp=fopen("student.txt","w");
        if(fp==0)
        {
        printf("error in file opening\n");
        return;
        }
    
    switch(n)
    {
        case 1:
            printf("n/N sort with name \np/P sort with marks\nr/R sort by rollno\na/A as it is\n");
            scanf(" %c",&op);
            switch(op)
            {
                case 'n':
                case 'N': sort_name(ptr);
                          while(ptr)
                            {
                                fprintf(fp,"%d %s %f\n",ptr->rollno,ptr->name,ptr->marks);
                                ptr=ptr->next;
                            }
                            printf("data saved successfully\n");
                            fclose(fp);
                          break;
                          
                case 'p':
                case 'P':sort_marks(ptr);
                        while(ptr)
                            {
                                fprintf(fp,"%d %s %f\n",ptr->rollno,ptr->name,ptr->marks);
                                ptr=ptr->next;
                            }
                            printf("data saved successfully\n");
                            fclose(fp);
                          break;
                case 'r':
                case 'R':sort_rollno(ptr);
                        while(ptr)
                            {
                                fprintf(fp,"%d %s %f\n",ptr->rollno,ptr->name,ptr->marks);
                                ptr=ptr->next;
                            }
                            printf("data saved successfully\n");
                            fclose(fp);
                          break;
                 case 'a':
                 case 'A':
                          while(ptr)
                          {
                              fprintf(fp,"%d %s %f\n",ptr->rollno,ptr->name,ptr->marks);
                              ptr=ptr->next;
                          }
                          printf("data saved successfully\n");
                          break;
                default :printf("invalid input\n");
            }
            break;
        
        case 2:
        printf("exited without saving\n");
        break;
        
        default:printf("invalid input\n");
    }
    }
}
//////////////////////////////////////////////////////////////////////////////////
void sort_name(sll *ptr)
{
    int i,j,c=count_node(ptr);  
    sll *p1=ptr,*p2,temp;
    for(i=0;i<c-1;i++)
    {
        p2=p1->next;
        for(j=0;j<c-1-i;j++)
        {
            if((strcmp(p1->name,p2->name))>0)
            {
                temp.rollno=p1->rollno;
                strcpy(temp.name,p1->name);
                temp.marks=p1->marks;
                
                p1->rollno=p2->rollno;
                strcpy(p1->name,p2->name);
                p1->marks=p2->marks;
                
                p2->rollno=temp.rollno;
                strcpy(p2->name,temp.name);
                p2->marks=temp.marks;
            }
            p2=p2->next;
        }
        p1=p1->next;
    }
}
//////////////////////////////////////////////////////////////////////////////////
void sort_marks(sll *ptr)
{
    int i,j,c=count_node(ptr);  
    sll *p1=ptr,*p2,temp;
    for(i=0;i<c-1;i++)
    {
        p2=p1->next;
        for(j=0;j<c-1-i;j++)
        {
            if(p1->marks < p2->marks)
            {
                temp.rollno=p1->rollno;
                strcpy(temp.name,p1->name);
                temp.marks=p1->marks;
                
                p1->rollno=p2->rollno;
                strcpy(p1->name,p2->name);
                p1->marks=p2->marks;
                
                p2->rollno=temp.rollno;
                strcpy(p2->name,temp.name);
                p2->marks=temp.marks;
            }
            p2=p2->next;
        }
        p1=p1->next;
    }
}
//////////////////////////////////////////////////////////////////////////////////
void sort_rollno(sll *ptr)
{
    int i,j,c=count_node(ptr);  
    sll *p1=ptr,*p2,temp;
    for(i=0;i<c-1;i++)
    {
        p2=p1->next;
        for(j=0;j<c-1-i;j++)
        {
            if(p1->rollno > p2->rollno)
            {
                temp.rollno=p1->rollno;
                strcpy(temp.name,p1->name);
                temp.marks=p1->marks;
                
                p1->rollno=p2->rollno;
                strcpy(p1->name,p2->name);
                p1->marks=p2->marks;
                
                p2->rollno=temp.rollno;
                strcpy(p2->name,temp.name);
                p2->marks=temp.marks;
            }
            p2=p2->next;
        }
        p1=p1->next;
    }
}
//////////////////////////////////////////////////////////////////////////////////
void sort_the_list(sll **ptr)
{
    char op;
    printf("select the choice\nm/M based on marks\nN/n based on name\n");
    scanf(" %c",&op);
    switch(op)
    {
        case 'm':
        case 'M':
                 sort_marks(*ptr);
                 break;
        case 'n':
        case 'N':
                 sort_name(*ptr);
                 break;
        default :printf("**** invalid input ****\n");
                break;
    }
}
//////////////////////////////////////////////////////////////////////////////////
void delete_all_record(sll **ptr)
{
    if(*ptr==0)
    {
        printf("****no record found****\n");
        return ;
    }
    sll *del=*ptr;
    while(del)
    {
        *ptr=del->next;
        free(del);
        del=*ptr;
    }
    printf("****all nodes deleted****\n");
}
//////////////////////////////////////////////////////////////////////////////////
void reverse_the_file(sll **ptr)
{
    if(*ptr==0)
    {
        printf("****no record found****\n");
        return ;
    }
    int c=count_node(*ptr);
    sll **a,*temp=*ptr;
    if(c>1)
    {
        a=(sll **)malloc(sizeof(sll)*c);
        int i=0;
        while(temp)
        {
            a[i++]=temp;
            temp=temp->next;
        }
        for(i=1;i<c;i++)
            a[i]->next=a[i-1];
        
        a[0]->next=0;
        *ptr=a[c-1];
    }
}
//////////////////////////////////////////////////////////////////////////////////
int count_node(sll *ptr)
{
    int c=0;
    while(ptr)
    {
        c++;
        ptr=ptr->next;
    }
    return c;
}
////////////////////////// THANK YOU  //////////////////////////////////////////