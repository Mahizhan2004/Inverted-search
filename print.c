#include<stdio.h>
#include"header.h"
#include<string.h>
#include<ctype.h>
#include<stdlib.h>

void display(hash_node*arr)            // display function
{
    printf("ind  file_count  word  word_count  filename\n");
    for(int i=0;i<27;i++)                 //using for loop
    {
        if(arr[i].link !=NULL)
        {
            main_node*main_node_temp=arr[i].link;
            while(main_node_temp !=NULL)                  // using while loop
            {
                sub_node*sub_node_temp=main_node_temp->sublink;
                while(sub_node_temp!= NULL)               // using while loop
                {
                    printf("%d %d %s %d %s\n",arr[i].index,main_node_temp->file_count,main_node_temp->word,sub_node_temp->word_count,sub_node_temp->filename);
                    sub_node_temp=sub_node_temp->link;
                }
                main_node_temp=main_node_temp->link;
            }
        }
    }
}

int save(hash_node*arr)            //functiomn call for save
{
    char save[50];
    printf("ENTER THE FILE TO SAVE\n");
    scanf("%s",save);
    char*fptr=strstr(save,".");
    if(fptr ==NULL || strcmp(fptr,".txt")!=0)            // using if condtion
    {
        printf("ENTER A VALID INPUT\n");
        return FAILURE;
    }
    FILE*qtr=fopen(save,"w");
    if(qtr ==NULL)
    {
        return FAILURE;
    }
    for(int i=0;i<27;i++)              // using for loop
    {
        if(arr[i].link !=NULL)
        {
            main_node*main_node_temp=arr[i].link;
            while(main_node_temp != NULL)             //using while loop
            {
                fprintf(qtr,"#%d;%d;%s;",arr[i].index,main_node_temp->file_count,main_node_temp->word);
                sub_node*sub_node_temp=main_node_temp->sublink;
                while(sub_node_temp !=NULL)
                {
                    fprintf(qtr,"%d;%s;",sub_node_temp->word_count,sub_node_temp->filename);
                    sub_node_temp=sub_node_temp->link;
                }
                fprintf(qtr,"#\n");
                main_node_temp=main_node_temp->link;
            }
            
        }
    }
    fclose(qtr);
    return SUCCESS;
}

int search(hash_node*arr)        // function call for search function
{
    char word[25];
    printf("ENTER THE WORD YOU WANT TO SEARCH\n");
    scanf("%s",word);
    int index=tolower(word[0])-'a';
    if(index<0 || index > 25)
    {
        index=26;
    }
    if(arr[index].link == NULL)
    {
        printf("DATA NOT FOUND\n");
        return FAILURE;
    }
    main_node*main_node_temp=arr[index].link;
    while(main_node_temp!= NULL)                      //using while loop
    {
        if(strcmp(word,main_node_temp->word)==0)     // using if condtion
        {
            printf("word %s is present in %d files\n",main_node_temp->word,main_node_temp->file_count);
            sub_node*sub_node_temp=main_node_temp->sublink;
            while(sub_node_temp !=NULL)         //using while loop
            {
                printf("In %s %d times\n",sub_node_temp->filename,sub_node_temp->word_count);
                sub_node_temp=sub_node_temp->link;
                
            }
            return SUCCESS;
        }
        main_node_temp=main_node_temp->link;
    }

    printf("DATA NOT FOUND\n");
    return FAILURE;
}

int sl_delete_element(Slist **head,char*file_name)        // fucntion call for delete elemnts
{
    if(*head==NULL)// Check if list is empty
    return FAILURE;
    Slist*temp=*head;// Initialize temp to head
    Slist*prev=NULL;// Initialize previous pointer
    while(temp!=NULL)// Traverse the list
    {
        if(strcmp(temp->filename,file_name)==0)// Check if file name matches
        {
            if(prev==NULL)// If node to delete is head
            {
                *head=temp->link;
            }
            else
            prev->link=temp->link;//Bypass current node
            free(temp);//free deleted node
            return SUCCESS;
        }
        else
        {
            prev=temp;// Move prev to current node
            temp=temp->link;// Move temp to next node
        }
    }
    return DATA_NOT_FOUND;
}

int update(Slist**head,hash_node*arr)
{
    char file[30];//to store the filename
    printf("Enter a file to update\n");
    scanf("%s", file);//reading the filename
    char *fptr = strstr(file, ".");
    if (fptr == NULL || strcmp(fptr, ".txt") != 0)//checking if it is a .txt file
    {
        printf("Enter a valid file name\n");
        return FAILURE;
    }
    FILE *qtr = fopen(file, "r");//opening the file in read mode
    if (qtr == NULL)//check if the file opened successfully 
        return FAILURE;
    char line[100];//to store each word read from file
    while (fscanf(qtr, "%s", line) == 1)//read file word by word
    {
        int len = strlen(line);
        if (line[0] == '#' && line[len - 1] == '#')//check if line starts and ends with #
        {
            char *token = strtok(&line[1], ";");//extracts index
            int index = atoi(token);//convert index to integer
            if (index < 0 || index >= 27)//validate index range
                continue;
            token = strtok(NULL, ";");//extract file count
            int filecount = atoi(token);//convert to integer
            token = strtok(NULL, ";");//extract word
            char word[25];
            strcpy(word, token);
            main_node *main = create_main_node(word);//create main node
            if (main == NULL)
                return FAILURE;
            main->file_count = filecount;//assign file count
            if (arr[index].link == NULL)
                arr[index].link = main;//insert main into hash table
            else
            {
                main_node *temp = arr[index].link;//declare a temp to traverse
                while (temp->link != NULL)//traversing to last node
                    temp = temp->link;
                temp->link = main;//attach new main node
            }
            while ((token = strtok(NULL, "#;")) != NULL)// Process sub nodes (word_count and filename)
            {
                int word_count = atoi(token);//extract word count
                token = strtok(NULL, "#;");//extract filename
                if (token == NULL)
                    break;
                char sub_filename[30];
                strcpy(sub_filename, token);
                sl_delete_element(head,sub_filename);//deleting the filenames which are already present
                sub_node *sub = create_sub_node(sub_filename);//creating the sub node
                if (sub == NULL)
                    return FAILURE;
                sub->word_count = word_count;//assign the word count
                sub->link = NULL;
                if (main->sublink == NULL)
                    main->sublink = sub;//insert sub node into main node's sublink
                else
                {
                    sub_node *sub_temp = main->sublink;//declaring the temp
                    while (sub_temp->link != NULL)//traversing to the last sub node
                        sub_temp = sub_temp->link;
                    sub_temp->link = sub;//attach the sub node
                }
            }
        }
    }
    fclose(qtr);//close file
    return SUCCESS;
}

int insert_at_last(Slist **head, char*data)     // function call for insert at last
{
    Slist * new= malloc(sizeof(Slist));    
    strcpy(new->filename,data);
    new->link=NULL;            // using if else condtion
    if(*head==NULL)                  
    {
        *head= new;
        return SUCCESS;
    }
    else                            
    {
        Slist*temp=*head;
        while(temp->link!= NULL)
        {
            temp=temp->link;
        }
        temp->link =new;
    }
}