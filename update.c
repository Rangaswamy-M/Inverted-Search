#include "inv.h"

int update_database(hash_t *arr, int size, backup **head1)
{
    // Ask the user for the saved database file
    char savefile[20];

    printf("Enter the File to load into database: ");
    scanf("%s", savefile);

    // Validate the file extension
    char *ptr = strstr(savefile, ".txt");

    FILE *fp = fopen(savefile, "r");

    if (fp == NULL)
    {
        return FAILURE;
    }

    fseek(fp, 0, SEEK_END);
    long size1 = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    if (size1 == 0)
    {
        printf("File contains no data. Update cannot be performed.\n");
        fclose(fp);
        return FAILURE;
    }
    else
    {
        printf("File opened successfully\n");

        int index;
        char word[20];
        int f_count;
        char filename[20];
        int w_count;

        // Read each saved main node from the file
        while (fscanf(fp, "#%d;%[^;];%d;",
                      &index,
                      word,
                      &f_count) == 3)
        {
            fscanf(fp, "%[^;];%d;", filename, &w_count);

            if (check_duplicate(arr[index].m_link,
                                word,
                                filename,
                                w_count) == FAILURE)
            {
                m_node *temp1 = malloc(sizeof(m_node));

                if (temp1 == NULL)
                {
                    fclose(fp);
                    return FAILURE;
                }

                // Link the main node to the hash table
                strcpy(temp1->word, word);
                temp1->f_count = f_count;
                temp1->s_link = NULL;
                temp1->m_link = arr[index].m_link;
                arr[index].m_link = temp1;

                s_node *temp2 = malloc(sizeof(s_node));

                if (temp2 == NULL)
                {
                    fclose(fp);
                    return FAILURE;
                }

                strcpy(temp2->filename, filename);
                temp2->w_count = w_count;
                temp2->s_link = NULL;

                temp1->s_link = temp2;

                int res = duplicate1(*head1, filename);

                if (res == 0)
                {
                    insert_last1(head1, filename);
                }

                for (int i = 1; i < f_count; i++)
                {
                    fscanf(fp, "%[^;];%d;",
                           filename,
                           &w_count);

                    temp2->s_link = malloc(sizeof(s_node));

                    if (temp2->s_link == NULL)
                    {
                        fclose(fp);
                        return FAILURE;
                    }

                    temp2 = temp2->s_link;

                    strcpy(temp2->filename, filename);
                    temp2->w_count = w_count;
                    temp2->s_link = NULL;

                    res = duplicate1(*head1, filename);

                    if (res == 0)
                    {
                        insert_last1(head1, filename);
                    }
                }
            }
            else
            {
                for (int i = 1; i < f_count; i++)
                {
                    fscanf(fp, "%[^;];%d;",
                           filename,
                           &w_count);

                    check_duplicate(arr[index].m_link,
                                    word,
                                    filename,
                                    w_count);

                    int res = duplicate1(*head1, filename);

                    if (res == 0)
                    {
                        insert_last1(head1, filename);
                    }
                }
            }

            fscanf(fp, "#");
        }

        fclose(fp);
        return SUCCESS;
    }
}