#ifndef HEADER_H
#define HEADER_H
#include<stdio.h>

#define SUCCESS 1
#define FAILURE 0
#define DATA_NOT_FOUND -1

typedef struct filenode
{
	char filename[50];
	struct filenode *link;
}Slist;

typedef struct subnode
{
    int word_count;
    char filename[50];
    struct subnode*link;
}sub_node;

typedef struct mainnode
{
    int file_count;
    char word[50];
    sub_node* sublink;
    struct mainnode*link;
}main_node;

typedef struct hashnode
{
    int index;
    main_node* link;
}hash_node;

int insert_at_last(Slist**head,char*data);
void print_list(hash_node*arr);
int create(Slist*head,hash_node*arr);
main_node*create_main_node(char*word);
sub_node*create_sub_node(char*filename);
void display(hash_node*arr);
int save(hash_node*arr);
int search(hash_node*arr);
int sl_delete_element(Slist **head,char*file_name);
int update(Slist**head,hash_node*arr);
#endif