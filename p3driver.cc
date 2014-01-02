#include <vector>
#include <iostream>
#include <cstdlib>
#include <cassert>
#include <fstream>
#include "SmartPlayer.h"
#include "RandomPlayer.h"
#include "HumanPlayer.h"
#include "Deck.h"
#include "Trick.h"

using namespace std;

int playerScore[4] = {0,0,0,0};

int main(int argc, char *argv[]){
   //Player list, vector
   vector<Player*> playerlst;
   //Default maximum point
   int maxPoint = 40;
   //Number of game played
   //13 tricks = 1 game
   int ngame = 1;
   //For generating deck properly
   bool havedeck = false;
   //Deck
   Deck deck1;
   //For playing card game
   int leftCards;
   //Winner's score and index; initialize to maxPoint
   int winnerScore, winnerIndex = 0;
   //Game Termination
   bool endGame = false;
   //Player Index who goes over the maxPoint
   //maX is the maximum score of players' scores
   int playerOver, maX=0;
   //For spliting hand cards to player
   int splitIndex = 0;
   //For play Hearts game
   Trick t;

   // Since there is no assumption that each option will be input only once, 
   // hence we cannot find out the maximum number of arguments.
   // And by testing Hearts_32, if repeated options are input then the program
   // takes the lastest option. Hence by make a for loop each argument will be 
   // checked to make sure all options are input correctly   
   
   //Options can occur at any order with some restrictions
   for(int index=1;index<argc;index++){
      //From here options are provided
      //For change maximum point for the game
      if((string)argv[index] == "-s"){
	 //Error Message
	 if(argc == index+1){
	    cerr<<"Error, -s requires another argument.  Aborting.\n";
	    exit(1);
         }
	 //Set the maximum point for the game
	 //Default Maximum Point is 40
	 maxPoint = atoi(argv[index+1]);
	 //If the maxPoint is not positive
         if(maxPoint <= 0){
	    cerr<<"Error, maxScore must be positive.\n";
	    exit(1);
         }
	 index += 1;
      }
      //For change a seed number for generating a random number
      else if((string)argv[index] == "-r"){
	 //Error Message
         if(index+1 == argc){
	    cerr<<"Error, -r requires another argument.  Aborting.\n";
	    exit(1);
 	 }
	 //If a deck is already generated, then do not generate again
	 if(havedeck){
	    cerr<<"Aborting; -r must occur before -d on command line if both flags are used.\n";
	    exit(1);
         } 
	 //If no deck is generated yet, set the seed value for randomly generating
         deck1.setRandomSeed(atoi(argv[index+1]));
	 index += 1;
      }
      //For read cards from a certain file if it is exists
      else if((string)argv[index] == "-d"){
	 //Error Message
         if(index+1 == argc){
	    cerr<<"Error, -d requires another argument.  Aborting.\n";
	    exit(1);
 	 }
	 //File Name
         string filename = argv[index+1];
	 //File resource
         ifstream fin(filename.c_str());
	 //Fail to open the file
         if(fin.fail()){
	    cerr<<"Error, couldn't open card deck input file \""<<filename<<"\""<<endl;
	    exit(1);
         }
	 //Temporary card for making a deck
         Card *tmp;
	 //Needed when read card from the file
         string strcard;
	 //Loop for generating a deck
         for(int i=0;i<52;i++){
	    fin>>strcard;
	    tmp = new Card(strcard);
	    deck1.push_back(tmp);
         }
	 //Ensure that only one deck is generated
         havedeck = true;
	 //argument index
	 index += 1;
      }
      //For assigning players with custmized name and type
      else if((string)argv[index] == "-p"){
	 //Error message
         if(index+1 == argc){
	    cerr<<"Error, -p requires another argument.  Aborting.\n";
	    exit(1);
	 }
 	 //Player real name
         string pname;
	 //Player name with type specified 
         string tmpname;
	 //argument index, add 1 to ignore excutable file
	 int tmpargc = index + 1;
         //Make this run 4 times because there will be always 4 players
         for(int i=0;i<4;i++){
	    //If the type of player is "SmartPlayer"
            if((string)argv[tmpargc+1] == "S"){
	       tmpname = argv[tmpargc];
               //add "s" in front of the name of palyer
	       pname = "s" + tmpname;
	       //add player into a player list vector
	       playerlst.push_back(new SmartPlayer(pname));
	       //increase the argument index by 2 since it takes 2 
	       tmpargc += 2;
            }
 	    //If the type of player is "RandomPlayer"
            else if((string)argv[tmpargc+1] == "R"){
	       //Set the seed value for random number generation
	       int seedAssigned = atoi(argv[tmpargc+2]);
	       tmpname = argv[tmpargc];
	       //add "r" in front of the player name
	       pname = "r" + tmpname;
	       //add player into a player list vector
       	       playerlst.push_back(new RandomPlayer(pname,seedAssigned));
	       //increase the argument index by 3 since it requires 3
	       //playername, playertype, and seed value for random number
	       tmpargc += 3;
            }
	    //If the type of player is "HumanPlayer"
            else if((string)argv[tmpargc+1] == "H"){
	       tmpname = argv[tmpargc];
	       //add "h" at the front of player name
	       pname = "h" + tmpname;
	       //add player into the player list, vector
	       playerlst.push_back(new HumanPlayer(pname));
	       //increase argument index by 2 since it requires 2 arguments
	       tmpargc += 2;
            }
	    //If the type of player is non of the three types
            else if((string)argv[tmpargc+1] != "S" || 
	            (string)argv[tmpargc+1] != "R" ||
	            (string)argv[tmpargc+1] != "H"){
	       cerr << "Illegal player kind: \"" << (string)argv[tmpargc+1] << "\"\n";
	       exit(1);
            }
	    //Otherwises, all goes to printing error
            else{
	       cerr<<"Error, -p requires another argument. Aborting."<<endl;
	       exit(1);
	    }
         }
	 //index = tmpargc;
      }
   }
   //If no deck is generated
   if(!havedeck)
      deck1.generate();
   //If no players are specified 
   if(playerlst.size() != 4){
      playerlst.push_back(new SmartPlayer("sAlice"));
      playerlst.push_back(new SmartPlayer("sBob"));
      playerlst.push_back(new SmartPlayer("sCarole"));
      playerlst.push_back(new SmartPlayer("sTed"));
   }
   //State the beginning of game!
   cout << "Starting a new game of Hearts. The MaxPoints is " <<maxPoint<<".\n\n";

   //Game Start!
   while(!endGame){
      cout<<"At the beginning of hand "<<ngame<<", here is the deck:\n    ";
      //Shuffle the generated deck
      deck1.shuffle(); 
      //Print the deck
      deck1.print();
      cout<<"\n\n";
      cout<<"Here are the hands for each player at the start of hand number "<<ngame<<endl; 
      //Number of players must be 4
      //52 / 4 = 13
      leftCards = 13;
       
      //Spliting cards to each player.
      //Logic I applied here is every time the ganme is over, 
      //the last card in the deck is given to the next player
      //In first game, the last card in deck is the first card of first player
      //In second game, the last card in deck is the first card of second player
      //so on this pattern is kept and cards are splited with this pattern until
      //the game is over.
      for(int i=51;i>=0;){
	 for(int j=0;j<4;j++){
            playerlst.at(splitIndex)->push_back(deck1.at(i));
	    if(splitIndex == 3)
	       splitIndex = 0;
	    else
	       splitIndex++;
	    i--;
         }
      }
      //Show the hand of each player before the game starts!
      for(int i=0;i<4;i++){
         cout<<playerlst.at(i)->getName()<<" has these cards:\n";
         playerlst.at(i)->printhand();
         cout<<"\n";
      }

      //Play the HEARTS GAME 
      t.playing(playerlst, ngame,leftCards);

      //Delete the used deck and make a new deck
      for(unsigned int i=0;i<deck1.size();i++){
	 delete deck1.at(i);
      }
      //Make sure that the deck is deleted completely
      deck1.clear();
      //Generate a new deck for next game
      deck1.generate();
      //Increase game number by 1
      ngame++;
      splitIndex++;
      if(splitIndex == 4)
	 splitIndex = 0;
      //Check if any player's score is going over the maxPoint
      //If so, stop game and print the result of game played
      //If not, keep playing~
      for(int i=0;i<4;i++){
	 if(maX < playerScore[i]){
	    playerOver = i;
	    maX = playerScore[i];
         }
      }
      //If the maximum score from the players goes over the maxPoint
      if(maX >= maxPoint)
	 endGame = true;
   }

   //Game Result~:
   cout<<"The game is over."<<endl;
   cout<<playerlst.at(playerOver)->getName()<<" has exceeded "<<maxPoint<<" points.\n";

   //Find out the winner of this HEARTS GAME!!!!!!!!!
   //winnerScore is initialized with maxPoint
   winnerScore = maxPoint;
   for(int i=0;i<4;i++){
      if(playerScore[i] < winnerScore){
	 winnerIndex = i;
	 winnerScore = playerScore[i];
      }
   }
   //STATE WINNER
   cout<<"The winner is "<<playerlst.at(winnerIndex)->getName()<<endl;      

   //PLAYERS went home(deleting)
   for(int i=0;i<4;i++){
      delete playerlst[i];
   } 
   //Done!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
   return 0;
} 
