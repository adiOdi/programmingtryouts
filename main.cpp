// this is a implementation of an https://en.m.wikipedia.org/wiki/Autokey_cipher
// I implemented a nonlinear key advance mechanism to hopefully combat the weaknesses described

#include <string>
#include <iostream>
#include <fstream>
#include <exception>
#include "mathhelpers.hpp"

using std::string;

string encrypt(string &key, const string &message);
string decrypt(string &key, string &ciphertext);
void advanceKey(string &key, const string &message, size_t pos);

int main(int argc, char *argv[])
{
    try
    {
        if (argc < 2)
            throw std::invalid_argument("usage: mode[-d/-e] key message");
        string mode = argv[1];
        string key;
        string text;
        if (mode == "-e")
        {
            if (argc != 4)
                throw std::invalid_argument("usage: mode[-d/-e] key message");
            key = argv[2];
            text = argv[3];
            std::cout << encrypt(key, text) << std::endl;
        }

        else
        {
            if (argc != 4 && argc != 3)
                throw std::invalid_argument("usage: mode[-d/-e] key message");
            key = argv[2];
            if (argc == 4)
                text = argv[3];
            else
                text = "";
            std::cout << decrypt(key, text) << std::endl;
        }

        return 0;
    }
    catch (const std::invalid_argument &e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }
}
string encrypt(string &key, const string &message)
{
    string ciphertext;
    for (size_t i = 0; i < message.size(); i++)
    {
        ciphertext += add(message.at(i), key.at(i));
        advanceKey(key, message, i);
    }
    std::ofstream file("ciphertext.txt");
    file.clear();
    file << ciphertext;
    file.close();
    return ciphertext;
}
string decrypt(string &key, string &ciphertext)
{
    if (ciphertext.size() == 0)
    {
        std::cout << "geting ciphertext from file..." << std::endl;
        std::ifstream file("ciphertext.txt");
        if (file.is_open())
        {
            std::getline(file, ciphertext);
            file.close();
        }
        std::cout << "got:" << ciphertext << std::endl;
    }

    string message;
    for (size_t i = 0; i < ciphertext.size(); i++)
    {
        message += sub(ciphertext.at(i), key.at(i));
        advanceKey(key, message, i);
    }
    return message;
}
void advanceKey(string &key, const string &message, size_t pos)
{
    char msg_now = message.at(pos);
    key += add(msg_now, key.at(key.size() - (msg_now - 'a') - 1));
}
