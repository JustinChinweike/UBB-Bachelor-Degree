 #  Bank accounts
At a bank, we have to keep track of the balance of some accounts.

We have concurrently run transfer operations, to be executer on multiple threads. Each operation transfers a given amount of money from one account to someother account.

From time to time, as well as at the end of the program, a consistency check shall be executed. It shall verify that the total amount of money in all accounts is the same as in the beginning.

### Requirements Summary
- Use multiple threads to perform random transfer operations on shared data.
- Protect shared data using mutexes to avoid race conditions.
- Ensure invariants hold: total balance remains constant.
- Threads must run independently where possible (fine-grained locking).
- Main thread waits for all threads to finish, then verifies consistency.
- Performance experiments should vary thread count and locking granularity.
