#include "units.h"
#include "cards.h"

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <random>
#include <algorithm>

#include <vector>

Game::Game(int n_player)
{
  //set number of roles
  {
      n_sheriff = 1;
      n_renegade = 1;

      if (n_player == 5)
      {
          n_vice = 1;
          n_outlaw = 2;
      }
      else if (n_player == 6)
      {
          n_vice = 1;
          n_outlaw = 3;
      }
      else if (n_player == 7)
      {
          n_vice = 2;
          n_outlaw = 3;
      }
      else if (n_player == 8)
      {
          n_vice = 2;
          n_outlaw = 3;
          n_renegade = 2;
      }
  }
  max_range = n_player / 2;
  //make character instances
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> dis(Game::CharacterCode(0), Game::CharacterCode(15));
  std::vector<int> usedchrcode(n_player, 100);
  for (int i = 0; i < n_player; i++)
  {
      int code;
      std::vector<int>::iterator it;
      do
      {
          code = dis(gen);
          it = std::find(usedchrcode.begin(), usedchrcode.end(), code);
      } while (it != usedchrcode.end());

      switch (code)
      {
      case Game::WillytheKid:
          player_table.push_back(WillytheKid::WillytheKid(this));
          break;
      case Game::CalamityJanet:
          player_table.push_back(CalamityJanet::CalamityJanet(this));
          break;
      case Game::KitCalrson:
          player_table.push_back(KitCalrson::KitCalrson(this));
          break;
      case Game::BartCassidy:
          player_table.push_back(BartCassidy::BartCassidy(this));
          break;
      case Game::SidKetchum:
          player_table.push_back(SidKetchum::SidKetchum(this));
          break;
      case Game::LuckyDuke:
          player_table.push_back(LuckyDuke::LuckyDuke(this));
          break;
      case Game::Jourdonais:
          player_table.push_back(Jourdonais::Jourdonais(this));
          break;
      case Game::BlackJack:
          player_table.push_back(BlackJack::BlackJack(this));
          break;
      case Game::VultureSam:
          player_table.push_back(VultureSam::VultureSam(this));
          break;
      case Game::JesseJones:
          player_table.push_back(JesseJones::JesseJones(this));
          break;
      case Game::SuzyLafayette:
          player_table.push_back(SuzyLafayette::SuzyLafayette(this));
          break;
      case Game::PedroRamirez:
          player_table.push_back(PedroRamirez::PedroRamirez(this));
          break;
      case Game::SlabtheKiller:
          player_table.push_back(SlabtheKiller::SlabtheKiller(this));
          break;
      case Game::RoseDoolan:
          player_table.push_back(RoseDoolan::RoseDoolan(this));
          break;
      case Game::PaulRegret:
          player_table.push_back(PaulRegret::PaulRegret(this));
          break;
      case Game::ElGringo:
          player_table.push_back(ElGringo::ElGringo(this));
          break;
      default:
          break;
      }
        
  }
  
  //set player role
  {
      srand((static_cast<unsigned int>(time(NULL))));
      int* shuffle = new int[n_player];
      for (int i = 0; i < n_player; i++)
      {
          shuffle[i] = i;
      }
      for (int i = 0; i < 50; i++)
      {
          int x = rand() % n_player;
          int y = rand() % n_player;
          int temp = shuffle[x];
          shuffle[x] = shuffle[y];
          shuffle[y] = temp;
      }
      int i = 0;
      now_playing = shuffle[i];
      player_table[shuffle[i]].setRole(Game::Sheriff);
      player_table[shuffle[i]].MaxLife(+1);
      i++;
      for (int count = 0; count < n_vice; count++)
      {
          player_table[shuffle[i]].setRole(Game::Vice);
          i++;
      }
      for (int count = 0; count < n_outlaw; count++)
      {
          player_table[shuffle[i]].setRole(Game::Outlaw);
          i++;
      }
      for (int count = 0; count < n_renegade; count++)
      {
          player_table[shuffle[i]].setRole(Game::Renegade);
          i++;
      }
  }
  //players get cards
  for (int i = 0; i < n_player; i++)
  {
      for (int j = 0; j < player_table[i].rtnLife(); j++)
      {
          player_table[i].draw();
      }
  }
}
void Game::play()
{
    while (!isEnd())
    {
        //phase 0
        if (player_table[now_playing].rtnfield().isJail())
        {
            int test = player_table[now_playing].cardOpen();
            if (deck.Cardlist[test]._Trump() != Trumps::Heart)
            {
                moveCard(player_table[now_playing].rtnfield(), grave, "jail");
                player_table[now_playing].turnEnd();
                continue;
            }
            else
            {
                moveCard(player_table[now_playing].rtnfield(), grave, "jail");
            }
        }
        if (player_table[now_playing].rtnfield().isDynamite())
        {
            int test = player_table[now_playing].cardOpen();
            if (deck.Cardlist[test]._Trump() == Trumps::Spade&& deck.Cardlist[test]._Number()>=0&& deck.Cardlist[test]._Number()<=7)
            {
                moveCard(player_table[now_playing].rtnfield(), grave, "dynamite");
                player_table[now_playing].setLife(-3);
            }
            else
            {
                int next = now_playing + 1;
                if (next >= n_player)
                    next = 0;
                moveCard(player_table[next].rtnfield(), player_table[now_playing].rtnfield(),"dynamite");
            }
        }

        //phase1
        player_table[now_playing].draw();

        //phase2
        player_table[now_playing].usingCard();
        //phase 3
        player_table[now_playing].turnEnd();
    }

}
void Game::pop_player(Player& dead)
{
    auto it_dead = find(player_table.begin(), player_table.end(), dead);
    for (auto i = (*it_dead).rtnCoH().begin(); i != (*it_dead).rtnCoH().end(); i++)
    {
        moveCard(it_dead->rtnCoH(), grave, *i);
    }
    for (auto i = (*it_dead).rtnfield().begin(); i != (*it_dead).rtnfield().end(); i++)
    {
        moveCard(it_dead->rtnfield(), grave, *i);
    }


    player_table.erase(it_dead);
    n_player--;
}
bool Game::isEnd()
{
    if(n_sheriff==0)
    {
        if (n_vice == 0 )
        {
            ending_code = Role::Renegade;
            return true;
        }
        ending_code = Role::Outlaw;
        return true;
    }
    if (n_outlaw == 0)
    {
        if (n_renegade == 0)
        {
            ending_code = Role::Sheriff;
            return true;
        }
    }
    return false;
}
vector<Player>& Game::rtnPlayers()
{
    return player_table;
}
vector<int>& Game::rtnGrave()
{
    return grave;
}
int Game::rtnNplayer()
{
    return n_player;
}

Player::Player(Game* g)
{
    range = 1;
    maxlife = 4;
    life = 4;
    bangcount = 1;
    game = g;
    field = Field(this);
}
Player::~Player(){}
bool Player::operator==(Player& p)
{
    if (this->name == p.name)
        return true;
    else
        return false;
}
ostream& operator<<(ostream& os, Player& player)
{
    os << player.name;
    return os;
}
void Player::setRole(int rl)
{
    role = rl;
}
void Player::MaxLife(int plus)
{
    this->maxlife += plus;
}
void Player::setLife(int value)
{
    life += value;
    if (life == 0)
    {
        if (haveCard("beer"))
            life++;
        else
            game->pop_player(*this);
    }
}
int Player::rtnLife()
{
    return this->life;
}
int Player::cardOpen()
{
    int index = game->deck.rtnTopCard();
    game->deck.moveTop();
    return index;
}
void Player::draw()
{
    cards_on_hand.push_back(game->deck.rtnTopCard());
    game->deck.moveTop();
}
void Player::usingCard()
{
    do
    {
        cout << "Choose card to use or press 'q' to end turn.\n";
        auto itbegin = this->rtnCoH().begin();
        for (auto it = itbegin; it != this->rtnCoH().end(); it++)
        {
            cout << it - itbegin << " : " << game->deck.Cardlist[*it]._Name() << endl;
        }
        int code;
        cin >> code;
        cin.get();
        if (code == 'q')
            break;
        else
        {
            bool discard=game->deck.Cardlist[*(itbegin + code)].use();
            if (discard)
            {
                moveCard(this->rtnCoH(), game->rtnGrave(), *(itbegin + code));
            }
        }

    } while (true);
}
void Player::turnEnd()
{
    if (this->rtnCoH().size() > this->rtnLife())
    {
        while(this->rtnCoH().size() != this->rtnLife())
        cout << "choose card to discard\n";
        auto itbegin = this->rtnCoH().begin();
        for (auto it = itbegin; it != this->rtnCoH().end(); it++)
        {
            cout << it - itbegin << " : " << game->deck.Cardlist[*it]._Name() << endl;
        }
        int code;
        cin >> code;
        cin.get();
        moveCard(this->rtnCoH(), game->rtnGrave(), *(itbegin + code));
    }
    else
    {
        game->now_playing++;
        if (game->now_playing >= game->rtnNplayer())
            game->now_playing = 0;
    }
}
bool Player::haveCard(string name)
{
    auto itbegin = this->rtnCoH().begin();
    for (auto it = itbegin; it != this->rtnCoH().end(); it++)
    {
        if (game->deck.Cardlist[*it]._Name() == name)
            return true;
    }
    return false;
}

WillytheKid::WillytheKid(Game* g) :Player(g)
{

}

Card::Card(string n,char num, int t, Game* g)
{
    name = n;
    number = num;
    trump = t;
    game = g;
}
bool Card::operator==(Card& card)
{
    if (this->name == card._Name())
        return true;
    else
        return false;
}
bool operator==(Card& card, string name)
{
    if (card._Name() == name)
        return true;
    else
        return false;
}
string Card::_Name()
{
    return name;
}
int Card::_Trump()
{
    return trump;
}
int Card::_Index()
{
    return index;
}
Deck::Deck()
{
    Cardlist = new Card[80];
    int i = 0;
    for (int j=0; j < 3 ; i++,j++)
    {
        Cardlist[i] = bang("bang",j+10,Trumps::Heart);
    }
    for (int j=0; j < 13; i++, j++)
    {
        Cardlist[i] = bang("bang", j, Trumps::Diamond);
    }
    for (int j=0; j < 8; i++, j++)
    {
        Cardlist[i] = bang("bang", j, Trumps::Clover);
    }
    Cardlist[i] = bang("bang", 12, Trumps::Spade);

    for (int j = 0; j < 7; i++, j++)
    {
        Cardlist[i] = missed("missed", j + 2, Trumps::Spade);
    }
    for (int j = 0; j < 5; i++, j++)
    {
        Cardlist[i] = missed("missed", j + 10, Trumps::Clover);
    }

    for (int j = 0; j < 6; i++, j++)
    {
        Cardlist[i] = beer("beer", j + 6, Trumps::Heart);
    }

    for (int j = 0; j < 4; i++, j++)
    {
        Cardlist[i] = panic("panic", j + 11, Trumps::Heart);
    }
    for (int j = 0; j < 1; i++, j++)
    {
        Cardlist[i] = panic("panic", j + 8, Trumps::Diamond);
    }

    for (int j = 0; j < 4; i++, j++)
    {
        Cardlist[i] = catbalou("catbalou", j + 9, Trumps::Diamond);
    }

    for (int j = 0; j < 2; i++, j++)
    {
        Cardlist[i] = stagecoach("stagecoach", 9, Trumps::Spade);
    }

    for (int j = 0; j < 1; i++, j++)
    {
        Cardlist[i] = wellspargo("wellspargo", j + 3, Trumps::Heart);
    }

    for (int j = 0; j < 1; i++, j++)
    {
        Cardlist[i] = gatling("gatling", j + 10, Trumps::Heart);
    }

    for (int j = 0; j < 1; i++, j++)
    {
        Cardlist[i] = battle("battle", 12, Trumps::Diamond);
    }
    for (int j = 0; j < 1; i++, j++)
    {
        Cardlist[i] = battle("battle", 11, Trumps::Spade);
    }
    for (int j = 0; j < 1; i++, j++)
    {
        Cardlist[i] = battle("battle", 18, Trumps::Clover);
    }

    for (int j = 0; j < 2; i++, j++)
    {
        Cardlist[i] = indian("indian", j+13, Trumps::Diamond);
    }

    for (int j = 0; j < 1; i++, j++)
    {
        Cardlist[i] = store("store", 9, Trumps::Clover);
    }
    for (int j = 0; j < 1; i++, j++)
    {
        Cardlist[i] = store("store", 12, Trumps::Spade);
    }

    for (int j = 0; j < 1; i++, j++)
    {
        Cardlist[i] = salon("salon", 5, Trumps::Heart);
    }

    for (int j = 0; j < 2; i++, j++)
    {
        Cardlist[i] = jail("jail", j+10, Trumps::Spade);
    }
    for (int j = 0; j < 1; i++, j++)
    {
        Cardlist[i] = jail("jail", 4, Trumps::Heart);
    }

    for (int j = 0; j < 1; i++, j++)
    {
        Cardlist[i] = dynamite("dynamite", 2, Trumps::Heart);
    }

    for (int j = 0; j < 2; i++, j++)
    {
        Cardlist[i] = barrel("barrel", j+12, Trumps::Spade);
    }

    for (int j = 0; j < 1; i++, j++)
    {
        Cardlist[i] = scope("scope", 14, Trumps::Spade);
    }

    for (int j = 0; j < 2; i++, j++)
    {
        Cardlist[i] = mustang("mustang", j+8, Trumps::Heart);
    }



    //make shuffled index
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0, 80);
    std::vector<int> shuffledIndex(80);
    int i = 0;
    int count=0;
    while (true)
    {
        int index = dis(gen);
        auto it = std::find(shuffledIndex.begin(), shuffledIndex.end(), index);
        if (it != shuffledIndex.end())
        {
            shuffledIndex[i] = index;
            i++;
            if (i == 80)
                break;
        }
        else
            continue;
    }
    top = 0;
}

int Deck::rtnTopCard()
{
    return shuffledIndex[top];
}

void Deck::moveTop()
{
    this->top++;
    if (this->top > 80)
    {
        this->top = 0;
    }
}

Field::Field(Player* p)
{
    owner = p;
}
bool Field::isJail()
{
    auto it = find(fieldcards.begin(), fieldcards.end(), "jail");
    if (it != fieldcards.end())
    {
        return true;
    }
    return false;
}

void moveCard(vector<int>& cards1, vector<int>& cards2, string card)
{
    auto it = find(cards1.begin(), cards1.end(), card);
    cards2.push_back(*it);
    cards1.erase(it);
}
void moveCard(vector<int>& cards1, vector<int>& cards2, int index)
{
    auto it = find(cards1.begin(), cards1.end(), index);
    cards2.push_back(*it);
    cards1.erase(it);
}

