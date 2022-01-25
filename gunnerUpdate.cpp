/*
	author: Abhishek Agarwala
	last modified: August 8, 2008
*/
# include "iGraphics.h"
# include "gl.h"
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <Windows.h>
# include <string.h>
struct high
{
    char str[100];
    int a;
} ;
struct high *p;
FILE *fpResume,*fpPlay,*fpSave,*fpOpen,*fWHigh,*fRHigh;
int fMainMenu,fBack2,fDrawLevel,fDrawGame,flag=0,f,fDrawInput,direc=0,flagobs=0,lev,remain=6,cnt,fEnd,fRemain,fResume,fPlayPause=0,maxi=0,i,ans,j,jth,key=0,k;;
char str[10000],pro[10000],EnStr[10000],input[10000],str2[10000],Enhigh[10][100],arr[10][100],strhigh[100],temp[100];
int n=3,x=0,cnst=12,flag2=0,v=60,ith,flag3=0,fhighsc,mode,len,fname=1,fLockLevel;
double incre=10.83,degre=45,cn_deg=15,dx=12,ball_x=-10,ball_y=-10,t=0,g=9.8;
double obs_x[10]={480,600,720,840,960},obs_y[10],hght[10]={60,72,84,96,108,120};
double polys_x[7]={10,20,60,55,10},polys_y[7]={10,10,45,54,20};
double ell_x[]={550,670,790,910},ell_y[]={8,8,8,8,8};
/*
	c1,d1,c2,d2;
	function iDraw() is called again and again by the system.
*/
/*void wHigh()
{
	fWHigh=fopen("MyHigh.txt","w");
	if(cnt*1000 > maxi) {maxi=cnt*1000;fprintf(fWHigh,"%d",maxi);}
	fclose(fWHigh);
}*/

void rHigh()
{
	/*fRHigh=fopen("MyHigh.txt","r");
	fscanf(fRHigh,"%d",&fhighsc);
	if(cnt*1000 > fhighsc){
		fWHigh=fopen("MyHigh.txt","w");
		fprintf(fWHigh,"%d",cnt*1000);
		fclose(fWHigh);
	}
	fclose(fRHigh);*/
	 FILE *fRHigh;
    fRHigh=fopen("MyHigh.txt","r");
    p=(struct high *) malloc(10*sizeof(struct high));
    strcpy(strhigh,str2);
	ans=cnt*1000;
    for(i=0;i<10;i++)
    {
        fscanf(fRHigh,"%s %d",(p+i)->str,&((p+i)->a));
    }
    /*for(i=0;i<10;i++)
    {
        printf("%s %d\n",(p+i)->str,(p+i)->a);
    }*/
    if(ans>((p+i-1)->a))
    {
        for(jth=0;jth<10;jth++)
        {

            if(ans==((p+jth)->a))
            {
                for(k=jth;k<10 &&((p+k)->a==ans);k++)
                {
                   printf("%dj %dk %s %s\n",j,k,(p+k)->str,strhigh);
                    if(strcmp(((p+k)->str),strhigh)>0)
                       {printf("%dj %dk %s %s\n",j,k,(p+k)->str,str);
                          key=k;
                          break;
                       }
                }
                if(key)
                {
                    printf("%d\n",key);
                    break;
                }
            }
            else if(ans>((p+jth)->a))
            {
                key=jth;
                break;
            }
        }
    }
    else
    {
        printf("You have not made a highscore");
    }
    for(i=8;i>key-1;i--)
    {
        *(p+i+1)= *(p+i);
    }
    strcpy((p+key)->str,strhigh);
    (p+key)->a=ans;
	printf("%d",ans);
    for(i=0;i<10;i++)
    {
        sprintf(Enhigh[i],"%s %d\n",(p+i)->str,(p+i)->a);
		printf("%s\n",Enhigh[i]);
    }
    printf("%d",key);
    fclose(fRHigh);

}

void wSave()
{
	int i,j,k;
	fpSave=fopen("MySavee.txt","w");
	fprintf(fpSave," %lf %lf %lf %lf %d %d %d ",degre,t,ball_x,ball_y,cnt,v,remain);
	for(i=0;i<5;i++) fprintf(fpSave," %lf %lf ",obs_x[i],hght[i]);
	for(i=0;i<4;i++) fprintf(fpSave," %lf %lf ",ell_x[i],ell_y[i]);

	fclose(fpSave);
}
void rSave()
{
	int i,j,k;
	fpOpen=fopen("MySavee.txt","r");
	fscanf(fpOpen,"%lf%lf%lf%lf%d%d%d",&degre,&t,&ball_x,&ball_y,&cnt,&v,&remain);
	for(i=0;i<5;i++) fscanf(fpOpen,"%lf%lf ",&obs_x[i],&hght[i]);
	for(i=0;i<4;i++) fscanf(fpOpen," %lf%lf",&ell_x[i],&ell_y[i]);

	fclose(fpOpen);
}
void wResume()
{
	int i,j,k;
	fpResume=fopen("MyResume.txt","w");
	for(i=0;i<4;i++) fprintf(fpResume," %lf %lf ",ell_x[i],ell_y[i]);
	for(i=0;i<5;i++) fprintf(fpResume," %lf %lf ",obs_x[i],hght[i]);
	fprintf(fpResume," %d %d -10.000 -10.000",remain,cnt);
	fclose(fpResume);
}
void rPlay()
{
	int i,j,k;
	fpPlay=fopen("MyResume.txt","r");
	for(i=0;i<4;i++) fscanf(fpPlay,"%lf%lf",&ell_x[i],&ell_y[i]);
	for(i=0;i<5;i++) fscanf(fpPlay,"%lf%lf",&obs_x[i],&hght[i]);
	fscanf(fpPlay,"%d%d%lf%lf",&remain,&cnt,&ball_x,&ball_y);
	fclose(fpPlay);
}
void DrawBack2()
{
    iSetColor(250,0,100);
    iRectangle(90*4,105*4,40*4,10*4);
    iText(103*4,109*4,"BACK",GLUT_BITMAP_TIMES_ROMAN_24);
	//if(remain==0)
		//fDrawGame=1;
}
void DrawName()
{

	iSetColor(150, 15, 150);
	iRectangle(282, 360, 250, 30);
	if(mode == 1)
	{
		iSetColor(111, 255, 210);
		iText(320, 370, input);
	}
	iSetColor(05, 155, 255);
	iText( 350,400, "Type Your Name",GLUT_BITMAP_HELVETICA_18);
	iSetColor(155, 5, 255);
	iText(100,450,"Welcome to play the exclusive gunner game by ABHISHEK AND HASAN",GLUT_BITMAP_HELVETICA_18);
	iText(200, 100, "Click to activate the box, enter to finish.",GLUT_BITMAP_HELVETICA_18);
}
void DrawEnd()
{
	iSetColor(255,0,0);
	iText(97*4,80*4,"GAME IS OVER",GLUT_BITMAP_TIMES_ROMAN_10);
	if(cnt==n-1){
		iSetColor(255,0,0);
		iText(100*4,74*4,"YOU WIN!",GLUT_BITMAP_TIMES_ROMAN_10);
		iRectangle(85*4,60*4,50*4,8*4);
		iText(95*4,63*4,"GO TO NEXT LEVEL",GLUT_BITMAP_TIMES_ROMAN_10);
	}
	else if(cnt<n-1 && remain == 0){
		iSetColor(255,0,0);
		iText(100*4,74*4,"YOU LOST!",GLUT_BITMAP_TIMES_ROMAN_10);
		/*iRectangle(85*4,60*4,50*4,8*4);
		iText(95*4,63*4,"GO TO NEXT LEVEL",GLUT_BITMAP_TIMES_ROMAN_10);*/
	}
	rHigh();
	sprintf(EnStr,"YOUR SCORE : %d",cnt*1000);
	iSetColor(255,0,0);
	iText(95*4,55*4,EnStr,GLUT_BITMAP_TIMES_ROMAN_10);
	for(i=0;i<10;i++)
    {
		iSetColor(255,0,0);
		printf("%s",Enhigh[i]);
		iText(95*4,50*4-i*10,Enhigh[i],GLUT_BITMAP_TIMES_ROMAN_10);
    }
}
void DrawMainMenu()
{
    iSetColor(0,0,150);
    iRectangle(60*4,30*4,90*4,90*4);

    iSetColor(0,200,0);
    iRectangle(85*4,35*4,50*4,17*4);
    iRectangle(85*4,56*4,50*4,17*4);
    iRectangle(85*4,77*4,50*4,17*4);
    iRectangle(85*4,98*4,50*4,17*4);
    iSetColor(200,0,0);
    iText(100*4,105*4,"PLAY NOW",GLUT_BITMAP_TIMES_ROMAN_10);
    iText(100*4,84*4,"INSTRUCTIONS",GLUT_BITMAP_TIMES_ROMAN_10);
	iText(100*4,63*4,"EXIT",GLUT_BITMAP_TIMES_ROMAN_10);
}
void DrawInput()
{
	iSetColor(200,0,100);
	iText(88*4,74*4,"FIX VELOCITY AND ANGLE.",GLUT_BITMAP_HELVETICA_18);
	iText(90*4,70*4,"PRESS ENTER TO CONTINUE!",GLUT_BITMAP_HELVETICA_18);
}
void DrawGame()
{

	iShowBMP(0, 0, "per_back.BMP");
	//iShowBMP2(500,300,"foo.bmp",0);
	sprintf(str,"SCORE : %d",cnt*1000);
	iSetColor(255,0,0);
	iText(210*4,130*4,str,GLUT_BITMAP_TIMES_ROMAN_24);

	sprintf(pro,"SHOOT REMAINING : %d",remain-1);
	iSetColor(255,0,0);
	iText(10*4,130*4,pro,GLUT_BITMAP_TIMES_ROMAN_24);

	iSetColor(0,255,150);
	iFilledRectangle(7,0,10,20);
    iSetColor(0, 0, 0);
	iFilledPolygon(polys_x,polys_y,5);

	iSetColor(0,0,255);
	if(!lev) n=3;
	else n=4;
	for(int i=0;i<n;i++)
		iFilledRectangle(obs_x[i],obs_y[i],25,hght[i]);

	iSetColor(255, 0, 0);
	for(int i=0;i<n-1;i++){
		iFilledEllipse(ell_x[i],ell_y[i],30,18);
	}
	iSetColor(255, 100, 10);
	iFilledCircle(ball_x, ball_y, 5);

	if(flag2)
	{
		flag3=0;
		for(ith=65,j=0;ith<=v;ith+=3,j+=5)
		iFilledRectangle(120*3+(ith-30)*2+j,110*5,10,20);
	}
	if(flag3)
	{
		flag2=0;
		for(ith=65,j=0;ith<=v;ith+=3,j+=5)
		iFilledRectangle(120*3+(ith-30)*2+j,110*5,10,20);
	}

}

void DrawPlayPause()
{
	iRectangle(70*4,40*4,80*4,100*4);

    iSetColor(255,0,0);

	iRectangle(85*4,50*4,50*4,15*4);
	iRectangle(85*4,65*4,50*4,15*4);

    iSetColor(200,0,0);
    iText(102*4,70*4,"PLAY NEW",GLUT_BITMAP_TIMES_ROMAN_10);
	iText(105*4,55*4,"RESUME",GLUT_BITMAP_TIMES_ROMAN_10);
}
void DrawLevel()
{
    iSetColor(200,200,200);
    iRectangle(96*4,127*4,36*4,7*4);
    iText(100*4,129*4,"CHOOSE LEVEL",GLUT_BITMAP_TIMES_ROMAN_10);
    iRectangle(65*4,25*4,95*4,100*4);

    iSetColor(0,200,0);

	iRectangle(80*4,54*4,70*4,20*4);
	iRectangle(80*4,78*4,70*4,20*4);

    iSetColor(200,0,0);
    iText(104*4,86*4,"LEVEL 1",GLUT_BITMAP_TIMES_ROMAN_10);
	iText(104*4,62*4,"LEVEL 2",GLUT_BITMAP_TIMES_ROMAN_10);
}
void iDraw()
{

	iClear();
	iSetColor(200,200,200);

    if(fMainMenu) DrawMainMenu();
	if(fDrawLevel) DrawLevel();
	if(fDrawGame) DrawGame();
	if(fname) DrawName();
    if(fBack2) DrawBack2();
	if(fDrawInput && flag==0) DrawInput();
	if(fPlayPause) DrawPlayPause();
	if(fEnd && fRemain) DrawEnd();
	if(fEnd)  {fDrawGame=0;fDrawInput=0;fBack2=1;fRemain=1;}
	//if(remain <= 0 || cnt==n-1 ) {DrawEnd();fBack2MainMenu=1;fDrawGame=0;fDrawInput=0;}
}

/*
	function iMouseMove() is called when the user presses and drags the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouseMove(int mx, int my)
{
	//place your codes here
}


/*
	function iMouse() is called when the user presses/releases the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouse(int button, int state, int mx, int my)
{
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		//place your codes here
		if(fname)
		{
			if(mx >= 282 && mx <= 532 && my >= 360 && my <= 390 && mode == 0)
			{
				mode = 1;
			}
		}
		if(fMainMenu)
        {

            if(mx>=85*4 && mx<=85*4+35*4 && my>=98*4 && my<=98*4+17*4)
            {
                fMainMenu=0;
                //fDrawLevel=1;
				fPlayPause=1;
                fBack2=1;
				//wSave();
            }
			if(mx>=85*4 && mx<=85*4+50*4 && my>=35*4 && my<=35*4+17*4)
			{
				exit(0);
			}
        }
		/*if(fDrawLevel){
			if(mx>=80*4 && mx<=80*4+70*4 && my>=78*4 && my<=78*4+20*4) {fDrawGame=1;fDrawLevel=0;fDrawInput=1;lev=0;}
			if(mx>=80*4 && mx<=80*4+70*4 && my>=54*4 && my<=54*4+20*4) {fDrawGame=1;fDrawLevel=0;fDrawInput=1;lev=1;}
		}*/
		/*if(fDrawLevel){
			if(mx>=80*4 && mx<=80*4+70*4 && my>=78*4 && my<=78*4+20*4) {fPlayPause=1;fDrawLevel=0;lev=0;}
			if(mx>=80*4 && mx<=80*4+70*4 && my>=54*4 && my<=54*4+20*4) {fPlayPause=1;fDrawLevel=0;lev=1;}
			if(mx>=90*4 && mx<=90*4+40*4 && my>=105*4 && my<=105*4+10*4) {fDrawLevel=0;fMainMenu=1;fBack2=0;}
		}*/
		if(fPlayPause){
			if(mx>=85*4 && mx<=85*4+50*4 && my>=65*4 && my<=65*4+15*4) {fPlayPause=0;lev=0;fDrawGame=1;rSave();fDrawInput=1;}
			if(mx>=90*4 && mx<=90*4+40*4 && my>=105*4 && my<=105*4+10*4) {fMainMenu=1;fPlayPause=0;fBack2=0;}
			if(mx>=85*4 && mx<=85*4+50*4 && my>=50*4 && my<=50*4+15*4) {fPlayPause=0;rPlay();fDrawGame=1;fDrawInput=1;}
		}

		if(fDrawGame)
			if(mx>=90*4 && mx<=90*4+40*4 && my>=105*4 && my<=105*4+10*4)  {fPlayPause=1;fDrawGame=0;wResume();fDrawInput=0;}
		if(fEnd){
			if(mx>=85*4 && mx<=85*4+50*4 && my>=60*4 && my<=60*4+8*4) {lev=0;rSave();fRemain=0;fDrawGame=1;fEnd=0;fDrawInput=1;fPlayPause=0;}
			//if(mx>=90*4 && mx<=90*4+40*4 && my>=105*4 && my<=105*4+10*4) {fDrawLevel=1;fEnd=0;remain=6;fRemain=0;cnt=0;}
			if(mx>=90*4 && mx<=90*4+40*4 && my>=105*4 && my<=105*4+10*4) {fDrawLevel=1;fEnd=0;fRemain=0;}
		}

	}
	if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		//place your codes here
	}
}


/*
	function iKeyboard() is called whenever the user hits a key in keyboard.
	key- holds the ASCII value of the key pressed.
*/
void iKeyboard(unsigned char key)
{
	int i;
	if(mode == 1)
	{
		if(key == '\r')
		{
			mode = 0;
			strcpy(str2, input);
			printf("%s\n", str2);
			for(i = 0; i < len; i++)
				input[i] = 0;
			len = 0;
			fMainMenu=1;
			fname=0;
		}
		else
		{
			input[len] = key;
			len++;
		}
	}
	if(key == 'p')
	{
		iPauseTimer(0);
	}
	if(key == 'r')
	{
		iResumeTimer(0);
	}
	if(key == 'a' && flag==0 && v<=95) {flag2=1;v+=3;flag3=0;}

	if(key == 's' && flag==0 && v>=60) {flag3=1;v-=3;;flag2=0;}
	if(key == '\r' && flag==0 && fRemain==0) {
		flag=1;
		remain--;
		if(remain == 0) {fRemain=1;fEnd=1;}
		//if(cnt==n-1) {fEnd=1;fBack2MainMenu=1;fDrawGame=0;fDrawInput=0;}
		//else if(remain <= 0) {fEnd=1;fBack2MainMenu=1;fDrawGame=0;fDrawInput=0;}
		ball_x=(polys_x[2]+polys_x[3])/2;
		ball_y=(polys_y[2]+polys_y[3])/2;

		PlaySound((LPCSTR) "C:\\Users\\mrahman\\Desktop\\gunshot.wav", NULL,
SND_FILENAME | SND_ASYNC);
		//flag2=0;
		//flag3=0;
	}

	//place your codes for other keys here
}

/*
	function iSpecialKeyboard() is called whenver user hits special keys like-
	function keys, home, end, pg up, pg down, arraows etc. you have to use
	appropriate constants to detect them. A list is:
	GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
	GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
	GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
	GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
*/

void iSpecialKeyboard(unsigned char key)
{

	if(key == GLUT_KEY_UP) {
		if(flag==0){
			if(polys_x[2]>=40){
				for(int i=2;i<4&&(degre>0);i++) {polys_x[i]-=incre;polys_y[i]+=incre;}
				//printf("%lf\n",polys_x[2]);
				degre+=cn_deg;
			}
		}

	}

	if(key == GLUT_KEY_DOWN) {
		if(flag==0){
			if(polys_x[2]<=70){
				for(int i=2;i<4;i++) {polys_x[i]+=incre;polys_y[i]-=incre;}
				degre-=cn_deg;
			}
			//printf("%lf\n",degre);
		}
	}
	//place your codes for other keys here
}


void ballChange()
{

	if(flag==1)
	{
		if(!flagobs){
			ball_y=(ball_x*tan((3.14/180)*degre) - (g*ball_x*ball_x)/(2*(v*cos((3.14/180)*degre))*(v*cos((3.14/180)*degre))));
			ball_x+=v*cos((3.14/180)*degre)*0.3;//ball_x1=ball_x;ball_y1=ball_y;
		}
		if(flagobs)
		{
			//printf("%lf  %lf",ball_x1,ball_y1);
			//ball_x1+=(-1)*cos((3.14/180)*degre)*0.3;
			ball_x-=4;
			ball_y-=4;
			//ball_y1-=(ball_x*tan((3.14/180)*degre) - (g*ball_x*ball_x)/((-2)*(v*cos((3.14/180)*degre))*(v*cos((3.14/180)*degre))));
		}
		for(int i=0;i<5;i++){
			if((ball_x >= ell_x[i]-30 && ball_x <= ell_x[i]+30) && ball_y < ell_y[i]+18 && ball_y>=0) {ell_x[i]=-200;ell_y[i]=-200;flag=0;flagobs=0;ball_x=-10;ball_y=-10;cnt++;
				if(cnt==n-1) {fRemain=1;fEnd=1;}
			}

			else if(ball_x>=obs_x[i] && ball_x<=obs_x[i]+5 && ball_y < hght[i]) {flagobs=1;hght[i]-=cnst;}
			else if((ball_x >= obs_x[i]+6 && ball_x <= obs_x[i]+25) && ball_y <= hght[i] && ball_y>=0 && flagobs==0) {
				hght[i]-=cnst;
				ball_x=-10;
				ball_y=-10;
			}

			if(ball_y < 0) {ball_x=-10,ball_y=-10;flag=0;flagobs=0;}
		}
	}

}

int main()
{
	//place your own initialization codes here
	//75
	//13
	wSave();
	iSetTimer(150,ballChange);

	iInitialize(250*4, 150*4, "Gunner");
	return 0;
}
