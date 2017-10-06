#ifndef CLASS_H
#define CLASS_H

typedef struct 
{
	char name[20];
	/* 0 1d4, 1 1d6, 2 1d8, 3 1d12 */
	int dmgDie;
	int critValue;
	int range;
	int goldValue;
	/* 0 for normal, 1 for precision */
	int wepType;
	int lethalFlag;
}Weapon;

typedef struct 
{
	char name[20];
	int armourClassMod;
	/* 0 = none, 1 = light, 2 = medium, 3 = heavy */
	int type;
}Armour;

typedef struct
{
	char name[20];
	int itemID; /* may get rid of this??? not sure how to design this */
}Item;

typedef struct
{
	int strength;
	int constitution;
	int dexterity;
	int wisdom;
	int intelligence;
	int charisma;
}Abilities;

typedef struct
{
	int oLocationX;
	int oLocationY;
	int dLocationX;
	int dLocationY;
	int dungeonFlag;
}Location;

typedef struct
{
	char name[20];
	int hitDie;
	int armourClass;
	int genderFlag;
	int lvl;
	int exp;
	/* 0 = America, 1 = England, 2 = Germany, 3 = Russia, 4 = China */
	int nationFlag;
	int classFlag;
	int totalHealth;
	int currentHealth;
	int currentME;
	int totalME;
	int currentFood;
	int totalFood;
	Abilities abil;
	Armour arm;
	Weapon wep;
	Item inventory[16];
	Location spot;
}Class;

Armour initArmour();
Weapon initWeapon();
void displayClassButtons();
Class createCharacter();
Class chooseClass(Class);
void introStory();
void displayNationalityButtons();
int restMenu(int*, Class*);
int chooseNation();
int saveGame(Class);
void attack(Class*, Class*, int*);
void drawGameUI(Class);
void gameLoop(Class);
char* getPlayerName();
Abilities getAbilities();
void drawSpellBook();
int initmouse();
void characterMenu(Class);
int toHit(Class*, Class*);
void showmouseptr();
int getModValue(int, Abilities);
void getmousepos(int*, int*, int*);
void inventoryUI(Class);
void mainMenu();
Class loadGame();
int chooseGender();
void displayGenderButtons();
void drawSilloette();
int timedRest();
int fullRest(Class);
void drawRatLord();
void death();
void getEncounter(Class*);
void move(Class*, int, int);
void encounter(Class*);
void createMonster(Class*);
#endif