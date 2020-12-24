#include "character.h"
#include <iostream>
#include "Container.h"
#include <fstream>

character::character(string name_input, int height_input, int weight_input, int isGender_input)
{
	name = name_input;
	weight = weight_input;
	height = height_input;
	isMale = isGender_input;
}
string character::getName()
{
	return name;
}
int character::getHeight()
{
	return height;
}
int character::getWeight()
{
	return weight;
}
int character::getGender()
{
	return isMale;
}
void character::displayCharacter()
{
	cout << "\tName: \t\t" << getName() << endl;
	if (getGender() == 1){cout << "\tGender: \tMale" << endl;}
	else {cout << "\tGender: \tFemale" << endl;}
	cout << "\tHeight: \t" << getHeight() << " inches" << endl;
	cout << "\tWeight: \t" << getWeight() << " lbs" << endl;
}
void character::setStats()
{
	//base stats

	//example: if height is 75 inches (6'4) then the characters stamina would be 64.5
	speed = speed - ((getHeight() / 2) - 5);
	//differing for stamina for male and female because they will have varying weight
	//for male if 180 lbs then stamina will be 75
	if (getGender() == 1)
		stamina = stamina - (getWeight() / 7);
	//for women is 120 lbs then stamina will be 81
	else
		stamina = stamina - ((getWeight() / 8.5) + 5);

	//meaning is male
	if (getGender() == 1)
		IQ = IQ - 22.5;
	else
		IQ = IQ - 19.5;

	if (getGender() == 1)
		strength = (getWeight() / 2) - 5;
	//for females if you are 120 then youre strength will be 
	else
		strength = strength - (getWeight() / 4);

	//set charisma
	charisma = 100 - (IQ * .3);
}
