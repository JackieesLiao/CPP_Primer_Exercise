/*
函数合法：给数组ia赋值i
*/
#include<iostream>
 int &get(int *array,int index)
 {
     return array[index];
 }
 int main()
 {
     int ia[10];
     for(int i=0;i!=10;i++)
         get(ia,i)=i;
     for(int i=0;i!=10;++i)
         std::cout<<ia[i]<<std::endl;
 }
