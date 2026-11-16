#include "inv.h"

int validate(char *str, int argc, char *argv[], Slist **head)
{
    char *ptr = strstr(str, ".txt");
    Slist *temp = *head;

    if (ptr == NULL)
    {
        printf("-----");
        printf("%s ", str);
        printf("File must contain .txt Extension");
        printf("-----\n");
        return 0;
    }

    int res = strcmp(ptr, ".txt");

    // Validate whether the given file has .txt extension
    if (res == 0)
    {
        // Open the file to check whether it exists
        FILE *fp = fopen(str, "r");

        if (fp == NULL)
        {
            printf("-----");
            printf("%s ", str);
            printf("File does not Exist");
            printf("-----\n");
        }
        else
        {
            char ch;

            // Check whether the file contains data
            if (fscanf(fp, "%c", &ch) == 1)
            {
                printf("-----");
                printf("%s ", str);
                printf("File contains data");
                printf("-----\n");

                // Check whether the file is already present in the list
                int res = duplicate(temp, str);

                if (res == 0)
                {
                    // Insert the valid file into the linked list
                    insert_last(head, str);
                }
            }
            else
            {
                printf("-----");
                printf("%s ", str);
                printf("File does not contain data");
                printf("-----\n");
            }

            fclose(fp);
        }
    }
    else
    {
        printf("File is empty\n");
    }

    return 0;
}

int duplicate(Slist *temp, char *str)
{
    // Traverse the list and check for duplicate file names
    while (temp != NULL)
    {
        if (strcmp(temp->file, str) == 0)
        {
            return 1;
        }

        temp = temp->link;
    }

    return 0;
}

int insert_last(Slist **head, char *str)
{
    Slist *new = malloc(sizeof(Slist));
    Slist *temp;

    strcpy(new->file, str);
    new->link = NULL;

    // Insert the first file into an empty list
    if (*head == NULL)
    {
        *head = new;
    }
    else
    {
        temp = *head;

        // Traverse to the last node
        while (temp->link != NULL)
        {
            temp = temp->link;
        }

        temp->link = new;
    }

    return SUCCESS;
}

int find_index(char *buffer)
{
    // Check upper character
    if (buffer[0] >= 'A' && buffer[0] <= 'Z')
    {
        return buffer[0] - 'A';
    }

    // Check lower character
    else if (buffer[0] >= 'a' && buffer[0] <= 'z')
    {
        return buffer[0] - 'a';
    }

    // Check number
    else if (buffer[0] >= '0' && buffer[0] <= '9')
    {
        return 25;
    }

    // Check special character
    else
    {
        return 26;
    }
}

int duplicate1(backup *temp1, char *str)
{
    // Traverse the list and check for duplicate file names
    while (temp1 != NULL)
    {
        if (strcmp(temp1->file, str) == 0)
        {
            return 1;
        }

        temp1 = temp1->link;
    }

    return 0;
}

int insert_last1(backup **head1, char *str)
{
    backup *new = malloc(sizeof(backup));
    backup *temp;

    strcpy(new->file, str);
    new->link = NULL;

    // Insert the first file into an empty list
    if (*head1 == NULL)
    {
        *head1 = new;
    }
    else
    {
        temp = *head1;

        // Traverse to the last node
        while (temp->link != NULL)
        {
            temp = temp->link;
        }

        temp->link = new;
    }

    return SUCCESS;
}

int to_continue()
{
    char ch;

    scanf(" %c", &ch);

    switch (ch)
    {
        case 'Y':
        case 'y':
            return 1;

        case 'N':
        case 'n':
            return 0;

        default:
            printf("Invalid choice\n");
            return 0;
    }
}

int check_duplicate(m_node *head, char *word, char *filename, int w_count)
{
    m_node *temp = head;

    while (temp != NULL)
    {
        if (strcmp(temp->word, word) == 0)
        {
            s_node *stemp = temp->s_link;

            while (stemp != NULL)
            {
                if (strcmp(stemp->filename, filename) == 0)
                {
                    return SUCCESS;
                }

                stemp = stemp->s_link;
            }

            s_node *new = malloc(sizeof(s_node));

            if (new == NULL)
            {
                return FAILURE;
            }

            strcpy(new->filename, filename);
            new->w_count = w_count;
            new->s_link = NULL;

            if (temp->s_link == NULL)
            {
                temp->s_link = new;
            }
            else
            {
                stemp = temp->s_link;

                while (stemp->s_link != NULL)
                {
                    stemp = stemp->s_link;
                }

                stemp->s_link = new;
            }

            temp->f_count++;

            return SUCCESS;
        }

        temp = temp->m_link;
    }

    return FAILURE;
}