/**
 * @file gfd.cpp
 * @brief Stepwise demo of evaluating grouped frequency distribution.
 * @date 2022-12-22
 * @rawData Integers accepted
 * @copyright Copyright (c) 2022
 * 
 */
#include <bits/stdc++.h>
using namespace std;

int getupb(int* rawdat, int size){
    int curval=-2147483648;
    int curind=-1;

    for(int i=0;i<size;++i){
        if(rawdat[i]>curval){
            curval=rawdat[i];
            curind=i;
        }
    }

    printf("Highest value: %d\n", curval);
    return curval;
}

int getlwb(int* rawdat, int size){
    int curval=2147483647;
    int curind=-1;

    for(int i=0;i<size;++i){
        if(rawdat[i]<curval){
            curval=rawdat[i];
            curind=i;
        }
    }

    printf("Lowest value: %d\n", curval);
    return curval;
}

int getRange(int _upb_, int _lwb_){
    printf("Range = %d - %d = %d\n",_upb_,_lwb_,(_upb_-_lwb_));

    return (_upb_-_lwb_);
}

int getWidth(int range, int clscnt){
    int width=ceil((double)range/(double)clscnt);

    printf("Width = %d / %d = %d\n",range,clscnt,width);
    return width;
}

int main(){
    int _size_;
    int* _rawdat_;

    int _clscnt_;

    // Read the size of raw data.
    printf("Enter the size of raw data: \n>>> ");
    scanf("%d",&_size_);

    // Read the values of raw data.
    printf("Input raw data: \n--------------------\n");
    _rawdat_=new int[_size_];
    for(int i=0;i<_size_;++i){
        scanf("%d",&_rawdat_[i]);
    }
    printf("--------------------\n");

    // Read the number of classes. Keep rejecting the input if this number is not 5-20.
    printf("Input the number of classes: \n>>> ");
    scanf("%d",&_clscnt_);
    while(_clscnt_<5 || _clscnt_>20){
        printf("Invalid. There should be 5-20 classes.\n");
        printf("Input the number of classes \n>>> ");
        scanf("%d",&_clscnt_);
    }

    // Compute upper and lower bounds of raw data.
    int upb=getupb(_rawdat_,_size_);
    int lwb=getlwb(_rawdat_,_size_);

    // Compute the range of raw data.
    int range=getRange(upb,lwb);

    // Evaluating the class width.
    // Every class has the same exact width.
    int width=getWidth(range,_clscnt_);

    // Evaluate the frequency distribution.
    int* freqs=new int[_clscnt_];
    for(int i=0;i<_clscnt_;++i){
        freqs[i]=0;
    }
    // Count the number of values in raw data that fall into each of the classes.
    int curind=0;
    for(int i=0;i<_size_;++i){
        curind=floor((double)(_rawdat_[i]-lwb)/(double)width);

        freqs[curind]++;
    }

    // Evaluate the cumulative frequency.
    // Cumulative frequency is just the prefix-sum of frequency.
    int* culf=new int[_clscnt_];
    int curcul=0;
    for(int i=0;i<_clscnt_;++i){
        curcul+=freqs[i];
        culf[i]=curcul;
    }

    // Print out the table of class limits, frequencies and cumulative frequencies.
    printf("--------------------\n(CL: Class Limits)\n(F: Frequencies)\n(CF: Cumulative Frequencies)");
    printf("--------------------\n");
    printf("CL\t\tF\tCF\t\n");
    
    for(int i=0;i<_clscnt_;++i){
        printf("%d - %d\t\t%d\t%d\n",
            lwb+width*i,
            lwb+width*(i+1)-1,
            freqs[i],
            culf[i]);
    }

    // Free the arrays of raw data and frequencies from memory.
    delete [] _rawdat_;
    delete [] freqs;
    delete [] culf;
    exit(0);
}