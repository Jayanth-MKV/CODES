package com.jay;

import java.util.Arrays;

public class Quicksort {
    public static void main(String[] args) {
        int[] arr= new int[]{1, 166, 14, 223, 44, 97, 45};
        quisort(arr,0,arr.length-1);
        System.out.println(Arrays.toString(arr));
    }

    private static void quisort(int[] arr, int l, int r) {
        if (l>=r){
            return;
        }
        int p=partition(arr,l,r);
        quisort(arr,l,p-1);
        quisort(arr,p+1,r);
    }

    private static int partition(int[] arr, int l, int r) {
        int i,j,p;
        i=l;
        j=r-1;
        p=r;
        while(i<=j){
            while(arr[i]<arr[p] && i<=r){
                i++;
            }
            while(arr[j]>arr[p] && j>=l){
                j--;
            }
            if (i<j){
                int temp = arr[i];
                arr[i]=arr[j];
                arr[j]=temp;
            }
            else{
                int temp = arr[i];
                arr[i]=arr[p];
                arr[p]=temp;
                return i;
            }
        }

        return p ;
    }


}
