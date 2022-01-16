//
//  main.c
//  hw7
//
//  Created by 孫渝鈞 on 2022/1/12.
//

#include <stdio.h>
#include <time.h>
#include<stdlib.h>

#define MILLION 1000000
int main(){
    float A[200][198];
    float B[200][198];
    float C[200];
    
    FILE *input_file=fopen("data.txt", "r");
    FILE *output_file=fopen("output.txt", "w");
    
    struct timespec trstart,cstart,twstart;
    struct timespec trend,cend,twend;
    long readtime,ctime,wtime;
    
    clock_gettime(CLOCK_MONOTONIC, &trstart);
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
    for(int i=0;i<200;i++){
        C[i]=0;
        for(int j=0;j<200;j++){
            for(int k=0;k<198;k++){
                C[i]+=A[i][k]*B[j][k];
            }
        }
    }
    clock_gettime(CLOCK_MONOTONIC, &cend);
    ctime=MILLION*(cend.tv_sec-cstart.tv_sec)+(cend.tv_nsec-cstart.tv_nsec)/1000;
    
    clock_gettime(CLOCK_MONOTONIC, &twstart);
    for(int i=0;i<200;i++){
        fprintf(output_file,"%f\n",C[i]);
    }
    clock_gettime(CLOCK_MONOTONIC, &twend);
    wtime=MILLION*(twend.tv_sec-twstart.tv_sec)+(twend.tv_nsec-twstart.tv_nsec)/1000;
    
    fprintf(output_file, "read data took %ld microseconds\n",readtime);
    fprintf(output_file, "operat took %ld microseconds\n",ctime);
    fprintf(output_file, "write data took %ld microseconds\n",wtime);
    
    fclose(output_file);
    
    return 0;
}
/*float A[200][198];
float B[200][198];
float C[200];


for(int i=0;i<200;i++){      //read A
    for(int j=0;j<198;j++){
        scanf("%f",&A[i][j]);
    }
}


for(int i=0;i<200;i++){      //read B
    for(int j=0;j<198;j++){
        scanf("%f",&B[i][j]);
    }
}
for(int i=0;i<200;i++){
    C[i]=0;
    for(int j=0;j<200;j++){
        for(int k=0;k<198;k++){
            C[i]+=A[i][k]*B[j][k];
        }
    }
}
for(int i=0;i<200;i++){
    printf("%.1f\n",C[i]);
}*/
