package com.jay;

import java.util.Arrays;

public class Bubblesort {
    public static void main(String[] args) {
        int[] arr= new int[]{1, 166, 14, 223, 44, 97, 45};
        bubsort(arr);
        System.out.println(Arrays.toString(arr));    }

     private static void bubsort(int[] arr){
     for (int i = 0; i < arr.length; i++) {
     boolean flag=false;
         for (int j=0;j<arr.length-i-1;j++) {
         int temp;
     if (arr[j]>arr[j+1]){
         flag=true;
          temp =arr[j+1];
          arr[j+1]=arr[j];
          arr[j]=temp;
     }
     }
         if (flag==false) {
             break;
         }
     }
    }
}
