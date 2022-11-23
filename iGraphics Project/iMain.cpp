#include "iGraphics.h"
#include "bitmap_loader.h"
#include <stdio.h>
#include "profile.h"
#include <string.h>
void ss(int gg);

/*
 function iDraw() is called again and again by the system.
 
 */
int menu_s = 0;
int go_s = 0;
int play_s = 0;
int fflag = 1;
 
char show[100];
int image1, g1, g2, g3, g4, g5, g6, g7, g8, g9, g10, background;// menu, bg and horses
int horseAnimationTimer, scoreTimer, loadingTimer;  // timers
int ghora; // current image of horse
int loadingScreen, showing=1; // load screen
int playing = 0;
int instruction, ins = 0; //instruction bg and flag
int loadScores=0; // show screen from home menu flag
int jumpButton,boostButton,pauseButton,resumeButton; // button images
int back1,back2,back3,back4,back5; // 5 bases
int base1X=600,base2X=50,base1,base2; // 650
int falling = 0; // flag falling
int brokenLogChikon,brokenLogMota; // broken log base images


//boost
int boostedHorse;
int boost=0;
int boostTimer=0;

//jumpRotate
int floog=0; // up
int flog=0; // down
 
int jumpy = 0; // change of co-ordinate
int ghora_y=150; // y of horse
int paused = 0; // pause flag

// coin related
int coinImage;
int coinFlag = 1;

//Game overs
char myText[20];
int len = 0;
int point;
char temp[100];
int gameOver;


void resetEverything(){ // resets everything after game over

	base1X = 600;
	base2X = 50;
	falling = 0;
	base1 = back1;
	base2 = back2;
	jumpy = 0;
	boost = 0;
	floog = 0;
	flog = 0;
	ghora_y = 150;
	coinFlag = 1;
	menu_s = 0;
	go_s = 0;
	play_s - 0;
	 
}





void collision(){ // collide for rocks and break through logs



	if(base1==back1)
	{
		if(base1X+165<=190 && base1X+30+165>=190 && ghora_y<=33+170)//chikongach
		{
			if(boost == 1)
			{
				base1=brokenLogChikon; // if boosted, show the broken log base else die
			}
			else{
				
					point = topPlayers[5].getScore();
				sprintf(temp,":   %d",point);
					playing = 99;
					ghora_y = 150;
					jumpy = 0;
					resetEverything();
			}
		}
	}
	if(base1==back3)
	{
		if(base1X+190<=190 && base1X+40+190>=190 && ghora_y<=33+165)//rock
		{
			
			point = topPlayers[5].getScore();
				sprintf(temp,":   %d",point);
					playing = 99;
					ghora_y = 150;
					jumpy = 0;
					resetEverything();
					
		}
	}
	if(base1==back5)
	{
		if(base1X+195<=190 && base1X+45+195>=190 && ghora_y<=33+160)//motagach
		{
		
			if(boost == 1)
			{
				base1=brokenLogMota; // if boosted, show the broken log base else die
			}
			else
				{
				point = topPlayers[5].getScore();
				sprintf(temp,":   %d",point);
					playing = 99;
					ghora_y = 150;
					jumpy = 0;
					resetEverything();
				
			}
		}
	}



}


void jumpGhora(){
    ghora_y+=jumpy; // increase or decrease the Y co-ordinate of ghora
    if(ghora_y>300) // maximum height reached
    {
		flog=0; // take off
		floog=1; // landing
        jumpy=(-1)*jumpy; // negetive increasing... goes down
    }
	/*if(ghora_y<170)
		floog=0;*/

    /*if(ghora_y<=150)
    {
        floog = 0;
		if(falling==0){
			ghora_y = 150;
			jumpy = 0;
			
		}
    }
	
		if(jumpy==0 && ((base1X + 400 <110 && base2X > 190) || (base2X + 400 < 110 && base1X > 190))){
			falling = 1;
		}
		if(falling==1)
			ghora_y -= 15;*/


	if(ghora_y <= 150) // landing on base
	{
		if((base1X + 400 <110 && base2X > 190) || (base2X + 400 < 110 && base1X > 190)) // payer nich mati nai
			falling = 1; // more jabe
		if(falling == 1) // more jaitese
		{
			boost = 0; // morar shomoy boost dibe na
			ghora_y -= 10; // ghora niche portese
			jumpy=0; // no jump
		}
		else // payer niche mati ase
		{
			floog = 0; // niche pora bondho
			jumpy = 0; // jump shesh
			ghora_y = 150; // perfect landing
		}


	}

}
 
void unboost()
{
	if(boost == 1)
	{
		boostTimer++; // boost beshikkhon hoy nai
	}
	if(boostTimer > 120) //60
	{
		boost = 0; // boost shesh
		boostTimer = 0; // abar boost deyar jonno upojukto
	}
	
}


void showScore(){ // current score show kore
    iSetColor(255, 255, 255);
    sprintf(show, "Score: %d", topPlayers[5].score);
    //puts(show);
    iText(20, 430, show, GLUT_BITMAP_HELVETICA_18);
}
void scoreIncrement(){ // score barbe, timer diye
    if(playing == 1)
        topPlayers[5].score++;
}
void dontShowLoad(){ // loading screen dekhabe na
    showing=0;
}
void changeImage(){ // ghora animation
    if(ghora==g1)   ghora = g2;
    else if(ghora==g2)  ghora = g3;
    else if(ghora==g3)  ghora = g4;
    else if(ghora==g4)  ghora = g5;
    else if(ghora==g5)  ghora = g6;
    else if(ghora==g6)  ghora = g7;
    else if(ghora==g7)  ghora = g8;
    else if(ghora==g8)  ghora = g9;
    else if(ghora==g9)  ghora = g10;
    else if(ghora==g10) ghora = g1;
	jumpGhora();
}

void baseImageChange() // arbitarily base gula ashe one after another
{
	if(base1X+400<=0)
	{
		base1X = base2X + 550;
		if(base1 == back1 || base1 == brokenLogChikon)
			base1 = back3;
		else if(base1 == back3)
			base1 = back5;
		else if(base1 == back5 || base1 == brokenLogMota)
			base1 = back1;
		coinFlag = 1;
	}

	if(base2X+400<=0)
	{
		base2X = base1X + 550;
		if(base2 == back2)
			base2 = back4;
		else if(base2 == back4)
			base2 = back2;
		coinFlag = 1;
	}
	

}
int tX; // coin collect korar por +100 lekha er co-ordinate
void showCoin(){ // coin show korbe or collected hoile text dekhabe
	int cX;
	
	if(base1X < base2X) // 2nd base er shamne coin
		cX = base2X-75; 
	else
		cX = base1X - 75; // 1st base er shamne coin
	if(coinFlag)// coin collect hoy nai so, show korbo
		iShowImage(cX, 245, 25, 25, coinImage);
	if(tX>0){// 
		iSetColor(255, 255, 255);
		iText(tX, 260, "+100", GLUT_BITMAP_HELVETICA_18 );
		tX -= 1;
	}
	if(cX>=135 && cX<=185 && ghora_y>=220 && ghora_y<=240){// coin collected
		if(coinFlag){
			ss(3);
			play_s = 0;
			topPlayers[5].score += 100;// coin collection reward
			coinFlag = 0;
			tX = cX+50;

		}
	}
}


void ss(int gg)
{
	if(gg == 0)
		PlaySound("sound\\intro.wav",NULL,SND_LOOP | SND_ASYNC);
	else if(gg == 1)
		PlaySound("sound\\Horse Gallop.wav",NULL,SND_LOOP | SND_ASYNC);
	else if(gg == 3)
		PlaySound("sound\\coin.wav",NULL, SND_ASYNC);
	else
		PlaySound("sound\\gameover.wav",NULL,SND_ASYNC);
}




 
void iDraw()
{
    //place your drawing codes here
	//printf("%d %d",base1X , base2X);
    iClear();

	collision(); // tokkor lagar logic
	if(playing == 0)
    {
		iShowImage(0, 0, 800, 470, image1);//menu
		if(menu_s == 0)
		{
			ss(0);
			menu_s = 1;
		}
	}

	if(playing == 99) // game over screen
	{
		if(go_s == 0)
		{
			ss(99);
			go_s = 1;
		}

		iShowImage(0,0,800,470,gameOver);	
		iSetColor(0,255,255);
		iText(374,230,temp,GLUT_BITMAP_HELVETICA_18);
		iSetColor(0,0,0);
		iText(350,120,myText,GLUT_BITMAP_HELVETICA_18);
	}
 
    if(playing==1){ 
		
	
		if(play_s == 0)
		{
			ss(1);
			play_s = 1;
		}
	
			
		
		
		// if playing

        iShowImage(0, 0, 800, 470, background);
        
		iShowImage(20, 10, 50, 50,jumpButton);
        iShowImage(730, 10, 50, 50,boostButton);
        iShowImage(430, 400, 50, 50,pauseButton);
        iShowImage(370, 400, 50, 50,resumeButton);
        showScore();
		if(paused==0){ // changing base co-ordinate
			baseImageChange();
			base1X -= 1; // base er co-ordinate change
			base2X -= 1; // same
			if(ghora_y<0){ // ghora died

					point = topPlayers[5].getScore();
				sprintf(temp,":   %d",point);
					playing = 99;
					ghora_y = 150;
					jumpy = 0;


			}
		}
		
		iShowImage(base1X,33,400,220,base1); // showing base 1
		iShowImage(base2X,33,400,220,base2); // showing base 2

		showCoin();// coin er kaj

		if(floog==1) // landing
		{
			iRotate(110,ghora_y,-30);
			//if(falling==0)
			iShowImage(110, ghora_y, 80, 50 ,ghora);
			iUnRotate();
		}
	   else if(flog==1) // takeOff
		{
			iRotate(110,ghora_y,25);
			if(falling==0)
				iShowImage(110, ghora_y, 80, 50,ghora);
			iUnRotate();
		}
		else{ // normal dour

			iUnRotate();
			if(boost==1)
			{
				unboost();
				iShowImage(100, ghora_y, 90, 50,boostedHorse);
			}
			else if(falling==0)
		    iShowImage(110, ghora_y, 80, 50,ghora);
			if(falling==1){
				boost = 0;
				iRotate(110,ghora_y,-30);
				iShowImage(110, ghora_y, 80, 50 ,ghora);
				iUnRotate();
			}

		}
	

    }
 
    if(showing==1) // loading screen
        iShowImage(0,0,800,470,loadingScreen);
 
    if(ins == 1) // instruction button
    {
        iSetColor(0,0,0);
        iFilledRectangle(47, 187, 406, 231);
        iShowImage(50,190,400,225,instruction);
    }
    if(loadScores==1){ // previous scores
       fileReader();
        iSetColor(0,0,0);
        iFilledRectangle(47, 187, 406, 231);
        iSetColor(185,215,165);
        iFilledRectangle(50, 190, 400, 225);
        iSetColor(0, 0, 0);

		sprintf(show, "%d", topPlayers[0].getScore());
        iText(100, 380,topPlayers[0].getPlayerName(), GLUT_BITMAP_TIMES_ROMAN_24);
		iText(270, 380, show, GLUT_BITMAP_TIMES_ROMAN_24);

		sprintf(show, "%d", topPlayers[1].getScore());
        iText(100, 340, topPlayers[1].getPlayerName(), GLUT_BITMAP_TIMES_ROMAN_24);
		iText(270, 340, show, GLUT_BITMAP_TIMES_ROMAN_24);

		sprintf(show, "%d",  topPlayers[2].getScore());
        iText(100, 300, topPlayers[2].getPlayerName(), GLUT_BITMAP_TIMES_ROMAN_24);
		iText(270, 300, show, GLUT_BITMAP_TIMES_ROMAN_24);

		sprintf(show, "%d",  topPlayers[3].getScore());
        iText(100, 260, topPlayers[3].getPlayerName(), GLUT_BITMAP_TIMES_ROMAN_24);
		iText(270, 260, show, GLUT_BITMAP_TIMES_ROMAN_24);

		sprintf(show, "%d",  topPlayers[4].getScore());
        iText(100, 220, topPlayers[4].getPlayerName(), GLUT_BITMAP_TIMES_ROMAN_24);
		iText(270, 220, show, GLUT_BITMAP_TIMES_ROMAN_24);

        /*iText(100, 340, "Parvez     980", GLUT_BITMAP_TIMES_ROMAN_24);
        iText(100, 290, "Pabon     800", GLUT_BITMAP_TIMES_ROMAN_24);
        iText(100, 240, "Zakia     750", GLUT_BITMAP_TIMES_ROMAN_24);
        iText(100, 200, "Pabon     80", GLUT_BITMAP_TIMES_ROMAN_24);*/
    }
 
}
 
void iPassiveMouse(int x, int y)
{
    ;
}
 
 
/*
 function iMouseMove() is called when the user presses and drags the mouse.
 (mx, my) is the position where the mouse pointer is.
 */
void iMouseMove(int mx, int my)
{
    //printf("x = %d, y= %d\n", mx, my);
    //place your codes here

	



}
 
/*
 function iMouse() is called when the user presses/releases the mouse.
 (mx, my) is the position where the mouse pointer is.
 */
void iMouse(int button, int state, int mx, int my)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        //place your codes here
        //printf("x = %d, y= %d\n",mx,my);
 


 
        if(mx>=475 && mx<= 700  && my>=375 && my<=415) // play button
        {  
			playing = 1;
            ins=0;
            loadScores = 0;
			resetEverything();
        }
        else if(mx>= 475 && mx<=700 && my>= 315 && my<=355){ // show score button
            loadScores = 1;
            ins = 0;
        }
        else if(mx>=475 && mx<= 700  && my>=255 && my<=295){ // manual button
            ins = 1;
            loadScores = 0;
        }
        else if(mx>=475 && mx<= 700  && my>=195 && my<=235){ // exit
            exit(0);
        }
 
        else if(playing ==1 && mx>=20 && mx<=70 && my>=10 && my<=60) // jump button
        {
            if(jumpy==0 && paused == 0 && falling == 0)
				{
					jumpy=20; //20
			        flog=1;
					boost = 0;
				}
        }
		else if(playing ==1 && mx>=730 && mx<=780 && my>=10 && my<=60) // boost button
		{
			if(boost == 0 && paused == 0 && falling == 0)
			boost = 1;
		}

		else if(playing==1 && mx>=430 && mx<=480 && my>=400 && my<=450){ // pause button
			paused = 1;
			iPauseTimer(horseAnimationTimer);
			iPauseTimer(scoreTimer);
		}

		else if(playing==1 && mx>=370 && mx<=420 && my>=400 && my<=450){ // resume button
			paused = 0;
			iResumeTimer(horseAnimationTimer);
			iResumeTimer(scoreTimer);
		}
 
        else{ // home menu te bahire click korle current page off
            ins = 0;
            loadScores = 0;
        }
       
 
    }
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
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

    
    if(key == ' ') // jump
    {
       if(jumpy==0 && paused == 0 && falling == 0)
				{
					jumpy=20;
			        flog=1;
					boost = 0;
				}
    }
	else if(key=='j'){ // boost
		if(boost == 0 && paused == 0 && falling == 0)
			boost = 1;
	}
	else if(key=='k'){ // pause
			paused = 1;
			iPauseTimer(horseAnimationTimer);
			iPauseTimer(scoreTimer);
	}
	else if(key=='f'){ // resume
		paused = 0;
		iResumeTimer(horseAnimationTimer);
		iResumeTimer(scoreTimer);
	}

	if(playing == 99) // name input
{
	
		if(key == '\r')
		{
			playing= 0;

			topPlayers[5].setPlayerName(myText);

			//player.setScore(0);

			for(int i = 0; i < len; i++)
				myText[i] = 0;
			len = 0;

			sort();
			fileWriter();


			topPlayers[5].setScore(0);
			


		}
		else
		{
			myText[len] = key;
			len++;
		}

}

    /*else if (key == 'a' && speed < 5)
        speed += 1;
    else if (key == 's' && speed > 0)
        speed -= 1;*/
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
 
    if (key == GLUT_KEY_END)
    {
        exit(0);
    }
 
    //place your codes for other keys here
}
 
int main()
{
    //place your own initialization codes here.
 
   char str[80];
   int scr;
    FILE *fp = fopen("scores.txt", "r");
    for(int i=0; i<5; i++){     
        fscanf(fp, "%s %d", str, &scr);
        topPlayers[i].setPlayerName(str);
        topPlayers[i].setScore(scr);
    }
    fclose(fp);
	for(int i=0; i<5; i++){
		for(int j=0; j<4; j++){
			if(topPlayers[j].getScore() < topPlayers[j+1].getScore()){
				scr = topPlayers[j].getScore();
				topPlayers[j].setScore(topPlayers[j+1].getScore());
				topPlayers[j+1].setScore(scr);

				strcpy(str, topPlayers[j].getPlayerName());
				topPlayers[j].setPlayerName(topPlayers[j+1].getPlayerName());
				topPlayers[j+1].setPlayerName(str);
			}
		}
	}


			

	
    //boostTimer=iSetTimer(1200,unboost);  // pabon
    iInitialize(800, 470, "Unicorn Dash");
 
    image1 = iLoadImage("images\\menu.jpg"); // ghora image loading
    g1 = iLoadImage("images\\animated horse\\layer1.png");
    g2 = iLoadImage("images\\animated horse\\layer2.png");
    g3 = iLoadImage("images\\animated horse\\layer3.png");
    g4 = iLoadImage("images\\animated horse\\layer4.png");
    g5 = iLoadImage("images\\animated horse\\layer5.png");
    g6 = iLoadImage("images\\animated horse\\layer6.png");
    g7 = iLoadImage("images\\animated horse\\layer7.png");
    g8 = iLoadImage("images\\animated horse\\layer8.png");
    g9 = iLoadImage("images\\animated horse\\layer9.png");
    g10 = iLoadImage("images\\animated horse\\layer10.png");
    background = iLoadImage("images\\background.jpg");
    instruction = iLoadImage("images\\instruction.jpg");


	

	// base image loading
	back1 =  iLoadImage("images\\bases\\Asset 1.png");

	back2 =  iLoadImage("images\\bases\\Asset 2.png");

	back3 =  iLoadImage("images\\bases\\Asset 4.png");

	back4 =  iLoadImage("images\\bases\\Asset 3.png");

	back5 =  iLoadImage("images\\bases\\Asset 5.png");

	//boosted horse
	boostedHorse = iLoadImage("images\\boostedHorse.png");

	// base 
	base1 = back1;
	base2 = back2;

	coinImage = iLoadImage("images\\ScoreCollector.png");
 
 
    jumpButton = iLoadImage("images\\buttons\\jumpButton.png");
    boostButton = iLoadImage("images\\buttons\\boostButton.png");
    pauseButton = iLoadImage("images\\buttons\\pauseButton.png");
    resumeButton = iLoadImage("images\\buttons\\playButton.png");
 
    loadingScreen = iLoadImage("images\\loadingScreen.png");


	//brokenlog
	brokenLogChikon = iLoadImage("images\\bases\\brokenBase1.png");
	brokenLogMota = iLoadImage("images\\bases\\brokenBase2.png");


	//game over
	gameOver = iLoadImage("images\\gameOver.jpg");
 
    ghora = g1;
 
    loadingTimer= iSetTimer(1000, dontShowLoad);//1000
    scoreTimer = iSetTimer(200, scoreIncrement);//100
    horseAnimationTimer = iSetTimer(40, changeImage);//20

	
   
    iStart(); // it will start drawing
 
    return 0;
}
