#include "inv.h"

int search_database(hash_t *arr, int size, Slist **head2)
{
    if (*head2 == NULL)
    {
        return -1;
    }

    m_node *temp1 = NULL;

    printf("Enter Data To Search: ");

    char buffer[50];
    scanf("%s", buffer);

    // Find the hash index for the search word
    char ch = buffer[0];
    int index = find_index(&ch);

    hash_t *temp = &(arr[index]);

    // Check whether the hash index contains any data
    if (temp->m_link == NULL)
    {
        return FAILURE;
    }
    else
    {
        temp1 = temp->m_link;

        // Search the word in the main node list
        while (temp1 != NULL)
        {
            if (strcmp(temp1->word, buffer) == 0)
            {
                // Display the search result
                printf("-----------------------------------------------------------------------------------\n");

                printf("%-10s %-15s %-15s %-15s %-6s\n",
                       "Index",
                       "Word",
                       "Filecount",
                       "Filename",
                       "Wordcount");

                printf("-----------------------------------------------------------------------------------\n");

                printf("%-10d", index);
                printf("%-17s", temp1->word);
                printf("%-15d", temp1->f_count);

                temp1 = temp->m_link;

                if (temp1 != NULL)
                {
                    // Display the files containing the searched word
                    s_node *temp2 = temp1->s_link;

                    while (temp2 != NULL)
                    {
                        printf("%-20s", temp2->filename);
                        printf("%-10d", temp2->w_count);

                        temp2 = temp2->s_link;
                    }
                }

                printf("\n");
                printf("-----------------------------------------------------------------------------------\n");

                return SUCCESS;
            }

            temp1 = temp1->m_link;
        }
    }

    return FAILURE;
}