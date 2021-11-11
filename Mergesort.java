package com.jay;

import java.util.Arrays;

public class Mergesort {
    public static void main(String[] args) {
        int[] arr= new int[]{1, 166, 14, 223, 44, 97, 45};
        mersort(arr,0,arr.length-1);
        System.out.println(Arrays.toString(arr));
    }


    static void mersort(int[] arr,int l,int r){
        if (l<r){
            int m=(l+r)/2;
            mersort(arr,l,m);
            mersort(arr,m+1,r);
            merge(arr,l,m,r);
        }
    }

    static void merge(int[] arr,int l,int m,int r){
        int i=l;
        int j=m+1;
        int k=l;
        int[] temp= new int[r+1];
        while(i<=m&&j<=r){
            if (arr[i]<arr[j]){
                temp[k]=arr[i];
                i++;
                k++;
            }
            else{
                temp[k]=arr[j];
                k++;
                j++;
            }
        }
        while(i<=m){
            temp[k]=arr[i];
            k++;
            i++;
        }

        while(j<=r){
            temp[k]=arr[j];
            k++;
            j++;
        }

        for (int p=l;p<=r;p++){
            arr[p]=temp[p];
        }
    }

}
