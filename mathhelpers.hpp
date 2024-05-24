#include <exception>
#include <iostream>
int mod(int in, int max)
{
    while (in >= max)
    {
        in -= max;
    }
    while (in < 0)
    {
        in += max;
    }
    return in;
}
int toInt(char c)
{
    if (c == ' ')
    {
        return 0;
    }
    if (c >= '0' && c <= '9')
    {
        return c - '0' + 1;
    }
    if (c >= 'a' && c <= 'z')
    {
        return c - 'a' + 11;
    }
    if (c >= 'A' && c <= 'Z')
    {
        return c - 'A' + 37;
    }
    if (c == 0)
    {
        return 0;
    }
    throw std::invalid_argument("key or message contain non-characters");
}
char toChar(int i)
{
    // std::cout << "returning char at: " << i << std::endl;
    return " 0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"[i];
}
char add(char a, char b)
{
    return toChar(mod((toInt(a) + toInt(b)), 63));
}
char sub(char a, char b)
{
    return toChar(mod((toInt(a) - toInt(b)), 63));
}