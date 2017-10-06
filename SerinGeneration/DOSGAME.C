#include <dos.h>
#include <conio.h>
#include <graphics.h>
#include "CLASS.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

union REGS i, o;

int main()
{
	mainMenu();

	clrscr();
	cleardevice();
	closegraph();
	return 0;
}

void mainMenu()
{
	int gd = DETECT, exit = 0, controls, button, x, y, gm;

	initgraph(&gd, &gm, "");
	/* 0 = keyboard controls, 1 = mouse and keyboard controls */
	controls = initmouse();
	setcolor(WHITE);
	setlinestyle(0, 0xFFFF, 3);
	setfillstyle(SOLID_FILL, 8);
	settextstyle(4, HORIZ_DIR, 5);

	randomize();

	showmouseptr();

	rectangle(10, 10, getmaxx() - 10, getmaxy() - 10);

	outtextxy(185, 100,"GAME TITLE");
	settextstyle(0, HORIZ_DIR, 1);

	/* new game button */
	rectangle(275, 200, 355, 235);
	bar(277, 202, 353, 233);
	outtextxy(280, 213, "New Game");

	/* load game button */
	rectangle(275, 250, 355, 285);
	bar(277, 252, 353, 283);
	outtextxy(280, 263, "Load Game");

	/* Options button */
	rectangle(275, 300, 355, 335);
	bar(277, 302, 353, 333);
	outtextxy(280, 313, "Options");

	/* exit game button */
	rectangle(275, 350, 355, 385);
	bar(277, 352, 353, 383);
	outtextxy(280, 363, "Exit Game");

	while (exit == 0)
	{
		getmousepos(&button, &x, &y);

		/* exit game */
		if (button == 1 && (x >= 275 && x <= 355) && (y >= 350 && y <= 385))
		{
			exit = 1;
		}

		/* new game */
		else if (button == 1 && (x >= 275 && x <= 355) && (y >= 200 && y <= 235))
		{
			gameLoop(createCharacter());

			exit = 1;
		}

		else if (button == 1 && (x >= 275 && x <= 355) && (y >= 250 && y <= 285))
		{
			gameLoop(loadGame());
			exit = 1;
		}
	}

}

void drawGameUI(Class player)
{
	char *buf[15];

	clrscr();
	cleardevice();

	/* this is the outer portion of the UI */
	rectangle(10, 10, getmaxx() - 10, getmaxy() - 10);

	line(10,300,getmaxx()-10,300);
	line(400,10,400,300);
	
	/* Health display on the gameUI */
	sprintf(buf, "Health: %d /", player.currentHealth);
	outtextxy(425, 30, ("%s", buf));
	sprintf(buf, "%d", player.totalHealth);
	outtextxy(522, 30, ("%s", buf));

	/* Mental Energy display on the gameUI */
	sprintf(buf, "M.E.  : %d /", player.currentME);
	outtextxy(425, 50, ("%s", buf));
	sprintf(buf, "%d", player.totalME);
	outtextxy(522, 50, ("%s", buf));

	/* Hunger display on the gameUI */
	sprintf(buf, "Food  : %d /", player.currentFood);
	outtextxy(425, 70, ("%s", buf));
	sprintf(buf, "%d", player.totalFood);
	outtextxy(522, 70, ("%s", buf));

	/* Use/Attack button */
	rectangle(425,135,505,170);
	bar(427, 137, 503, 168);
	outtextxy(430,148,"Use");

	/* character button */
	rectangle(425,185,505,220);
	bar(427, 187, 503, 218);
	outtextxy(430,198,"Character");

	/* rest button */
	rectangle(425,235,505,270);
	bar(427, 237, 503, 268);
	outtextxy(430,248,"Rest");

	/* magic button */
	rectangle(525,135,605,170);
	bar(527, 137, 603, 168);
	outtextxy(530,148,"Talents");

	/* inventory button */
	rectangle(525,185,605,220);
	bar(527, 187, 603, 218);
	outtextxy(530,198,"Inventory");

	/* search button */
	rectangle(525,235,605,270);
	bar(527, 237, 603, 268);
	outtextxy(530,248,"Search");
}

void drawSpellBook()
{
	int exit = 0, button, x, y;

	clrscr();
	cleardevice();

	/* this is the outer portion of the UI */
	rectangle(10, 10, getmaxx() - 10, getmaxy() - 10);

	line(10, 300, getmaxx() - 10, 300);

	rectangle(525, 235, 605, 270);
	bar(527, 237, 603, 268);
	outtextxy(530, 248, "Cancel");

	while (exit == 0)
	{
		getmousepos(&button, &x, &y);

		if (button == 1 && (x >= 525 && x <= 605) && (y >= 235 && y <= 270))
		{
			exit = 1;
		}
	}
}

void characterMenu(Class player)
{
	int exit = 0, button, x, y;
	char buf[25];

	clrscr();
	cleardevice();

	/* this is the outer portion of the UI */
	rectangle(10, 10, getmaxx() - 10, getmaxy() - 10);

	rectangle(530, 415, 610, 450);
	bar(532, 417, 608, 448);
	outtextxy(535, 428, "Cancel");

	sprintf(buf, "%s's stats", player.name);
	outtextxy(267, 30, ("%s", buf));

	outtextxy(126, 75, "Info");
	outtextxy(97, 79, "___________");

	switch (player.genderFlag)
	{
		case 0:
			outtextxy(80, 94, "Gender : Male");
			break;
		case 1:
			outtextxy(80, 94, "Gender : Female");
			break;
	}

	outtextxy(80, 109, "Age :   22");

	switch (player.nationFlag)
	{
		case 0:
			outtextxy(80, 124, "Nationality : American");
			break;
		case 1:
			outtextxy(80, 124, "Nationality : English");
			break;
		case 2:
			outtextxy(80, 124, "Nationality : German");
			break;
		case 3:
			outtextxy(80, 124, "Nationality : Russian");
			break;
		case 4:
			outtextxy(80, 124, "Nationality : Chinease");
			break;
	}

	switch (player.classFlag)
	{
		case 1:
			outtextxy(80, 139, "Class : Agent");
			break;
		case 2:
			outtextxy(80, 139, "Class : Soldier");
			break;
		case 3:
			outtextxy(80, 139, "Class : Scientist");
			break;
		case 4:
			outtextxy(80, 139, "Class : Engineer");
			break;
		case 5:
			outtextxy(80, 139, "Class : Scout");
			break;
		case 6:
			outtextxy(80, 139, "Class : Nationalist");
			break;
	}

	sprintf(buf, "Lvl :        %d", player.lvl);
	outtextxy(80, 154, buf);

	sprintf(buf, "Exp :        %d", player.exp);
	outtextxy(80, 169, buf);

	outtextxy(106, 204, "Abilities");
	outtextxy(97, 208, "___________");

	sprintf(buf, "Strength :     %d", player.abil.strength);
	outtextxy(80, 223, ("%s", buf));

	sprintf(buf, "Constitution : %d", player.abil.constitution);
	outtextxy(80, 238, ("%s", buf));

	sprintf(buf, "Dexterity :    %d", player.abil.dexterity);
	outtextxy(80, 253, ("%s", buf));

	sprintf(buf, "Wisdom :       %d", player.abil.wisdom);
	outtextxy(80, 268, ("%s", buf));

	sprintf(buf, "Intelligence : %d", player.abil.intelligence);
	outtextxy(80, 283, ("%s", buf));

	sprintf(buf, "Charisma :     %d", player.abil.charisma);
	outtextxy(80, 298, ("%s", buf));

	/* Start of second column */

	sprintf(buf, "Health: %d /", player.currentHealth);
	outtextxy(425, 75, ("%s", buf));
	sprintf(buf, "%d", player.totalHealth);
	outtextxy(527, 75, ("%s", buf));

	sprintf(buf, "M.E.  : %d /", player.currentME);
	outtextxy(425, 90, ("%s", buf));
	sprintf(buf, "%d", player.totalME);
	outtextxy(527, 90, ("%s", buf));

	sprintf(buf, "Food  : %d /", player.currentFood);
	outtextxy(425, 105, ("%s", buf));
	sprintf(buf, "%d", player.totalFood);
	outtextxy(527, 105, ("%s", buf));

	sprintf(buf, "Armour Class : %d", player.armourClass);
	outtextxy(425, 120, ("%s", buf));

	switch (player.wep.wepType)
	{
		case 0:
			sprintf(buf, "Damage :  %d -", 1 + getModValue(0, player.abil));
			outtextxy(425, 135, ("%s", buf));
			sprintf(buf, "%d", player.wep.dmgDie + getModValue(0, player.abil));
			outtextxy(537, 135, ("%s", buf));
			break;
		case 1:
			sprintf(buf, "Damage :  %d -", 1 + getModValue(2, player.abil));
			outtextxy(425, 135, ("%s", buf));
			sprintf(buf, "%d", player.wep.dmgDie + getModValue(2, player.abil));
			outtextxy(537, 135, ("%s", buf));
			break;
	}


	while (exit == 0)
	{
		getmousepos(&button, &x, &y);

		if (button == 1 && (x >= 530 && x <= 610) && (y >= 415 && y <= 450))
		{
			exit = 1;
		}
	}
}

int restMenu(int *saveFlag, Class *player)
{
	int exit = 0, quit = 0, button, x, y;

	clrscr();
	cleardevice();

	settextstyle(4, HORIZ_DIR, 5);
	outtextxy(185, 100, "GAME TITLE");
	settextstyle(0, HORIZ_DIR, 1);

	/* this is the outer portion of the UI */
	rectangle(10, 10, getmaxx() - 10, getmaxy() - 10);

	/* rest button */
	rectangle(275, 200, 355, 235);
	bar(277, 202, 353, 233);
	outtextxy(280, 213, "Rest");

	/* time rest button */
	rectangle(275, 250, 355, 285);
	bar(277, 252, 353, 283);
	outtextxy(280, 263, "Time Wait");

	/* save game button */
	rectangle(275, 300, 355, 335);
	bar(277, 302, 353, 333);
	outtextxy(280, 313, "Save");

	/* exit game button */
	rectangle(275, 350, 355, 385);
	bar(277, 352, 353, 383);
	outtextxy(280, 363, "Exit Game");

	/* cancel button */
	rectangle(275, 400, 355, 435);
	bar(277, 402, 353, 433);
	outtextxy(280, 413, "Cancel");

	while (exit == 0)
	{
		getmousepos(&button, &x, &y);

		/* exit game */
		if (button == 1 && (x >= 275 && x <= 355) && (y >= 350 && y <= 385))
		{
			exit = 1;
			quit = 1;
		}

		else if (button == 1 && (x >= 275 && x <= 355) && (y >= 200 && y <= 235))
		{
			*saveFlag = fullRest(*player);
			player->currentHealth = player->currentHealth + *saveFlag;
			player->currentME = player->totalME;
			exit = 1;
		}

		else if (button == 1 && (x >= 275 && x <= 355) && (y >= 250 && y <= 285))
		{
			*saveFlag = timedRest();
			player->currentME = player->totalME;
			exit = 1;
		}

		/* return to the main game */
		else if (button == 1 && (x >= 275 && x <= 355) && (y >= 400 && y <= 435))
		{
			*saveFlag = -2;
			exit = 1;
		}

		else if (button == 1 && (x >= 275 && x <= 355) && (y >= 300 && y <= 335))
		{
			*saveFlag = saveGame(*player);
			exit = 1;
		}
	}

	return quit;
}

void inventoryUI(Class player)
{
	int exit = 0, button, x, y, i;

	clrscr();
	cleardevice();

	/* this is the outer portion of the UI */
	rectangle(10, 10, getmaxx() - 10, getmaxy() - 10);

	line(10, 300, getmaxx() - 10, 300);
	line(400, 10, 400, 300);

	for (i = 1; i <= 16; i = i + 1)
	{
		line(400, 10 + (i * 18), getmaxx() - 10, 10 + (i * 18));
	}

	drawSilloette();
	outtextxy(52, 79, player.wep.name);
	outtextxy(296, 79, player.wep.name);


	for (i = 0; i < 16; i = i + 1)
	{
		outtextxy(415, 28 + (i * 18) - 9, player.inventory[i].name);
	}

	rectangle(530,315,610 ,350);
	bar(532, 317, 608, 348);
	outtextxy(535, 328, "Equip");

	rectangle(530, 365, 610, 400);
	bar(532, 367, 608, 398);
	outtextxy(535, 378, "Inspect");

	rectangle(530, 415, 610, 450);
	bar(532, 417, 608, 448);
	outtextxy(535, 428, "Cancel");

	while (exit == 0)
	{
		getmousepos(&button, &x, &y);

		if (button == 1 && (x >= 530 && x <= 610) && (y >= 415 && y <= 450))
		{
			exit = 1;
		}
	}
}

void gameLoop(Class player)
{
	int exit = 0, button, x, y, gm, test;
	int *saveFlag;
	char buf[50];
	char key;

	drawGameUI(player);

	while(exit == 0)
	{
		getmousepos(&button, &x, &y);

		/* spell book page */
		if(button == 1 && (x >= 525 && x <= 605) && (y >= 135 && y <= 170))
		{
			drawSpellBook();
			drawGameUI(player);
		}

		/* rest menu */
		else if (button == 1 && (x >= 425 && x <= 505) && (y >= 235 && y <= 270))
		{
			exit = restMenu(saveFlag, &player);
			drawGameUI(player);
			test = *saveFlag;
			switch (*saveFlag)
			{
				case -1:
					outtextxy(20, 310, "Save Successful!");
					break;
				
				case -2:
					break;

				default:
					sprintf(buf, "Rested for %d hours", *saveFlag);
					outtextxy(20, 310, ("%s", buf));
					break;
			}
		}

		/* character menu */
		else if (button == 1 && (x >= 425 && x <= 505) && (y >= 185 && y <= 220))
		{
			characterMenu(player);
			drawGameUI(player);
		}

		/* Inventory */
		else if (button == 1 && (x >= 525 && x <= 605) && (y >= 185 && y <= 220))
		{
			inventoryUI(player);
			drawGameUI(player);
		}

		/* TODO add functionality to the movement keys */
		else if(kbhit())
		{
			key = getch();

			switch (key)
			{
				case 'w':
					move(&player, 0, 10);
					break;
				case 's':
					move(&player, 0, -10);
					break;
				case 'a':
					move(&player, -10, 0);
					break;
				case 'd':
					move(&player, 10, 0);
					break;
			}

			key = 0;
		}
	}
}

int initmouse()
{
	i.x.ax = 0;
	int86(0X33, &i, &o);
	return (o.x.ax);
}

void showmouseptr()
{
	i.x.ax = 1;
	int86(0X33, &i, &o);
}

void getmousepos(int *button, int *x, int *y)
{
	i.x.ax = 3;
	int86(0X33, &i, &o);

	*button = o.x.bx;
	*x = o.x.cx;
	*y = o.x.dx;
}

Class createCharacter()
{
	int i;

	Class player;
	player.genderFlag = chooseGender();
	player.nationFlag = chooseNation();
	player = chooseClass(player);
	player.exp = 0;
	player.lvl = 1;
	player.abil = getAbilities();
	player.totalHealth = player.hitDie + getModValue(1, player.abil);
	player.currentHealth = player.totalHealth;
	player.totalME = player.hitDie + getModValue(3, player.abil);
	player.currentME = player.totalME;
	player.totalFood = player.hitDie + getModValue(0, player.abil);
	player.currentFood = player.totalFood;
	player.arm = initArmour();
	player.wep = initWeapon();
	player.armourClass = 10 + player.arm.armourClassMod + getModValue(2, player.abil);
	strcpy(player.name, getPlayerName());
	player.spot.oLocationX = 0;
	player.spot.oLocationY = 0;
	player.spot.dLocationX = 0;
	player.spot.dLocationY = 0;
	player.spot.dungeonFlag = 0;
	for (i = 0; i < 16; i = i + 1)
	{
		strcpy(player.inventory[i].name, "Empty");
		player.inventory[i].itemID = 0;
	}

	return player;
}

char* getPlayerName()
{
	char name[20];
	int exit = 0, count = 0, x, y;
	char key;
	char buf[10];

	outtextxy(20, 320, "Enter character Name:");

	while (exit == 0)
	{
		if (kbhit)
		{
			key = getch();

			switch (key)
			{
				case 13:
					while (count < 20)
					{
						name[count] = NULL;
						count = count + 1;
					}
					exit = 1;
					break;

				case 8:
					count = count - 1;

					for (y = 0; y <= 10; y = y + 1)
					{
						for (x = 0; x <= 10; x = x + 1)
						{
							putpixel(200 + ((count * 8) + x), 320 + y, BLACK);
						}
					}
					break;

				default:
					name[count] = key;

					sprintf(buf, "%c", name[count]);
					outtextxy(200 + (count * 8), 320, ("%s", buf));
					count = count + 1;
					break;
			}
		}
	}

	return name;
}

Class chooseClass(Class player)
{
	int choice = 0, button, x, y;

	displayClassButtons();

	while (choice == 0)
	{
		getmousepos(&button, &x, &y);

		if (button == 1 && (x >= 75 && x <= 155) && (y >= 120 && y <= 155))
		{
			choice = 1;
			player.classFlag = 1;
			player.hitDie = 8;
		}
		else if (button == 1 && (x >= 165 && x <= 245) && (y >= 120 && y <= 155))
		{
			choice = 1;
			player.classFlag = 2;
			player.hitDie = 10;
		}
		else if (button == 1 && (x >= 255 && x <= 335) && (y >= 120 && y <= 155))
		{
			choice = 1;
			player.classFlag = 3;
			player.hitDie = 4;
		}
		else if (button == 1 && (x >= 345 && x <= 425) && (y >= 120 && y <= 155))
		{
			choice = 1;
			player.classFlag = 4;
			player.hitDie = 8;
		}
		else if (button == 1 && (x >= 435 && x <= 515) && (y >= 120 && y <= 155))
		{
			choice = 1;
			player.classFlag = 5;
			player.hitDie = 10;
		}
		else if (button == 1 && (x >= 525 && x <= 605) && (y >= 120 && y <= 155))
		{
			choice = 1;
			player.classFlag = 6;
			player.hitDie = 10;
		}
	}

	return player;
}

Abilities getAbilities()
{
	int reRoll = 0, rolls = 0, buttonPress = 0, button, x, y;
	char buf[20];
	Abilities abil;

	while (reRoll == 0)
	{
		buttonPress = 0;
		rolls += 1;
		abil.strength = roll(20);
		sprintf(buf, "Strength: %d", abil.strength);
		outtextxy(20, 175, ("%s", buf));

		abil.constitution = roll(20);
		sprintf(buf, "Constitution: %d ", abil.constitution);
		outtextxy(20, 185, ("%s", buf));

		abil.dexterity = roll(20);
		sprintf(buf, "Dexterity: %d", abil.dexterity);
		outtextxy(20, 195, ("%s", buf));

		abil.wisdom = roll(20);
		sprintf(buf, "Wisdom: %d", abil.wisdom);
		outtextxy(20, 205, ("%s", buf));
		
		abil.intelligence = roll(20);
		sprintf(buf, "Intelligence: %d", abil.intelligence);
		outtextxy(20, 215, ("%s", buf));
		
		abil.charisma = roll(20);
		sprintf(buf, "Charisma: %d", abil.charisma);
		outtextxy(20, 225, ("%s", buf));

		sprintf(buf, "%d rolls remaining: ", 5 - rolls);
		outtextxy(20, 245, ("%s", buf));

		/* re-roll button */
		if (rolls < 5)
		{
			rectangle(20, 265, 100, 300);
			bar(22, 268, 98, 298);
			outtextxy(25, 277, "Re-Roll");
		}

		/* keep roll button */
		rectangle(110, 265, 190, 300);
		bar(112, 268, 188, 298);
		outtextxy(115, 277, "Keep roll");

		while (buttonPress == 0)
		{
			getmousepos(&button, &x, &y);

			if (button == 1 && (x >= 20 && x <= 100) && (y >= 265 && y <= 300) && rolls < 5)
			{
				displayGenderButtons();
				displayNationalityButtons();
				displayClassButtons();
				buttonPress = 1;
			}
			else if (button == 1 && (x >= 110 && x <= 190) && (y >= 265 && y <= 300))
			{
				buttonPress = 1;
				reRoll = 1;
			}
		}
		
	}

	return abil;
}

int roll(int dieID)
{
	return random(dieID);
}

/* TODO write Introductory story */
void introStory()
{
	outtextxy(20, 310, "Just testing the position of the text that will be in the games information");
}

void displayClassButtons()
{
	outtextxy(20, 133, "Class:");

	/* Rouge class button */
	rectangle(75, 120, 155, 155);
	bar(77, 122, 153, 153);
	outtextxy(80, 133, "Agent");

	/* Fighter class button */
	rectangle(165, 120, 245, 155);
	bar(167, 122, 243, 153);
	outtextxy(170, 133, "Soldier");

	/* Wizard class button */
	rectangle(255, 120, 335, 155);
	bar(257, 122, 333, 153);
	outtextxy(260, 133, "Scientist");

	/* Cleric class button */
	rectangle(345, 120, 425, 155);
	bar(347, 122, 423, 153);
	outtextxy(350, 133, "Engineer");

	/* Ranger class button */
	rectangle(435, 120, 515, 155);
	bar(437, 122, 513, 153);
	outtextxy(440, 133, "Scout");

	/* Paladin class button */
	rectangle(525, 120, 605, 155);
	bar(527, 122, 603, 153);
	outtextxy(535, 133, "Nationalist");
}

Armour initArmour()
{
	Armour clothes;

	strcpy(clothes.name, "Clothes");
	clothes.armourClassMod = 0;
	clothes.type = 0;

	return clothes;
}

Weapon initWeapon()
{
	Weapon fists;

	strcpy(fists.name, "Fists");
	fists.critValue = 20;
	fists.dmgDie = 4;
	fists.goldValue = 0;
	fists.lethalFlag = 0;
	fists.range = 5;
	fists.wepType = 0;

	return fists;
}

int getModValue(int abilityFlag, Abilities abilities)
{
	switch (abilityFlag)
	{
		case 0:
			abilityFlag = (abilities.strength - 10) / 2;
			break;
		case 1:
			abilityFlag = (abilities.constitution - 10) / 2;
			break;
		case 2:
			abilityFlag = (abilities.dexterity - 10) / 2;
			break;
		case 3:
			abilityFlag = (abilities.wisdom - 10) / 2;
			break;
		case 4:
			abilityFlag = (abilities.intelligence - 10) / 2;
			break;
		case 5:
			abilityFlag = (abilities.charisma - 10) / 2;
			break;
	}

	return abilityFlag;
}

int saveGame(Class player)
{
	int i;
	char buf[20];
	FILE *saveFile = fopen("player.txt", "w");

	/* saves character */
	sprintf(buf, "%s\n", player.name);
	fputs(buf, saveFile);

	sprintf(buf, "%d\n", player.armourClass);
	fputs(buf, saveFile);

	sprintf(buf, "%d\n", player.lvl);
	fputs(buf, saveFile);

	sprintf(buf, "%d\n", player.exp);
	fputs(buf, saveFile);

	sprintf(buf, "%d\n", player.hitDie);
	fputs(buf, saveFile);

	sprintf(buf, "%d\n", player.classFlag);
	fputs(buf, saveFile);

	sprintf(buf, "%d\n", player.nationFlag);
	fputs(buf, saveFile);

	sprintf(buf, "%d\n", player.genderFlag);
	fputs(buf, saveFile);

	sprintf(buf, "%d\n", player.abil.strength);
	fputs(buf, saveFile);

	sprintf(buf, "%d\n", player.abil.constitution);
	fputs(buf, saveFile);

	sprintf(buf, "%d\n", player.abil.dexterity);
	fputs(buf, saveFile);

	sprintf(buf, "%d\n", player.abil.wisdom);
	fputs(buf, saveFile);

	sprintf(buf, "%d\n", player.abil.intelligence);
	fputs(buf, saveFile);

	sprintf(buf, "%d\n", player.abil.charisma);
	fputs(buf, saveFile);

	sprintf(buf, "%d\n", player.totalHealth);
	fputs(buf, saveFile);

	sprintf(buf, "%d\n", player.currentHealth);
	fputs(buf, saveFile);

	sprintf(buf, "%d\n", player.totalME);
	fputs(buf, saveFile);

	sprintf(buf, "%d\n", player.currentME);
	fputs(buf, saveFile);

	sprintf(buf, "%d\n", player.totalFood);
	fputs(buf, saveFile);

	sprintf(buf, "%d\n", player.currentFood);
	fputs(buf, saveFile);

	sprintf(buf, "%s\n", player.arm.name);
	fputs(buf, saveFile);

	sprintf(buf, "%d\n", player.arm.armourClassMod);
	fputs(buf, saveFile);

	sprintf(buf, "%d\n", player.arm.type);
	fputs(buf, saveFile);

	sprintf(buf, "%s\n", player.wep.name);
	fputs(buf, saveFile);

	sprintf(buf, "%d\n", player.wep.wepType);
	fputs(buf, saveFile);

	sprintf(buf, "%d\n", player.wep.dmgDie);
	fputs(buf, saveFile);

	sprintf(buf, "%d\n", player.wep.critValue);
	fputs(buf, saveFile);

	sprintf(buf, "%d\n", player.wep.range);
	fputs(buf, saveFile);

	sprintf(buf, "%d\n", player.wep.goldValue);
	fputs(buf, saveFile);

	sprintf(buf, "%d\n", player.wep.lethalFlag);
	fputs(buf, saveFile);

	sprintf(buf, "%d\n", player.spot.oLocationX);
	fputs(buf, saveFile);

	sprintf(buf, "%d\n", player.spot.oLocationY);
	fputs(buf, saveFile);

	sprintf(buf, "%d\n", player.spot.dLocationX);
	fputs(buf, saveFile);

	sprintf(buf, "%d\n", player.spot.dLocationY);
	fputs(buf, saveFile);

	sprintf(buf, "%d\n", player.spot.dungeonFlag);
	fputs(buf, saveFile);

	for (i = 0; i < 16; i = i + 1)
	{
		sprintf(buf, "%s\n", player.inventory[i].name);
		fputs(buf, saveFile);

		sprintf(buf, "%d\n", player.inventory[i].itemID);
		fputs(buf, saveFile);
	}

	fclose(saveFile);

	return -1;
}

Class loadGame()
{
	Class player;
	FILE *loadFile = fopen("player.txt", "r");
	int i;
	char buf[20];
	
	/* loads character */
	fscanf(loadFile, "%s", buf);
	strcpy(player.name, buf);

	fscanf(loadFile, "%s", buf);
	player.armourClass = atoi(buf);

	fscanf(loadFile, "%s", buf);
	player.lvl = atoi(buf);

	fscanf(loadFile, "%s", buf);
	player.exp = atoi(buf);

	fscanf(loadFile, "%s", buf);
	player.hitDie = atoi(buf);

	fscanf(loadFile, "%s", buf);
	player.classFlag = atoi(buf);

	fscanf(loadFile, "%s", buf);
	player.nationFlag = atoi(buf);

	fscanf(loadFile, "%s", buf);
	player.genderFlag = atoi(buf);

	fscanf(loadFile, "%s", buf);
	player.abil.strength = atoi(buf);

	fscanf(loadFile, "%s", buf);
	player.abil.constitution = atoi(buf);

	fscanf(loadFile, "%s", buf);
	player.abil.dexterity = atoi(buf);

	fscanf(loadFile, "%s", buf);
	player.abil.wisdom = atoi(buf);

	fscanf(loadFile, "%s", buf);
	player.abil.intelligence = atoi(buf);

	fscanf(loadFile, "%s", buf);
	player.abil.charisma = atoi(buf);

	fscanf(loadFile, "%s", buf);
	player.totalHealth = atoi(buf);

	fscanf(loadFile, "%s", buf);
	player.currentHealth = atoi(buf);

	fscanf(loadFile, "%s", buf);
	player.totalME = atoi(buf);

	fscanf(loadFile, "%s", buf);
	player.currentME = atoi(buf);

	fscanf(loadFile, "%s", buf);
	player.totalFood = atoi(buf);

	fscanf(loadFile, "%s", buf);
	player.currentFood = atoi(buf);

	fscanf(loadFile, "%s", buf);
	strcpy(player.arm.name, buf);

	fscanf(loadFile, "%s", buf);
	player.arm.armourClassMod = atoi(buf);

	fscanf(loadFile, "%s", buf);
	player.arm.type = atoi(buf);

	fscanf(loadFile, "%s", buf);
	strcpy(player.wep.name, buf);

	fscanf(loadFile, "%s", buf);
	player.wep.wepType = atoi(buf);

	fscanf(loadFile, "%s", buf);
	player.wep.dmgDie = atoi(buf);

	fscanf(loadFile, "%s", buf);
	player.wep.critValue = atoi(buf);

	fscanf(loadFile, "%s", buf);
	player.wep.range = atoi(buf);

	fscanf(loadFile, "%s", buf);
	player.wep.goldValue = atoi(buf);

	fscanf(loadFile, "%s", buf);
	player.wep.lethalFlag = atoi(buf);

	fscanf(loadFile, "%s", buf);
	player.spot.oLocationX = atoi(buf);

	fscanf(loadFile, "%s", buf);
	player.spot.oLocationY = atoi(buf);

	fscanf(loadFile, "%s", buf);
	player.spot.dLocationX = atoi(buf);

	fscanf(loadFile, "%s", buf);
	player.spot.dLocationY = atoi(buf);

	fscanf(loadFile, "%s", buf);
	player.spot.dungeonFlag = atoi(buf);

	for (i = 0; i < 16; i = i + 1)
	{
		fscanf(loadFile, "%s", buf);
		strcpy(player.inventory[i].name, buf);

		fscanf(loadFile, "%s", buf);
		player.inventory[i].itemID = atoi(buf);
	}

	fclose(loadFile);
	return player;
}

void attack(Class* attacker, Class* defender, int *i)
{
	int dmg = 0;
	char buf[35];

	switch (toHit(attacker, defender))
	{
		case 0:
			sprintf(buf, "%s Missed!", attacker->name);
			outtextxy(20, 310 + (*i * 10), ("%s", buf));
			break;
		case 1:
			switch (attacker->wep.wepType)
			{
				case 0:
					dmg = roll(attacker->wep.dmgDie) + getModValue(0, attacker->abil);
					defender->currentHealth = defender->currentHealth - dmg;
					break;
				case 1:
					dmg = roll(attacker->wep.dmgDie) + getModValue(0, attacker->abil);
					defender->currentHealth = defender->currentHealth - dmg;
					break;
			}
			sprintf(buf, "hit for %d damage", dmg);
			outtextxy(20, 310 + (*i * 10), ("%s", buf));
			break;
	}
}

int toHit(Class* attacker, Class *defender)
{
	int hitRoll;

	switch (attacker->wep.wepType)
	{
		case 0:
			hitRoll = roll(20) + attacker->abil.strength;
			break;
		case 1:

			hitRoll = roll(20) + attacker->abil.dexterity;
			break;
	}

	if (hitRoll > defender->armourClass)
		return 1;
	else
		return 0;
}

void displayNationalityButtons()
{
	rectangle(10, 10, getmaxx() - 10, getmaxy() - 10);

	outtextxy(20, 83, "Nation:");

	/* America nation button */
	rectangle(75, 70, 155, 105);
	bar(77, 72, 153, 103);
	outtextxy(80, 83, "America");

	/* England nation button */
	rectangle(165, 70, 245, 105);
	bar(167, 72, 243, 103);
	outtextxy(170, 83, "England");

	/* Germany Nation button */
	rectangle(255, 70, 335, 105);
	bar(257, 72, 333, 103);
	outtextxy(260, 83, "Germany");

	/* Russia nation button */
	rectangle(345, 70, 425, 105);
	bar(347, 72, 423, 103);
	outtextxy(350, 83, "Russia");

	/* China nation button */
	rectangle(435, 70, 515, 105);
	bar(437, 72, 513, 103);
	outtextxy(440, 83, "China");
}

int chooseNation()
{
	int choice = -1, button, x, y;

	displayNationalityButtons();

	while (choice == -1)
	{
		getmousepos(&button, &x, &y);

		if (button == 1 && (x >= 75 && x <= 155) && (y >= 70 && y <= 105))
		{
			choice = 0;
		}
		else if (button == 1 && (x >= 165 && x <= 245) && (y >= 70 && y <= 105))
		{
			choice = 1;
		}
		else if (button == 1 && (x >= 255 && x <= 335) && (y >= 70 && y <= 105))
		{
			choice = 2;
		}
		else if (button == 1 && (x >= 345 && x <= 425) && (y >= 70 && y <= 105))
		{
			choice = 3;
		}
		else if (button == 1 && (x >= 435 && x <= 515) && (y >= 70 && y <= 105))
		{
			choice = 4;
		}
	}

	return choice;
}

int chooseGender()
{
	int choice = -1, button, x, y;

	displayGenderButtons();

	while (choice == -1)
	{
		getmousepos(&button, &x, &y);

		if (button == 1 && (x >= 75 && x <= 155) && (y >= 20 && y <= 55))
		{
			choice = 0;
		}
		else if (button == 1 && (x >= 165 && x <= 245) && (y >= 20 && y <= 55))
		{
			choice = 1;
		}
	}

	return choice;
}

void displayGenderButtons()
{
	cleardevice();
	rectangle(10, 10, getmaxx() - 10, getmaxy() - 10);

	outtextxy(20, 33, "Gender:");

	/* America nation button */
	rectangle(75, 20, 155, 55);
	bar(77, 22, 153, 53);
	outtextxy(80, 33, "Male");

	/* England nation button */
	rectangle(165, 20, 245, 55);
	bar(167, 22, 243, 53);
	outtextxy(170, 33, "Female");
}

void drawSilloette()
{
	int i;

	/* Square for head */
	for (i = 0; i <= 30; i = i + 1)
	{
		putpixel(190 + i, 30, RED);
		putpixel(220, 30 + i, RED);
		putpixel(220 - i, 60, RED);
		putpixel(190, 60 - i, RED);
	}

	/* line for body */
	for (i = 0; i <= 120; i = i + 1)
	{
		putpixel(205, 60 + i, RED);
		putpixel(206, 60 + i, RED);
	}

	/* line for arms */
	for (i = 0; i <= 150; i = i + 1)
	{
		putpixel(130 + i, 110, RED);
	}

	/* lines for legs */
	for (i = 0; i <= 70; i = i + 1)
	{
		putpixel(205 - i, 180 + i, RED);
		putpixel(206 + i, 180 + i, RED);
	}

	/* lines for equiped items */
	for (i = 0; i <= 15; i = i + 1)
	{
		putpixel(127 - i, 107 - i, RED);
		putpixel(281 + i, 107 - i, RED);
	}

	for (i = 0; i <= 60; i = i + 1)
	{
		putpixel(112 - i, 92, RED);
		putpixel(296 + i, 92, RED);
	}
}

/* TODO get rid of the time stuff */
int fullRest(Class player)
{
	int hours = 0;

	while (player.currentHealth < player.totalHealth)
	{
		/* TODO Roll for every health point and see if a random encounter occurs */

		player.currentHealth = player.currentHealth + 1;
		hours = hours + 1;
	}

	return hours;
}

int timedRest()
{
	int hours = 0, exit = 0, button, x, y, count = 0, key;
	char hourValue[5], buf[5];

	clrscr();
	cleardevice();

	/* this is the outer portion of the UI */
	rectangle(10, 10, getmaxx() - 10, getmaxy() - 10);
	rectangle(150, 125, 485, 340);

	outtextxy(260, 200, "Hours to wait:");

	while (exit == 0)
	{
		if (kbhit)
		{
			key = getch();

			switch (key)
			{
				case 13:
					while (count <= 5)
					{
						hourValue[count] = NULL;
						count = count + 1;
					}
					exit = 1;
					break;

				case 8:
					count = count - 1;

					for (y = 0; y <= 10; y = y + 1)
					{
						for (x = 0; x <= 10; x = x + 1)
						{
							putpixel(375 + ((count * 8) + x), 200 + y, BLACK);
						}
					}
					break;

				default:
					hourValue[count] = key;
					sprintf(buf, "%c", hourValue[count]);
					outtextxy(375 + (count * 8), 200, ("%s", buf));
					count = count + 1;
					break;
			}
		}
	}

	hours = atoi(buf);

	return hours;
}

/* TODO add perma-death function that wipes the save file */
void death()
{
	char buf[20];

	if (remove("player.txt") == 0)
	{
		/* Call a game over screen */
	}
}

void getEncounter(Class *player)
{
	if (roll(20) > 14)
	{
		encounter(player);
	}
}

void encounter(Class *player)
{
	int button, x, y, gm, i = 0, tempx, tempy;
	Class monster;
	char buf[30];

	createMonster(&monster);

	while (player->currentHealth > 0 && monster.currentHealth > 0)
	{
		getmousepos(&button, &x, &y);

		if (x == tempx && y == tempy)
		{

		}
		else if (button == 1 && (x >= 425 && x <= 505) && (y >= 135 && y <= 170))
		{
			attack(player, &monster, &i);
			/* attack(&monster, player); */
			i = i + 1;
			tempx = x;
			tempy = y;
			if (i == 16)
			{
				i = 0;
				setfillstyle(SOLID_FILL, BLACK);
				bar(12, 302, getmaxx() - 12, getmaxy() - 12);
				setfillstyle(SOLID_FILL, DARKGRAY);
			}
		}
		/* TODO work on the talents */
		else if (button == 1 && (x >= 525 && x <= 605) && (y >= 135 && y <= 170))
		{
			drawSpellBook();
		}
	}
}

void createMonster(Class* monster)
{
	monster->totalHealth = 10;
	monster->currentHealth = 10;
	monster->armourClass = 15;

	drawRatLord();
}

/* TODO Test move function */
void move(Class *player, int x, int y)
{
	switch (player->spot.dungeonFlag)
	{
		case 0:
			player->spot.oLocationX = player->spot.oLocationX + x;
			player->spot.oLocationY = player->spot.oLocationY + y;
			/* TODO draw player here */
			break;
		case 1:
			player->spot.dLocationX = player->spot.dLocationX + x;
			player->spot.dLocationY = player->spot.dLocationY + y;
			/* TODO draw surrondings for players move here */
			break;
	}

	getEncounter(player);
}

/* TODO make an enemy function */
void drawRatLord()
{
	int x = 0, y = 0;

	/*for (y = 0; y < 5; y = y + 1)
	{
		for (x = 0; x < 11; x = x + 1)
		{
			switch (y)
			{
				case 0:
					putpixel(203 + x, 30, BROWN);
					putpixel(203 - x, 30, BROWN);
					break;
			}
		}
	}*/

	/* Raster line 1 */
	putpixel(200, 30, BROWN);
	putpixel(201, 30, BROWN);
	putpixel(202, 30, BROWN);
	putpixel(203, 30, BROWN);
	putpixel(204, 30, BROWN);
	putpixel(205, 30, BROWN);
	putpixel(206, 30, BROWN);

	/* Raseter line 2 */
	putpixel(198, 31, BROWN);
	putpixel(199, 31, BROWN);
	putpixel(200, 31, BROWN);
	putpixel(201, 31, BROWN);
	putpixel(202, 31, BROWN);
	putpixel(203, 31, BROWN);
	putpixel(204, 31, BROWN);
	putpixel(205, 31, BROWN);
	putpixel(206, 31, BROWN);
	putpixel(207, 31, BROWN);
	putpixel(208, 31, BROWN);

	/* Raster line 3 */
	putpixel(197, 32, BROWN);
	putpixel(198, 32, BROWN);
	putpixel(199, 32, BROWN);
	putpixel(200, 32, BROWN);
	putpixel(201, 32, BROWN);
	putpixel(202, 32, BROWN);
	putpixel(203, 32, BROWN);
	putpixel(204, 32, BROWN);
	putpixel(205, 32, BROWN);
	putpixel(206, 32, BROWN);
	putpixel(207, 32, BROWN);
	putpixel(208, 32, BROWN);
	putpixel(209, 32, BROWN);

	/* Raster line 4 */
	putpixel(197, 32, BROWN);
	putpixel(198, 32, BROWN);
	putpixel(199, 32, BROWN);
	putpixel(200, 32, BROWN);
	putpixel(201, 32, BROWN);
	putpixel(202, 32, BROWN);
	putpixel(203, 32, BROWN);
	putpixel(204, 32, BROWN);
	putpixel(205, 32, BROWN);
	putpixel(206, 32, BROWN);
	putpixel(207, 32, BROWN);
	putpixel(208, 32, BROWN);
	putpixel(209, 32, BROWN);

	/* Raster line 5 */
	putpixel(196, 33, BROWN);
	putpixel(197, 33, BROWN);
	putpixel(198, 33, BROWN);
	putpixel(199, 33, BROWN);
	putpixel(200, 33, BROWN);
	putpixel(201, 33, BROWN);
	putpixel(202, 33, BROWN);
	putpixel(203, 33, BROWN);
	putpixel(204, 33, BROWN);
	putpixel(205, 33, BROWN);
	putpixel(206, 33, BROWN);
	putpixel(207, 33, BROWN);
	putpixel(208, 33, BROWN);
	putpixel(209, 33, BROWN);
	putpixel(210, 33, BROWN);
}