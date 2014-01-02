#include "RandomPlayer.h"

//Constructor
RandomPlayer::RandomPlayer(string name, uint32_t randomSeed):Player(name){
   prng.seed(randomSeed);
}

//Destructor
RandomPlayer::~RandomPlayer() {}

/************ Part 4 **************/

//lead: When a player leads a trick
Card RandomPlayer::lead(int numCards, bool first){
   Card leadCard;
   //If the very first game (having 2C)
   if(first){
      Card twoclubCard = Card("2C");
      for(int i=0;i<numCards;i++){
	 Card tmp = *at(i);
	 if(tmp.getSuit() == twoclubCard.getSuit() &&
	    tmp.getRank() == twoclubCard.getRank()){
	    leadCard = tmp;
	    erase(begin()+i);
	    return leadCard;
	 }
      }
   }
   //or just pick a random card
   int randomIndex = prng(0,numCards-1);
   Card tmp = *at(randomIndex);
   leadCard = tmp;
   erase(begin()+randomIndex);
   return leadCard;
}

//throwOff: A player selects a random card 
//          or nth card where n is a random number
//          from 1 to number of cards left
Card RandomPlayer::throwOff(int numCards){
   Card leadCard;
   int randomIndex = prng(0,numCards-1);
   Card tmp = *at(randomIndex);
   leadCard = tmp;
   erase(begin()+randomIndex);
   return leadCard;
}

//Assumption: There is at least one card which has the same suit
// 	      with the trump card.
//Such assumption is made from Player::playCard
Card RandomPlayer::followSuit(int numCards, const Card &trumpCard){
   int randomIndex;
   Card followCard;
   //Total number of cards which has the same suit as trump card
   int nMatch=0;

   //And count number of suit-matching cards in the player's hand
   for(int i=0;i<numCards;i++){
      Card tmp = *at(i);
      if(tmp.getSuit() == trumpCard.getSuit())
	 nMatch++;
   }

   randomIndex = prng(1,nMatch);
   
   //Now select nth random card
   for(int i=0;i<numCards;i++){
      Card tmp = *at(i);
      if(tmp.getSuit() == trumpCard.getSuit())
	 randomIndex--;
      if(randomIndex == 0){
	 followCard = tmp;
	 erase(begin()+i);
         break;
      }
   }  
   return followCard;
}
      
