#include <iostream>
#include <string>
#include <cstdlib>
#include "include/Player.h"
#include "include/Map.h"
using namespace std;

void displayHelp()
{
    system("cls");
    cout << "Tile codes: [P] = Player. [M] = Enemy. [I] = Item. [E] = Elevator. \nCommands:\n";
    cout << "[w] north: move north\n";
    cout << "[s] south: move south\n";
    cout << "[a] west: move west\n";
    cout << "[d] east: move east\n";
    cout << "[v] elevator: use an elevator to travel up a floor\n";
    cout << "[p] pick: pick up an item\n";
    cout << "[e] equip: equip an item\n";
    cout << "[u] unequip: unequip an item\n";
    cout << "[f] attack: attack an enemy\n";
    cout << "[q] help: display the list of valid commands\n";
    cout << "[x] quit: quit the game\n";
    system("pause");
}

// A function to strip non-alphabetic characters from the start and end of the string.
// It will also convert all the remaining characters into lowercase.
string clean(const string& s)
{
    string r = "";
    for (int start = 0; start < s.length(); start++)
    {
        if (isalpha(s[start]))
        {
            for (int end = s.length()-1; end >= start; end--)
            {
                if (isalpha(s[end]))
                {
                    r = s.substr(start, end - start + 1);
                    break;
                }
            }
            break;
        }
    }

    for(int i = 0; i < r.size(); i++) {
        r[i] = tolower(r[i]);
    }

    return r;
}

int main()
{
    const bool DEBUG = true;

    // Map generation settings
    int rows = 5, cols = 5, floors = 2;
    int startingX = 0, startingY = 0, startingZ = floors-1;
    double monsterSpawnRate = .10;
    double itemSpawnRate = .25;
    Player pchar(startingX, startingY, startingZ);
    pchar.runCharacterCreation(DEBUG);
    Map gameMap(rows, cols, floors, startingX, startingY, startingZ, monsterSpawnRate, itemSpawnRate);

    string input = "";
    while(input != "quit" && input != "x" && !pchar.wonGame()) {
        gameMap.print();
        Tile currentTile = gameMap.playerTile();
        cout << "Walls: ";
        if(currentTile.checkWall("up")) cout << " north ";
        if(currentTile.checkWall("down")) cout << " south ";
        if(currentTile.checkWall("left")) cout << " west ";
        if(currentTile.checkWall("right")) cout << " east ";

        cout << "\nEnemies in tile: \n";
        gameMap.displayEnemiesInPlayerTile();

        cout << "\nItems in tile: \n";
        gameMap.displayItemsInPlayerTile();

        cout << "\nPlayer inventory: \n";
        pchar.displayInventory();

        cout << "\nItem equipped: \n\t";
        cout << pchar.getEquippedItem() << endl;

        cout << "\nPlease enter a command. (\"help\" or \"q\" for help)\n";
        cin >> input;
        input = clean(input);
        if((input == "up" || input == "north" || input == "w") && !currentTile.checkWall("up"))
        {
            pchar.moveUp();
        }
        else if((input == "down" || input == "south" || input == "s") && !currentTile.checkWall("down"))
        {
            pchar.moveDown();
        }
        else if((input == "left" || input == "west" || input == "a") && !currentTile.checkWall("left"))
        {
            pchar.moveLeft();
        }
        else if((input == "right" || input == "east" || input == "d") && !currentTile.checkWall("right"))
        {
            pchar.moveRight();
        }
        else if((input == "elevator" || input == "v") && currentTile.containsElevator())
        {
            pchar.goUpFloor();
        }
        else if((input == "pick up" || input == "pick" || input == "p") && currentTile.containsItem())
        {
            int itemNumber;
            cout << "Please enter the list number of the item to pick up (0 to cancel). ";
            cin >> itemNumber;
            int idx = itemNumber-1;
            if(idx >= 0 && idx < gameMap.playerTile().getNumItems())
            {
                pchar.addToInventory(gameMap.playerTile().getItem(idx));
                gameMap.playerTile().removeItem(idx);
            }
        }
        else if((input == "equip" || input == "e") && pchar.hasItemsInInventory())
        {
            int itemNumber;
            cout << "Please enter the list number of the item to equip (0 to cancel). ";
            cin >> itemNumber;
            int idx = itemNumber-1;
            if(idx >= 0 && idx < pchar.numItemsInInventory())
            {
                pchar.equip(idx);
            }
        }
        else if((input == "unequip" || input == "u") && pchar.getEquippedItem() != pchar.defaultItem)
        {
            pchar.unequip();
        }
        else if((input == "attack" || input == "fight" || input == "f") && currentTile.containsEnemy() && pchar.getEquippedItem() != pchar.defaultItem)
        {
            int enemyNumber;
            cout << "Please enter the list number of the enemy to attack (0 to cancel). ";
            cin >> enemyNumber;
            int idx = enemyNumber-1;
            if(idx >= 0 && idx < gameMap.playerTile().getNumEnemies())
            {
                pchar.attack(gameMap.playerTile().getEnemy(idx));
            }
        }
        else if(input == "help" || input == "q")
        {
            displayHelp();
        }
        else if(input == "x")
        {
            system("cls");
            cout << "Thanks for playing!";
        }

        gameMap.updatePlayerLoc(pchar.getX(), pchar.getY(), pchar.getZ());

        gameMap.updateEnemyLocs();

        system("cls");
    }

    if(pchar.wonGame())
    {
        cout << "~~~~~~~~ You win! Great job! Thanks for playing. ~~~~~~~~ \nStats: ";
        cout << pchar;
    }

    return 0;
}
