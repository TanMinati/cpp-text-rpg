#include<iostream>
#include<string>
#include<string_view>
#include "random.h"

// Base class for all creatures in the game
class Creature{
protected:
    std::string m_name{};
    char m_symbol{};
    int m_health{};
    int m_damage{};
    int m_gold{};
public:
    // Constructor to initialize creature attributes
    Creature(std::string_view name,char symbol,int health,int damage,int gold)
        : m_name{name}
        , m_symbol{symbol}
        , m_health{health}
        , m_damage{damage}
        , m_gold{gold}
    {
    }
    const std::string getName() const {return m_name;}
    char getSymbol() const {return m_symbol;}
    int getHealth() const {return m_health;}
    int getDamage() const {return m_damage;}
    int getGold() const {return m_gold;}
    // Reduce health by given amount
    void reduceHealth(int health){
        m_health-=health;
    }
    // Check if creature is dead
    bool isDead() const{
        return m_health<=0;
    }
    // Add gold to creature's total
    void addGold(int gold){
        m_gold+=gold;
    }
};

// Player class derived from Creature
class Player : public Creature{
private:
    int m_level{1};
public:
    Player(std::string_view name)
        : Creature(name,'@',10,1,0)
    {
    }
    // Increase player level and damage
    void levelUp(){
        m_level++;
        m_damage++;
    }
    int getLevel() const {return m_level;}
    // Check if player has reached victory condition
    bool hasWon() const{
        return m_level>=20;
    }
};

// Monster class derived from Creature
class Monster : public Creature{
public:
    enum Type{
        dragon,
        orc,
        slimes,
        max_types,
    };
private:
    // Static array containing monster data
    static inline Creature monsterData[]{
        {"dragon",'D',20,4,100},
        {"orc",'o',4,2,25},
        {"slime",'s',1,1,10}
    };
public:
    Monster(Type type) : Creature(monsterData[type]) {};
    // Generate a random monster from available types
    static Monster getRandomMonster(){
        return Monster(static_cast<Type>(Random::get(0,max_types-1)));
    }
};

// Player attacks monster dealing damage
void attackMonster(Player& player,Monster& monster){
    monster.reduceHealth(player.getDamage());
    std::cout<<"You hit the "<<monster.getName()<<" for "<<player.getDamage()<<" damage."<<std::endl;
    if(monster.isDead()){
        player.levelUp();
    }
}

// Monster attacks player dealing damage
void attackPlayer(Player& player,Monster& monster){
    player.reduceHealth(monster.getDamage());
    std::cout<<"The "<<monster.getName()<<" hit you for "<<monster.getDamage()<<" damage."<<std::endl;
}

// Battle loop between player and monster
void fightMonster(Player& player,Monster& monster){
    std::cout<<"You have encountered a "<<monster.getName()<<" ("<<monster.getSymbol()<<")."<<std::endl;
    while(true){
        std::cout<<"(R)un or (F)ight :"<<std::endl;
        char input;
        std::cin>>input;
        if(input=='F'){
            attackMonster(player,monster);
            if(monster.isDead()) return;
            attackPlayer(player,monster);
            if(player.isDead()) return;
        }else{
            // Attempt to flee with 50% success rate
            int x=Random::get(0,1);
            if(x==0){
                std::cout<<"You failed to flee."<<std::endl;
                attackPlayer(player,monster);
                if(player.isDead()) return;
            }else{
                std::cout<<"You successfully fled."<<std::endl;
                return;
            }
        }
    }
}

int main()
{
    // Initialize player with user input
    std::string playerName;
    std::cout<<"Enter your name: ";
    std::cin>>playerName;
    Player player(playerName);
    std::cout<<"Welcome,"<<playerName<<std::endl;
    std::cout<<"You have 10 health and are carrying 0 gold."<<std::endl;
    
    // Main game loop
    while(true){
        // Check if player has won
        if(player.hasWon()){
            std::cout<<"Congrats! You won the game and you have "<<player.getGold()<<"."<<std::endl;
            break;
        }
        // Encounter a random monster
        Monster monster=Monster::getRandomMonster();
        fightMonster(player,monster);
        
        // Handle combat results
        if(monster.isDead()){
            std::cout<<"You killed the "<<monster.getName()<<"."<<std::endl;
            std::cout<<"You are now level "<<player.getLevel()<<"."<<std::endl;
            std::cout<<"You found "<<monster.getGold()<<" gold."<<std::endl;
            player.addGold(monster.getGold());
        }else if(player.isDead()){
            std::cout<<"You died at level "<<player.getLevel()<<" and with "<<player.getGold()<<" gold."<<std::endl;
            std::cout<<"Too bad you can't take it with you!"<<std::endl;
            break;
        }
    }
	return 0;
}