#include "inv.h"

int create_HT(hash_t *arr, int size)
{
    // Initialize all hash table entries
    for (int i = 0; i < size; i++)
    {
        arr[i].index = i;
        arr[i].m_link = NULL;
    }

    return SUCCESS;
}