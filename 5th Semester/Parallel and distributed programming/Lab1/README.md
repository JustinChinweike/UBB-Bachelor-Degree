# Bank Accounts

At a bank, we have to keep track of the balance of several accounts.

We run concurrent transfer operations executed on multiple threads.  
Each operation transfers a given amount of money from one account to another.

From time to time, as well as at the end of the program, a **consistency check** is performed to verify that the **total amount of money in all accounts** remains the same as in the beginning.

