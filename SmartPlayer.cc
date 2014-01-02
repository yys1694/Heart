#include "SmartPlayer.h"

//Constructor
SmartPlayer::SmartPlayer(string name) : Player(name) {}

//Destructor
SmartPlayer::~SmartPlayer() {}

//lead: When a player leads a trick
Card SmartPlayer::lead(int numCards, bool first){
   int returnIndex;
   Card lowestCard;

   //If a player has 2C then the player is leader of trick
   if(first){
      for(int i=0;i<numCards;i++){
	 Card tmp = *at(i);
	 //Find out 2C card
	 if(tmp.getSuit() == Card::Clubs && 
	    tmp.getRank() == Card::Two){
	    lowestCard = tmp;
	    returnIndex = i;
	    break;
	 }
      }
   }
   //If only one card left then..
   else{
      if(numCards == 1){
         lowestCard = *at(0);
         returnIndex = 0;
      }
      //Otherwise, a trick leader with no 2C
      else{
	 lowestCard = *at(0);
	 returnIndex = 0;
	 for(int i=1;i<numCards;i++){
	    Card tmp = *at(i);
	    if(tmp < lowestCard){
	       lowestCard = tmp;
	       returnIndex = i;
	    }
         }
      }
   }
   //erase selected card from the hand
   erase(begin()+returnIndex);
   return lowestCard;
}

//throwOff: When a player has no cards which match the suit with
//          trump card, "Broke hearts alike"
Card SmartPlayer::throwOff(int numCards){
   int returnIndex;
   Card throwCard;
   //Cards with suit of Hearts
   vector<Card> heartCards;

   //Temporary set
   throwCard = *at(0);
   returnIndex = 0;
   //loop to check all cards if necessary
   for(int i=0;i<numCards;i++){
      Card tmp = *at(i);
      //If the player has QueenOfSpades
      if(tmp.getSuit() == Card::Spades &&
	 tmp.getRank() == Card::Queen){
	 //select it and erase it
	 erase(begin()+i);
	 return tmp;
      }
      //Find out any Hearts where exists
      else if(tmp.getSuit() == Card::Hearts)
	 heartCards.push_back(*at(i));
      //highest card which is non-Hearts nor QueenOfSpades
      else if(throwCard < tmp){
	 returnIndex = i;
	 throwCard = tmp;
      }
   }
   //This implies that the player has some Hearts cards
   if(heartCards.size() != 0){
      throwCard = heartCards[0];
      for(unsigned int i=1;i<heartCards.size();i++){
	 if(throwCard.getRank() < heartCards[i].getRank())
	    throwCard = heartCards[i];
      }
      //Now find the selected Hearts card from the hand
      for(int i=0;i<numCards;i++){
	 Card tmp = *at(i);
	 if(tmp == throwCard){
	    returnIndex = i;
	    throwCard = tmp;
         }
      }
   }
   //If the above if test is failed then it means 
   //the player has no QueenOfSpades or Hearts cards
   //then the player select the highest such card
   //which is already chosen;
   erase(begin()+returnIndex);
   return throwCard;
}


//We have an assumption that at least one card from hands must have 
//the same suit as the suit of trump card. 
//And trumpCard cannot be the same card from the player's hand
//Such assumptions are made from Player::playCard()
Card SmartPlayer::followSuit(int numCards, const Card &trumpCard){
   int returnIndex;
   //Cards with same suit as trump card but lower rank
   vector<Card> lowerRank;
   //Cards with same suit as trump card but higher rank
   vector<Card> higherRank;
   Card followCard;

   //Since at least one card from the hand has the same suit 
   //as the trump card and trumpCard != cards from hand
   //At least one vector will be filled with a card
   for(int i=0;i<numCards;i++){
      Card tmp = *at(i);
      if(tmp.getSuit() == trumpCard.getSuit() && 
	 tmp.getRank() < trumpCard.getRank())
	 lowerRank.push_back(*at(i));
      else if(tmp.getSuit() == trumpCard.getSuit() &&
	      tmp.getRank() > trumpCard.getRank())
	 higherRank.push_back(*at(i));
   }
   //All cards from the hand have higher rank than the trump card
   //Condition (b) from explanation of SmartPlayer::followSuit
   if(lowerRank.size() == 0){
      Card tmp = higherRank[0];
      for(unsigned int i=1;i<higherRank.size();i++){
	 if(higherRank[i].getRank() < tmp.getRank())
	    tmp = higherRank[i];
      }
      followCard = tmp;
   }
   //If at least one card from the hand with the same suit as trump card
   //whose rank is less than trump card then select highest rank of such
   //card (Condition a from explanation of SmartPlayer::followSuit)
   else{
      Card tmp = lowerRank[0];
      for(unsigned int i=1;i<lowerRank.size();i++){
	 if(tmp.getRank() < lowerRank[i].getRank())
	    tmp = lowerRank[i];
      }
      followCard = tmp;
   }
   //Now the card is selected, I have to know the index of this card
   //in the hand and emliminate it as it is selected
   for(int i=0;i<numCards;i++){
      Card tmp = *at(i);
      if(tmp == followCard){
	 returnIndex = i;
 	 break;
      }
   }

   erase(begin()+returnIndex);
   return followCard;
}
