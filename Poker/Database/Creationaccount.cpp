#include <iostream>
#include <cstring>
#include <sqlite3.h>
#include "Creationaccount.hpp"
#include "hash.hpp"

using namespace std;

//This is a constructor
CreationAccount::CreationAccount(const char* dbName) : db(nullptr) {
        int rc = sqlite3_open(dbName, &db);
        if (rc) {
            std::cerr << "Cannot open database: " << sqlite3_errmsg(db) << std::endl;
        } else {
            std::cout << "Open database Successfully" << std::endl;
        }
}

//This closes the database
CreationAccount::~CreationAccount() {
    if (db) {
        sqlite3_close(db);
    }
}

sqlite3* CreationAccount::get_db(){
    return this->db;
}

int CreationAccount::callback(void* data, int argc, char** argv, char** azColName) {
    CreationAccount* instance = static_cast<CreationAccount*>(data);
    return instance->callbackMemberFunction(argc, argv, azColName);
}

int CreationAccount::moneycallback(void* data, int argc, char** argv, char** azColName) {
    if (argc > 0 && argv[0]) {
        double* money = static_cast<double*>(data);
        *money = std::stod(argv[0]);
    }
    return 0;
}

//callback function allows for printing all of data
int CreationAccount::callbackMemberFunction(int argc, char** argv, char** azColName) {
    static int count = 0;

    int i;
    for (i = 0; i < argc; i++) {
            std::cout<< azColName[i] << "=" << (argv[i] ? argv[i] : "NULL") <<std::endl;
    }
    std::cout<<std::endl;
    return 0;
}

int CreationAccount::countCallback(void* data, int argc, char** argv, char** azColName) {
    int* count = static_cast<int*>(data);
    if (argc > 0 && argv[0]) {
        *count = std::stoi(argv[0]);
    }
    return 0;
}

int CreationAccount::printcallback(void *NotUsed, int argc, char **argv, char **azColName) {
    for (int i = 0; i < argc; i++) {
        std::cout << azColName[i] << " = " << (argv[i] ? argv[i] : "NULL") << std::endl;
    }
    std::cout << std::endl;
    return 0;
}

//This function allows for the execution of the sql sentence
void CreationAccount::executeSQL(const char* sql) {
    char* zErrMsg = nullptr;
    int rc = sqlite3_exec(db, sql, callback, this, &zErrMsg);
    if (rc != SQLITE_OK) {
            std::cerr << "SQL Operation mistake: " << sqlite3_errmsg(db) << std::endl;
            sqlite3_free(zErrMsg);
    }
    else{
        std::cout << "SQL Operation success" << std::endl;
    }
}

//This creates a table which lets us store data 
void CreationAccount::CreationTable(const char* sql){
    char *zErrMsg = 0;
    int rc = sqlite3_exec(db, sql, 0, 0, &zErrMsg);

    if (rc != SQLITE_OK){
        std::cerr << "Cannot create the table: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_free(zErrMsg);
    } 
    else {
        std::cout << "Create the table succesfully" << std::endl;
    }
}

//Insert the data into the table 
void CreationAccount::Insertaccount(const std::string &username, const std::string &password) {
    char* errMsg = nullptr;
    Hash hashpass = Hash(password);
    string salt = hashpass.generate(16);
    string new_str = hashpass.HashPassword() + salt;
    std::string insertQuery = "INSERT INTO ACCOUNT (USERNAME, PASSWORD, MONEY, SALT) VALUES ('" 
                              + username + "', '" + new_str + "', " 
                              + std::to_string(1000) + ", '" + salt + "');";
    sqlite3_exec(db, insertQuery.c_str(), 0, 0, &errMsg);
}

double CreationAccount::get_money(sqlite3* db, const std::string &username){
    double money = 0.0;
    std::string sqlQuery = "SELECT money FROM ACCOUNT WHERE username = '" + username + "';";
    char* errMsg = nullptr;

    if (sqlite3_exec(db, sqlQuery.c_str(), moneycallback, &money, &errMsg) != SQLITE_OK) {
        std::cerr << "Error executing SQL query: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }

    return money;
}

void CreationAccount::update(sqlite3* db, const std::string &username, double number){
    double money = get_money(db, username);
    char* errMsg = nullptr;
    std::string sqlQuery = "UPDATE ACCOUNT SET money = " + std::to_string(money + number) + " WHERE username = '" + username + "';";
    sqlite3_exec(db, sqlQuery.c_str(), 0, 0, &errMsg);
}

//Check if there is a repetition name
bool CreationAccount::Check_repetition(const std::string &username){
    std::string query = "SELECT COUNT(*) FROM ACCOUNT WHERE USERNAME=?;";

    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);

    if (rc != SQLITE_OK) {
        std::cerr << "SQL prepare error: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    rc = sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL bind error: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return false;
    }

    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        int count = sqlite3_column_int(stmt, 0);
        sqlite3_finalize(stmt);
        return count > 0;
    } else {
        std::cerr << "SQL step error: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return false;
    }
}

//Print all of data in table
void CreationAccount::Print(){
    char *zErrMsg = 0;
    const char *selectDataSQL = "SELECT * FROM ACCOUNT;";
    int rc = sqlite3_exec(db, selectDataSQL, printcallback, 0, &zErrMsg);

    if (rc != SQLITE_OK) {
        std::cerr << "SQL Operation mistake: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_free(zErrMsg);
    } else {
        std::cout << "Printed all data successfully" << std::endl;
    }
}

//Delete all of data in table
void CreationAccount::Delete(){
    std::string deleteDataSQL = "DELETE FROM Account";
    executeSQL(deleteDataSQL.c_str());
}

//This function checks if account information is correct when people try to log in
bool CreationAccount::login(const std::string &username, const std::string &password){
    std::string query = "SELECT COUNT(*) FROM ACCOUNT WHERE USERNAME=? AND PASSWORD=?;";

    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);

    if (rc != SQLITE_OK) {
        std::cerr << "SQL prepare error: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    rc = sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL bind username error: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return false;
    }

    rc = sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL bind password error: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return false;
    }

    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        int count = sqlite3_column_int(stmt, 0);
        sqlite3_finalize(stmt);
        return count > 0; 
    } else {
        std::cerr << "SQL step error: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return false;
    }
}

string CreationAccount::get_Salt(sqlite3* db, const std::string& username) {
    std::string sqlQuery = "SELECT salt FROM ACCOUNT WHERE USERNAME = '" + username + "';";
    sqlite3_stmt* stmt;
    std::string salt;

    if (sqlite3_prepare_v2(db, sqlQuery.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Error preparing statement: " << sqlite3_errmsg(db) << std::endl;
        return "";
    }

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        const unsigned char* saltText = sqlite3_column_text(stmt, 0);
        if (saltText) {
            salt = reinterpret_cast<const char*>(saltText);
        }
    }

    sqlite3_finalize(stmt);
    return salt;
}

