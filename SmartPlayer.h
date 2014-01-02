#ifndef __SMARTPLAYER_H__
#define __SMARTPLAYER_H__

#include <iostream>
#include "Player.h"

using namespace std;

class SmartPlayer : public Player {
   public:
      SmartPlayer(string name);
      virtual ~SmartPlayer();

      //Part 4
      Card lead(int numCards, bool first);
      Card throwOff(int numCards);
      Card followSuit(int numCards, const Card &trumpCard);
};

#endif
