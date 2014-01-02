#ifndef __HUMANPLAYER_H__
#define __HUMANPLAYER_H__

#include <iostream>
#include "Player.h"

using namespace std;

class HumanPlayer : public Player {
   public:
      HumanPlayer(string name);
      virtual ~HumanPlayer();

      //Part 4
      bool haveCard(int numCards, Card testCard);
      Card lead(int numCards, bool first);
      Card throwOff(int numCards);
      Card followSuit(int numCards, const Card &trumpCard);
      string getPlayerName();

};

#endif
