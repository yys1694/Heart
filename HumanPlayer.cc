#include "HumanPlayer.h"

//Constructor
HumanPlayer::HumanPlayer(string name) : Player(name) {}

//Destructor
HumanPlayer::~HumanPlayer() {}

/*****************Part4*****************/
//Get human player's name
string HumanPlayer::getPlayerName(){
   return Player::playername;
}

//Find out if the player has a certain card in the hand
bool HumanPlayer::haveCard(int numCards, Card testCard){
   bool haveThisCard = false;
   
   for(int i=0;i<numCards;i++){
      Card tmp = *at(i);
      if(tmp == testCard){
	 haveThisCard = true;
	 break;
      }
   }
   return haveThisCard;
}   

//lead function, suggested from website
Card HumanPlayer::lead(int numCards, bool first){
   string inputCard;
   Card leadCard;

   //If the player who leads the trick has the 2C
   //Automatical play
   if(first){
      for(int i=0;i<numCards;i++){
	 Card tmp = *at(i);
	 if(tmp.getSuit() == Card::Clubs &&
	    tmp.getRank() == Card::Two){
	    leadCard = tmp;
	    erase(begin()+i);
	    break;
	 }
      }
   }
   //If the human player leads the trick but no 2C in the hand
   else{
      cout<<"Human player "<<HumanPlayer::getPlayerName()<<" has these cards:\n";
      Player::printhand();
      while(1){
         cout<<"What card would you like to play, "<<HumanPlayer::getPlayerName()<<"? ";
         cin>>inputCard;
	 //Check if the card is valid
         if(!(Card::stringIsALegalCard(inputCard)))
	    cout<<inputCard<<" is not a card\n";
	 //Check if the player has the card in the hand
	 else if(!HumanPlayer::haveCard(numCards,Card(inputCard)))
	    cout<<Card(inputCard)<<" is not in your hand\n";
	 //If card is valid and player has the card
	 else{
	    leadCard = Card(inputCard);
	    for(int i=0;i<numCards;i++){
	        Card tmp = *at(i);
	        //Find out the index of that card in the hand
	        if(tmp == leadCard){
		   leadCard = tmp;
	 	   erase(begin()+i);
		   break;
	        }
             } 
             break;
          }
      } 
   }
   return leadCard;
}

//throwOff : when player cannot follow the suit of trump card
//           player is able to choose random suit 
//           "broke hearts alike"
Card HumanPlayer::throwOff(int numCards){
   Card throwCard;
   string inputCard;
   cout<<"Human player "<<HumanPlayer::getPlayerName()<<" has these cards:\n";
   HumanPlayer::printhand();
   //Loop until the player get the valid card
   while(1){
      cout<<"What card would you like to play, "<<HumanPlayer::getPlayerName()<<"? ";
      cin>>inputCard;
      //If the card is valid
      if(!(Card::stringIsALegalCard(inputCard)))
         cout<<inputCard<<" is not a card\n";
      //If the player has that card
      else if(!HumanPlayer::haveCard(numCards,Card(inputCard)))
         cout<<Card(inputCard)<<" is not in your hand\n";
      //If the card is valid and it's in player's hand
      //Find it out from the player's card list and erase it 
      else{
         throwCard = Card(inputCard);
         for(int i=0;i<numCards;i++){
            Card tmp = *at(i);
            if(tmp == throwCard){
               erase(begin()+i);
               break;
            }
         }
         break;
      }
   }
   return throwCard;
}

//followSuit: When a player can follow the suit of the trump card
//            Player needs to choose a proper card to play
Card HumanPlayer::followSuit(int numCards, const Card &trumpCard){
   Card followCard;
   string inputCard;
   cout<<"Human player "<<HumanPlayer::getPlayerName()<<" has these cards:\n";
   HumanPlayer::printhand();
   //Loop until a player gets the right card
   while(1){
      cout<<"What card would you like to play, "<<HumanPlayer::getPlayerName()<<"? ";
      cin>>inputCard;
      //If the card is valid
      if(!(Card::stringIsALegalCard(inputCard)))
         cout<<inputCard<<" is not a card\n";
      //If the player has that card
      else if(!HumanPlayer::haveCard(numCards,Card(inputCard)))
         cout<<Card(inputCard)<<" is not in your hand\n";
      //If that card is in player's hand but not a suit-matching card
      else if(Card(inputCard).getSuit() != trumpCard.getSuit())
	 cout<<"You have at least one "<<Card::SuitName[trumpCard.getSuit()]
	     <<"; you must follow suit!\n";
      //If all test become false then a player chooses a proper card
      //Now find that card from the list and erase it
      else{
         followCard = Card(inputCard);
         for(int i=0;i<numCards;i++){
            Card tmp = *at(i);
            if(tmp == followCard){
               erase(begin()+i);
               break;
            }
         }
         break;
      }
   }
   return followCard;
}
