#include <iostream>
#include <cstring>
#include <sqlite3.h>
#include <cryptopp/rsa.h>
#include <cryptopp/osrng.h>
#include <cryptopp/base64.h>
#include "Creationaccount.hpp"

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

int CreationAccount::callback(void* data, int argc, char** argv, char** azColName) {
    CreationAccount* instance = static_cast<CreationAccount*>(data);
    return instance->callbackMemberFunction(argc, argv, azColName);
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
    std::string insertQuery = "INSERT INTO ACCOUNT (USERNAME, PASSWORD) VALUES ('" + username + "', '" + password + "');";
    //std::string insertQuery = "INSERT INTO ACCOUNT (USERNAME, PASSWORD) VALUES ('" + encryptRSA(username, public_key) + "', '" + encryptRSA(password, public_key) + "');";
    executeSQL(insertQuery.c_str());
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

