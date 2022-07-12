#include<stdio.h>
#include<string.h>

void charstuff(char a[],char sd,char ed,char flag){
char res[50]= " ", t[2];
char c[2]={sd,'\0'},
     b[2]={ed,'\0'},
	x[3]={flag,flag},
        s[3]={flag,sd},
        d[3]={flag,ed};

strcat(res, c);
int i;
        for(i = 0; i < strlen(a); i++)
        {
            t[0] = a[i];
            t[1] = '\0';
            if(t[0] == sd)
                strcat(res, s);
            else if(t[0] == ed)
                strcat(res, d);
            else if(t[0]==flag)
		strcat(res,x);
	    else
                strcat(res, t);
        }
strcat(res, b);
printf("After stuffing:%s\n", res);

}

int main()
{
        char a[30], sd, ed,flag;
        printf("Enter characters to be stuffed:\n");
        scanf("%s", a);
        printf("Enter a character that represents starting delimiter\n:");
        scanf(" %c", &sd);
        printf("Enter a character that represents ending delimiter\n:");
        scanf(" %c", &ed);
	printf("Enter the flag\n:");
        scanf(" %c", &flag);
        charstuff(a,sd,ed,flag);

	return 0; 
}

