#include <stdio.h>
#include <string.h>

void encrypt(char[], int, int);
void decrypt(char[], int, int);

int main()
{

    int c;
    printf("Enter Your Choice :\n 1.Encrypt\n 2.Decrypt\n 0.Exit\n");
    scanf("%d", &c);

    while (c != 0)
    {

        if (c == 1)
        {
            char str[100], ch;
            int key;
            printf("Enter the Key : ");
            scanf(" %d", &key);

            printf("Enter The Plain Text : ");
            scanf(" %[^\n]s", str);

            // scanf(" %c", &ch);

            // printf("%ld\n",strlen(str));
            printf("Plain Text      : %s\n", str);
            printf("Key      : %d\n", key);
            encrypt(str, key, strlen(str));
        }
        else if (c == 2)
        {

            char str[100], ch;
            printf("Enter The Cipher Text : ");
            scanf(" %[^\n]s", str);

            int key;
            printf("Enter the Key : ");
            scanf(" %d", &key);

            printf("Cipher Text      : %s\n", str);
            printf("Key      : %d\n", key);
            decrypt(str, key, strlen(str));
        }

        printf("Enter Your Choice :\n 1.Encrypt\n 2.Decrypt\n 0.Exit\n");
        scanf("%d", &c);
    }

    return 0;
}

void encrypt(char str[], int key, int len)
{
    char res[100];
    res[len] = '\0';
    for (int i = 0; i < len; i++)
    {
        res[i] = tolower(str[i]);
    }

    // printf("Lower Text  : %s\n", res);
    //  printf("size  : %ld\n", strlen(res));

    key = key % 26;
    for (int i = 0; i < len; i++)
    {
        if (res[i] == 32)
            continue;

        res[i] = 'a' + ((res[i] - 'a') + key) % 26;
    }

    printf("Cipher Text  : %s\n", res);
}

void decrypt(char cip[], int key, int len)
{
    char res[100];
    res[len] = '\0';
    key = key % 26;
    for (int i = 0; i < len; i++)
    {
        if (cip[i] == 32)
            continue;
        cip[i] = 'a' + (26 + cip[i] - 'a' - key) % 26;
    }

    printf("Plain Text  : %s\n", cip);
}