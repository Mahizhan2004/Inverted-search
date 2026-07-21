/*NAME : Mahizhan A
DATE : 2/3/2026
PROJECT TITLE : INVERTED SEARCH
DESCRIPTION : An inverted search project in C involves building a text indexing and searching program that uses an inverted index data structure for efficient information retrieval.
*/

#include<stdio.h>
#include<string.h>
#include"header.h"
#include<stdlib.h>
hash_node arr[27];
int main(int argc, char*argv[])
{
    

    if(argc == 1)     
    {
        printf("Insuffient arguments\n");
    }
    Slist*head=NULL;
    for(int i=1;i<argc;i++)              
    {
        char*p=strstr(argv[i],".");
        if(p==NULL || strcmp(p,".txt")!=0)
        {
            printf("%s is not a .txt file\n",argv[i]);
            continue;
        }
        FILE*fptr=fopen(argv[i],"r");
        if(fptr==NULL)                     
        {
            printf("file is not found\n");
            continue;
        }
        fseek(fptr,0,SEEK_END);
        long size=ftell(fptr);
        if(size == 0)
        {
            printf("%s is empty\n",argv[i]);
            continue;
        }
        fclose(fptr);
        insert_at_last(&head,argv[i]);
    }

    for(int i=0;i<27;i++)
    {
        arr[i].index=i;
        arr[i].link=NULL;
    }
    
        
    
     
    int opt, flag = 0;;
    while(1)             
    {
    printf("1.Creat Database\n2.Search Database\n3.Display database\n4.Update Database\n5.Save Database\n6.Exit\n");
    printf("Enter the option\n");
    scanf("%d",&opt);
    
    switch(opt)
    {
        case 1:
        if(flag == 0)
        {
            create(head,arr);                   
            flag = 1;
        }
        else
        {
            printf("Database already created\n");
        }
            
            break;
        case 2:
        if(flag == 1)
        {
            search(arr);                
        }
        else{
            printf("Database not yeet created.\n");
        }
            break;
        case 3:
            display(arr);              
            break;
        case 4:
            update(&head,arr);         
            break;
        case 5:
            save(arr);             
            break; 
        case 6 : return 0;  
        default:
            printf("Invalid input\n");
            break;  
    }
}

}