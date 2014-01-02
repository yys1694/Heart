#ifndef __TRICK_H__
#define __TRICK_H__

#include "Deck.h"
#include "Player.h"

using namespace std;

class Trick : public Deck {
   public:
      Trick();
      void playing(vector<Player*>& plist, int ntricks, int cardLeft);
};

#endif
