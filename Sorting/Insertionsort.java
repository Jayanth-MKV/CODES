package com.jay;

import java.util.Arrays;

public class Insertionsort {
    public static void main(String[] args) {
        int[] arr= new int[]{1, 166, 14, 223, 44, 97, 45};
        inssort(arr);
        System.out.println(Arrays.toString(arr));
    }

    static void inssort(int[] arr){
        int key=0;
        int j=0;

        for (int i=1;i<arr.length;i++) {
        key=arr[i];
        j=i-1;
        while(j>=0 && arr[j]>key) {
        arr[j+1]=arr[j];
        j=j-1;
        }
        arr[j+1]=key;
        }
        }

    }

