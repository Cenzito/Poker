#include <cryptopp/sha.h>
#include <cryptopp/hex.h>
#include <cryptopp/filters.h>
#include <string>
#include <iostream>
#include <random>
#include <algorithm>

using namespace std;


class Hash{
public:
    Hash(string password);
    string get_pass();
    string HashPassword();
    string generate(size_t len);
private:
    string password;
};
