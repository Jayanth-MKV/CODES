#include<stdio.h>
#include<string.h>

void charstuff(char a[],char sd,char ed){
char res[50]= " ", t[2];
char x[3]={sd,'\0'},
	s[3]={sd,sd},
	d[3]={ed,ed},
	y[3]={ed,'\0'};

strcat(res, x);
int i;
        for(i = 0; i < strlen(a); i++)
        {
            t[0] = a[i];
            t[1] = '\0';
            if(t[0] == sd)
                strcat(res, s);
            else if(t[0] == ed)
                strcat(res, d);
            else
                strcat(res, t);
        }
        strcat(res, y);
        printf("After stuffing:%s\n", res);

}

int main()
{
        char a[30]= " ", sd, ed;
        printf("Enter characters to be stuffed:\n");
        scanf("%s", a);
        printf("Enter a character that represents starting delimiter\n:");
        scanf(" %c", &sd);
        printf("Enter a character that represents ending delimiter\n:");
        scanf(" %c", &ed);
        charstuff(a,sd,ed);
        
    }
