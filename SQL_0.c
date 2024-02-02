//
//  main.c
//  final0
//
//  Created by 孫渝鈞 on 2021/1/9.
//  Copyright © 2021 孫渝鈞. All rights reserved.
//
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
char _my_buffer;
int _is_my_buffer_filled = 0;
int check=0;
int count=0;
int ans=0;
char peek_next_char(){
    if(_is_my_buffer_filled==0){
        _my_buffer = getchar();
        _is_my_buffer_filled=1;
    }
    return _my_buffer;
    
}
void my_getchar(){
    if(_is_my_buffer_filled==1){
        _is_my_buffer_filled=0;
       // putchar(_my_buffer);
    }
   
}
struct student {
    int ID;
    char Name[21];
    int StudentID;
    char Class;
    char Email[41];
    int Phone;
};
struct student tableA[300];
int main()
{
    int num_students,m;
    scanf("%d %d",&num_students,&m);
    for(int i=0;i<num_students;i++){
        scanf("%d %s %d %c %s %d",&tableA[i].ID,
              tableA[i].Name,
              &tableA[i].StudentID,
              &tableA[i].Class,
              tableA[i].Email,
              &tableA[i].Phone);
    }

    _my_buffer=peek_next_char();
    while(_my_buffer!=EOF)
    {
        if(_my_buffer==32||_my_buffer==9||_my_buffer==10||_my_buffer==13)
              my_getchar();
                   
        else if(_my_buffer=='S'){
            _my_buffer=getchar();
            if(_my_buffer=='t'){
                _my_buffer=getchar();
                if(_my_buffer=='u'){
                _my_buffer=getchar();
                    if(_my_buffer=='d'){
                    _my_buffer=getchar();
                        if(_my_buffer=='e'){
                            _my_buffer=getchar();
                             if(_my_buffer=='n'){
                                    _my_buffer=getchar();
                                 if(_my_buffer=='t'){
                                             _my_buffer=getchar();
                                     if(_my_buffer=='I'){
                                                 _my_buffer=getchar();
                                         if(_my_buffer=='D'){
                                                     
                                             count=1;
                                         }
                                         
                                     }
                                }
                         }
                    }
                  }
                }
            }
        }
        else if(_my_buffer=='P'){
            _my_buffer=getchar();
            if(_my_buffer=='h'){
                _my_buffer=getchar();
                if(_my_buffer=='o'){
                _my_buffer=getchar();
                    if(_my_buffer=='n'){
                    _my_buffer=getchar();
                        if(_my_buffer=='e'){
                            count=2;
                    }
                  }
                }
            }
        }
        else if(_my_buffer=='I'){
            _my_buffer=getchar();
            if(_my_buffer=='D'){
                count=3;
            }
        }
        else if(_my_buffer=='='){
            check=1;
            char str=getchar();
              ans=0;
              char str2[1000000];
              int i=0;
              int n=0;
              while(str!=EOF){    //ex:345fvnoinfiv
                 
                  if(isdigit(str)){        //str=3
                      i=0;
                      n=0;
                      str2[i]=getchar();   //str2[0]=4
                      if(isdigit(str2[i])){  //如果下個字元也是數字的話
                           
                          while(isdigit(str2[i])){    //迴圈判斷總共有幾個迴數字連再一起
                              i++;                //i=2
                              n++;   //計算有幾個數字 //n=2
                              str2[i]=getchar();  //str2[1]=5
                          }
                        
                          int i=-1; //i要從-1進入迴圈因為這樣再跑第二次str[i]才會是str[0]
                          int k=n;  //k=2
                          for(;i<n;i++){
                            while(k>=0){   //i=-1,k=2進入
                                if(k==n){
                                    ans=ans+((int)(str-48))*(pow(10,k)); //+300
                                    k--;   //k=1
                                    break;  //跳出裡面那層迴圈裡面那層迴圈再再重新進入以i=0,k=1重新進入
                                }
                                else if(k>0){   //i=0,k=1
                                    ans=ans+((int)(str2[i]-48))*(pow(10,k)); //+40
                                    k--;  //k=0
                                    break;  //跳出裡面那層迴圈裡面那層迴圈再再重新進入以i=1,k=0重新進入
                                }
                                else if(k==0){  //i=1,k=0
                                    ans=ans+((int)(str2[i]-48));  //+5
                                    k--;
                                    break;  //跳出迴圈i=2=n不會進入迴圈了
                                }
                             }
                          }
                      }
                      else{        //如果下個字元不是數字的話
                          ans=ans+(int)(str-48);    //直接加
                          
                      }
                      
                       }
                      str=getchar();
                   }
          
            
        }
        else if(_my_buffer=='<'){
            check=2;
             char str=getchar();
                         ans=0;
                         char str2[1000000];
                         int i=0;
                         int n=0;
                         while(str!=EOF){    //ex:345fvnoinfiv
                            
                             if(isdigit(str)){        //str=3
                                 i=0;
                                 n=0;
                                 str2[i]=getchar();   //str2[0]=4
                                 if(isdigit(str2[i])){  //如果下個字元也是數字的話
                                      
                                     while(isdigit(str2[i])){    //迴圈判斷總共有幾個迴數字連再一起
                                         i++;                //i=2
                                         n++;   //計算有幾個數字 //n=2
                                         str2[i]=getchar();  //str2[1]=5
                                     }
                                   
                                     int i=-1; //i要從-1進入迴圈因為這樣再跑第二次str[i]才會是str[0]
                                     int k=n;  //k=2
                                     for(;i<n;i++){
                                       while(k>=0){   //i=-1,k=2進入
                                           if(k==n){
                                               ans=ans+((int)(str-48))*(pow(10,k)); //+300
                                               k--;   //k=1
                                               break;  //跳出裡面那層迴圈裡面那層迴圈再再重新進入以i=0,k=1重新進入
                                           }
                                           else if(k>0){   //i=0,k=1
                                               ans=ans+((int)(str2[i]-48))*(pow(10,k)); //+40
                                               k--;  //k=0
                                               break;  //跳出裡面那層迴圈裡面那層迴圈再再重新進入以i=1,k=0重新進入
                                           }
                                           else if(k==0){  //i=1,k=0
                                               ans=ans+((int)(str2[i]-48));  //+5
                                               k--;
                                               break;  //跳出迴圈i=2=n不會進入迴圈了
                                           }
                                        }
                                     }
                                 }
                                 else{        //如果下個字元不是數字的話
                                     ans=ans+(int)(str-48);    //直接加
                                     
                                 }
                                 
                                  }
                                 str=getchar();
                              }
                   
            
        }
        else if(_my_buffer=='>'){
            check=3;
             char str=getchar();
                         ans=0;
                         char str2[1000000];
                         int i=0;
                         int n=0;
                         while(str!=EOF){    //ex:345fvnoinfiv
                            
                             if(isdigit(str)){        //str=3
                                 i=0;
                                 n=0;
                                 str2[i]=getchar();   //str2[0]=4
                                 if(isdigit(str2[i])){  //如果下個字元也是數字的話
                                      
                                     while(isdigit(str2[i])){    //迴圈判斷總共有幾個迴數字連再一起
                                         i++;                //i=2
                                         n++;   //計算有幾個數字 //n=2
                                         str2[i]=getchar();  //str2[1]=5
                                     }
                                   
                                     int i=-1; //i要從-1進入迴圈因為這樣再跑第二次str[i]才會是str[0]
                                     int k=n;  //k=2
                                     for(;i<n;i++){
                                       while(k>=0){   //i=-1,k=2進入
                                           if(k==n){
                                               ans=ans+((int)(str-48))*(pow(10,k)); //+300
                                               k--;   //k=1
                                               break;  //跳出裡面那層迴圈裡面那層迴圈再再重新進入以i=0,k=1重新進入
                                           }
                                           else if(k>0){   //i=0,k=1
                                               ans=ans+((int)(str2[i]-48))*(pow(10,k)); //+40
                                               k--;  //k=0
                                               break;  //跳出裡面那層迴圈裡面那層迴圈再再重新進入以i=1,k=0重新進入
                                           }
                                           else if(k==0){  //i=1,k=0
                                               ans=ans+((int)(str2[i]-48));  //+5
                                               k--;
                                               break;  //跳出迴圈i=2=n不會進入迴圈了
                                           }
                                        }
                                     }
                                 }
                                 else{        //如果下個字元不是數字的話
                                     ans=ans+(int)(str-48);    //直接加
                                     
                                 }
                                 
                                  }
                                 str=getchar();
                              }
                      
            
        }
        
        _my_buffer= getchar();
    }
   
    if(count==1&&check==1){
        for(int i=0;i<num_students;i++){
            if(tableA[i].StudentID==ans){
                printf("%d %s %d %c %s %d\n",tableA[i].ID,
                tableA[i].Name,
                tableA[i].StudentID,
                tableA[i].Class,
                tableA[i].Email,
                tableA[i].Phone);
            }
            
        }
    }
    if(count==1&&check==2){
         for(int i=0;i<num_students;i++){
                   if(tableA[i].StudentID<ans){
                       printf("%d %s %d %c %s %d\n",tableA[i].ID,
                       tableA[i].Name,
                       tableA[i].StudentID,
                       tableA[i].Class,
                       tableA[i].Email,
                       tableA[i].Phone);
                   }
                   
               }
        
    }
    if(count==1&&check==3){
        for(int i=0;i<num_students;i++){
            if(tableA[i].StudentID>ans){
                printf("%d %s %d %c %s %d\n",tableA[i].ID,
                tableA[i].Name,
                tableA[i].StudentID,
                tableA[i].Class,
                tableA[i].Email,
                tableA[i].Phone);
            }
            
        }
        
    }
    if(count==2&&check==1){
        for(int i=0;i<num_students;i++){
            if(tableA[i].Phone==ans){
                printf("%d %s %d %c %s %d\n",tableA[i].ID,
                tableA[i].Name,
                tableA[i].StudentID,
                tableA[i].Class,
                tableA[i].Email,
                tableA[i].Phone);
            }
            
        }
    }
    if(count==2&&check==2){
        for(int i=0;i<num_students;i++){
            if(tableA[i].Phone<ans){
                printf("%d %s %d %c %s %d\n",tableA[i].ID,
                tableA[i].Name,
                tableA[i].StudentID,
                tableA[i].Class,
                tableA[i].Email,
                tableA[i].Phone);
            }
            
        }
        
    }
    if(count==2&&check==3){
        for(int i=0;i<num_students;i++){
            if(tableA[i].Phone>ans){
                printf("%d %s %d %c %s %d\n",tableA[i].ID,
                tableA[i].Name,
                tableA[i].StudentID,
                tableA[i].Class,
                tableA[i].Email,
                tableA[i].Phone);
            }
            
        }
        
    }
    if(count==3&&check==1){
        for(int i=0;i<num_students;i++){
            if(tableA[i].ID==ans){
                printf("%d %s %d %c %s %d\n",tableA[i].ID,
                tableA[i].Name,
                tableA[i].StudentID,
                tableA[i].Class,
                tableA[i].Email,
                tableA[i].Phone);
            }
            
        }
        
    }
    if(count==3&&check==2){
        for(int i=0;i<num_students;i++){
            if(tableA[i].ID<ans){
                printf("%d %s %d %c %s %d\n",tableA[i].ID,
                tableA[i].Name,
                tableA[i].StudentID,
                tableA[i].Class,
                tableA[i].Email,
                tableA[i].Phone);
            }
            
        }
        
    }
    if(count==3&&check==3){
        for(int i=0;i<num_students;i++){
            if(tableA[i].ID>ans){
                printf("%d %s %d %c %s %d\n",tableA[i].ID,
                tableA[i].Name,
                tableA[i].StudentID,
                tableA[i].Class,
                tableA[i].Email,
                tableA[i].Phone);
            }
            
        }
        
    }

    return 0;
}

