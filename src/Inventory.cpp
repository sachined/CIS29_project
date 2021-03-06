#include "../include/Inventory.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>
using namespace std;

void Inventory::remove(const Item& obj)
{
    //if there is more than one health kit than it removes the first one that it finds
    auto idx = find(items.begin(), items.end(), obj);
    if(idx != items.end())
        items.erase(idx);
}

void Inventory::remove(const std::string& name)
{
    for(int i = 0; i < items.size(); i++)
    {
        if(items[i].itemName == name)
            items.erase(items.begin() + i);
    }
}

bool Inventory::contains(const Item& obj)
{
    auto idx = find(items.begin(), items.end(), obj);
    if(idx != items.end())
        return true;
    return false;
}

bool Inventory::contains(const std::string& name)
{
    for(int i = 0; i < items.size(); i++)
    {
        if(items[i].itemName == name)
            return true;
    }
    return false;
}

void Inventory::craft(const std::string& itemName)
{
    if(itemName == "Stimpak")
    {
        if (contains("Steel") && contains("Blood Pack"))
        {
            remove("Steel");
            remove("Blood Pack");
            add(Item("Stimpak"));
        }
        else
        {
            std::cout << "You do not have the items to craft a Stimpak.\n";
            system("pause");
        }
    }
    else if(itemName == "DeathClaw Gauntlet")
    {
        if (contains("Leather") && contains("Steel") && contains("Claw"))
        {
            remove("Leather");
            remove("Steel");
            remove("Claw");
            add(Item("DeathClaw Gauntlet"));
        }
        else
        {
            cout << "You do not have the items to craft a Deathclaw Gauntlet.\n";
            system("pause");
        }
    }
    else if(itemName == "Shishkebab")
    {
        if(contains("Steel") && contains("Leather") && contains("GasContainer"))
        {
            remove("Steel");
            remove("Leather");
            remove("GasContainer");
            add(Item("Shishkebab"));
        }
        else
        {
            cout << "You do not have the items to craft a Shishkebab.\n";
            system("pause");
        }
    }
    else if(itemName == "Shortsword")
    {
        Item ShortSword{};//create an item object with stats of a stimpak
        if(contains("Steel") && contains("Leather"))
        {
            remove("Steel");
            remove("Leather");
            add(Item("Shortsword"));
        }
        else
        {
            cout << "You do not have the items to craft a Shortsword.\n";
            system("pause");
        }
    }
    else if(itemName == "Longsword")
    {
        if(contains("Steel") && contains("Leather"))
        {
            remove("Steel");
            remove("Leather");
            add(Item("Longsword"));
        }
        else
        {
            cout << "You do not have the items to craft a Longsword.\n";
            system("pause");
        }
    }
    else if(itemName == "Light Armor")
    {
        cout << "YAASHHSH";
        if(contains("Steel") && contains("Leather")) //the items that are being removed are in the inventory
        {
            remove("Steel");
            remove("Leather");
            add(Item("Light Armor"));
        }
        else
        {
            cout << "You do not have the items to craft Light Armor.\n";
            system("pause");
        }
    }
    else if(itemName == "Heavy Armor")
    {
        if(contains("Steel") && contains("Leather")) //the items that are being removed are in the inventory
        {
            remove("Steel");
            remove("Leather");
            add(Item("Heavy Armor"));
        }
        else
        {
            cout << "You do not have the items to craft Heavy Armor.\n";
            system("pause");
        }
    }
    else if(itemName != "e")
    {
        cout << "Crafting recipe not found.\n";
        system("pause");
    }
}

string Inventory::getCraftingChoice()
{
    system("cls");
    string option;
    cout << "List of items that can be crafted: " <<endl;
    cout <<setw(20)<<left <<"ITEM"<<setw(5) <<"|" << "REAGENTS NEEDED" <<setw(10)<<endl;
    cout << "-----------------------------------------------------------------------------\n";
    cout <<setw(20)<<left <<"Stimpak"<<setw(5) <<"|" << "Blood Pack , Steel" <<endl;
    cout <<setw(20)<< left<<"DeathClaw Gauntlet"<<setw(5) <<"|" << "Leather , Steel , Claw" <<endl;
    cout <<setw(20)<< left<<"ShishKebab"<<setw(5) <<"|" << "Steel , Leather , Gas Container" <<endl;
    cout <<setw(20)<< left<<"Shortsword"<<setw(5) <<"|" << "Steel, Leather" <<endl;
    cout <<setw(20)<< left<<"Longsword"<<setw(5) <<"|" << "Steel , Leather" <<endl;
    cout <<setw(20)<< left<<"Light Armor"<<setw(5) <<"|" << "Leather , Buckles" <<endl;
    cout <<setw(20)<< left<<"Heavy Armor"<<setw(5) <<"|" << "Steel , Buckles" <<endl;

    cout << "\nWhat would you like to craft? (Type e to exit) \n" <<endl;
    cin >> option;

    return option;
}
