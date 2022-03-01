#ifndef CARDS_H_
#define CARDS_H_

#include "units.h"
//class Card
//{
//private:
//    string name;
//    int number;
//    int trump;
//    int index;
//public:
//    Card();
//    Card(string, int, int);
//    ~Card();
//    bool operator==(Card&);
//    friend bool operator==(Card&, string);
//    string _Name();
//    int _Number();
//    int _Trump();
//    int _Index();
//    virtual bool use();
//};

class bang : public Card
{
public:
    bang(string name, int number, int trump, Game* game) :Card(name, number, trump, game) {};
    ~bang();
    virtual bool use();
};

class missed : public Card
{
public:
    missed(string name, int number, int trump, Game* game) :Card(name, number, trump, game) {};
    ~missed();
};

class beer : public Card
{
public:
    beer(string name, int number, int trump, Game* game) :Card(name, number, trump, game) {};
    ~beer();
};

class panic : public Card
{
public:
    panic(string name, int number, int trump, Game* game) :Card(name, number, trump, game) {};
    ~panic();
};

class catbalou : public Card
{
public:
    catbalou(string name, int number, int trump, Game* game) :Card(name, number, trump, game) {};
    ~catbalou();
};

class stagecoach : public Card
{
public:
    stagecoach(string name, int number, int trump, Game* game) :Card(name, number, trump, game) {};
    ~stagecoach();
};

class wellspargo : public Card
{
public:
    wellspargo(string name, int number, int trump, Game* game) :Card(name, number, trump, game) {};
    ~wellspargo();
};

class gatling : public Card
{
public:
    gatling(string name, int number, int trump, Game* game) :Card(name, number, trump, game) {};
    ~gatling();
};

class battle : public Card
{
public:
    battle(string name, int number, int trump, Game* game) :Card(name, number, trump, game) {};
    ~battle();
};

class indian : public Card
{
public:
    indian(string name, int number, int trump, Game* game) :Card(name, number, trump, game) {};
    ~indian();
};

class store : public Card
{
public:
    store(string name, int number, int trump, Game* game) :Card(name, number, trump, game) {};
    ~store();
};

class salon : public Card
{
public:
    salon(string name, int number, int trump, Game* game) :Card(name, number, trump, game) {};
    ~salon();
};

class jail : public Card
{
public:
    jail(string name, int number, int trump, Game* game) :Card(name, number, trump, game) {};
    ~jail();
};

class dynamite : public Card
{
public:
    dynamite(string name, int number, int trump, Game* game) :Card(name, number, trump, game) {};
    ~dynamite();
};

class barrel : public Card
{
public:
    barrel(string name, int number, int trump, Game* game) :Card(name, number, trump, game) {};
    ~barrel();
};

class scope : public Card
{
public:
    scope(string name, int number, int trump, Game* game) :Card(name, number, trump, game) {};
    ~scope();
};

class mustang : public Card
{
public:
    mustang(string name, int number, int trump, Game* game) :Card(name, number, trump, game) {};
    ~mustang();
};


#endif
