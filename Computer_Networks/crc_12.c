#include<stdio.h>
int main(){

	int n,i;
	printf("Enter no of bits \n");
	scanf("%d",&n);
	int a[n];
	printf("Enter the bits \n");
/*	for(i=0;i<n;i++){
	scanf("%d",a[i]);
	}
*/	int divisor[]={1,0,1,1};
	int m=sizeof(divisor)/sizeof(divisor[0]);
	int b[n+m];
	for(i=0;i<n;i++){
        if(i<m){
	b[i]=a[i];
	}
	else{
	b[i]=0;
	}
        }
	int carry=0,num[m],res[m],j,quo_cnt=0;
	for(i=0;i<m;i++){
    	   res[i]=0;
  	   num[i]=0;	   
        }

	i=0;
	int one_occur=0;
	while(i<n){
		int cnt=0;
	for(k=0;k<m;k++){
		if(!one_occur&&res[k]==0){
		continue;	
		}
		else{
		one_occur=1;
		}
	   num[cnt]=res[k];
	   cnt++;
	   }
	int borrow_cnt=0;
	for(k=cnt;k<m;k++){
	borrow_cnt=i+m;
	if(m-k<=1){
	num[k]=a[borrow_cnt++];
	}
	else{
	quo[quo++]=0;
	num[k]=a[borrow_cnt++];
	}
	}

          for(j=0;j<m;j++){
			
        }

        }



return 0;
}
