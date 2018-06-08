#include <reg52.h>

#define uint unsigned int

//数码管数据（共阳极）
#define SEG P0
#define WE P2
uint code scandate[]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};

//数码管数值
uint num;

//声强传感器
sbit SoundDetection=P1^0;

//电机控制
sbit motor11=P3^3;
sbit motor12=P3^4;
sbit motor21=P3^5;
sbit motor22=P3^6;

//蜂鸣器
sbit SPK=P3^2;

//光感测距器
//检测地面
sbit measurement1=P1^1;
sbit measurement2=P1^2;
sbit measurement3=P1^3;
//检测物体
sbit measurement4=P1^4;
sbit measurement5=P1^5;
sbit measurement6=P1^6;
sbit measurement7=P1^7;

//声音检测函数
void SoundDetectionFunction(){
	while(1){
		if(SoundDetection==0){
			break;
		}
	}
}

//延时函数 单位毫秒
void delay(uint DelayTime){
	uint i,y;
	for(i=DelayTime;i>0;i--)
		for(y=110;y>0;y--);
}

//电机1正转
void motor1Up(){
	motor11=0;
	motor12=1;
}

//电机1反转
void motor1Down(){
	motor11=1;
	motor12=0;
}

//电机1停止
void motor1Stop(){
	motor11=1;
	motor12=1;
}

//电机2正转
void motor2Up(){
	motor21=1;
	motor22=0;
}

//电机2反转
void motor2Down(){
	motor21=0;
	motor22=1;
}

//电机2停止
void motor2Stop(){
	motor21=1;
	motor22=1;
}



/*小车方向
1：前进
2：左转
3：右转
4：后退
5：停止
*/
void direction(uint par){
	if(par==1){
		motor1Up();
		motor2Up();
	}
	else if(par==2){
		motor1Down();
		motor2Up();
	}
	else if(par==3){
		motor1Up();
		motor2Down();
	}
	else if(par==4){
		motor1Down();
		motor2Down();
	}
	else if(par=5){
		motor1Stop();
		motor2Stop();
	}
}

//右转
void RTurnTime(uint time){
	while(time--){
		if(time%2==0)
			direction(3);
	}
}

//左转
void LTurnTime(uint time){
	while(time--){
		if(time%2==0){
			direction(2);
		}
	}
}

//后退
void DTime(uint time){
	while(time--){
		direction(4);
	}
}


//数码管显示（num1，num2）
//void display_led(uint NUM1,uint NUM2){
//	WE=0x01;
//	SEG=scandate[NUM1];
//	delay(1);
//	WE=0x02;
//	SEG=scandate[NUM2];
//	delay(1);
//}
void display_led(uint NUM1,uint NUM2,uint n){
	uint a;
	for(a=n;a>0;a--){
		WE=0x01;
		SEG=scandate[NUM1];
		delay(1);
		WE=0x02;
		SEG=scandate[NUM2];
		delay(1);
		WE=0x00;
	}

}

void main(){
	SoundDetectionFunction();
	num=0;
	while(1){
		//小车行走
		direction(1);

		//边缘检测函数
		if( (measurement1==1) || (measurement2==1) || (measurement3==1) ){
			direction(5);
			//delay(500);
			num++;
			display_led(num/10,num%10,500);
			if(measurement1==1){
				DTime(15000);
				RTurnTime(12000);
			}
			else if(measurement3==1){
				DTime(15000);
				LTurnTime(12000);
			}
			else if(measurement2==1){
				DTime(20000);
				RTurnTime(12000);
			}
		}
		else{
			direction(1);
		}

		//数码管显示
		//display_led(num/10,num%10);

		//前方物体检测
		if( (measurement4==0) || (measurement5==0) || (measurement6==0) || (measurement7==0) ){
			delay(1);//值越小，越亮
			SPK=0;
			delay(1);
			SPK=1;
		}
	}
}