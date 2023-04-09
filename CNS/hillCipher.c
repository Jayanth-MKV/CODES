#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void getKeyMatrix(char* key, int keyMatrix[][3])
{
    int k = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            keyMatrix[i][j] = (key[k]) % 65;
            k++;
        }
    }
}

void encrypt(int cipherMatrix[][1],
             int keyMatrix[][3],
             int messageVector[][1])
{
    int x, i, j;
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 1; j++)
        {
            cipherMatrix[i][j] = 0;

            for (x = 0; x < 3; x++)
            {
                cipherMatrix[i][j] +=
                    keyMatrix[i][x] * messageVector[x][j];
            }

            cipherMatrix[i][j] = cipherMatrix[i][j] % 26;
        }
    }
}

void HillCipher(char* message, char* key)
{
    int keyMatrix[3][3];
    getKeyMatrix(key, keyMatrix);

    int messageVector[3][1];

    for (int i = 0; i < 3; i++)
        messageVector[i][0] = (message[i]) % 65;

    int cipherMatrix[3][1];

    encrypt(cipherMatrix, keyMatrix, messageVector);

    char *CipherText = (char *)malloc(3 * sizeof(char));

    for (int i = 0; i < 3; i++){
        CipherText[i] = cipherMatrix[i][0] + 65;
    }

    printf("%s", CipherText);
}

int main(){
    char* message = "ACTACTBAT";
    char *key = "GYBNQKURP";
    int k = 0;
    char* m=(char*)malloc(3*sizeof(char));
    printf("CipherText: ");
    for (int i = 0; i < strlen(message); i++)
    {
        m[k] = message[i];
        k++;
        if(k%3==0){
            HillCipher(m, key);
            k = 0;
        }
    }

    return 0;
}