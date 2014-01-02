#include "Trick.h"

//Constructor
Trick::Trick() {}

//Extern int array for player's score
extern int playerScore[4];

//Trick class function, playing, for playing a Hearts Card Game
void Trick::playing(vector<Player*> &plist, int ntricks, int cardLeft){
   //Number of nth trick number
   int nthTrick;
   //Game Leader Index
   int leader;
   //Game Winner Index
   int winner;
   //Name of Winner
   string win;
   //Card index for playing Hearts game
   int cardIndex=0;
   Card trump;
   //Card array when winner collects four selected cards
   Card chosenCard[4];
   //A player index for rest three players to play their Hearts Game
   int index;

   //A for loop which repeats 13 times 
   //One game = 13 tricks
   for(nthTrick=1;nthTrick<14;nthTrick++){
      cout<<endl;
      cout<<"Now starting round "<<nthTrick<<" of hand "<<ntricks<<endl;
      
      //Very First Game
      if(cardLeft == 13){
	 //Find out who has Two of Clubs
	 for(int i=0;i<4;i++){
	    if(plist.at(i)->hasTC(cardLeft)){
	       //Here, true mean the player leads with 2C
	       trump = plist.at(i)->playCard(cardLeft, true);
	       //If 2C exists, becomes temporary leader
	       leader = i;
	       //temporary winner
	       winner = i;
	       //Find out who has 2C
	       win = plist.at(i)->getName();
	       //Print
	       cout<<"  "<<plist.at(i)->getName()<<" has "<<trump
		   <<" and leads with it\n";
	       //And collects for now
	       chosenCard[cardIndex] = trump;
	       cardIndex++;
	       break;
     	    }
   	 }
         //Now rest of players play their games
	 index = leader+1;
	 for(int i=0;i<3;i++){
	    //Since the index of player list is from 0 to 3
	    //if the index becomes 4, then reset to 0
	    if(index == 4)
	       index = 0;
	    //Get the card
            Card next = plist.at(index)->playCard(cardLeft,trump);
	    chosenCard[cardIndex] = next;
	    cardIndex++;
            //If the player can follow the trump card
            if(next.getSuit() == trump.getSuit()){
               cout<<"  "<<plist.at(index)->getName()<<" followed suit with "<<next<<endl;
	       //If the trump card is less than the current card
               if(trump.getRank() < next.getRank()){
	          //Temporary winner
                  winner = index;
	          //Switch the trump card to current card
                  trump = next;
	       }
            }
 	    //If player has no same-suit cards in the hand 
            else
               cout<<"  "<<plist.at(index)->getName()<<" threw off "<<next<<endl;
	    index++;
         }
         //Now one trick is over, print who collects four cards
         cout<<"  "<<plist.at(winner)->getName()<<" won the trick and added the following cards:"
             <<endl<<"    ";
	 //Print out collection of cards and calculate the score
	 //if players collect Hearts cards or QueenOfSpades
 	 for(int i=0;i<4;i++){
	    cout<<chosenCard[i]<<" ";
	    playerScore[winner] += chosenCard[i].getHeartsValue();
         }
         //Reinitialize card index and the winner will be chosen for next round
	 cout<<"\n";
         //Initialize the card index(collecting 4 card array one)
	 cardIndex = 0;
	 //Winner becomes next game's leader
	 leader = winner;
      }
      //After the very first game, from trick 2 to trick 13,
      //Player does not have TwoOfClubs card start trick with rules from website
      else{
         //"false" means leader does not TwoOfClubs
	 trump = plist.at(leader)->playCard(cardLeft, false);
	 //Collect a card for now
	 chosenCard[cardIndex] = trump;
         //For card array
	 cardIndex++;
	 //Player who starts the trick
	 win = plist.at(leader)->getName();
	 cout<<"  "<<plist.at(leader)->getName()<<" led "<<trump<<endl;
         
      	 //Rest three players
	 index = leader + 1;
         for(int i=0;i<3;i++){
	    //Again, since the player list index is 0 to 3
	    //If it becomes 4, then reset to 0
            if(index == 4)
	       index = 0;
	    //Temporary Card
	    Card next = plist.at(index)->playCard(cardLeft,trump);
	    //Collect card for trick winner
	    chosenCard[cardIndex] = next;
	    cardIndex++;
   	    //If one of rest players can follow the trump card's suit
	    if(next.getSuit() == trump.getSuit()){
	       cout<<"  "<<plist.at(index)->getName()<<" followed suit with "<<next<<endl;
	       if(trump.getRank() < next.getRank()){
		  winner = index;
		  trump = next;
   	       }
	    }
	    //If the player cannot follow the suit of trump card
	    else
	       cout<<"  "<<plist.at(index)->getName()<<" threw off "<<next<<endl;
	    index++;
	 }
 	 //Winner of the trick played is chosen 
	 cout<<"  "<<plist.at(winner)->getName()<<" won the trick and added the following cards:"
             <<endl<<"    ";
  	 //Print what four cards will winner collect
         for(int i=0;i<4;i++){
            cout<<chosenCard[i]<<" ";
	    playerScore[winner] += chosenCard[i].getHeartsValue();
         }
         //Reinitialize the index of card and choose who will play first next
	 cout<<endl;
         cardIndex = 0;
         leader = winner;
      }
      //After one trick is over before starting the next trick game, decrease one card
      cardLeft--;
   }
   //All 13 tricks are over, one round is over 
   //Print out the final scores of each player
   cout<<endl;
   cout<<"At the end of hand "<<ntricks<<", the score is:"<<endl;
   for(int i=0;i<4;i++){
      cout<<"    "<<plist.at(i)->getName()<<"  "<<playerScore[i]<<endl;
   }
   cout<<endl;
}
