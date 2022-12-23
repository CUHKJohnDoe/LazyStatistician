/**
 * @file central_tendency.cpp
 * @brief Demo of calculating mean, median, mode(s) and midrange of a raw data-set. 
 * @date 2022-12-24
 * @rawData Decimals accepted.
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <bits/stdc++.h>
using namespace std;

/**
 * @brief Calculate the mean of an array of raw data.
 * 
 */
double getMean(double* seq, int size){

    // Sum up all data entries.
    double s=0.0;
    for(int i=0;i<size;++i){
        s+=seq[i];
    }

    // Divide the sum by the size of samples.
    s/=(double)size;
    return s;
}

/**
 * @brief Calculate the median of an array of raw data.
 * 
 */
double getMedian(double* seq, int size){
    // Clone the original array.
    double *cseq=new double[size];
    for(int i=0;i<size;++i){
        cseq[i]=seq[i];
    }

    /**
     *  Finding the median is equivalent to finding the k-th and/or (k+1)-th smallest raw data entries,
     *  ... where k is (size/2)+1;
     *  To achieve this we bubble-sort the first k elements of raw-data to obtain the said entries.
     */
    for(int i=0;i<(size/2+1);++i){
        for(int j=i;j<size;++j){
            double tmp;
            if(cseq[i]>cseq[j]){
                tmp=cseq[i];
                cseq[i]=cseq[j];
                cseq[j]=tmp;
            }
        }
    }
    
    /**
     *  The median is the [(size-1)/2]-th smallest entry if size of samples is odd;
     *  It is the average of (size/2)-th and [(size/2)+1]-th entries if size of sample is even.
     * 
     */
    double res=(size%2!=0)?(cseq[size/2]):((cseq[size/2]+cseq[size/2-1])/2.0);

    delete [] cseq;
    return res;
}

/**
 * @brief Calculate the mode(s) of an array of raw data.
 * 
 * @return vector<double> 
 */
vector<double> getMode(double* seq, int size){
    /**
     *  Iterate all raw-data entries and search for duplicates.
     *  flagseq[i] indicates whether the i-th entry is a duplicate of some entries before it.
     *  freqseq[i] stores the number of duplicates of the i-th entry after it, including itself. We call it "frequency" of an entry.
     *  
     */
    bool* flagseq=new bool[size];
    int* freqseq=new int[size];

    for(int i=0;i<size;++i){
        // Initially considering all entries to not have duplicates.
        flagseq[i]=true;

        // Set all frequencies of entries to 1. (itself at least appears once)
        freqseq[i]=1;
    }

    for(int i=0;i<size;++i){
        
        if(!flagseq[i]){ continue; }

        for(int j=i;j<size;++j){
            if(!flagseq[j]){ continue; }

            if(seq[j]==seq[i]){
                freqseq[i]++;
                flagseq[j]=false;
            }
        }
    }

    int maxfreq=-1;
    int maxind=-1;
    for(int i=0;i<size;++i){
        if(freqseq[i]>maxfreq){
            maxfreq=freqseq[i];
            maxind=i;
        }
    }

    vector<double> res;
    for(int i=0;i<size;++i){
        if(freqseq[i]==maxfreq){
            res.push_back(seq[i]);
        }
    }

    delete [] flagseq;
    delete [] freqseq;
    return res;
}

double getMidrange(double* seq, int size){
    int minind=-1;
    int maxind=-1;
    double minval=__DBL_MAX__;
    double maxval=__DBL_MIN__;

    for(int i=0;i<size;++i){
        if(seq[i]<minval){
            minind=i;
            minval=seq[i];
        }
        if(seq[i]>maxval){
            maxind=i;
            maxval=seq[i];
        }
    }

    return (minval+maxval)/2.0;
}

int main(){
    int _size_;
    double* _dat_;

    printf("Input the size of samples:\n>>> ");
    scanf("%d", &_size_);
    _dat_=new double[_size_];

    printf("Input raw data: \n--------------------\n");
    for(int i=0;i<_size_;++i){
        scanf("%lf", &_dat_[i]);
    }
    printf("\n--------------------\n\n");


    printf("---MEAN---\n%.5lf\n",getMean(_dat_,_size_));

    printf("---MEDIAN---\n%.5lf\n",getMedian(_dat_,_size_));

    printf("---MODE(S)---\n");
    vector<double> modes=getMode(_dat_,_size_);
    for(int i=0;i<modes.size();++i){
        printf("%5lf, ", modes.at(i));
    }
    printf("\n");
    
    printf("---MIDRANGE---\n%.5lf\n",getMidrange(_dat_,_size_));

    delete [] _dat_;
    exit(0);
}