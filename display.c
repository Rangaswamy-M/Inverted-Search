#include "inv.h"

int display_database(hash_t *arr, int size, Slist **head2)
{
    if (*head2 == NULL)
    {
        printf("Hash table is Empty\n");
        return 0;
    }

    // Traverse the hash table
    for (int i = 0; i < size; i++)
    {
        m_node *temp1 = arr[i].m_link;

        if (temp1 == NULL)
        {
            continue;
        }

        // Traverse the main node list
        while (temp1 != NULL)
        {
            printf("%-10d", i);
            printf("%-17s", temp1->word);
            printf("%-15d", temp1->f_count);

            s_node *temp2 = temp1->s_link;

            // Display files and their word counts
            while (temp2 != NULL)
            {
                printf("%-20s", temp2->filename);
                printf("%-10d", temp2->w_count);

                temp2 = temp2->s_link;
            }

            printf("\n");

            temp1 = temp1->m_link;
        }
    }

    return SUCCESS;
}