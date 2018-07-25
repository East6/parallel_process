#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include<omp.h>//追記
#include <time.h> //時間計測のため

#define MAXSIZE 1000

int main(){
        int x[MAXSIZE];
		int y[MAXSIZE];//追記
		int ChangeCounte_xy=0;//追記
		struct timespec startTime, endTime;//時間計測のため
        int i,j,k;
        char fn[255];
        FILE *fp;

        strcpy(fn, getenv("PWD"));
        strcat(fn, "/data.txt");
        if( NULL == (fp = fopen(fn, "r")) ) {
                printf("Can't open the input file: %s\n\n", fn);
                exit(1);
        }

        for(i=0;i<MAXSIZE;i++){
                fscanf(fp,"%d",&x[i]);
        }
		
        printf("\n");

		/* 時間計測 開始 */
		clock_gettime(CLOCK_REALTIME, &startTime);//時間計測のため
        
		for(k=MAXSIZE-1;k>=0;k--){
				if(ChangeCounte_xy%2 == 0){//追記
					#pragma omp parallel for//追記
                	for(j=0;j<k;j++){
                        y[j] = x[j] + x[j+1];//変更
                        y[j] = y[j] % 10;//変更
//                        printf("y[%d]=%d ",j, y[j]);//変更
                	}
					ChangeCounte_xy++;
				}else{//追記
					#pragma omp parallel for//追記
					for(j=0;j<k;j++){
                        x[j] = y[j] + y[j+1];//変更
                        x[j] = x[j] % 10;//変更
//                       printf("x[%d]=%d ",j, x[j]);//変更
                	}
					ChangeCounte_xy++;
				}

//               printf("\n");
        }

		/* 時間計測 終了 */
		clock_gettime(CLOCK_REALTIME, &endTime);//時間計測のため



		/* 計算にかかった時間を表示 */
		printf("elapsed time = ");
		if (endTime.tv_nsec < startTime.tv_nsec) {
		  printf("%5ld.%09ld", endTime.tv_sec - startTime.tv_sec - 1,
				 endTime.tv_nsec + (long int)1.0e+9 - startTime.tv_nsec);
		} else {
		  printf("%5ld.%09ld", endTime.tv_sec - startTime.tv_sec,
				 endTime.tv_nsec - startTime.tv_nsec);
		}
		printf("(sec)\n");


		printf("\n");
		//最終結果を表示
		if(ChangeCounte_xy%2 == 0){
			printf("結果は %d\n",y[0]);
		}else{
			printf("結果は %d\n",x[0]);
		}


        return 0;
}
