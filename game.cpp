#include "game.h"
#include <iostream>
#include "area.h"

using namespace std;

Game::Game() : player(new Character()), inventory(new Inventory(player)), currentArea(0), wolfEventTriggered(false), witchDefeated(false),  crowEventCompleted(false), crowEventPostAction(false), ghostEventTriggered(false), fiendDefeated(false), bigFiendDefeated(false) {
    //Areas
    areas.push_back(Area("Forest of Falsehoods", "A mysterious forest full of lies and deception."));
    areas[0].items.push_back(Item("Veteran Sword", "Your long-used sword, a trusted companion in countless battles.", 10));
    areas[0].items.push_back(Item("Spell Book", "A mysterious magic book that belonged to your mother.", 15));
    areas.push_back(Area("Lake of Envisage", "A lake so clear, it reflects not just your image, but your soul."));
    areas.push_back(Area("Mountain of Illusions", "A towering peak that plays tricks on your mind."));
    areas.push_back(Area("Emerald Plateau", "A plateau shimmering with an otherworldly green glow."));
    areas[3].items.push_back(Item("Silver Sword", "A sharp, shining precious sword. (+10 damage)", 10));
    areas[3].items.push_back(Item("Enhanced Necklace", "It contains some magic power. (Passive: +1 magic)", 0));
    areas.push_back(Area("The Grand Hall", "A grand hall filled with ancient artifacts and echoes of the past."));
    areas[4].items.push_back(Item("Fruit Nectar", "Delicious juice. As far as you know, it doesn't have any extra functions.", 0));
    areas.push_back(Area("Throne of Ending", "A dark throne room where destinies are decided."));

    //Connections
    areas[0].connections = { {"north", {2, {"You see a steep hill ahead.", "The wind howls as you ascend."}}},
                             {"east", {1, {"You walk through dense trees.", "A small stream crosses your path."}}} };
    areas[1].connections = { {"west", {0, {"The forest seems darker now.", "You feel watched."}}} };
    areas[2].connections = { {"south", {0, {"The mountain path is slippery.", "You hear distant thunder."}}},
                             {"east", {3, {"The ground glows faintly green.", "A mysterious fog surrounds you."}}} };
    areas[3].connections = { {"west", {2, {"You retrace your steps cautiously.", "The fog begins to lift."}}},
                             {"east", {4, {"You see a grand structure ahead.", "The path widens and feels ominous."}}} };
    areas[4].connections = { {"west", {3, {"The grand hall echoes behind you.", "The path feels narrow again."}}},
                             {"east", {5, {"A dark energy fills the air.", "You feel a powerful presence ahead."}}} };
    areas[5].connections = { {"west", {4, {"You sense hesitation as you leave.", "The air feels lighter behind you."}}},
                             {"north", {6, {"You see a throne in the distance.", "The final portal awaits."}}} };
    areas.push_back(Area("End", "You have reached the end of your journey."));
}

Game::~Game() {
    delete player;
    delete inventory;
}



void Game::startGame() {
    cout << "A nameless warrior is involved in an ominous war to protect his hometown." << endl;
    cout << "During this war, a dark sorcerer sends him to a land unknown to mankind, using a forbidden spell." << endl;
    cout << "The warrior's aim is to explore this mysterious land, parry its dangers and find a way out of this dimension." << endl;
    player->showStats();
    explore();
}

void Game::explore() {
    string command;
    while (true) {
        areas[currentArea].describe();
        cout << "Available directions: ";
        for (const auto& connection : areas[currentArea].connections) {
            cout << connection.first << " ";
        }
        cout << "\nEnter a command (or 'quit' to exit): ";
        getline(cin, command);
        if (command == "stats") {
            player->showStats(); //Show player's stats
            continue;
        }
        if (command == "quit") {
            cout << "Thanks for playing!" << endl;
            break;
        }

        if (command == "look") {
            if (!areas[currentArea].items.empty()) {
                cout << "You found the following items:" << endl;
                for (const auto& item : areas[currentArea].items) {
                    cout << "- " << item.name << ": " << item.description << endl;
                }
                areas[currentArea].itemsVisible = true; //Items become visible.
            }
            else if (areas[currentArea].name == "Lake of Envisage" && !areas[currentArea].itemsVisible) {
                cout << "While looking at your reflection, you see your wife and your newborn baby appearing behind you. "
                    << "Tears fill your eyes with worry and sorrow. Then you remember that you need to find a way back to them, one way or another." << endl;

                player->modifyStat("composure", 1); // +1 Composure
                cout << "Your Composure increased by 1.\n";
            }
            else {
                cout << "There is nothing interesting here." << endl;
            }
            continue;
        }

        if (command == "take") {
            if (areas[currentArea].itemsVisible) {
                if (!areas[currentArea].items.empty()) {
                    cout << "You have taken the following items:" << endl;
                    for (const auto& item : areas[currentArea].items) {
                        cout << "- " << item.name << endl;
                        inventory->addItem(item);
                    }
                    areas[currentArea].items.clear();
                }
                else {
                    cout << "There are no items to take here." << endl;
                }
            }
            else {
                cout << "There are no items at your vision." << endl;
            }
            continue;
        }
        if (command == "inventory") {
            inventory->showInventory(); //Show the items in inventory.
            continue;
        }

        if (areas[currentArea].connections.find(command) != areas[currentArea].connections.end()) {
            auto& connection = areas[currentArea].connections[command];
            int& stepCount = stepCounts[command]; //Follow the move count.

            if (stepCount < connection.second.size()) {
                //Trigger the event on current area.
                cout << connection.second[stepCount] << endl;
                stepCount++;
            }
            else {
                //When the area is completed, move to the new area.
                cout << "You have reached a new location." << endl;
                currentArea = connection.first;
                stepCounts.clear(); //Resets counts when moving to new area.
            }
        }
        else {
            cout << "You can't go that way!" << endl;
        }
        if (currentArea == 2 && !areas[currentArea].visited ) { //Mountain of Illusions event
            areas[currentArea].describe();
            string choice;
            cout << "Would you like to eat the pears? (yes or no): ";
            getline(cin, choice);

            if (choice == "yes") {
                cout << "You decided to eat the pear. But as soon as you took a bite, you realized it was poisonous!" << endl;
                cout << "You lost 1 Strength.\n";//Lose strength
                player->modifyStat("strength", -1);
                cout << "The shape of the child started to change. It turned out to be a foul witch!"<<endl;
            }
            else if (choice == "no") {
                cout << "You decided not to eat the pear. The young girl looked at you in wrath and revealed her true form: a foul witch!" << endl;
            }

            cout << "Fury ignited within you as you unsheathed your sword. The battle has begun!" << endl;
            Character* witch = createEnemy();
            battle(witch, true);
            delete(witch);
            cout << "You defeated the witch, and her body dissolved into thin air in an instant." << endl;
            areas[currentArea].visited = true; 
            areas[currentArea].battleCompleted = true;  //This battle is done.
        }

        if (currentArea == 2 && areas[currentArea].battleCompleted && !wolfEventTriggered && command == "east") {
            wolfEventTriggered = true; //Don't repeat the event.

            cout << "You progress in your journey to the pinnacle of the mountain." << endl;
            cout << "At a small distance ahead of you, two wolves fight and attack each other in a lust for death." << endl;
            cout << "Seemingly, they hunted down a gazelle but have a hard time taking their own share." << endl;
            cout << "The living conditions on this mountain are quite tough." << endl;
            cout << "Would you want to break up the battle of the wolves? (yes or no): ";

            string choice;
            getline(cin, choice);

            if (choice == "yes") {
                cout << "You unsheathed your sword and jumped in between them. The wolves feared your sword and ran away from the scene." << endl;
            }
            else if (choice == "no") {
                cout << "You ignored the wolves and kept going your way." << endl;
            }
            else {
                cout << "Invalid choice. The wolves continued their fight as you moved on." << endl;
            }

            cout << "It has been a long and dangerous way, but you, yourself, are a resilient man." << endl;
            cout << "As you approached the pinnacle of the mountain, a subtle green glimmer caught your eye." << endl;
            cout << "Upon reaching the summit, you observed a vast plateau stretching eastward." << endl;
            cout << "The grass on the plateau, the plants, and the trees held such an enthralling shade of green that they were nothing but eye-catchingly vibrant." << endl;
        }

        if (currentArea == 3 && areas[currentArea].visited && !areas[currentArea].crowEventTriggered && command == "east") {
            areas[currentArea].triggerCrowEvent();
            crowEventCompleted = true;
        }
        if (currentArea == 3 && crowEventCompleted && !crowEventPostAction && command == "east") {
            crowEventPostAction = true; //It's ready to trigger the ghost event
            cout << "You feel an eerie silence as you move forward. Something strange lies ahead..."<<endl;
            continue;
        }

        // Hayalet eventini tetikle
        if (currentArea == 3 && crowEventPostAction && !ghostEventTriggered && command == "east") {
            ghostEventTriggered = true; //Trigger the ghost event only once
            cout << "You keep walking towards the tower. As you approached the tower more and more, an uneasy feeling courses through your spine."<<endl;
            cout << "This tower indeed looks like the craft of the devil. Of course, you would not compromise on your determination."<<endl;
            cout << "You need to remember where you belong to, and if possible, save your loved ones."<<endl;
            cout << "A while later, you hear a deafening cry and feel startled. This sound seems to resemble its source: an unnervingly vocal ghost."<<endl <<endl;
            cout << "- SALUTATIONS TO YE, THE DOUGHTY TRAVELLER. SWORDS AND SORCERY HATH EVER PORTRAYED THE ABSOLUTE MIGHT!"<<endl;
            cout << "YETTTTTT THE MIGHTIEST OF ALL IS BUT KNOWLEDGE! FOR THE POWER OF MORE, I WOULDST HAVE SURRENDERED FAR MORE, INDEED, EVERYTHING!"<<endl;
            cout << "BESTOW UPON ME THY KNOWLEDGE, AND HEREBY I SHALL I PLEDGE UNTO THEE ALL THAT LIETH WITHIN MY POSSESSION!"<<endl<<endl;
            cout << "It seems like a trade, what is your answer? (yes or no) " << endl;

            string choice;
            getline(cin, choice);

            if (choice == "yes") {
                cout << "-HAHAHAHAHHAHAH! MY GRATITUDE UNTO THEE, THOU FOOL!\n";
                player->modifyStat("strength", 1);
                player->modifyStat("magic", 1);
                player->modifyStat("ability", 1);
                player->modifyStat("composure", 1);
                player->modifyStat("wisdom", -1);
                cout << "+1 Strength, +1 Magic, +1 Ability, +1 Composure, -1 Wisdom."<<endl;
                cout << "The reverie vanishes into thin air."<<endl;
            }
            else if (choice == "no") {
                cout << "- INDEED, HOW COULD A FOOLISH MORTAL SUCH AS THEE OFFER ME AUGHT OF WISDOM? BE GONE! NAY, LET IT BE WHO I DEPART!"<<endl;
                player->modifyStat("wisdom", 1);
                cout << "+1 Wisdom."<<endl;
                cout << "The reverie vanishes into thin air."<<endl;
            }
            else {
                cout << "The ghost faded away without any response."<<endl;
            }
        }
        if (currentArea == 4 && !areas[currentArea].visited) {
            cout << "There is a long hall ahead of you. The items in the hall seem to be scattered everywhere, as if a brawl had taken place."<<endl;
            cout << "As you proceed through the hall, you become startled by a thing you stepped on accidentaly."<<endl;
            cout << "You realize that the thing you stepped on belongs to a bone of a finger!"<<endl;
            areas[currentArea].visited = true; //Only once event when entering The Grand Hall.
        }
        
        if (currentArea == 4 && command == "east") {
            if (!fiendDefeated) {
                cout << "As you proceed further, a fiend appears in front of you. You unsheathe your sword. The battle has begun!"<<endl;
                Character* fiend = createFiend(); //Create the fiend
                battle(fiend); 
                delete fiend; 
                fiendDefeated = true; //This fiend is defeated.
            }
            else {
                cout << "The path is now clear, and no enemies remain here."<<endl;
            }
        }
        if (currentArea == 4 && fiendDefeated && command == "east" && !bigFiendDefeated) {
            cout << "As you proceed further, an even larger fiend emerges from the shadows. Its sheer size and aura of malice sends shivers down your spine!" << endl;
            cout << "The battle with the Greater Fiend has begun!" << endl;

            Character* bigFiend = createBigFiend(); //Create bigger fiend
            battle(bigFiend);
            delete bigFiend;
            bigFiendDefeated = true; //This fiend is defeated too.
        }
        if (currentArea == 5 && !areas[currentArea].visited) {
            cout << "After this long walk, you reach the throne room. You find a portal behind the throne."<<endl;
            cout << "The place you see through the portal seems familiar. It is your own hometown."<<endl<<endl;
            cout << "With excitement overflowing from your heart, you run toward the portal, but another fiend appears, "<<endl;
            cout << "and this one seems to be the mightiest of all the fiends you have vanquished so far."<<endl<<endl;
            cout << "- As soon as you arrived on these lands, I have been watching you. You have intruded into my castle, "<<endl;
            cout << "massacred soldiers at my command, and penetrated into my throne room."<<endl;
            cout << "- But I must confess, you are a formidable warrior. For this reason, punishing you without a generous "<<endl;
            cout << "offer would be a great shame. Join me. Be my henchman and let us make the whole world feel our might! "<<endl;
            cout << "There is no limit to the power I can bestow upon you! (Yes or No): ";

            string choice;
            getline(cin, choice);

            if (choice == "yes") {
                cout << "- At last, a mortal who can wield their mind. With you by my side, we shall conquer the impossible "<<endl;
                cout << "and achieve feats beyond imagination."<<endl<<endl;
                cout << "The Demonic King casts a spell upon you with words unbeknownst to you. Then, your body begins to "<<endl;
                cout << "decompose, and you become the embodiment of a half-man, half-demon."<<endl;
                cout << "\nYou have reached the end of the game. But of course, it is debatable what kind of an end it is."<<endl;
                cout << "GAME OVER."<<endl;
                break; //End the game
            }
            else if (choice == "no") {
                cout << "- For God sake, surprise me for once! Alright. I will dissect your body into a thousand pieces "<<endl;
                cout << "and make garlic out of all of them!" <<endl;
                cout << "The battle has begun." <<endl<<endl;

                Character* demonicKing = createDemonicKing(); //Create Demonic King
                battle(demonicKing);
                delete demonicKing;

                cout << "\nAfter the Demonic King falls defeated, the light emanating from the portal becomes stronger, " << endl;
                cout << "and you enter through the portal. You have successfully escaped the land that you were imprisoned in." << endl;
                cout << "\033[32mCongratulations, you have completed the game!" << endl;
                break; //Complete the game
            }
            else {
                cout << "Invalid choice. The Demonic King annihilates you in an instant." << endl;
                cout << "GAME OVER.\n";
                break; //End the game
            }
        }
        

    }
}

void Game::battle(Character* enemy, bool isWitchBattle) {
    cout << "Battle begins!\n";
    while (player->currentHealth > 0 && enemy->currentHealth > 0) {
        string command;
        //Player's turn.
        cout << "Your turn! Enter,'Attack' to attack" << endl;
        getline(cin, command);
        if (command == "attack") {
            int playerDamage = player->calculateDamage();
            enemy->takeDamage(playerDamage);
            cout << "You dealt " << playerDamage << " damage to the enemy. Enemy's remaining health: " << enemy->currentHealth << endl;
            if (enemy->currentHealth <= 0) {
                cout << "You defeated the enemy!" <<endl;
                player->replenishHealth();
                if (isWitchBattle) {
                    witchDefeated = true; //Witch is dead
                }
                return;
            }
        }
        else {
            cout << "Invalid command! Please enter 'attack'." << endl;
            continue;
        }

        cout << endl <<"Enemy's turn!" << endl;
        int enemyDamage = enemy->calculateDamage();
        player->takeDamage(enemyDamage);
        cout << "Enemy dealt " << enemyDamage <<    " damage to you. Your remaining health: " << player->currentHealth << endl;

        if (player->currentHealth <= 0) {
            cout << "You have been defeated..." << endl;
            cout << "GAME OVER." << endl;
            break;
        }
    }
}

    Character* Game::createEnemy() {
        Character* witch = new Character();
        witch->strength = 4;
        witch->magic = 2;
        witch->ability = 3;
        witch->composure = 2;
        witch->wisdom = 1;
        witch->currentHealth = 80; 
        return witch;
    }
    Character* Game::createFiend() {
        Character* fiend = new Character();
        fiend->strength = 6; 
        fiend->magic = 3;
        fiend->ability = 4;
        fiend->composure = 2;
        fiend->wisdom = 2;
        fiend->currentHealth = 100; 
        return fiend;
    }
    Character* Game::createBigFiend() {
        Character* bigFiend = new Character();
        bigFiend->strength = 10; 
        bigFiend->magic = 5;
        bigFiend->ability = 7;
        bigFiend->composure = 4;
        bigFiend->wisdom = 3;
        bigFiend->currentHealth = 150; 
        return bigFiend;
    }
    Character* Game::createDemonicKing() {
        Character* demonicKing = new Character();
        demonicKing->strength = 15; 
        demonicKing->magic = 10;
        demonicKing->ability = 12;
        demonicKing->composure = 8;
        demonicKing->wisdom = 7;
        demonicKing->currentHealth = 200; 
        return demonicKing;
    }
