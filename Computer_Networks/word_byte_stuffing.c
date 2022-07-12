#include<stdio.h>
#include<string.h>

void charstuff(char a[],char sd[],char ed[],char flag[]){
char res[100]= " ", t[2],temp[20];
int len_sd=strlen(sd),len_ed=strlen(ed),len_flag=strlen(flag);
//char str_sd[len_sd], str_ed[len_ed] , str_flag[len_flag];
char x[2*len_flag];
memset(x, '\0', sizeof(x));
strcat(x,flag);
strcat(x,flag);

       char s[len_sd];
       memset(s, '\0', sizeof(s));
       strcat(s,flag);
       strcat(s,sd);

       char d[len_ed];
       memset(d, '\0', sizeof(d));
       strcat(d,flag);
       strcat(d,ed);

strcat(res, sd);
int i,j;
        for(i = 0; i < strlen(a); i++)
        {int k=0;
	t[0]=a[i];
	t[1]='\0';
	char str_sd[len_sd+1], str_ed[len_ed+1] , str_flag[len_flag+1];
	memset(str_sd, '\0', sizeof(str_sd));
	memset(str_ed, '\0', sizeof(str_ed));
	memset(str_flag, '\0', sizeof(str_flag));
	//str_sd[]=" ",str_ed[0]='\0',str_flag[0]='\0';
	for(j = i; j <i+len_sd && i+len_sd<=strlen(a); j++){
	str_sd[k++]=a[j];
	}
	k=0;
	 for(j = i; j <i+len_ed && i+len_ed<=strlen(a); j++){
        str_ed[k++]=a[j];
        }
	k=0; 
	 for(j = i; j <i+len_flag&& i+len_flag<=strlen(a); j++){
        str_flag[k++]=a[j];
        }
	printf("%s-%d %s-%d %s-%d \n",str_sd,len_sd,str_ed,len_ed,str_flag,len_flag);

            if(!(strcmp(sd,str_sd)))
                strcat(res, s);
            else if(!(strcmp(ed,str_ed)))
                strcat(res, d);
            else if(!(strcmp(flag,str_flag)))
		strcat(res,x);
	    else
                strcat(res, t);
       printf("%s\n",res);
	}
strcat(res, ed);
printf("After stuffing:%s\n", res);

}

int main()
{
        char a[30], sd[10], ed[10],flag[10];
        printf("Enter characters to be stuffed:\n");
        scanf("%s", a);
        printf("Enter the starting delimiter\n:");
        scanf(" %s", sd);
        printf("Enter the  ending delimiter\n:");
        scanf(" %s", ed);
	printf("Enter the flag\n:");
        scanf(" %s", flag);
        charstuff(a,sd,ed,flag);

	return 0; 
}

