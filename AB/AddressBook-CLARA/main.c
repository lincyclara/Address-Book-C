/*
NAME : LINCY K
BATCH & REG.NO : 25021A_017
PROJECT TITLE : ADDRESS BOOK 
DESCRIPTION : The Address Book project is a practical application developed in C programming
              to efficiently store and manage contact information. It enables users to add, 
              search, update, delete, and display contacts in a structured manner. By using 
              structures, functions, pointers, and file handling concepts, the project 
              highlights the power of C programming in solving real-world problems through 
              effective data management and organization.
DATE : 23/09/2025
*/

#include <stdio.h>
#include "contact.h"
#include "file.h"
#include "populate.h"

int main() {
    int choice;
    int sortChoice=0;
    AddressBook addressBook;
    initialize(&addressBook); // Initialize the address book
    loadContactsFromFile(&addressBook);

    do {
        printf("\n\x1b[1;28mAddress Book Menu:\x1b[0m\n");
        printf("1. Create contact\n");
        printf("2. Search contact\n");
        printf("3. Edit contact\n");
        printf("4. Delete contact\n");
        printf("5. List all contacts\n");
    	printf("6. Save contacts\n");		
        printf("7. Exit\n");
        printf("\x1b[1;28mEnter your choice: \x1b[0m");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                createContact(&addressBook);
                break;
            case 2:
                searchContact(&addressBook);
                break;
            case 3:
                editContact(&addressBook);
                break;
            case 4:
                deleteContact(&addressBook);
                break;
            case 5:          
                listContacts(&addressBook, sortChoice);
                break;
            case 6:
                saveContactsToFile(&addressBook);
                printf("Saving and Exiting...\n");
                break;
            case 7:
                saveContactsToFile(&addressBook); // save before exit
                printf("\x1b[2;30mExiting...\x1b[0m\n");
                return 0;
            default:
                printf("\x1b[2;30mInvalid choice. Please try again.\x1b[0m\n");
        }
    } while (choice != 7);
    
       return 0;
}
