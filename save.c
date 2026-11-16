#include "inv.h"

int save_database(hash_t *arr, int size)
{
    char savefile[20];

    printf("Enter the filename to save the database: ");
    scanf("%s", savefile);

    // Check whether the file has .txt extension
    char *ptr = strstr(savefile, ".txt");

    if (ptr == NULL)
    {
        return FAILURE;
    }

    // Open the file in write mode
    FILE *fptr = fopen(savefile, "w");

    if (fptr == NULL)
    {
        return FAILURE;
    }

    // Traverse the hash table
    for (int i = 0; i < size; i++)
    {
        hash_t *temp = &(arr[i]);

        // Skip the index if there is no main node
        if (temp->m_link == NULL)
        {
            continue;
        }
        else
        {
            m_node *temp1 = arr[i].m_link;

            if (temp1 == NULL)
            {
                continue;
            }

            // Save each main node and its subnodes
            while (temp1 != NULL)
            {
                fprintf(fptr, "#%d;%s;%d;",
                        i,
                        temp1->word,
                        temp1->f_count);

                // Traverse the subnode list
                s_node *temp2 = temp1->s_link;

                while (temp2 != NULL)
                {
                    fprintf(fptr,
                            "%s;%d;",
                            temp2->filename,
                            temp2->w_count);

                    temp2 = temp2->s_link;
                }

                fprintf(fptr, "#");

                temp1 = temp1->m_link;
            }
        }
    }

    fclose(fptr);

    return SUCCESS;
}