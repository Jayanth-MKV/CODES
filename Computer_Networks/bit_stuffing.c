
#include<stdio.h>

void bitstuff(int arr[],int N){

	int i,j,k,count;
	i=0,j=0,count=1;
	int res[30];
	while(i<N){
		if(arr[i]==1){
			res[j]=arr[i];
			for(k=i+1;arr[k]==1&&count<5&&k<N;k++){
				j++;
				res[j]=arr[k];
				count++;	
			}
			if(count==5){
				j++;
				res[j]=0;
			}
			i=k-1;
		}
		else{
			res[j]=arr[i];
		}
		i++;
		j++;
		count=1;
	}

	for(i=0;i<j;i++){
		printf("%d\n",res[i]);
	}

}


int main(){
	int arr[]={1,1,1,1,1,1,1,1,1,1,1,1};
	int N=12;
	bitstuff(arr,N);
	return 0;
}
