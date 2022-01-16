//
//  main.c
//  hw7simd
//
//  Created by 孫渝鈞 on 2022/1/12.
//
#include<stdio.h>
#include<stdlib.h>
#include<xmmintrin.h>
#include<time.h>
#define MILLION 1000000

int main(){
    
    float A[200][200]__attribute__((aligned(16)));
    float B[200][200]__attribute__((aligned(16)));
    float C[200][200]__attribute__((aligned(16)));
    __m128 *a,*b,*c;
    
    FILE *input_file=fopen("data.txt", "r");
    FILE *output_file=fopen("output.txt", "w");
    
    struct timespec trstart,cstart,twstart;
    struct timespec trend,cend,twend;
    long readtime,ctime,wtime;
    
    clock_gettime(CLOCK_MONOTONIC, &trstart);
    for(int i=0;i<200;i++){     //全部初始化0
        for(int j=0;j<200;j++){
            A[i][j]=B[i][j]=C[i][j]=0;
        }
    }
    for(int i=0;i<200;i++){      //read A
        for(int j=0;j<198;j++){
            fscanf(input_file,"%f",&A[i][j]);
        }
    }
    for(int i=0;i<200;i++){      //read B
        for(int j=0;j<198;j++){
            fscanf(input_file,"%f",&B[i][j]);
        }
    }
    clock_gettime(CLOCK_MONOTONIC, &trend);
    readtime=MILLION*(trend.tv_sec-trstart.tv_sec)+(trend.tv_nsec-trstart.tv_nsec)/1000;
    
    fclose(input_file);

    clock_gettime(CLOCK_MONOTONIC, &cstart);
    for(int i=0;i<50*200;i+=50){
        c = (__m128*)C;
        for(int j=0;j<50*200;j+=50){
            a=(__m128*)A;
            b=(__m128*)B;
            for(int k=0;k<50;k++){
                c[i]+=_mm_mul_ps(*(a+i+k),*(b+j+k));
            }
        }
        for(int u=1;u<50;u++){
            c[i]=_mm_add_ps(c[i],c[i+u]);    //讓c[i]變成最後要加的那四個
        }
     
    }
    clock_gettime(CLOCK_MONOTONIC, &cend);
    ctime=MILLION*(cend.tv_sec-cstart.tv_sec)+(cend.tv_nsec-cstart.tv_nsec)/1000;
    
   
    clock_gettime(CLOCK_MONOTONIC, &twstart);
    float ANS[200];
    for(int i=0;i<200;i++){
        for(int j=0;j<4;j++){
            ANS[i]+=C[i][j];
        }
        fprintf(output_file,"%f\n",ANS[i]);
    }
    clock_gettime(CLOCK_MONOTONIC, &twend);
    wtime=MILLION*(twend.tv_sec-twstart.tv_sec)+(twend.tv_nsec-twstart.tv_nsec)/1000;
    
    fprintf(output_file, "read data took %ld microseconds\n",readtime);
    fprintf(output_file, "operat took %ld microseconds\n",ctime);
    fprintf(output_file, "write data took %ld microseconds\n",wtime);
    
    fclose(output_file);
  

    return 0;
}
