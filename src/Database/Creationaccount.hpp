#include <iostream>
#include <sqlite3.h>
#include <cryptopp/rsa.h>
#include <cryptopp/osrng.h>
#include <cryptopp/base64.h>

class CreationAccount {
public:

    CreationAccount(const char* dbName);
    ~CreationAccount();
    static int callback(void* data, int argc, char** argv, char** azColName);
    int callbackMemberFunction(int argc, char** argv, char** azColName);
    int countCallback(void* data, int argc, char** argv, char** azColName);
    static int printcallback(void* data, int argc, char** argv, char** azColName);
    void executeSQL(const char* sql);
    void CreationTable(const char* sql);
    void Insertaccount(const std::string &username, const std::string &password);
    bool Check_repetition(const std::string &username);
    void Print();
    void Delete();
    bool login(const std::string &username, const std::string &password);

private:
    sqlite3* db;
    //CryptoPP::RSA::PublicKey public_key;
    //CryptoPP::RSA::PrivateKey private_key;
};