#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <vector>
#include <iostream>
#include "Deck.h"

using namespace std;

class Player : protected vector<Card*> {
   //Protected member for inheritance classes
   protected:
      string playername; //Player Name

   public:
      
      //For using vector<Card*>
      using vector<Card*>::size;
      using vector<Card*>::begin;
      using vector<Card*>::push_back;
      using vector<Card*>::at;
      using vector<Card*>::erase;
      using vector<Card*>::empty;

      Player(string name);
      virtual ~Player();
      virtual string getName();
      virtual void printhand();

      //Part4
      Card playCard(int numCards, bool gotTwoClubs);
      Card playCard(int numCards, Card trumpCard);
      virtual bool hasTC(int numCards);
      virtual bool canFollow(int numCards, Card trumpCard);
   //Details at {Human,Smart,Random}Player.{h,cc}
   private:
      virtual Card lead(int numCards, bool first)=0;
      virtual Card throwOff(int numCards)=0;
      virtual Card followSuit(int numCards, const Card &trumpCard)=0;

}; 

#endif
