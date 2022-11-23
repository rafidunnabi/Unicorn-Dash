#ifndef PROFILE_H_INCLUDED
#define PROFILE_H_INCLUDED

#include <stdio.h>
#include <string.h>

// WRITE YOUR CODE HERE
///////////////////////

struct Profile {
	char player_name [80];
	int score;

    Profile(){
		strcpy(player_name, "_Guest");
		score = 0;
	}

	
	Profile(char* player_name, int _score)
	  {
		strcpy(this->player_name,player_name);
		score = _score;
	  }

	Profile(char* player_name)
	  {
		strcpy(this->player_name,player_name);
		score = 0;
	  }

	char* getPlayerName(){
		return player_name;
	}

	void setPlayerName(char* _player_name){
		strcpy(player_name, _player_name);
	}

	int getScore(){
		return score;
	}

	void setScore(int _score){
		score = _score;
	}

};




Profile player("Pabon");// initial player
Profile topPlayers[10]; // player er array to write and read file



//filereade kore
void fileReader(void)
{

   char str[80];
   int scr;
    FILE *fp = fopen("scores.txt", "r");
    for(int i=0; i<5; i++){     
        fscanf(fp, "%s %d", str, &scr);
        topPlayers[i].setPlayerName(str);
        topPlayers[i].setScore(scr);
    }
    fclose(fp);
}

//filewrite kore
void fileWriter(void)
{
	FILE *fp = fopen("scores.txt","w");
	for(int i=0;i<5;i++)
	{
		fprintf(fp,"%s %d\n",topPlayers[i].getPlayerName(),topPlayers[i].getScore());
	}

fclose(fp);

}

//sort
void sort(void)
{
	char str[80];
	int scr;
	for(int i=0; i<6; i++){
		for(int j=0; j<5; j++){
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
}


















///////////////////////

#endif