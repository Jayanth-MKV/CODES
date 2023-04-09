#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

char KT[5][5] = {0};

void getpos(char a, char b, int arr[])
{
    if (a == 'j')
        a = 'i';
    if (b == 'j')
        b = 'i';
    // printf("%c %c\nn", a, b);

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            // printf("%c ", KT[i][j]);
            if (KT[i][j] == a)
            {
                arr[0] = i;
                arr[1] = j;
            }
            else if (KT[i][j] == b)
            {
                arr[2] = i;
                arr[3] = j;
            }
        }
        // printf("\n");
    }

    // for (int f = 0; f < 4; f++)
    //     printf("%d ", arr[f]);
}

void encrypt(char text[])
{
    int n = strlen(text);
    int j = 0;
    // Convert to Lower and remove spaces
    for (int i = 0; i < n; i++)
    {
        if (text[i] != ' ')
            text[j++] = tolower(text[i]);
    }
    n = j;
    char ans[20] = "";

    // add extra chars at end if it is odd length and also if same letter exists
    int no_x = 1;
    while (no_x)
    {
        no_x = 0;
        for (int i = 0; i < n; i += 2)
        {
            if (text[i] == text[i + 1])
            {
                n++;
                char t = text[i + 1];
                for (int j = n - 1; j >= i + 1; j--)
                {
                    text[j] = text[j - 1];
                }
                text[i + 1] = 'x';
                no_x = 1;
                i -= 2;
            }
        }
    }

    if (n % 2 != 0)
    {
        text[n++] = 'x';
        text[n] = '\0';
    }

    // for (int i = 0; i < n; i++)
    // {
    //     printf("%c ", text[i]);
    // }
    // printf("\n");

    for (int i = 0; i < n; i += 2)
    {
        int arr[4];
        printf("%c %c\n", text[i], text[i + 1]);
        getpos(text[i], text[i + 1], arr);
        
        for (int f = 0; f < 4; f++)
            printf("%d ", arr[f]);
        printf("\n");

        if (arr[0] == arr[2])
        {
            ans[i] = KT[arr[0]][(arr[1] + 1) % 5];
            ans[i + 1] = KT[arr[0]][(arr[3] + 1) % 5];
        }
        else if (arr[3] == arr[1])
        {
            ans[i] = KT[(arr[0] + 1) % 5][arr[1]];
            ans[i + 1] = KT[(arr[2] + 1) % 5][arr[1]];
        }
        else
        {
            ans[i] = KT[arr[0]][arr[3]];
            ans[i + 1] = KT[arr[2]][arr[1]];
        }
    }

    printf("%d\n", strlen(ans));
    printf("%s\n", ans);
}

void KeyTable(char key[], char text[])
{
    int k = strlen(key);
    // printf("%d\n", k);

    int *dict = (int *)malloc(sizeof(int) * 26);

    for (int i = 0; i < 26; i++)
        dict[i] = 0;

    for (int i = 0; i < k; i++)
    {
        key[i] = tolower(key[i]);
        dict[key[i] - 97] = 1;
    }
    dict['j' - 97] = 1;
    
    for (int i = 0; i < 26; i++)
        printf("%c - %d\n", (i + 97), dict[i]);

    int p = 0, q = 0;

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (p < k)
                KT[i][j] = key[p++];
            else
            {
                while(dict[q] != 0)
                {
                    q++;
                }
                KT[i][j] = (char)(q + 97);
                dict[q++] = 1;
            }
            // p++;
        }
    }

    encrypt(text);

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            printf("%c ", KT[i][j]);
        }
        printf("\n");
    }
}

void search(){

}

int main(int argc, char const *argv[])
{
    char keyword[10], text[20];
    strcpy(keyword, "MONARCHY");
    // strcpy(text, "instruments");
    strcpy(text, "Helloe");
    KeyTable(keyword, text);
    // encrypt(text);
    return 0;
}