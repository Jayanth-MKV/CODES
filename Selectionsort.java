package com.jay;

import java.util.Arrays;

public class Selectionsort {
   public static void main(String[] args){
       int[] arr= new int[]{1, 166, 14, 223, 44, 97, 45};
       selectsort(arr);
       System.out.println(Arrays.toString(arr));
   }

   static void selectsort(int[] arr){
        for(int i=0;i<arr.length;i++){
           int min=i;
        for (int j=i+1;j<arr.length;j++){
        if (arr[j]>arr[min]){
        min=j;
        }
        }

        if (i!=min){
        int temp=arr[min];
        arr[min]=arr[i];
        arr[i]=temp;
        }

        }
        }
}
