#ifndef INV_H
#define INV_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SUCCESS 1
#define FAILURE 0
// Define the node structure for storing backup file names
typedef struct node1
{
    char file[20];
    struct node1 *link;
} backup;
// Define the node structure for storing input file names
typedef struct node
{
    char file[30];
    struct node *link;
} Slist;
// Define the hash table structure used to store words
typedef struct hash
{
    int index;
    struct m_node *m_link;
} hash_t;
// Define the main node structure for storing each unique word
typedef struct m_node
{
    int f_count;
    char word[30];
    struct sub_node *s_link;
    struct m_node *m_link;
} m_node;
// Define the sub node structure for storing file names and word counts
typedef struct sub_node
{
    int w_count;
    char filename[30];
    struct sub_node *s_link;
} s_node;
int validate(char *, int, char *[], Slist **);
int to_continue();
int find_index(char *);
int create_HT(hash_t *, int);
int create_database(hash_t *, int, int, char *, int, char *, backup **);
int display_database(hash_t *, int, Slist **);
int save_database(hash_t *arr, int);
int search_database(hash_t *arr, int, Slist **);
int update_database(hash_t *, int, backup **);
int duplicate(Slist *, char *);
int insert_last(Slist **, char *);
int duplicate1(backup *, char *);
int insert_last1(backup **, char *);
int check_duplicate(m_node *, char *, char *, int);
#endif