Week 9

My partner implemented the basic server which could make people communicate and I read the documents about SQLite and 
try to implement the account creation by the library <sqlite3.h>.

Eventually, I did not use the SQL to build the account creation. Instead of that, I utilise the struct and class to implement.
The function in class could check if the username exists and if the username and password are correct.

Week 10

During this week, I change something to create the account. We find out we need to store all of the account information in a file because
the program cannot execute 24/7 thus I use the <sqlite3.h> to implement it. I created the class which has attribute db and some auxilliary
functions.

Main functions:

void CreationTable(const char* sql);
void Insertaccount(const std::string &username, const std::string &password);
bool Check_repetition(const std::string &username);

Functionality:
Now, we can let people create the account and delete the account. Moreover, we could check if people try to create the account with
the same username as other's. There will be the detailed illustration in code file.


