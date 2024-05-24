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
char add(char a, char b)
{
    return mod(((a - 'a') + (b - 'a')), 26) + 'a';
}
char sub(char a, char b)
{
    return mod(((a - 'a') - (b - 'a')), 26) + 'a';
}