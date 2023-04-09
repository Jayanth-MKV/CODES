// C program to illustrate Rail Fence Cipher
// Encryption and Decryption

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void encryptRailFence(char* text, int key)
{
    int n = strlen(text);
    char rail[key][(n)];

    for (int i = 0; i < key; i++)
        for (int j = 0; j < n; j++)
            rail[i][j] = '\n';

    int dir_down = 0;
    int row = 0, col = 0;

    for (int i = 0; i < n; i++)
    {

        if (row == 0 || row == key - 1){
            if(dir_down==0)
            dir_down = 1;
            else
            dir_down = 0;
        }

        rail[row][col++] = text[i];

        dir_down==1 ? row++ : row--;
    }

    int k = 0;
    for (int i = 0; i < key; i++)
        for (int j = 0; j < n; j++){

            if (rail[i][j] != '\n'){
                printf("%c", rail[i][j]);
                k++;
            }
        }

    printf("\n");

}

void decryptRailFence(char* cipher, int key)
{

    int n = strlen(cipher);
    char rail[key][n];

    for (int i = 0; i < key; i++)
        for (int j = 0; j < n; j++)
            rail[i][j] = '\n';

    int dir_down=0;

    int row = 0, col = 0;

    for (int i = 0; i < n; i++)
    {
        if (row == 0)
            dir_down = 1;
        if (row == key - 1)
            dir_down = 0;

        rail[row][col++] = '*';

        dir_down==1 ? row++ : row--;
    }

    int index = 0;
    for (int i = 0; i < key; i++)
        for (int j = 0; j < n; j++)
            if (rail[i][j] == '*' && index < n)
                rail[i][j] = cipher[index++];


    row = 0, col = 0;
    int k = 0;
    for (int i = 0; i < n; i++)
    {
        if (row == 0)
            dir_down = 1;
        if (row == key - 1)
            dir_down = 0;

        if (rail[row][col] != '*'){
            printf("%c", rail[row][col++]);
            k++;
        }

        dir_down ? row++ : row--;
    }
    printf("\n");
}

int main()
{
    encryptRailFence("attack at once", 2);
    encryptRailFence("GeeksforGeeks ", 3);
    encryptRailFence("defend the east wall", 3);

    decryptRailFence("GsGsekfrek eoe", 3);
    decryptRailFence("atc toctaka ne", 2);
    decryptRailFence("dnhaweedtees alf tl", 3);

    return 0;
}
