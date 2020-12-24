#ifndef _CHARACTER_H_
#define _CHARACTER_H_
#include <string>
using namespace std;

class character {
protected:
	string name;
	int weight, height, isMale, percentage;
	int speed = 100, stamina = 100, strength = 100, IQ = 100, charisma = 100;
public:
	character(string name, int height, int weight, int isMale, int percentage_input);
	void displayCharacter();

	//the character stats are hidden from the user
	void setSpeed(int speed);
	void setStrength(int strength);
	void setStamina(int stamina);
	void setCharisma(int charisma);
	void setIQ(int IQ);
	void setPercentage(int percent);

	int getSpeed();
	int getStamina();
	int getStrength();
	int getIQ();
	int getCharisma();
	int getPercentage();

	//defined in the Main Menu class
	//for saving and loading characters
	//friend void saveCharacters(string filename);
	friend void loadCharacters(string filename);
	friend int removeCharacter(string employeeName_input);

	string getName();
	int getWeight();
	int getHeight();
	int getGender();

	//for editing the base of an existing character
	friend void changeName(character* ptr, string name);
	friend void changeGender(character* ptr, int gen);
	friend void changeWeight(character* ptr, int weight);
	friend void changeHeight(character* ptr, int height);
	//changing the stats of character to save progress
};
#endif // !_CHARACTER_H_
