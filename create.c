#include "inv.h"

int create_database(hash_t *arr, int argc, int size, char *buffer, int index, char *filename, backup **head1)
{
    hash_t *temp = &arr[index];

    if (temp->m_link == NULL)
    {
        // Create main node
        m_node *main = malloc(sizeof(m_node));

        if (main == NULL)
        {
            return FAILURE;
        }

        temp->m_link = main;

        strcpy(main->word, buffer);
        main->f_count = 1;
        main->m_link = NULL;

        // Create sub node for the file
        s_node *sub = malloc(sizeof(s_node));
        if (sub == NULL)
        {
            return FAILURE;
        }
        strcpy(sub->filename, filename);
        sub->w_count = 1;
        sub->s_link = NULL;

        main->s_link = sub;

        return SUCCESS;
    }

    // Main list already exists
    m_node *temp1 = temp->m_link;
    m_node *prev = NULL;

    while (temp1 != NULL)
    {
        // Check whether the word already exists
        if (strcmp(buffer, temp1->word) == 0)
        {
            s_node *temp2 = temp1->s_link;
            s_node *prev1 = NULL;

            // Search for the file in the sub list
            while (temp2 != NULL)
            {
                // Same word and same file found
                if (strcmp(temp2->filename, filename) == 0)
                {
                    temp2->w_count++;
                    return SUCCESS;
                }

                prev1 = temp2;
                temp2 = temp2->s_link;
            }

            // Same word but a different file
            s_node *sub2 = malloc(sizeof(s_node));

            if (sub2 == NULL)
            {
                return FAILURE;
            }

            strcpy(sub2->filename, filename);
            sub2->w_count = 1;
            sub2->s_link = NULL;

            prev1->s_link = sub2;

            // Increase file count for the new file
            temp1->f_count++;

            return SUCCESS;
        }

        prev = temp1;
        temp1 = temp1->m_link;
    }

    // Word not found, so create a new main node
    m_node *main1 = malloc(sizeof(m_node));

    if (main1 == NULL)
    {
        return FAILURE;
    }

    strcpy(main1->word, buffer);
    main1->f_count = 1;
    main1->m_link = NULL;

    // Create sub node for the new word
    s_node *sub = malloc(sizeof(s_node));

    if (sub == NULL)
    {
        free(main1);
        return FAILURE;
    }

    strcpy(sub->filename, filename);
    sub->w_count = 1;
    sub->s_link = NULL;

    main1->s_link = sub;

    prev->m_link = main1;

    return SUCCESS;
}