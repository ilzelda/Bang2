#ifndef UNITS_H_
#define UNITS_H_

#include <string>
#include <map>
#include <vector>

using namespace std;

class Player;

class Game
{
private:
    enum Role { Sheriff, Vice, Outlaw, Renegade };
    enum CharacterCode
    {
        WillytheKid,   //0
        CalamityJanet, //1
        KitCalrson, //2
        BartCassidy, //3
        SidKetchum, //4
        LuckyDuke, //5
        Jourdonais, //6
        BlackJack, //7
        VultureSam, //8
        JesseJones, //9
        SuzyLafayette, //10
        PedroRamirez, //11
        SlabtheKiller, //12
        RoseDoolan, //13
        PaulRegret, //14
        ElGringo //15
    };
  
    int n_player;
    int n_sheriff;
    int n_vice;
    int n_outlaw;
    int n_renegade;
    int max_range;

    vector<Player> player_table;
    vector<int> grave;

    int ending_code;

public:
    Game(int);
    ~Game();
    Deck deck;
    int now_playing;
    void play();
    void pop_player(Player&);
    bool isEnd();
    //void end(int);
    vector<Player>& rtnPlayers();
    vector<int>& rtnGrave();
    int rtnNplayer();
};

class Player
{
private:
    string name;
    int role;
    int range;
    int maxlife;
    int life;
    int phase;
    vector<int> cards_on_hand;
    Field field;
    Game* game;

public:
    Player();
    Player(Game*);
    ~Player();
    int bangcount;

    bool operator==(Player&);
    friend ostream& operator<<(ostream&, Player&);
    void setRole(int);
    void MaxLife(int);
    void setLife(int);
    int rtnLife();
    virtual int cardOpen();
    virtual void draw();
    virtual void usingCard();
    virtual void turnEnd();
    bool haveCard(string);
    vector<int>& rtnCoH() { return cards_on_hand; };
    Field& rtnfield() { return field; };
};

class WillytheKid: public Player
{
public:
    WillytheKid();
    WillytheKid(Game*);
    ~WillytheKid();
    void usingCard();
};


enum Trumps {Heart, Diamond, Spade, Clover};

class Card
{
private:
    string name;
    int number;
    int trump;
    int index;
public:
    Game* game;
    Card();
    Card(string,int,int, Game*);
    ~Card();
    bool operator==(Card&);
    friend bool operator==(Card&, string);
    string _Name();
    int _Number();
    int _Trump();
    int _Index();
    virtual bool use();
};

class Deck :public Card
{
public:
    Deck();
    Card* Cardlist;
    vector<int> shuffledIndex;
    int top;
    int rtnTopCard();
    void moveTop();
};
class Gun : public Card
{
   private:    int range;public:
    Gun();
};


class Field :public Card
{
    int gun;
public:
    Player* owner;
    vector<int> fieldcards;
    Field();
    Field(Player*);
    bool isJail();
    bool isDynamite();
};

void moveCard(vector<int>&, vector<int>&, string);
void moveCard(vector<int>&, vector<int>&, int);

#endif