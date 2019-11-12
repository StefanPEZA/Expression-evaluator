float stringToNumber(char *ch)
{
    bool isDecimal = false;
    short j = 0;
    if (ch == NULL)
        return 0;
    float n = 0, p = 1;
    if (ch[0] == '-')
        j++;
    for (int i = j; ch[i]; i++)
    {
        if (!isDecimal && ch[i] != '.')
        {
            if (ch[i] == '0')
                n = n*10 + 0;
            else if (ch[i] == '1')
                n = n*10 + 1;
            else if (ch[i] == '2')
                n = n*10 + 2;
            else if (ch[i] == '3')
                n = n*10 + 3;
            else if (ch[i] == '4')
                n = n*10 + 4;
            else if (ch[i] == '5')
                n = n*10 + 5;
            else if (ch[i] == '6')
                n = n*10 + 6;
            else if (ch[i] == '7')
                n = n*10 + 7;
            else if (ch[i] == '8')
                n = n*10 + 8;
            else if (ch[i] == '9')
                n = n*10 + 9;
            else
                return 0;
        }
        else if (!isDecimal && ch[i] == '.')
        {
            p *= 10;
            isDecimal = true;
        }
        else if (isDecimal && ch[i] != '.')
        {
            if (ch[i] == '0')
                n = n + 0;
            else if (ch[i] == '1')
                n = n + 1/p;
            else if (ch[i] == '2')
                n = n + 2/p;
            else if (ch[i] == '3')
                n = n+ 3/p;
            else if (ch[i] == '4')
                n = n + 4/p;
            else if (ch[i] == '5')
                n = n + 5/p;
            else if (ch[i] == '6')
                n = n+ 6/p;
            else if (ch[i] == '7')
                n = n + 7/p;
            else if (ch[i] == '8')
                n = n + 8/p;
            else if (ch[i] == '9')
                n = n + 9/p;
            else
                return 0;
            p = p * 10;
        }

    }
    if (ch[0] == '-')
    {
        n = -n;
    }
    return n;
}



