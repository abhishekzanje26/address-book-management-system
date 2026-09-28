#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
void listContacts(AddressBook *addressBook) 
{
    // Sort contacts based on the chosen criteria
    Contact temp;
    for (int i=0; i<addressBook->contactCount-1; i++){
        for (int j = i+1; j<addressBook->contactCount; j++){
            if (strcmp(addressBook->contacts[i].name,addressBook->contacts[j].name)>0){
             temp = addressBook->contacts[i]; 
             addressBook->contacts[i]=addressBook->contacts[j];
             addressBook->contacts[j]=temp;
            }
        }
    }
    for (int i=0; i<addressBook->contactCount;i++){
         printf("%s\t%s\t%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone, addressBook->contacts[i].email);
    }
}
void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    
    loadContactsFromFile(addressBook);
    printf("Total contacts: %d\n", addressBook->contactCount);
}
void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}


void createContact(AddressBook *addressBook)
{
	/* Define the logic to create a Contacts */
    int i, j, chance;
    int flag;

    i = addressBook->contactCount;

    if(i >= MAX_CONTACTS)
    {
        printf("Address Book is full\n");
        return;
    }

    /* Name */
for(chance = 1; chance <= 3; chance++){
    flag = 1;
    printf("Enter Name: ");
    scanf(" %[^\n]", addressBook->contacts[i].name);
    if(strlen(addressBook->contacts[i].name) < 4){
        printf("Name must contain at least 4 characters\n");
        flag = 0;
    }
    for(j = 0; addressBook->contacts[i].name[j] != '\0'; j++){
        if(!((addressBook->contacts[i].name[j] >= 'A' && addressBook->contacts[i].name[j] <= 'Z') ||
             (addressBook->contacts[i].name[j] >= 'a' && addressBook->contacts[i].name[j] <= 'z')||(addressBook->contacts[i].name[j] == ' '))){
            printf("Name should contain only alphabets\n");
            flag = 0;
            break;
        }
    }
    if(flag == 1)
        break;
}
if(flag == 0){
    return;
}
    /* Phone */
    
for(chance = 1; chance <= 3; chance++){
    flag = 1;
    printf("Enter Phone Number: ");
    scanf("%s", addressBook->contacts[i].phone);
    if(strlen(addressBook->contacts[i].phone) != 10){
        printf("Phone number must contain exactly 10 digits\n");
        flag = 0;
    }
    if(addressBook->contacts[i].phone[0] < '6' ||addressBook->contacts[i].phone[0] > '9'){
        printf("First digit must be between 6 and 9\n");
        flag = 0;
    }
    for(j = 0; addressBook->contacts[i].phone[j] != '\0'; j++){
        if(addressBook->contacts[i].phone[j] < '0' ||addressBook->contacts[i].phone[j] > '9'){
            printf("Phone number should contain only digits\n");
            flag = 0;
            break;
        }
    }
    for(j = 0; j < addressBook->contactCount; j++){
        if(strcmp(addressBook->contacts[j].phone,addressBook->contacts[i].phone) == 0){
            printf("Phone number already exists\n");
            flag = 0;
            break;
        }
    }
    if(flag == 1)
        break;
}
if(flag == 0)
    return;


    /* Email */
/* Email */
for(chance = 1; chance <= 3; chance++)
{
    flag = 1;

    printf("Enter Email id: ");
    scanf("%s", addressBook->contacts[i].email);

    int at = 0, dot = 0;
    int atpos = -1, dotpos = -1;

    for(j = 0; addressBook->contacts[i].email[j] != '\0'; j++)
    {
        char ch = addressBook->contacts[i].email[j];

        if(ch == '@')
        {
            at++;
            atpos = j;
        }
        else if(ch == '.')
        {
            dot++;

            if(dotpos == -1)
                dotpos = j;
        }
        else if(!((ch >= 'A' && ch <= 'Z') ||(ch >= 'a' && ch <= 'z') ||(ch >= '0' && ch <= '9'))){
            printf("Invalid symbol in email\n");
            flag = 0;
            break;
        }
    }
    if(flag == 0)
        continue;
    if(at != 1) {
        printf("Email must contain exactly one @\n");
        flag = 0;
    }
    else if(dot < 1){
        printf("Email must contain at least one dot\n");
        flag = 0;
    }
    else if(atpos == 0) {
        printf("@ cannot be first\n");
        flag = 0;
    }
    else if(dotpos < atpos) {
        printf("Dot must appear after @\n");
        flag = 0;
    }
    else if(dotpos == atpos + 1) {
        printf("Character required between @ and dot\n");
        flag = 0;
    }
    else if(dotpos == strlen(addressBook->contacts[i].email) - 1){
        printf("Domain is missing\n");
        flag = 0;
    }
    if(flag == 0)
        continue;
    /* Check domain */
    for(j = atpos + 1; addressBook->contacts[i].email[j] != '\0'; j++){
        char ch = addressBook->contacts[i].email[j];
        if(ch != '.' &&!((ch >= 'A' && ch <= 'Z') ||(ch >= 'a' && ch <= 'z') ||(ch >= '0' && ch <= '9'))) {
            printf("Invalid symbol in domain\n");
            flag = 0;
            break;
        }
    }
    if(flag == 0)
        continue;
    /* Check characters after final dot */
    int lastdot = -1;
    for(j = 0; addressBook->contacts[i].email[j] != '\0'; j++){
        if(addressBook->contacts[i].email[j] == '.')
            lastdot = j;
    }
    for(j = lastdot + 1;addressBook->contacts[i].email[j] != '\0';j++){
        char ch = addressBook->contacts[i].email[j];
        if(!((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'))) {
            printf("Extra characters after domain\n");
            flag = 0;
            break;
        }
    }
    if(flag == 1)
        break;
}
if(flag == 0){
    printf("3 attempts completed. Invalid Email!\n");
    return;
}
addressBook->contactCount++;   
}

void searchContact(AddressBook *addressBook) {
    /* Define the logic for search */
   int choice, found = 0;
    char input[50];

    printf("\n1. Search by Name\n");
    printf("2. Search by Phone\n");
    printf("3. Search by Email\n");
    printf("4. Exit\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    if(choice == 4)
        return;

    if(choice < 1 || choice > 4){
        printf("Invalid choice\n");
        return;
    }
    printf("Enter search value: ");
    if(choice == 1)
        scanf(" %[^\n]", input);
    else
        scanf("%s", input);
    for(int i = 0; i < addressBook->contactCount; i++){
 if((choice == 1 && strcmp(input, addressBook->contacts[i].name) == 0) || (choice == 2 && strcmp(input, addressBook->contacts[i].phone) == 0) ||
           (choice == 3 && strcmp(input, addressBook->contacts[i].email) == 0)){
            found = 1;
            printf("\nName  : %s", addressBook->contacts[i].name);
            printf("\nPhone : %s", addressBook->contacts[i].phone);
            printf("\nEmail : %s\n", addressBook->contacts[i].email);
        }
    }
    if(found == 0)
        printf("Contact not found\n");
}

void editContact(AddressBook *addressBook){
	/* Define the logic for Editcontact */
    int choice, edit, count = 0, index = -1, select,flag;
    char input[50];

    printf("1. Name\n2. Phone\n3. Email\n4. Exit\n");
    printf("Search by: ");
    scanf("%d", &choice);
    if(choice == 4)
        return;
    if(choice < 1 || choice > 4){
        printf("Invalid choice\n");
        return;
    }
    printf("Enter value: ");
    if(choice == 1)
        scanf(" %[^\n]", input);
    else
        scanf("%s", input);
    /* Find matching contacts */
    for(int i = 0; i < addressBook->contactCount; i++){
        if((choice == 1 && strcmp(input, addressBook->contacts[i].name) == 0) ||(choice == 2 && strcmp(input, addressBook->contacts[i].phone) == 0) ||
           (choice == 3 && strcmp(input, addressBook->contacts[i].email) == 0)){
            count++;
            index = i;
            printf("%d. %s\t%s\t%s\n", count,addressBook->contacts[i].name, addressBook->contacts[i].phone,addressBook->contacts[i].email);
        }
    }
    if(count == 0){
        printf("Contact not found\n");
        return;
    }
    if(count > 1){
        printf("Select contact: ");
        scanf("%d", &select);
        if(select < 1 || select > count){
            printf("Invalid choice\n");
            return;
        }
        count = 0;
        for(int i = 0; i < addressBook->contactCount; i++){
if((choice == 1 && strcmp(input, addressBook->contacts[i].name) == 0) ||(choice == 2 && strcmp(input, addressBook->contacts[i].phone) == 0) ||
               (choice == 3 && strcmp(input, addressBook->contacts[i].email) == 0)){
                count++;
                if(count == select){
                    index = i;
                    break;
                }
            }
        }
    }
    printf("\n1. Name\n2. Phone\n3. Email\n4. Exit\n");
    printf("Edit: ");
    scanf("%d", &edit);
    if(edit == 4)
        return;
    if(edit < 1 || edit > 4){
        printf("Invalid choice\n");
        return;
    }
    // Edit Name 
    if(edit == 1){
        printf("Enter new Name: ");
        scanf(" %[^\n]", input);
        if(strlen(input) < 4){
            printf("Name must contain at least 4 characters\n");
            return;
        }
        for(int j = 0; input[j] != '\0'; j++){
            if(!((input[j] >= 'A' && input[j] <= 'Z') ||(input[j] >= 'a' && input[j] <= 'z')||(input[j] == ' ') )){
                printf("Name should contain only alphabets\n");
                return;
            }
        }
        strcpy(addressBook->contacts[index].name, input);
    }
    /* Edit Phone */
    else if(edit == 2){
        printf("Enter new Phone Number: ");
        scanf("%s", input);
        if(strlen(input) != 10){
            printf("Phone number must contain exactly 10 digits\n");
            return;
        }
        if(input[0] < '6' || input[0] > '9'){
            printf("First digit must be between 6 and 9\n");
            return;
        }
        for(int j = 0; input[j] != '\0'; j++){
            if(input[j] < '0' || input[j] > '9'){
                printf("Phone number should contain only digits\n");
                return;
            }
        }
        for(int j = 0; j < addressBook->contactCount; j++){
            if(j != index && strcmp(input, addressBook->contacts[j].phone) == 0){
                printf("Phone number already exists\n");
                return;
            }
        }
        strcpy(addressBook->contacts[index].phone, input);
    }
    /* Edit Email - validation will be added later */
    else if(edit == 3){
    int at = 0, dot = 0;
    for(int chance = 1; chance <= 3; chance++) {
        flag = 1;
        printf("Enter new Email id: ");
        scanf("%s", input);

        at = dot = 0;
        for(int j = 0; input[j] != '\0'; j++) {
            if(input[j] == '@')
                at++;

            if(input[j] == '.')
                dot++;
        }
        if(at != 1) {
            printf("Email must contain exactly one @\n");
            flag = 0;
        }
        else if(dot < 1) {
            printf("Email must contain at least one dot\n");
            flag = 0;
        }
        if(flag == 1)
            break;
    }
    if(flag == 0){
        printf("3 attempts completed. Invalid Email!\n");
        return;
    }
    strcpy(addressBook->contacts[index].email, input);
}
    printf("Contact updated!\n");
}


void deleteContact(AddressBook *addressBook){
	/* Define the logic for deletecontact */
int choice, select, count = 0, index = -1;
    char input[50];
    char confirm;
 printf("\n1. Name\n2. Phone\n3. Email\n4. Exit\n");
    printf("Search by: ");
    scanf("%d", &choice);
if(choice == 4)
        return;
    if(choice < 1 || choice > 4){
        printf("Invalid choice\n");
        return;
    }
    printf("Enter value: ");
    if(choice == 1)
        scanf(" %[^\n]", input);
    else
        scanf("%s", input);
    // Find matching contacts
    for(int i = 0; i < addressBook->contactCount; i++){
    if((choice == 1 && strcmp(input, addressBook->contacts[i].name) == 0) ||(choice == 2 && strcmp(input, addressBook->contacts[i].phone) == 0) ||
           (choice == 3 && strcmp(input, addressBook->contacts[i].email) == 0)){
            count++;
            index = i;
    printf("%d. %s\t%s\t%s\n", count,addressBook->contacts[i].name, addressBook->contacts[i].phone,addressBook->contacts[i].email);
        }
    }
    if(count == 0){
        printf("Contact not found\n");
        return;
    }
    // Select contact if duplicate found
    if(count > 1){
        printf("Select contact: ");
        scanf("%d", &select);
        if(select < 1 || select > count){
            printf("Invalid choice\n");
            return;
        }
        count = 0;
        for(int i = 0; i < addressBook->contactCount; i++){
 if((choice == 1 && strcmp(input, addressBook->contacts[i].name) == 0) || (choice == 2 && strcmp(input, addressBook->contacts[i].phone) == 0) ||
               (choice == 3 && strcmp(input, addressBook->contacts[i].email) == 0)){
                count++;
                if(count == select){
                    index = i;
                    break;
                }
            }
        }
    }
    printf("\nName  : %s", addressBook->contacts[index].name);
    printf("\nPhone : %s", addressBook->contacts[index].phone);
    printf("\nEmail : %s\n", addressBook->contacts[index].email);
    printf("Are you sure you want to delete? (y/n): ");
    scanf(" %c", &confirm);
    if(confirm != 'y' && confirm != 'Y'){
        printf("Deletion cancelled\n");
        return;
    }
    // Shift contacts after deleted contact
    for(int i = index; i < addressBook->contactCount - 1; i++){
        addressBook->contacts[i] = addressBook->contacts[i + 1];
    }
    addressBook->contactCount--;
    printf("Contact deleted successfully!\n");
}