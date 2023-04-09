// C code to implement Vigenere Cipher

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* generateKey(char* str, char* key)
{
    int x = strlen(str);
    int n = strlen(key);

    char *res = (char *)malloc(x);

    for (int i = 0;i<x; i++)
    {
        res[i] = key[i % n];
    }
    return res;
}


void cipherText(char* str, char* key)
{
    int n = strlen(str);
    char* cipher_text=(char*)malloc(n);

    for (int i = 0; i < n; i++)
    {
        char x = (str[i] + key[i]) % 26;

        x += 'A';
        printf("%c", x);
    }
}


void originalText(char* cipher_text, char* key)
{
    int n = strlen(cipher_text);

    for (int i = 0; i < n; i++)
    {
        char x = (cipher_text[i] - key[i] + 26) % 26;

        x += 'A';
        printf("%c", x);
    }
}

int main()
{
    char* str = "GEEKSFORGEEKS";
    char* keyword = "AYUSH";

    char* key = generateKey(str, keyword);
    cipherText(str, key);
    printf("\n");
    originalText("GCYCZFMLYLEIM", key);

    return 0;
}
