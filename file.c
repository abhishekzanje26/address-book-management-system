#include <stdio.h>
#include "file.h"

// Save contacts to file
void saveContactsToFile(AddressBook *addressBook)
{
    FILE *fp = fopen("telephone.csv", "w");

    if(fp == NULL)
    {
        printf("File opening failed\n");
        return;
    }

    for(int i = 0; i < addressBook->contactCount; i++)
    {
        fprintf(fp, "%s,%s,%s\n", addressBook->contacts[i].name,addressBook->contacts[i].phone, addressBook->contacts[i].email);
    }

    fclose(fp);
}

// Load contacts from file
void loadContactsFromFile(AddressBook *addressBook)
{
    FILE *fp = fopen("telephone.csv", "r");

    if(fp == NULL)
    {
        printf("File opening failed\n");
        return;
    }

    while(fscanf(fp, " %[^,],%[^,],%[^\n]",
                 addressBook->contacts[addressBook->contactCount].name,
                 addressBook->contacts[addressBook->contactCount].phone,
                 addressBook->contacts[addressBook->contactCount].email) == 3)
    {
        addressBook->contactCount++;
    }

    fclose(fp);
}