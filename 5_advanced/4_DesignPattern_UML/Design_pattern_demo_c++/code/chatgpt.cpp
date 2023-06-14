//
// Created by likun on 5/28/23.
//
#include <iostream>
#include <vector>
using namespace std;

class Packing
{
public:
    virtual string pack() = 0;
};

class Item
{
public:
    virtual string name() = 0;
    virtual Packing* packing() = 0;
    virtual float price() = 0;
};

class Wrapper : public Packing
{
public:
    string pack(){
        return "wrapper";
    }
};

class Bottle : public Packing
{
public:
    string pack(){
        return "bottle";
    }
};

class Burger : public Item
{
public:
    Packing* packing(){
        return new Wrapper();
    }
};

class Cola : public Item{
public:
    Packing* packing() {
        return new Bottle();
    }
};

class VegBurger : public Burger
{
public:
    float price()
    {
        return 25.0;
    }

    string name()
    {
        return "veg_burger";
    }
};

class ChickenBurger : public Burger
{
public:
    float price(){
        return 50.5;
    }

    string name(){
        return "chicken_burger";
    }
};

class CokeCola : public Cola
{
public:
    float price(){
        return 30.0;
    }

    string name(){
        return "coke_cola";
    }
};

class PesiCola : public Cola
{
public:
    float price(){
        return 35.0;
    }

    string name(){
        return "pesi_cola";
    }
};

class Meal
{
private:
    vector<Item> items;

public:
    void addItem(const Item& item){
        items.push_back(&item);
    }

    float getCost(){
        float cost = 0.0;
        for(auto it : items)
            cost += it.price();
        return cost;
    }

    void showItems(){
        for(auto it : items){
            cout << "Item name: " << it.name() << endl
                 << "Pack type: " << it.packing()->pack() << endl
                 << "Price: " << it.price() << endl
                 << "--------------------------" << endl;
        }
        cout << endl;
    }
};

class MealBuilder {
public:
    Meal prepareVegMeal(){
        Meal meal1;
        VegBurger veg1;
        CokeCola cola1;
        meal1.addItem(veg1);
        meal1.addItem(cola1);
        return meal1;
    }

    Meal prepareChickenMeal(){
        Meal meal1;
        ChickenBurger chicken1;
        PesiCola cola1;
        meal1.addItem(chicken1);
        meal1.addItem(cola1);
        return meal1;
    }
};

int main(int argc, char** argv)
{
    MealBuilder mb;
    mb.prepareVegMeal().showItems();
    mb.prepareChickenMeal().showItems();
    return 0;
}
