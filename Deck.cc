#include "Deck.h"
#include <map>

using namespace std;

//Constructor creates an empty deck
Deck::Deck() {}
      
//Destructor for Deck
Deck::~Deck(){
   Card* tmp;
   for(unsigned int i=0;i<size();i++){
      tmp = at(i);
      delete tmp;
   }
   for(unsigned int i=0;i<size();i++){
      erase(begin()+i);
   }
}
     
//Take an existing (ideally, empty) deck and fill it with the 
//usual suspects of 52 cards by iterating through the elements of
//Card::Rank and Card::Suit
void Deck::generate(){
   for(int s=0;s<4;s++){
      for(int r=0;r<13;r++){
	 push_back(new Card((Card::Rank)r, (Card::Suit)s));
      }
   }
   assert(playingWithAFullDeck());
}
//Check that the deck of cards does indeed contain the usual
//52 suspects; this isn't hard if you know your STL containers
bool Deck::playingWithAFullDeck() const {
   map<Card, int> cardmap;
   pair<map<Card, int>::iterator, bool> result;
   
   for(int i=0;i<52;i++){
      result = cardmap.insert(pair<Card, int>(*at(i),i));
      if(!result.second)
	 return false; 
   }
   return true; 
}
//Take an existing (ideally, empty) deck and read in 52 cards from the
//indicated input stream, making use of operator>>(istream&, Card&).
//Make sure that you are playingWithAFullDeck at the end.
//The ordering should be so that the last card read in will be on the top
//of the deck.
istream& operator>>(istream& in, Deck& deck) {
   Card* tmpcard;
   string strcard;
   int ncard = 0;
   while(in>>strcard && ncard<52){
      tmpcard = new Card(strcard);
      deck.push_back(tmpcard);
      ncard++;
   }
   assert(deck.playingWithAFullDeck());

   return in;
}
