#include <string>
#include <cassert>
#include <iostream>
#include "Card.h"

using namespace std;

const string Card::RankName = "23456789TJQKA";
const string Card::SuitName = "SDCH";
const int Card::numRanks = RankName.length();
const int Card::numSuits = SuitName.length();
const int Card::numCards = Card::numRanks * Card::numSuits;
const Card Card::TwoOfClubs (Card::Two, Card::Clubs);
const Card Card::QueenOfSpades (Card::Queen, Card::Spades);

// We'll give you this one.
Card::Card() : rank(Ace), suit(Spades) {}

// Now you do the rest.

//Preferred cxr
Card::Card(Rank r, Suit s) : rank(r), suit(s) {}

//Takse a char string of length 2, which better be legal
Card::Card(string sCard){
   //Test if the string has a proper format
   //string with length 2
   //Don't need this part for a6p4
   //assert(sCard.length() == 2);
   //First letter of sCard is rank
   for(int i=0;i<Card::numRanks;i++){
      if(sCard[0] == Card::RankName[i]){
	 Card::rank = (Card::Rank)i;
	 break;
      }
   }
   //Second letter of sCard is suit
   for(int i=0;i<Card::numSuits;i++){
      if(sCard[1] == Card::SuitName[i]){
	 Card::suit = (Card::Suit)i;
	 break;
      }
   }
}

//Destructor; reset to default card
Card::~Card(){
   Card::rank = Ace;
   Card::suit = Spades;
}

//Accessor fcns => Rank
Card::Rank Card::getRank() const{
   return Card::rank;
}

//Accessor fcns => Suit
Card::Suit Card::getSuit() const{
   return Card::suit;
}

//Accessor fcns => Score
int Card::getHeartsValue() const{
   if(Card::suit == Hearts) return 1;
   else if((Card::suit == Spades) && (Card::rank == Queen)) return 13;
   else return 0;
}

//Static utility function to check if a two char string 
//represents a legal card value
bool Card::stringIsALegalCard(string s){
   //Test if length of string s is 2 or not
   
   //No need for a6p4
   //assert(s.length() == 2);

   int test1 = 0, test2 = 0;

   //Test1: if the first letter of s is proper rank
   for(int i=0;i<Card::numRanks;i++){
      if(s[0] == Card::RankName[i]){
	 test1 = 1;
	 break;
      }
   }
   //Test2: if the second letter of s is proper suit
   for(int i=0;i<Card::numSuits;i++){
      if(s[1] == Card::SuitName[i]){
	 test2 = 1;
	 break;
      }
   }
   //If both tests pass
   //This test needs to be modified
   if((test1+test2)==2 && s.length() == 2)
      return true;
   //To be a legal card, must pass both tests
   else
      return false;
}

//Overloaded operations
//c1 = c2 overloading
bool operator==(const Card& c1, const Card& c2){
   if((c1.getRank() == c2.getRank()) && (c1.getSuit() == c2.getSuit()))
      return true;
   else
      return false;
}

//c1 < c2 overloading
bool operator<(const Card& c1, const Card& c2){
   //we say c1<c2 if c1's rank is less than c2's or they have the same rank, but 
   //c1's suit is less than c2's. (from website)
   if((c1.getRank() < c2.getRank()) ||
      ((c1.getRank() == c2.getRank()) && (c1.getSuit() < c2.getSuit())))
      return true;
   else
      return false;
}

//IO overloading; cout overloading for print out a card
ostream& operator<<(ostream &out, const Card &c){
   char rank;
   char suit;
   //Rank of a card
   for(int i=0;i<Card::numRanks;i++){
      if(c.getRank() == (Card::Rank)i){
	 rank = Card::RankName[i];
	 break;
      }
   }
   //Suit of a card
   for(int i=0;i<Card::numSuits;i++){
      if(c.getSuit() == (Card::Suit)i){
	 suit = Card::SuitName[i];
	 break;
      }
   }
   out<<rank<<suit;
   return out;
}

//IO overloading; cin overloading for read in a card
istream& operator>>(istream& in, Card& c){
   string strcard;
   in>>strcard;
   //Before string to card, make sure that 
   //string is in a proper format of card
   assert(Card::stringIsALegalCard(strcard));

   c = Card::Card(strcard);
   return in;
}

