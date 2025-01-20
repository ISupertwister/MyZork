#include"area.h"
#include<iostream>
#include"item.h"

using namespace std;

Area::Area(string areaName, string areaDescription)
	: name(areaName), description(areaDescription), visited(false), itemsVisible(false), crowEventPostAction(false), battleCompleted(false) {}

void Area::describe() {
    if (!visited) {
        cout << "You are in " << name << "." <<endl << description << endl;

        if (name == "Forest of Falsehoods") {
            cout << endl<< "You realize that there is something inside the tree hollow "
                "that caught your eye while you were lying unconscious under it.\n"
                "As you look towards the east from where you are located, you see a path extending to an extraordinary lake.\n"
                "To the north, there is a rather tall mountain. "
                "You think that you might find the answers you are looking for ahead of this mountain." <<endl;
        }
        if (name == "Lake of Envisage") {
            cout << "After progressing for a bit, you have reached the lake. "
                << "You have never seen such a lucent lake before. You took a look at your reflection on the lake."<<endl
                << "There are scars left behind from the last war you took part in. You have a physique that could be considered strong."<<endl;
        }
        if (name == "Mountain of Illusions") {
            cout << "You have reached the mountain after a long adventure, and your journey to its pinnacle has begun." << endl;
            cout << "You have heard a melody as you walked along the path. You faced towards the sound and encountered a young girl." <<endl;
            cout << "What could a young girl be searching for in such a desolate and gloomy mountain?" <<endl;
            cout << "- Sir, I must warn you: there is nothing at the top of the mountain or beyond. No one has ever survived this journey. This is how I lost my family." <<endl;
            cout << "- Anyways, rest for a while. This morning I picked up a basket full of pears from a tree nearby. Could you believe it?" <<endl;
            cout << "A pear tree on a mountain like this! Would you want to join me in eating them? (yes or no)"<<endl;
        }
        if (name == "Emerald Plateau") {
            cout << "As you marched down to this plateau, as lustrous as Emerald, a mighty tower on the horizon caught your attention."<<endl;
            cout << "A tower larger and more foreboding than any structure you have ever seen before."<<endl;
            cout << "You proceeded, thinking that getting out of this dimension is through this tower."<<endl;
        }
        if (!items.empty()) {
            cout << "There seems to be something here. Perhaps you should look closer..."<<endl;
        }

        visited = true; 
    }
}
void Area::triggerCrowEvent() {
    if (!crowEventTriggered) {
        cout << "The very plateau you walk upon is so breathtakingly beautiful that it feels almost unreal."<<endl;
        cout << "As you proceed with a thousand thoughts in your head, a crow falls at the tips of your toes."<<endl;
        cout << "The crow is wounded, screaming in a death rattle."<<endl;
        cout << "- Please, help me! I was flying around the tower you see there. Then I got hit before I realized what was going on and found myself on the ground here. If you help me, I will forever be in a debt of gratitude to you. Please... (yes or no): ";

        string choice;
        getline(cin, choice);

        if (choice == "yes") {
            cout << "You picked up the crow in your palms and inspected its wounds. The poor animal is indeed badly wounded."<<endl;
            cout << "You tore a piece of cloth from your apparel and covered the crow's injuries." << endl;
            cout << "As you arrived at the crow's home, you gently laid it in its nest." << endl;
            cout << "- Thank you very much. If you were not there for me at that time, I would have probably died by now." << endl;
            cout << "- Here are a few presents as a token of my gratitude." << endl;

            if (items.empty()) { //If products are already added, done.
                items.push_back(Item("Enhanced Necklace", "It contains some magic power. (+1 magic)", 0));
                items.push_back(Item("Silver Sword", "A sharp, shining precious sword. (+10 damage)", 10));
            }

            //Show the items given to the player.
            for (const auto& item : items) {
                cout << "- " << item.name << ": " << item.description << endl;
            }
            itemsVisible = true;


            cout << "You can take these items using the 'take' command." << endl;
            crowEventTriggered = true; //Crow Event Completed.
            crowEventCompleted = true;
            crowEventPostAction = false;
        }
        else if (choice == "no") {
            cout << "Ignoring the crow, you walked away from the scene. In woe, it seems that the crow needs to accept its inevitable fate." << endl;
        }
        else {
            cout << "Invalid choice. The crow remained there, screaming in pain as you left." << endl;
        }

        crowEventTriggered = true; //the event is completed
    }
}