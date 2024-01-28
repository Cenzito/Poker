#include <cryptopp/sha.h>
#include <cryptopp/hex.h>
#include <cryptopp/filters.h>
#include <string>
#include <iostream>
#include "hash.hpp"

using namespace std;


Hash::Hash(string password){
    this->password = password;
}

string Hash::get_pass(){
    return this->password;
}

string Hash::HashPassword() {
    CryptoPP::SHA256 hash;
    std::string digest;

    CryptoPP::StringSource s(password, true,
        new CryptoPP::HashFilter(hash,
            new CryptoPP::HexEncoder(
                new CryptoPP::StringSink(digest)
            )
        )
    );
    return digest; // This is the hash you'd store in the database
}

string Hash::generate(size_t len){
    const std::string characters = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<> distribution(0, characters.size() - 1);

    std::string randomString;
    for (size_t i = 0; i < len; ++i) {
        randomString += characters[distribution(generator)];
    }

    return randomString;
}

