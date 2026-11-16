
/*
    Name:           Malagiri Rangaswamy

    Date:           10-11-2026

    Project Title:  Inverted Search using Hashing in C

    Description:    This project implements an Inverted Search application using the C programming language.
                    The application creates an inverted index of words from multiple text files, allowing efficient
                    searching of words and identifying the files in which they occur along with their word counts.
                    During database creation, the program reads words from the input files, stores them in a hash table,
                    and maintains the corresponding file names and word counts for each word. The application supports
                    searching for a specific word, displaying the complete database, saving the database to a file,
                    and updating the database using a new input file.
                    The program also validates the input files before creating the database and prevents duplicate
                    file entries from being added to the database.

    Key Features:   Implements Inverted Search using a hash table.
                    Supports multiple text files as input.
                    Creates and maintains an inverted index of words.
                    Stores file names and word counts for each word.
                    Supports searching for a specific word in the database.
                    Displays the complete inverted database.
                    Saves the database to a file for future use.
                    Supports updating the database with a new file.
                    Validates input files and checks whether files contain data.
                    Modular implementation using separate source and header files for better readability
                    and maintenance.

    Technologies used: Programming Language: C
                       Concepts: File Handling, Hashing, Structures, Linked Lists, String Manipulation,
                                 Command-Line Arguments, Modular Programming
                       Platform: Linux (GCC Compiler)

*/

#include "inv.h"

int main(int argc, char *argv[])
{
    int size, data, index;
    char opt;

    size = 28;
    int res;

    // Create and initialize the hash table
    hash_t arr[size];
    create_HT(arr, size);

    Slist *head = NULL;
    backup *head1 = NULL;
    Slist *head2 = NULL;

    // Check whether input files are given through command line
    if (argc <= 1)
    {
        printf("--------------------------------------------\n");
        printf("ERROR: ./a.out : INVALID ARGUMENTS\n");
        printf("USAGE:\n");
        printf("Please pass the filename like: ./a.out <filename>\n");
        printf("Example: ./a.out file.txt\n");
        printf("--------------------------------------------\n");
        return 0;
    }
    else
    {
        // Validate the given files and store valid files in linked list
        for (int i = 1; i < argc; i++)
        {
            validate(argv[i], argc, argv, &head);
        }
    }

    printf("Please create the database first before selecting other options.\n");

    while (1)
    {
        printf("\n");
        printf("Select your choice among following options\n");
        printf("1. Create Database\n");
        printf("2. Display Database\n");
        printf("3. Save Database\n");
        printf("4. Search Database\n");
        printf("5. Update Database\n");
        printf("6. Exit\n");
        printf("Enter your choice : ");

        int choice;
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
            {
                head2 = head;

                printf("FILES LIST\n");
                printf("--------------------------------------------------\n");

                // Display the files given through command line
                Slist *temp1 = head;

                while (temp1 != NULL)
                {
                    printf("%s  ", temp1->file);
                    temp1 = temp1->link;
                }

                printf("\n");
                printf("--------------------------------------------------\n");

                Slist *temp = head;

                while (temp != NULL)
                {
                    // Skip the file if it is already loaded in the database
                    int res = duplicate1(head1, temp->file);

                    if (res == 1)
                    {
                        printf("%s File already created/loaded\n", temp->file);

                        temp = temp->link;
                        continue;
                    }

                    FILE *fp = fopen(temp->file, "r");

                    if (fp == NULL)
                    {
                        temp = temp->link;
                        continue;
                    }

                    char buffer[50];

                    // Read each word and insert it into the hash table
                    while (fscanf(fp, "%49s", buffer) == 1)
                    {
                        int index = find_index(buffer);

                        create_database(
                            arr,
                            argc,
                            size,
                            buffer,
                            index,
                            temp->file,
                            &head1
                        );
                    }

                    fclose(fp);

                    // Add the newly created file to the backup list
                    insert_last1(&head1, temp->file);

                    printf("Successful Creation of Database for %s\n",
                           temp->file);

                    temp = temp->link;
                }

                printf("Do you want to continue? Yes(Y/y) No(N/n): ");
                res = to_continue();

                if (res)
                    break;
                else
                    return 0;
            }

            case 2:
            {
                // Display the complete inverted database
                if (head2 != NULL)
                {
                    printf("-----------------------------------------------------------------------------------\n");

                    printf("%-10s %-15s %-15s %-15s %-6s\n",
                           "Index",
                           "Word",
                           "Filecount",
                           "Filename",
                           "Wordcount");

                    printf("-----------------------------------------------------------------------------------\n");
                }

                display_database(arr, size, &head2);

                printf("-----------------------------------------------------------------------------------\n");

                printf("Do you want to continue? Yes(Y/y) No(N/n): ");
                res = to_continue();

                if (res)
                    break;
                else
                    return 0;
            }

            case 3:
            {
                // Save the current database into a file
                int ret = save_database(arr, size);

                if (ret == SUCCESS)
                {
                    printf("Saved Successfully\n");
                }
                else
                {
                    printf("File is not .txt\n");
                    printf("Not Saved try again with .txt file\n");
                }

                printf("Do you want to continue? Yes(Y/y) No(N/n): ");
                res = to_continue();

                if (res)
                    break;
                else
                    return 0;
            }

            case 4:
            {
                // Search for a word in the database
                int res = search_database(arr, size, &head2);

                if (res == 0)
                {
                    printf("Data Not Found\n");
                }
                else if (res == -1)
                {
                    printf("Hash table is empty\n");
                }
                else
                {
                    printf("Searched Successfully\n");
                }

                printf("Do you want to continue? Yes(Y/y) No(N/n): ");
                res = to_continue();

                if (res)
                    break;
                else
                    return 0;
            }

            case 5:
            {
                // Load the saved database and update the current database
                int ret = update_database(arr, size, &head1);

                // Display files currently present in the backup list
                if (ret == SUCCESS)
                {
                    printf("BACKUP FILES LIST\n");
                    printf("-----------------------------------------\n");

                    backup *temp1 = head1;

                    while (temp1 != NULL)
                    {
                        printf("%s  ", temp1->file);
                        temp1 = temp1->link;
                    }

                    printf("\n");
                    printf("-----------------------------------------\n");
                    printf("Updated Successfully\n");
                }
                else
                {
                    printf("Update Failed\n");
                }

                printf("Do you want to continue? Yes(Y/y) No(N/n): ");
                res = to_continue();

                if (res)
                    break;
                else
                    return 0;
            }

            case 6:
            {
                // Exit the program
                printf("Exit\n");
                return SUCCESS;
            }

            default:
            {
                printf("Invalid Choice\n");
            }
        }
    }
}