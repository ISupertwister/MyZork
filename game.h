#ifndef game_h
#define game_h

#include "character.h"
#include "inventory.h"
#include "area.h"
#include <vector>
#include <map>
#include <string>

class Game {
private:
    Character* player;
    Character* createEnemy();
    Character* createFiend();
    Character* createBigFiend();
    Character* createDemonicKing();
    Inventory* inventory;
    vector<Area> areas;
    int currentArea;
    map<string, int> stepCounts; //Order of events for each direction.
    bool wolfEventTriggered;
    bool witchDefeated;
    bool ghostEventTriggered; 
    bool crowEventCompleted;//Crow event is a only one time event.
    bool crowEventPostAction;//after crow event,it is necessary to start ghost event.
    bool fiendDefeated;
    bool bigFiendDefeated;

    void battle(Character* enemy, bool isWitchBattle = false);



public:
    Game();
    ~Game();

    void startGame();
    void explore();
};

#endif
