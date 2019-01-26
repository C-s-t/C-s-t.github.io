#define BMAX 100             //爆発後の光点の数
#define FSTAGE 46            //FAST STAGE計算回数
#define SSTAGE 54            //SECOND STAGEの計算回数
#define STAGE FSTAGE+SSTAGE  //全体の回数計算
#define PI 3.1415927          //円周率
#define G -9.8                //重力加速度
#define EXP_V 1.0              //爆発の初速度と打ち上げの初速度の関係

#include<stdio.h>
#include<math.h>
#include<time.h>

#include"avsu_n13.mac"   //microAVS用ファイル用関数

//代表値を配列全体にコピーする関数
//1変数用
void dist1(double t,double *st);
//3変数用
void dist3(double rx,double *sx,double ry,double *sy,double rz,double *sz);

//値を表示する関数(テスト用)
void disp(double *a);

int main(void)
{
	double sx1[BMAX],sx2[BMAX],sy1[BMAX],sy2[BMAX],sz1[BMAX],sz2[BMAX];
	double svx1[BMAX],svx2[BMAX],svy1[BMAX],svy2[BMAX],svz1[BMAX],svz2[BMAX];
	double stemp[BMAX];
	double vx1,vx2,vy1,vy2,vz1,vz2,vy_init;
	double x1,x2,y1,y2,z1,z2;
	double dt=0.025,temp;
	int i,j,k,l;
	unsigned int t;
	double theta_x,theta_y;
	
	//microAVS出力用構造体の定義
	//フィールドファイル名、コードファイル名、データファイル名
	//データ数、ステップの合計、各変数のラベル
	
	avsn13 hanabi={"hanabi.fld","avs/hanabi","avs/hanabi",BMAX,STAGE,"x","y","z","temp"};
	
	//フィールドファイルのヘッダ書き出し
	avsn13fh(hanabi);
	
	//初速度の設定
	printf("初速度(x,y,z方向）を入力してください。\n");
	printf("x[-2.0~2.0]y[10.0~20.0]z[-2.0~2.0]\n");
	scanf("%lf%lf%lf",&vx1,&vy1,&vz1);
	
	vy_init=vy1;
	x1=0.0;
	y1=0.0;
	z1=0.0;
	temp=1.0;
	//代表値を配列各値にコピーする
	dist1(temp,stemp);
	dist3(x1,sx1,y1,sy1,z1,sz1);
	dist3(vx1,svx1,vy1,svy1,vz1,svz1);
	//乱数の初期化
	t=time(NULL);
	srand(t);
	
	//FAST STAGE開始
	for(i=0;i<FSTAGE;i++){
		vx2=vx1;
		vy2=vy1+dt*G;
		vz2=vz1;
		x2=x1+dt*vx2;
		y2=y1+dt*vy2;
		z2=z1+dt*vz2;
		x1=x2;
		y1=y2;
		z1=z2;
		vx1=vx2;
		vy1=vy2;
		vz1=vz2;
		dist1(temp,stemp);
		dist3(x1,sx1,y1,sy1,z1,sz1);
		dist3(vx1,svx1,vy1,svy1,vz1,svz1);
		avsn13ft(hanabi,i);
		avsn13c(hanabi,sx1,sy1,sz1,i);
		avsn13d(hanabi,svx1,svy1,svz1,stemp,i);
		
		printf("step=%d\n",i);
	}
	
	//乱数によりランダムな方向へ爆発
	//速度は同じで、方向がランダム
	for(j=0;j<BMAX;j++){
		svx1[j]=svx1[j]*sin(2.0*PI*j/BMAX);
		svy1[j]=cos(2.0*PI*j/BMAX);
		svz1[j]=svz1[j];
	}

	//SECOND STAGE開始
	for(i=0;i<SSTAGE;i++){
		for(j=0;j<BMAX;j++){
			svx2[j]=svx1[j];
			svy2[j]=svy1[j]+dt*G;
			svz2[j]=svz1[j];
			sx2[j]=sx1[j]+dt*svx2[j];
			sy2[j]=sy1[j]+dt*svy2[j];
			sz2[j]=sz1[j]+dt*svz2[j];
			
			sx1[j]=sx2[j];
			sy1[j]=sy2[j];
			sz1[j]=sz2[j];
			svx1[j]=svx2[j];
			svy1[j]=svy2[j];
			svz1[j]=svz2[j];
		}
		temp=2.0-(double)i/(double)SSTAGE;
		dist1(temp,stemp);
		
		//各ステップごとにmicroAVS用ファイルの出力
		avsn13ft(hanabi,FSTAGE+i);
		avsn13c(hanabi,sx1,sy1,sz1,FSTAGE+i);
		avsn13d(hanabi,svx1,svy1,svz1,stemp,FSTAGE+i);
		printf("step=%d\n",FSTAGE+i);
	}
	return(0);
	}
	
	void dist1(double t,double *st)
	{
		int i;
		for(i=0;i<BMAX;i++){
			*st=t;
			st++;
		}
		return;
	}
	
	void dist3(double rx,double *sx,double ry,double *sy,double rz,double *sz)
	{
		int i;
		for(i=0;i<BMAX;i++){
			*sx=rx;
			*sy=ry;
			*sz=rz;
			sx++;
			sy++;
			sz++;
		}
		return;
	}
	void disp(double *a)
	{
		int i;
		for(i=0;i<BMAX;i++){
			printf("%d%f\n",i,*a);
			a++;
		}
		return;
	}
	