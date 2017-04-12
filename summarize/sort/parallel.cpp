#include <iostream>
#include <thread>
#include <string>
#include "test_sort.h"
#include <time.h>
#include <unistd.h>

using namespace std;

void sortBy(void(*op)(int* , int* ),int* copyTestArray, int totalNum, string opName)
{
    clock_t t_start, t_end;
    //t_start=time(NULL);   //秒级别，算的是总时间
    t_start=clock();        //微秒级别，算的是每个CPU运算总时间

    int* min=copyTestArray;
    int* max=copyTestArray+totalNum;
    op(min,max);
    t_end=clock();
    cout<<"method "<<opName<<": "<<(t_end-t_start)*1000/CLOCKS_PER_SEC<<endl;
}


void makeRandomList(int* testArray, int n)
{
    int i=0;
    while(i<n)
    {
        testArray[i++]=rand();
    }
}

int main()
{
    int totalNum=1000000;
    int* testArray=new int[totalNum];
    /*
    for(int i=0; i<totalNum; i++)
    {
        testArray[i]=totalNum-i;
    } 
    */
    srand((unsigned)time(NULL));//unsigned int seed=5; srand(seed);
    makeRandomList(testArray,totalNum); 

    
    auto InsertSortTest=[](int* tArray,int sFArray)
    {
        int* cTArray=new int[sFArray];                  
        memcpy(cTArray,tArray,sFArray*sizeof(cTArray[0]));
        /*
        for (int i=0; i<50; i++)
        {
            cout<<cTArray[i]<<' ';
        }
        cout<<endl;
        */
        sortBy(InsertSort,cTArray,sFArray,"InsertSort");
        /*
        for (int i=0; i<50; i++)
        {
            cout<<cTArray[i]<<' ';
        }
        cout<<endl;
        */
        delete[] cTArray;
    };
    auto QuickSortTest=[](int* tArray,int sFArray)
    {
        int* cTArray=new int[sFArray];
        memcpy(cTArray,tArray,sFArray*sizeof(cTArray[0]));
        sortBy(QuickSort,cTArray,sFArray,"QuickSort");
        delete[] cTArray;
    };
    auto QuickSortTestV2=[](int* tArray,int sFArray)
    {
        int* cTArray=new int[sFArray];
        memcpy(cTArray,tArray,sFArray*sizeof(cTArray[0]));
        sortBy(QuickSortV2,cTArray,sFArray,"QuickSortV2");
        delete[] cTArray;
    };
    auto MergeSortTest=[](int* tArray,int sFArray)
    {
        int* cTArray=new int[sFArray];
        memcpy(cTArray,tArray,sFArray*sizeof(cTArray[0]));
        sortBy(MergeSort,cTArray,sFArray,"MergeSort");
        delete[] cTArray;
    };

    clock_t t_start_for_all, t_end_for_all;
    t_start_for_all=clock();


    thread thread1(InsertSortTest,testArray,totalNum);
    thread1.detach();
    thread thread2(QuickSortTest,testArray,totalNum);
    thread2.join();
    thread thread3(QuickSortTestV2,testArray,totalNum);
    thread3.join();
    thread thread4(MergeSortTest,testArray,totalNum);
    thread4.join();

    t_end_for_all=clock();
    
    cout<<"All time is: "<<(t_end_for_all-t_start_for_all)*1000/CLOCKS_PER_SEC<<endl;
    
    delete[] testArray;
    
}