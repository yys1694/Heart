#include <iostream>
#include <algorithm>
#include <vector>
#include "Player.h"
#include "Card.h"

using namespace std;

//Constructor
Player::Player(string name){
   playername = name;
}  

//Destructor
Player::~Player() {}

//To get a player name
string Player::getName() {
   return playername;
}

//To print out the player's hand(cards)
void Player::printhand() {
   cout<<"    ";
   for(unsigned int i=0;i<size();i++){
      cout<<*at(i)<<" ";
   }
   cout<<"\n";
}

//Part 4
//Recommended method from website
//Using Template Method Design Pattern
Card Player::playCard(int numCards, bool gotTwoClubs){
   return lead(numCards, gotTwoClubs);    
}

Card Player::playCard(int numCards, Card trumpCard){
   if(canFollow(numCards, trumpCard))
      return followSuit(numCards, trumpCard);
   else
      return throwOff(numCards);
}

//Find out if any player has 2C card in the hand
bool Player::hasTC(int numCards){
   bool test = false;
   for(int i=0;i<numCards;i++){
      if(*at(i) == Card::TwoOfClubs){
	 test = true;
	 break;
      }
   }
   return test;
}

//Find out if the player can follow the suit of trump card
bool Player::canFollow(int numCards, Card trumpCard){
   bool following = false;
   for(int i=0;i<numCards;i++){
      Card tmp = *at(i);
      if(tmp.getSuit() == trumpCard.getSuit()){
	 following = true;
 	 break;
      }
   }
   return following;
}


