# Problem Statement
Our team is employed by a bank to implement a system for the management of customers, accounts and loans.  
## Customer specifications specific to my part:
    • Change the status of an account (blocked, inactive, active),
    • Present management statistics about the bank customers, such as number of customers, number of accounts, average accounts per customers, (average) account balances, loan histories per account or overall average loan sum, etc.
## Additional Tasks:
    • Set, and change APRs,
    • Delete account under management options changing statistics as required,
    • Password protect management options,
    • Create generic functions for rest of group:
        ◦ Number of structures in any file,
        ◦ View any requested structure type with specified account number,
        ◦ Check account exists,
        ◦ Check account status.
# Analysis
## Inputs:
    • User keyboard entries:
        ◦ Password (char),
        ◦ APR (float),
        ◦ Menu selection (int),
    • Files:
        ◦ Management file for password compare,
        ◦ Statistics file for reading,
        ◦ Number of other functions/ files provide information for statistic requests.
## Outputs:
    • Display:
        ◦ Menu options,
        ◦ Statistics,
        ◦ Usermanual,
        ◦ Function tasks.




# Design
## General Algorithm:
    • Create all files that program needs,
    • Populate essential files with information if not already done so,
    • Start user menu,
    • Allow full manoeuvrability up and down menu tree,
    • Have USER MANUAL and MANAGEMENT sections on same level as the main BANK options,
    • Only allow management functions to be selected after password protection function.
# Implementation
## Functions:
    • Main,
    • Startup,
    • Populate,
    • Mainmenu,
    • Usermanual,
    • Entermanagement,
    • Management,
    • Statistics,
    • Nofcus,
    • Nofstruct,
    • Avgcusacct,
    • Avgbal,
    • Loanacct,
    • Totloaned,
    • Totdep,
    • Totdraw,
    • Checkacctnum,
    • Viewstruct,
    • Delacct,
    • Delaccount,
    • Delloan,
    • Deldirdeb,
    • Decnumcus,
    • Deccustno,
    • Managevalues,
    • Bankmode,
    • Checkacctstat.
### Main
    • Clears screen,
    • Ensures that all files exist and are populated,
    • Enters the menu tree.
### Startup
    • Ensures all required files exist in the folder.

### Populate
    • Requests password and APR information,
    • Writes information to appropriate file.
### Mainmenu
    • First part of menu tree.
### Usermanual
    • Allows user to read about the program, learning about how it works and what it has to offer.
### Entermanagement
    • Enter password function.
### Management
    • Menu choose between management options.
### Statistics
    • Allows user to decide upon which statistics they wish to view.
### Nofcus
    • Reads from statistics file and returns number of customers (recorded in file).
### Nofstruct
    • Returns number of structures in a file,
    • Can return this number for any file type and depends on the input ‘int’.
### Avgcusacct
    • Returns the average number of accounts per customer.
### Avgbal
    • Returns the average balance across all accounts.
### Loanacct
    • Allows user to view all loans under any entered account.
### Totloaned
    • Returns the total amount loaned out by the bank at the time requested.
### Totdep
    • Returns the total amount that has been deposited under the files in that folder.
### Totdraw
    • Returns the total amount that has been withdrawn under the files in that folder.
### Checkacctnum
    • Checks to see if an account exists under the input account number,
    • Returns 0 for exists, 1 for does not exist.
### Viewstruct
    • Views all structures under the inputted account number,
    • Only views the type of structure requested from the associated file (inputted by the user),
    • Returns 0 if found, 1 if not.
### Delacct
    • Directs the deletion of the account and all associated loan and direct debit records under the user entered account number.
### Delaccount
    • Deletes the account from the accounts file.
### Delloan
    • Deletes the associated loan records from the loan file.
### Deldirdeb
    • Deletes the associated direct debit records from the direct debits file.
### Decnumcus
    • Returns the number of accounts that a specified customer has within the accounts file.
### Deccustno
    • Decreases the number of customers statistic in the statistics file.
### Managevalues
    • Option to change APRs and to change them,
    • Option to change a selected accounts status and changes it,
    • Option to delete account.
### Bankmode
    • The main BANK MENU, where the main branches of normal banking are options.
### Checkacctstat
    • Checks the status of an account,
    • Returns 0 is the account is active, 1 if it is blocked.



# Testing
Testing for my program had to occur in very broken down steps. Often testing could only be done where functions themselves were broken down into smaller chunks of code. The reason for this is because a lot of my program relies on the results of functions and actions that were the responsibility of others within the group. Usually, small chunks of code were tested and then built up into the functions that they exist as now. It wasn’t until later during the development stages that I could easily test my functions while they were completed. This is why my code will not compile on its own. It requires the rest of the program. However, as the program came together testing continued and some of the outcomes are as below.
Upon the program starting in a new folder, unless the user has copied across the required files, (specifically the management file), then the user will receive…

The program also requires APR values in the loan1, loan3 and loan5 files…

And will receive one for the next 2 term options too.
Once essential information is gathered then the first menu will be displayed.

Management requires the password...

## View statistics.
A range of stats are available, all have been tested:
    • The add function increases the number of customers when a new customer as added, and my delete function decreases it when a customer’s last account is deleted.
    • The number of accounts simply calls the generic function nofstruct with regards to the accounts file.



Within the change menu options to change APR, account status and delete account can be found.
The functions take the user through a very simple step-by-step process that provides the user with as much information as they could need to complete the task as they wish to. 
The account status will tell you what the state is before and after to ensure that the user knows the state at any time during the process.




During deletion, the information is all to view for the user so they can make a visual check on the account records before confirming that they wish to permanently delete them.
Other functions that have been used throughout the group program such as ‘checkacctnum’ and ‘checkacctstat’ have been tested on an individual level to ensure that they only return the values that they should. These functions are very regularly called as they are important check functions and make it an easy method to decide whether to go ahead with a loan or direct debit for any user entered account number.
