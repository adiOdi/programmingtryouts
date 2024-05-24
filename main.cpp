// this is a implementation of an https://en.m.wikipedia.org/wiki/Autokey_cipher
// I implemented a nonlinear key advance mechanism to hopefully combat the weaknesses described

#include <string>
#include <iostream>
#include <fstream>
#include <exception>
#include "mathhelpers.hpp"

using std::string;

string encrypt(string &key, string &message);
string decrypt(string &key, string &ciphertext);
void advanceKey(string &key, const string &message, size_t pos);
int main(int argc, char *argv[])
{
    std::cout << std::endl;
    try
    {
        if (argc < 2)
            throw std::invalid_argument("usage: mode[-d/-e] key message, argc <2");
        string mode = argv[1];
        string key;
        string text;
        if (mode == "-e")
        {
            if (argc < 4)
                throw std::invalid_argument("usage: mode[-d/-e] key message, argc <4");
            key = argv[2];
            if (key.size() < 26)
                throw std::invalid_argument("key must be longer than 26 characters");
            for (int i = 3; i < argc; i++)
            {
                text += argv[i];
                text += ' ';
            }
            std::cout << encrypt(key, text) << std::endl;
        }

        else
        {
            if (argc < 3)
                throw std::invalid_argument("usage: mode[-d/-e] key message, argc <3");
            key = argv[2];
            if (key.size() < 26)
                throw std::invalid_argument("key must be longer than 26 characters");
            if (argc >= 4)
                for (int i = 3; i < argc; i++)
                {
                    text += argv[i];
                    text += ' ';
                }
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
string encrypt(string &key, string &message)
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
    key += add(msg_now, key.at(key.size() - (int)(toInt(msg_now) / 2) - 1));
}
