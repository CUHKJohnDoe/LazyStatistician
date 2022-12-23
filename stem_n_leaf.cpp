/**
 * @file stem_n_leaf.cpp
 * @brief A demo for drawing stem-and-leaf plot.
 * 
 * @rawData Integers accepted.
 * @date 2022-12-24
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <bits/stdc++.h>
using namespace std;

/**
 * @brief Printing one layer of the plot which contains one stem entry and several corresponding leaf entries.
 * 
 */
void printLayer(int stem, vector<int> leaf){
    printf("%d\t", stem);
    for(int i=0;i<leaf.size();++i){
        printf("%d ", leaf.at(i));
    }
    printf("\n");
}

int main(){
    int _size_;  // Raw data size.
    vector<int> _seq_;  // Raw data.

    // Read the size of raw data.
    printf("Input the size of raw data:\n>>> ");
    scanf("%d",&_size_);

    // Read raw data.
    printf("Input raw data: \n-------------------\n");
    int tmp;
    for(int i=0;i<_size_;++i){
        scanf("%d",&tmp);
        _seq_.push_back(tmp);
    }
    printf("--------------------\n");

    // Sort raw data and print the result.
    sort(_seq_.begin(), _seq_.end());
    printf("Sorted raw data: \n--------------------\n");
    for(int i=0;i<_size_;++i){
        printf("%d ",_seq_.at(i));
    }
    printf("\n---------------------\n");
    
    // Determining the stem with lowest and highest value.
    int smin=_seq_.at(0)/10;
    int smax=_seq_.at(_size_-1)/10;

    // Determine the number of stem entries.
    int stem_size=smax-smin+1;

    // Iterate the list of sorted entries and assign them to each stem.
    int curstem=smin;  // Value of the current stem-entry.
    int curind=0;  // Index of the current raw-data entry.
    vector<int> curleaf;  // Leaf entries corresponding to the current stem.
    while(curind<_size_){

        /** Upon encountering a different stem entry, print and then clear the current stem. Begin assigning values to the 
         *  next larger stem.
         */
        if(_seq_.at(curind)/10!=curstem){
            printLayer(curstem,curleaf);
            curstem=_seq_.at(curind)/10;
            curleaf.clear();
        }

        // Assign the raw-data entry to the current stem.
        curleaf.push_back(_seq_.at(curind)%10);

        // Go on to the next raw-data entry
        ++curind;
    }
    // Upon exhausting raw data, print out the last layer.
    printLayer(curstem,curleaf);
    exit(0);
}