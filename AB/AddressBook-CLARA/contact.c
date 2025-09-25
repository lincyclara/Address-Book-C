#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<ctype.h>
#include "contact.h"
#include "file.h"
#include "populate.h"

void listContacts(AddressBook *addressBook, int sortCriteria) 
{
    // Sort contacts based on the chosen criteria
    int i;
    if((addressBook->contactCount)==0)
    {
        printf("\x1b[31mNo contacts \x1b[0m\n");
        return;
    }
    // --- Sort contacts alphabetically by name ---
    for(i=0;i<addressBook->contactCount - 1;i++){
        for(int j = i+1; j < addressBook -> contactCount ;j++){
            if(strcmp(addressBook->contacts[i].name,addressBook->contacts[j].name) > 0){
                //--Swap contacts--
                Contact temp = addressBook->contacts[i];
                addressBook->contacts[i]= addressBook->contacts[j];
                addressBook->contacts[j] = temp;
            }
        }
    }

    // --- Print contacts ---
    printf("%-5s %-30s %-15s %-30s \n","No.","Name" ,"Phone" , "Email");
    printf("----------------------------------------------------------------------\n");
    for(i=0;i<addressBook->contactCount;i++)
    {
        printf("%-5d %-30s %-15s %-30s \n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }

    
}

void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    populateAddressBook(addressBook);
    
    // Load contacts from file during initialization (After files)
    //loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    //FILE *fp=("","w")
    exit(EXIT_SUCCESS); // Exit the program
}

void createContact(AddressBook *addressBook)
{
	int i,l,l1,l2;
    Contact arr; //declare one temp array
    
    //----NAME----
    while(1)
    {
        int count=0;
        printf("\x1b[3;30mEnter the name of the user: \x1b[0m\n");
        scanf(" %[^\n]",arr.name);
        l=strlen(arr.name);
        if(l==0){
            printf("write some name...\n");
            continue;
        }
        //Checking for a valid name
        if(arr.name[0]==' ' || arr.name[0]=='.' || arr.name[l-1]==' ' || arr.name[l-1]=='.'){
            printf("\x1b[31mError! Name can't start or end with space/dot\x1b[0m\n");
            continue;
        }
        for(i=0;i<l;i++){
            if(!isalpha(arr.name[i]) && arr.name[i]!=' ' && arr.name[i]!='.'){
                count=1;
                break;   
            }
        }
        if(count==1){
            printf("\x1b[31mError!Enter the name correctly!!!\x1b[0m\n");
            continue;
        }
        break;
    }
    //----PHONE NUMBER----
    while(1){
        int c1=0,duplicate=0;
        //check if phone number already exists
        printf("\x1b[3;30mEnter the phone number: \x1b[0m\n");
        scanf(" %[^\n]",arr.phone);
        l1=strlen(arr.phone);
        if(l1 != 10)
        {
            printf("\x1b[31mError !enter 10 digit phone number!!!\x1b[0m\n");
            continue;
        }
        //--Checking for a valid phone number--
        for(i=0;i<l1;i++)
        {
            if(!(isdigit(arr.phone[i])))
            {
                c1=1;
                break;
            }
        }
        if(c1==1)
        {
            printf("\x1b[31mError ! Enter the valid phone number.\x1b[0m\n");
            continue;
        }
        if(addressBook->contactCount>0){
            for(i=0;i<addressBook->contactCount;i++){
                if(strcmp(addressBook->contacts[i].phone,arr.phone)==0){
                    duplicate=1;
                    break;
                }
            }
        }
        if(duplicate==1){
            printf("Phone number already exist! Enter a new number: \n");
            continue;
        }
        break;
    }
   
    //---EMAIL ID---
    while(1){
        int c2=0,duplicate1=0;
        //check if email already exists
        printf("\x1b[3;30mEnter the mail id: \x1b[0m\n");
        scanf(" %[^\n]",arr.email);
        l2=strlen(arr.email);
        if(l2==0)
        {
            printf("\x1b[31mError! enter a mail id..\x1b[0m\n");
            return;
        }
        int at_count=0,dot_count=0,at_pos,dot_pos;
        //---Checking for a valid email id---
        for(i=0;i<l2;i++)
        {
            char c=arr.email[i];
            if((islower(c)) || (isdigit(c)) || c =='_' || c =='.' || c =='@'){
                if(c=='@'){
                    at_count++;
                    at_pos = i;
                }
                if(c=='.'){
                    dot_count++;
                    dot_pos=i;
                }
            }
            else{
                printf("\x1b[31mError! Email doesn't have required characters...\x1b[0m\n");
                c2=1;
                break;
            }
        }
        if(c2)
        {
            continue;
        }

        if(at_count != 1){
            printf("\x1b[31mError ! Email must have an '@' character..\x1b[0m\n");
            continue; 
        }
        if(at_pos == 0)
        {   // <---- NEW CHECK
            printf("\x1b[31mError! Email must have a name before '@'.\x1b[0m\n");
            continue;
        }
        if(dot_count < 1){
            printf("\x1b[31mError ! The Email address must have  a '.' character after the '@'...\x1b[0m\n");
            continue;   
        }
        if(at_pos > dot_pos){
            printf("\x1b[31mError ! Enter the correct email address that '.' character must enter after the '@'...\x1b[0m\n ");
            continue;
        }
        if(arr.email[0] == '.'){  
            printf("\x1b[31mError! Email cannot start with '.'\x1b[0m\n");
            continue;
        }
        if(arr.email[l2-1] == '.'){  
            printf("\x1b[31mError! Email cannot end with '.'\x1b[0m\n");
            continue;
        }
        if(arr.email[at_pos+1] == '.'){  
            printf("\x1b[31mError! '.' cannot come immediately after '@'\x1b[0m\n");
            continue;
        }
        if(at_pos > 0 && arr.email[at_pos-1] == '.'){  
            printf("\x1b[31mError! '.' cannot come immediately before '@'\x1b[0m\n");
            continue;
        }

        if(addressBook->contactCount>0)
        {
            for(i=0;i<addressBook->contactCount;i++){
                if(strcmp(addressBook->contacts[i].email,arr.email)==0){
                    duplicate1=1;
                    break;
                }
            }
        }
        if(duplicate1==1){
            printf("Email is already exist!Enter a new Email id!\n");
            continue;
        }
        break;
    }
    //---Copying values to structure array---
    strcpy(addressBook->contacts[addressBook->contactCount].name, arr.name);
    strcpy(addressBook->contacts[addressBook->contactCount].phone, arr.phone);
    strcpy(addressBook->contacts[addressBook->contactCount].email, arr.email);
   
    //---Incrementing index count--   
    addressBook->contactCount++;
    //---Storing values in structure array---
    saveContactsToFile(addressBook);   
   
    
    printf("\x1b[3;30mContact added successfully!\x1b[0m\n");
}

void searchContact(AddressBook *addressBook) 
{
    int i,field,l,count,found;
    Contact temp1;
    if((addressBook->contactCount)==0){
        printf("-No contacts found!-\n");
        return;
    }
    //listContacts(addressBook,0); 
    while(1)
    {
        char input[50];
        printf("Search by:\n");
        printf("1.Name\n2.Phone\n3.Email\n4.Exit\n");
        printf("Enter your Choice: ");

        if (scanf("%d", &field) != 1) {
        printf("\x1b[31mError ! Invalid case...\x1b[0m\n");

        // clear bad input (e.g., abc, 1.2, #$%)
        while (getchar() != '\n');
        continue;   // restart loop, show menu again
        }
        /*fgets(input, sizeof(input), stdin);
        int j = 0;
        while (input[j] == ' ') j++;              // skip leading spaces
        if (input[j] == '+' || input[j] == '-') j++;
        int hasDigit = 0,invalid=0;
        for (; input[j] != '\0' && input[j] != '\n'; j++) {
            if (!isdigit((unsigned char)input[j])) { 
                invalid = 1; 
                break; 
            }
            hasDigit = 1;
        }

        if(invalid || !hasDigit){
            printf("Error ! Invalid case...\n");
            continue;
        }
        sscanf(input, "%d", &field);*/
        if(field < 1 || field > 4){
            printf("\x1b[31mError ! Invalid case...\x1b[0m\n");
            continue;
        }

        if(field==1){
        while(1){
            count=0;
            found=0;
            printf("\x1b[3;30mEnter the name to be searched :\x1b[0m\n");
            scanf(" %[^\n]",temp1.name);
            l=strlen(temp1.name);
            if(l==0){
                printf("\x1b[3;30mwrite some name...\x1b[0m\n");
                continue;
            }
            if(temp1.name[0] == ' ' || temp1.name[0]=='.' || temp1.name[l-1]==' ' || temp1.name[l-1]=='.'){
                printf("\x1b[31mError ! Name can't be start or end with space/ dot\x1b[0m\n");
                continue;
            }
            for(i=0;i<l;i++){
                if(!isalpha(temp1.name[i]) && temp1.name[i]!=' ' && temp1.name[i]!='.'){
                    count=1;
                    break;   
                }
            }
            if(count==1){
                printf("\x1b[31mError!Enter the name correctly!!!\x1b[0m\n");
                continue;
            }
            if(addressBook->contactCount>0){
                for(i=0;i<addressBook->contactCount;i++){
                    //substring search (case sensitive)
                    if(strcasestr(addressBook->contacts[i].name,temp1.name)!= NULL){
                        printf("---- Contact Found ----\n");
                        printf("Name : %s\n",addressBook->contacts[i].name);
                        printf("Phone : %s\n",addressBook->contacts[i].phone);
                        printf("Email : %s\n",addressBook->contacts[i].email);
                        found=1;
                    ;     
                    }
                }
            }
            if(!found){
                printf("\x1b[31mContact not found...!\x1b[0m\n");
                continue;
            }
            break;
        }
    }

    if(field==2){
        while(1){
            int c1=0,found=0;
            printf("\x1b[3;30mEnter the phone number to be searched:\x1b[0m\n");
            scanf(" %[^\n]",temp1.phone);
            l=strlen(temp1.phone);
            if(l!=10){
                printf("\x1b[31mError! enter 10 digit phone number!!!\x1b[0m\n");
                continue;
            }
            for(i=0;i<l;i++){
                if(!(isdigit((unsigned char)temp1.phone[i]))){
                    c1=1;
                    break;
                }
            }
            if(c1){
                printf("\x1b[31mError ! Enter a valid phone number. \x1b[0m\n");
                continue;
            }
            if(addressBook->contactCount>0){
                for(i=0;i<addressBook->contactCount;i++){
                    //substring search (numbers)
                    if(strstr(addressBook->contacts[i].phone,temp1.phone)!=NULL){
                        printf("----Contact Found----\n");
                        printf("Name : %s\n",addressBook->contacts[i].name);
                        printf("Phone : %s\n",addressBook->contacts[i].phone);
                        printf("Email : %s\n",addressBook->contacts[i].email);
                        found=1;
                        break;
                    }
                }
            }
            if(!found){
                printf("Contact not found...!\n");
                continue;
            }
            break;
        }
    }
    if(field==3){
       while(1){
        int c2=0,found=0,dott=0;
        printf("\x1b[3;30mEnter the Email to search : \x1b[0m\n");
        scanf(" %[^\n]",temp1.email);
        int at_count=0,dot_count=0,at_pos,dot_pos;
        l=strlen(temp1.email);
        //char ch= temp1.email[i];
        if(l==0)
        {
            printf("\x1b[31mError!Enter some Email address : \x1b[0m");
            return;
        }
        for(i=0;i<l;i++)
        {
            char ch= temp1.email[i];
            if((isalpha(ch)) || (isdigit(ch))  ||  ch=='_' || ch=='.' || ch=='@' ){
                if(ch=='@'){
                    at_count++;
                    at_pos=i;
                }
                if(ch=='.'){
                    dot_count++;
                    dot_pos=i;
                }
                if(temp1.name[i] == '.' || temp1.name[i-1]=='.'){
                    dott=1;
                    break;
                }
            }
            else
            {
                printf("\x1b[31mError! The entered Email address doesn't have required characters...\x1b[0m\n");
                c2=1;
                break;
            }
        }
        if(dott){
            printf("\x1b[31mError ! The email doesn't have consecutive dots\x1b[0m\n");
            continue;
        }
        if(c2) {
            continue;
        }
        if(at_count!=1){
            printf("\x1b[31mError ! Email must have an '@' character..\x1b[0m\n");
            continue; 
        }
        if(at_pos == 0){   // <---- NEW CHECK
            printf("\x1b[31mError! Email must have a name before '@'.\x1b[0m\n");
            continue;
        }
        if(dot_count<1){
            printf("\x1b[31mError ! The Email address must have  a '.' character after the '@'...\x1b[0m\n");
            continue;   
        }
        if(at_pos > dot_pos){
            printf("\x1b[31mError ! Enter the correct email address that '.' character must enter after the '@'...\x1b[0m\n ");
            continue;
        }
        if(temp1.email[0] == '.'){  
            printf("\x1b[31mError! Email cannot start with '.'\x1b[0m\n");
            continue;
        }
        if(temp1.email[l-1] == '.'){  
            printf("\x1b[31mError! Email cannot end with '.'\x1b[0m\n");
            continue;
        }
        if(temp1.email[at_pos+1] == '.'){  
            printf("\x1b[31mError! '.' cannot come immediately after '@'\x1b[0m\n");
            continue;
        }
        if(at_pos > 0 && temp1.email[at_pos-1] == '.'){  
            printf("\x1b[31mError! '.' cannot come immediately before '@'\x1b[0m\n");
            continue;
        }
        if(addressBook->contactCount>0){
                for(i=0;i<addressBook->contactCount;i++){
                    if(strcasestr(addressBook->contacts[i].email,temp1.email)!=NULL){
                        printf("----Contact Found----\n");
                        printf("Name : %s\n",addressBook->contacts[i].name);
                        printf("Phone : %s\n",addressBook->contacts[i].phone);
                        printf("Email : %s\n",addressBook->contacts[i].email);
                        found=1;
                        break;
                    }
                }
        }
        if(!found){
            printf("Contact not found...!\n");
            continue;
        }
        break;
    }
    }
    if(field==4)
    {
        return;
    }
break;
}
}

void editContact(AddressBook *addressBook)
{
    if((addressBook->contactCount)==0){
        printf("No contacts found!\n");
        return;
    }
    int value,number,found = -1;
    Contact temp;
    //--Displaying contact list--
    listContacts(addressBook,0);
    
    while(1){
    printf("\nSearch by:\n");
    printf("1.Name\n2.Phone\n3.Email\n4.Index\n");  //choices to edit
    printf("Enter your Choice: ");
        if (scanf("%d", &value) != 1) {
            printf("Error ! Invalid case...\n");
            // clear bad input (e.g., abc, 1.2, #$%)
            while (getchar() != '\n');
                continue;   // restart loop, show menu again
        }   
        //temp = addressBook->contacts[found];
    // -------------------------
    // Step 1: Enter search input
    // -------------------------
    char searchInput[50];
    if (value == 1) {
        printf("\x1b[3;30mEnter the existing name: \x1b[0m");
        scanf(" %[^\n]", searchInput);

        // validate name
        int valid = 1;
        for (int i = 0; i < strlen(searchInput); i++) {
            if (!(isalpha(searchInput[i]) || isspace(searchInput[i]))) {
                valid = 0;
                break;
            }
        }
        if (!valid) {
            printf("\x1b[31mInvalid name! Only alphabets and spaces allowed.\x1b[0m\n");
            continue;
        }

        // search by name
        for (int i = 0; i < addressBook->contactCount; i++) {
            if (strcasestr(addressBook->contacts[i].name, searchInput) != NULL) {
                found = i;
                break;
            }
        }
    }
    else if (value == 2) {
        printf("\x1b[3;30mEnter the existing phone: \x1b[0m");
        scanf("%s", searchInput);

        // validate phone: digits only, length 10
        int valid = 1;
        if (strlen(searchInput) != 10) valid = 0;
        for (int i = 0; i < strlen(searchInput); i++) {
            if (!isdigit(searchInput[i])) {
                valid = 0;
                break;
            }
        }
        if (!valid) {
            printf("\x1b[31mInvalid phone number! Must be 10 digits.\x1b[0m\n");
            continue;
        }

        // search by phone
        for (int i = 0; i < addressBook->contactCount; i++) {
            if (strstr(addressBook->contacts[i].phone, searchInput) != NULL) {
                found = i;
                break;
            }
        }
    }
    else if (value == 3) {
        printf("Enter the existing email: ");
        scanf("%s", searchInput);

        // validate email (simple check)
        int valid = 1;
        if (strchr(searchInput, '@') == NULL || strchr(searchInput, '.') == NULL) {
            valid = 0;
        }
        if (!valid) {
            printf("\x1b[31mInvalid email format!\x1b[0m\n");
            continue;
        }

        // search by email
        for (int i = 0; i < addressBook->contactCount; i++) {
            if (strcasestr(addressBook->contacts[i].email, searchInput) != NULL) {
                found = i;
                break;
            }
        }
    }
    else if (value == 4) {
        printf("\x1b[3;30mEnter contact index: \x1b[0m");
        scanf("%d", &number);
        if(number < 1 || number > addressBook->contactCount){
            printf("\x1b[31mInvalid index!\x1b[0m\n");
            continue;
        }
        found = number - 1;
    }
    else{
        printf("\x1b[31mInvalid choice! Try again.\x1b[0m\n");
        continue;
    }
    // -------------------------
    // Step 2: Not found?
    // -------------------------
    if (found == -1) {
        printf("Contact not found!\n");
        continue;
    }
    temp = addressBook->contacts[found];
    break;
    }
    // -------------------------
    // Step 3: Print details
    // -------------------------
    printf("\nContact found:\n");
    printf("Name  : %s\n", temp.name);
    printf("Phone : %s\n", temp.phone);
    printf("Email : %s\n", temp.email);
     // -------------------------
    // Step 4: Ask which field to edit
    // -------------------------
    int choice;
    printf("\nWhich field do you want to edit?\n");
    printf("1. Name\n2. Phone\n3. Email\n4. All\nEnter your choice: ");
    scanf("%d", &choice);
    //---NAME---
    if(choice==1 ||choice ==4){
        while(1){
            int count=0,i,l;
            printf("\x1b[3;30mEnter the new name: \x1b[0m\n");
            scanf(" %[^\n]",temp.name);
            l=strlen(temp.name);
            if(l==0){
                printf("write some name...\n");
                continue;   
            }
            if(temp.name[0]==' ' || temp.name[0]=='.' || temp.name[l-1]==' ' || temp.name[l-1]=='.'){
                printf("\x1b[31mError ! Name can't start or end with space /dot\x1b[0m\n");
                continue;
            }
            //Checking for a valid name
            for(i=0;i<l;i++){
                if(!isalpha(temp.name[i]) && temp.name[i]!=' ' && temp.name[i]!='.'){
                    count=1;
                    break;   
                }
            }
            if(count==1){
                printf("\x1b[31mError!Enter the name correctly!!!\x1b[0m\n");
                continue;
            }
            break;
        }
    }
    //----PHONE NUMBER---
    if(choice==2 || choice ==4){
        while(1){
            int c1=0,duplicate=0,i,l1;
            //check if phone number already exists
            printf("\x1b[3;40mEnter the new phone number: \x1b[0m\n");
            scanf(" %[^\n]",temp.phone);
            l1=strlen(temp.phone);
            if(l1 != 10)
            {
                printf("\x1b[31mError! enter 10 digit phone number!!!\x1b[0m\n");
                continue;
            }
            //--Checking for a valid phone number--
            for(i=0;i<l1;i++)
            {
                if(!(isdigit(temp.phone[i])))
                {
                    c1=1;
                    break;
                }
            }
            if(c1==1)
            {
                printf("\x1b[31mError ! Enter the valid phone number.\x1b[0m\n");
                continue;
            }
            if(addressBook->contactCount>0){
                for(i=0;i<addressBook->contactCount;i++){
                    if(strcmp(addressBook->contacts[i].phone,temp.phone)==0){
                        duplicate=1;
                        break;
                    }
                }
            }
            if(duplicate==1){
                printf("\x1b[3;30mPhone number already exist!\x1b[0m \n");
                continue;
            }
            break;
        }
    }
    //--MAIL ID
    if(choice == 3 || choice ==4){
        while(1){
        int c2=0,duplicate1=0,i,l2;
        //check if email already exists
        printf("\x1b[3;30mEnter the mail id: \x1b[0m\n");
        scanf(" %[^\n]",temp.email);
        l2=strlen(temp.email);
        if(l2==0)
        {
            printf("\x1b[31mError! enter a mail id..\x1b[0m\n");
            continue;
        }
        int at_count=0,dot_count=0,at_pos,dot_pos;
        //---Checking for a valid email id---
        for(i=0;i<l2;i++)
        {
            char c=temp.email[i];
            if(!(islower(c)) || !(isdigit(c)) || c =='_' || c =='.' || c =='@'){
                if(c=='@'){
                    at_count++;
                    at_pos = i;
                }
                if(c=='.'){
                    dot_count++;
                    dot_pos=i;
                }
            }
            else{
                printf("\x1b[31mError! Email doesn't have required characters...\x1b[0m\n");
                c2=1;
                break;
            }
        }
        if(c2){
            continue;
        }
        if(at_count!=1){
            printf("\x1b[31mError ! Email must have an '@' character..\x1b[0m\n");
            continue; 
        }
        if(at_pos == 0){   // <---- NEW CHECK
            printf("\x1b[31mError! Email must have a name before '@'.\x1b[0m\n");
            continue;
        }
        if(dot_count<1){
            printf("\x1b[31mError ! The Email address must have  a '.' character after the '@'...\x1b[0m\n");
            continue;   
        }
        if(at_pos > dot_pos){
            printf("\x1b[31mError ! Enter the correct email address that '.' character must enter after the '@'...\x1b[0m\n "); 
            continue;
        }
        if(temp.email[0] == '.'){  
            printf("\x1b[31mError! Email cannot start with '.'\x1b[0m\n");
            continue;
        }
        if(temp.email[l2-1] == '.'){  
            printf("\x1b[31mError! Email cannot end with '.'\x1b[0m\n");
            continue;
        }
        if(temp.email[at_pos+1] == '.'){  
            printf("\x1b[31mError! '.' cannot come immediately after '@'\x1b[0m\n");
            continue;
        }
        if(at_pos > 0 && temp.email[at_pos-1] == '.'){  
            printf("\x1b[31mError! '.' cannot come immediately before '@'\x1b[0m\n");
            continue;
        }
        if(addressBook->contactCount > 0)
        {
            for(i=0;i<addressBook->contactCount;i++){
                if(i != found && strcasestr(addressBook->contacts[i].email,temp.email)!=NULL){
                    duplicate1=1;
                    break;
                }
            }
        }
        if(duplicate1==1){
            printf("Email is already exist!Enter a new Email id!\n");
            continue;
        }
        break;
    }
    }
    addressBook->contacts[found] = temp ;   
    printf("Contact updated successfully!\n");
}
void deleteContact(AddressBook *addressBook)
{   
    int i,field,l,count,found,pos;
    Contact temp1; // Creating a temorary contact variable
    // check if contact list is empty
    if((addressBook->contactCount)==0){
        printf("No contacts found!\n");
        return;
    }
    while(1)
    {
        char input[50];
        int field;
        printf("Search by:\n");
        printf("1.Name\n2.Phone\n3.Email\n4.Exit\n");
        printf("Enter your Choice: ");

        if (scanf("%d", &field) != 1) {
        printf("\x1b[3;30mError ! Invalid case...\x1b[0m\n");

        // clear bad input (e.g., abc, 1.2, #$%)
        while (getchar() != '\n');
        continue;   // restart loop, show menu again
        }
        
        /*fgets(input, sizeof(input), stdin);
        int j = 0;
        while (input[j] == ' ') j++;         // skip leading spaces
        if (input[j] == '+' || input[j] == '-') j++;
        int hasDigit = 0;
        // Check if the input contains only digits
        for (; input[j] != '\0' && input[j] != '\n'; j++)    
        {
            if (!isdigit((unsigned char)input[j])) { 
                field = 0; 
                break; 
            }
            hasDigit = 1;
        }
        // If no digits were found, it's not a valid number
        if(!field || !hasDigit){
            printf("Error ! Invalid case...\n");
            continue;
        }
        sscanf(input, "%d", &field);*/

        // Deleting contact based on Name
        if(field==1){
        while(1){
            count=0;
            found=0;
            printf("\x1b[3;30mEnter the name to be searched!\x1b[0m\n");
            scanf(" %[^\n]",temp1.name);
            l=strlen(temp1.name);
            if(l==0){
                printf("\x1b[31mwrite some name...\x1b[0m\n");
                continue;
            }
            if(temp1.name[0]==' ' || temp1.name[0]=='.' || temp1.name[l-1]==' ' || temp1.name[l-1]=='.'){
                printf("\x1b[31mError ! Name can't start or end with space /dot\x1b[0m\n");
                continue;
            }
            for(i=0;i<l;i++){
                if(!isalpha(temp1.name[i]) && temp1.name[i]!=' ' && temp1.name[i]!='.'){
                    count=1;
                    break;   
                }
            }
            if(count==1){
                printf("\x1b[31mError!Enter the name correctly!!!\x1b[0m\n");
                continue;
            }
            if(addressBook->contactCount>0){
                for(i=0;i<addressBook->contactCount;i++){
                    //strcmp(addressBook->contacts[i].name,temp1.name);
                    if(strcasestr(addressBook->contacts[i].name,temp1.name)!=NULL){
                        printf("---- Contact Found ----\n");
                        found=1;
                        pos=i;
                        break;
                    }
                }
            }
            if(found==1){
                for(i=pos;i<addressBook->contactCount-1;i++){
                    addressBook->contacts[i]=addressBook->contacts[i+1];
                }
                printf("Contact deleted successfully!\n");
                addressBook->contactCount--;
            }
            if(!found){
                printf("Contact not found..!\n");
                continue;
            }
            break;
        }  
        }
        
        // Deleting contact based on Phone number
        if(field==2){
             while(1){
            int c1=0,found=0;
            printf("\x1b[3;30mEnter the phone number to be searched:\x1b[0m\n");
            scanf(" %[^\n]",temp1.phone);
            l=strlen(temp1.phone);
            if(l!=10){
                printf("\x1b[31mError! enter 10 digit phone number!!!\x1b[0m\n");
                continue;
            }
            for(i=0;i<l;i++){
                if(!(isdigit(temp1.phone[i]))){
                    c1=1;
                    break;
                }
            }
            if(c1==1){
                printf("\x1b[31mError ! Enter a valid phone number. \x1b[0m\n");
                continue;
            }
            if(addressBook->contactCount>0){
                for(i=0;i<addressBook->contactCount;i++){
                    if(strstr(addressBook->contacts[i].phone,temp1.phone)!=NULL){
                        printf("----Contact Found----\n");
                        found=1;
                        pos=i;
                        break;
                    }
                }
            }
            if(found==1){
                for(i=pos;i<addressBook->contactCount;i++){
                    addressBook->contacts[i]=addressBook->contacts[i+1];
                }
                printf("Contact deleted successfully!\n");
                addressBook->contactCount--;
            }
            if(!found){
                printf("Contact not found...!\n");
                continue;
            }
            break;
        }
        }
        // Deleting contact based on Email ID
        if(field==3){
            while(1){
            int c2=0,found=0;
            printf("\x1b[3;30mEnter the Email to search : \x1b[0m\n");
            scanf(" %[^\n]",temp1.email);
        int at_count=0,dot_count=0,at_pos,dot_pos;
        l=strlen(temp1.email);
        //char ch= temp1.email[i];
        if(l==0)
        {
            printf("\x1b[31mError!Enter some Email address : \x1b[0m");
            return;
        }
        for(i=0;i<l;i++)
        {
            char ch= temp1.email[i];
            if(!(islower(ch)) || !(isdigit(ch))  ||  ch=='_' || ch=='.' || ch=='@' ){
                if(ch=='a'){
                    at_count++;
                    at_pos=i;
                }
                if(ch=='.'){
                    dot_count++;
                    dot_pos=i;
                }
            }
            else{
                printf("\x1b[31mError! The entered Email address doesn't have required characters...\x1b[0m\n");
                c2=0;
                break;
            }
        }
        if(c2){
            continue;
        }
        if(at_count!=1){
            printf("\x1b[31mError ! Email must have an '@' character..\x1b[0m\n");
            continue; 
        }
        if(at_pos == 0){   // <---- NEW CHECK
            printf("\x1b[31mError! Email must have a name before '@'.\x1b[0m\n");
            continue;
        }
        if(dot_count<1){
            printf("\x1b[31mError ! The Email address must have  a '.' character after the '@'...\x1b[0m\n");
            continue;   
        }
        if(at_pos > dot_pos){
            printf("\x1b[31mError ! Enter the correct email address that '.' character must enter after the '@'...\x1b[0m\n ");
            continue;
        }
        if(temp1.email[0] == '.'){  
            printf("\x1b[31mError! Email cannot start with '.'\x1b[0m\n");
            continue;
        }
        if(temp1.email[l-1] == '.'){  
            printf("\x1b[31mError! Email cannot end with '.'\x1b[0m\n");
            continue;
        }
        if(temp1.email[at_pos+1] == '.'){  
            printf("\x1b[31mError! '.' cannot come immediately after '@'\x1b[0m\n");
            continue;
        }
        if(at_pos > 0 && temp1.email[at_pos-1] == '.'){  
            printf("\x1b[31mError! '.' cannot come immediately before '@'\x1b[0m\n");
            continue;
        }
        if(addressBook->contactCount>0){
                for(i=0;i<addressBook->contactCount;i++){
                    if(strcasestr(addressBook->contacts[i].email,temp1.email)!=NULL){
                        printf("----Contact Found----\n");
                        found=1;
                        pos=i;
                        break;
                    }
                }
        }

        if(found){
            for(i=pos;i<addressBook->contactCount-1;i++){
                addressBook->contacts[i]=addressBook->contacts[i+1];
            }
            printf("Contact deleted successfully!\n");
            addressBook->contactCount--;
        }
        if(!found){
            printf("Contact not found...!\n");
            continue;
        }
        break;
    }
    }

    // Exiting delete operation
    if(field == 4)
        {
            return;
        }
        break;
    }
}    