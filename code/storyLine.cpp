#include "character.h"
#include "Container.h"
#include "storyLine.h"
#include "windows.h"
#include <iostream>
#include <fstream>

const int esc = 27;

void storyLine::pickAbility(character* c)
{
	int decision;
	string choice;
	if (c->getPercentage() == 0)
	{
		cout << "\nEvery SINGLE decision you make will have an impact on your ultimate fate, so choose wisely...";
		cout << string(46, '\n');
		cout << "Hello " + c->getName() + ", glad to see you are awake finally. You do not know me just yet, people call me Doctor Ordinary.\nI have been running some tests on you while you were in a coma" +
			+" for the past three months,\nand you match all the criteria that we need in the patient.\n";
		cout << "Now " + c->getName() + ", would you like to be a part of the experiment? ";
		cin >> choice;
		if (choice[0] == 'n')
		{
			cout << "\nOkay, well just to be clear that wasn't much of me asking you your decision as it was me telling you that I am going to do it\n";
			cout << "You are currently strapped down to the bed so there is not much you can do\n";
		}
		else
			cout << "\nOkay I like the enthusiam, I can see why management picked you.\n";

		cout << "Let us get right into it, you have an option between two pills." << endl;
		cout << "I will not tell you what either one does, thus making it a single blind experiment.\n Now ";
		c->getGender() == 1 ? cout << "Mr. " : cout << "Ms. ";
		cout << c->getName() + " would you like to take the first or second pill? ";
		cin >> decision;
		while (decision != 1 && decision != 2)
		{
			cout << "Invalid input";
			cout << "Try again";
			cin >> decision;
		}

		switch (decision)
		{
			//Brawns
		case 1:
			c->setStrength(90);
			c->setSpeed(90);
			c->setStamina(90);
			c->setIQ(55);
			c->setCharisma(60);
			break;
			//Brains
		case 2:
			c->setSpeed(55);
			c->setStrength(60);
			c->setStrength(30);
			c->setIQ(95);
			c->setCharisma(90);
			break;
			//Shapeshifting
		}
		cout << "Oh... I almost forgot to tell you. It does not mean much now but because you took the pill you have to stay here for the rest of your life so that we can monitor the effects\n";
		c->setPercentage(1);
	}
	if (c->getPercentage() == 1)
	{
		cout << "I am going to leave you be for now, I will come back tomorrow and see how you're feeling by then.\n";
		cout << "*Doctor Ordinary has now left the room*";
	}
	





}


