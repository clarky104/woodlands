#include <fstream>
#include <iostream>
#include <string>
#include "Container.h"
#include "character.h"
#include "storyLine.h"
#include "windows.h"
	using namespace std;

void executeAction(char c);
void createCharacter(string name_input, int years_input, int weight_input, int isGender);
void displayList();
character* choosingCharacter(int decision);
void changeName(character* ptr, string name);
void changeGender(character* ptr, int gender);
void changeHeight(character* ptr, int height);
void changeWeight(character* ptr, int weight);
int removeCharacter(string employeeName_input);
//void saveCharacters(string filename);
void loadCharacters(string filename);
bool saveProgress(string filename, character* ptr);
bool loadProgress(string filename, character* ptr);

Container* list = NULL;
storyLine* campaign = new storyLine();


int main()
{
	char c = 'i';
	loadCharacters("characterlist.txt");
	do
	{
		cout << "\nKING OF THE WOODLANDS\n MAIN MENU\n\n";
		cout << "\t PICK A LETTER\n";
		cout << "\t n: Start New Game\n";
		cout << "\t l: Load Game\n";
		cout << "\t s: Settings\n";
		cout << "\t h: Help\n";
		cout << "\t e: Exit Game\n";
		cin >> c;
		cin.ignore();
		executeAction(c);
	} while (c != 'e');
	//no need to save characters at the end of the program because they are being saved when user breaks out of story line
	return 0;	
}
void executeAction(char c)
{
	string name, gender, remove;
	int height, weight, isMale;
	int decision = 0;
	char q;
	string final;
	character* head = NULL;

	switch (c)
	{
	//create a new character
	case 'n':
		cout << "\nWelcome to the Woodlands, you need to create a character\n";
		cout << "Keep in mind, when creating your character the choices you make will have an impact on your characters abilities...\n";
		//creating of character
		cout << "What is your characters name? ";
		cin >> name;
		cout << "Select gender, male or female: ";
		cin >> gender;
		if (gender == "male"){isMale = true;}
		else if (gender == "female") { isMale = false;}
		else { isMale = -1; }
		while (isMale == -1) //ensures its either male or female
		{
			cout << "Invalid input, please select either male or female. ";
			cin >> gender;
			if (gender == "male") { isMale = true; }
			else if (gender == "female") { isMale = false; }
			else { isMale = -1; }
		}
		cout << "Height(inches):  ";
		cin >> height;
		cout << "Weight(lbs):  ";
		cin >> weight;
		createCharacter(name, height, weight, isMale);
		head = list->character;
		
		campaign->pickAbility(head);
		//save the progress after the esc button has been pressed in the story
		saveProgress("characterlist.txt", head);
		break;

	//load a previous character
	case 'l':
		displayList();
		//makes sure the user chose the character they want
		if (list == NULL)
		{
			cout << "There are no currently no characters to choose from\n";
			break;
		}
		do
		{
			cout << "\nChoose which character you want, using numbers: ";
			cin >> decision;
			//gives the value of choosing character to head to be manipulated
			head = choosingCharacter(decision);
			//ensures the user chose a valid character
			while (head == NULL)
			{
				cout << "Invalid choice. Pick again: ";
				cin >> decision;
				head = choosingCharacter(decision);
			}
			cout << "You have chosen " << head->getName() << ", are you sure you would like to select ";
			head->getGender() == 1 ? cout << "him? " : cout << "her? ";
			cin >> final;
		} while (final[0] != 'y' && final[0] != 'Y');
		
		loadProgress("characterlist.txt", head);
		printf("Loading game...");
		cout << string(46, '\n');
		Sleep(3000);
		campaign->pickAbility(head);
		//saves progress after the esc button has been pressed
		saveProgress("characterlist.txt", head);
		break;

	//allows for editting of character and customizing theme of the terminal
	case 's':
		q = 'k';
		cout << "\nKINGS OF THE WOODLANDS\n SETTINGS\n\n";
		cout << "\t PICK A LETTER\n";
		cout << "\t d: Delete a Character\n";
		cout << "\t e: Edit a Character\n";
		cout << "\t r: Return to Main Menu\n";
		cin >> q;

		//if invalid input cannot leave until input satisfies
		while (q != 'd' && q != 'e' && q != 'r')
		{
			cout << q << " is invalid input!\n";
			cout << "\nKINGS OF THE WOODLANDS\n SETTINGS\n\n";
			cout << "\t PICK A LETTER\n";
			cout << "\t d: Delete a Character\n";
			cout << "\t e: Edit a Character\n";
			cout << "\t r: Return to Main Menu\n";
			cin >> q;
		}

		switch (q)
		{
		
		//delete a character
		case 'd':
			if (list == NULL)
			{
				cout << "The character list is empty, therefore you cannot delete any\n";
				break;
			}
			displayList();
			cout << "Which character would you like to remove? ";
			cin >> remove;
			if (removeCharacter(remove) == 1)
				cout << remove << " has been succesfully removed\n";
			else
				cout << "There is no character on the list with the name " << remove << endl;
			break;
		
		//editting characters
		case 'e':
			if (list == NULL)
			{
				cout << "There are no characters in the list to edit\n";
				break;
			}
			cout << "\nWhich character would you like to edit? ";
			displayList();
			cin >> decision;
			head = choosingCharacter(decision);
			while (head == NULL)
			{
				cout << "Invalid choice. Pick again: ";
				cin >> decision;
				head = choosingCharacter(decision);
			}
			cout << "\nWhat would you like to change about " << head->getName() << "? \n";
			cout << "1. Name\n" << "2. Gender\n" << "3. Height\n" << "4. Weight\n";
			cin >> decision;
			//name
			if (decision == 1)
			{
				cout << "\nWhat would you like the new name to be? ";
				cin >> name;
				changeName(head, name);
			}
			//gender
			else if (decision == 2)
			{
				if (head->getGender() == 1)
				{
					changeGender(head, 0);
					cout << head->getName() << " is now a female\n";
				}
				else
				{
					changeGender(head, 1);
					cout << head->getName() << " is now a male\n";
				}
			}
			//height
			else if (decision == 3)
			{
				cout << "\nWhat would you like " << head->getName() << "'s height to be? ";
				cin >> height;
				changeHeight(head, height);
				cout << head->getName() << "'s height was succesfully changed to " << height << " inches\n";
			}
			//weight
			else if (decision == 4)
			{
				cout << "\nWhat would you like " << head->getName() << "'s weight to be? ";
				cin >> weight;
				changeWeight(head, weight);
				cout << head->getName() << "'s weight succesfully changed to " << weight << " lbs\n";
			}
			else
				cout << "Invalid choice.";
			saveProgress("characterlist.txt", head);
			break;
		case 'r': //returns to main menu
			break;
		default: cout << q << " is invalid input: Returing to main menu\n";
		}

		break;

	//rundown of the game
	case 'h':
		cout << "\n\t\tSUMMARY\n";
		cout << "This is an open world terminal game\n";
		cout << "The story is about a group of friends in grade school taking place in the small town of Kingswood\n";
		cout << "Help them on their nightly journeys and adventures.\n\n";
		break;

	//case to quit
	case 'e':
		break;

	default: cout << c << " is invalid input!\n";
		break;
	}
}

void createCharacter(string name_input, int height_input, int weight_input, int isGender)
{
	Container* tempList = list;
	Container* newCharacter = new Container();
	//adds new character into the list
	newCharacter->character = new character(name_input, height_input, weight_input, isGender, 0);
	//adds into the the head of the list because the previous head is now assigned to the next value of the recently created character
	newCharacter->next = tempList;
	//assign it into the linkedlist
	tempList = newCharacter;
	//connect the new list to the previous one
	list = tempList;
	//campaign->pickAbility(newCharacter->character);
}
void displayList()
{
	Container* tempList = list;
	int count = 1;

	while (tempList != NULL)
	{
		cout << "\n" << count << ") ";
		tempList->character->displayCharacter();
		tempList = tempList->next;
		count++;
	}
}
character* choosingCharacter(int decision)
{
	int count = 1;
	Container* tempList = list;
	character* head = NULL;
	
	while (tempList != NULL)
	{
		if (count == decision)
		{
			head = tempList->character;
			return head;
		}
		tempList = tempList->next;
		count++;
	}
	return NULL;
}
void changeName(character* ptr, string name)
{
	ptr->name = name;
}
void changeGender(character* ptr, int gender)
{
	ptr->isMale = gender;
}
void changeHeight(character* ptr, int height)
{
	ptr->height = height;
}
void changeWeight(character* ptr, int weight)
{
	ptr->weight = weight;
}
int removeCharacter(string employeeName_input)
{
	Container* head = list;
	Container* temp = NULL;

	Container* previous = NULL;
	Container* current = list;

	//for the case of the character being the first one in the linkedlist
	if (head->character->getName() == employeeName_input)
	{
		//if theyre equal then assign temp to the head to give it a value
		temp = head;
		//move head to the next node
		head = head->next;
		//then you free the value assigned to temp which is head, the character to be deleted
		free(temp);
		head = NULL;
		list = head;
		return 1;
	}
	while (head != NULL)
	{
		//move current and previous one node ahead both
		previous = current;
		current = head;
		//if the new node is equal to the character to delete
		if (current->character->getName() == employeeName_input)
		{
			//put previous next node to current nexts node essentially overpassing the current
			//thus allowing you to remove it from the list because now it will not ruin the ordering
			previous->next = current->next;
			//now you can free current because it is not out of the order of the list
			free(current);
			return 1;
		}
		//iterate to the new node to find the specific node to delete
		head = head->next;
	}
	return 0;
}
//void saveCharacters(string filename)
//{
//	Container* head = list;
//	int count = 0;
//	Container* iterator = head;
//	//finds how many nodes are in the linked list
//	while (iterator != NULL)
//	{
//		iterator = iterator->next;
//		count++;
//	}
//	ofstream myfile; //cout but instead of printing out to the terminal it prints
//	myfile.open(filename);
//	if (myfile.is_open())
//	{
//		//brings back the iterator to the front of the list
//		iterator = head;
//		//inputs the count to the file for future use
//		myfile << count;
//		while (iterator != NULL)
//		{
//			myfile << iterator->character->getName() << endl;
//			myfile << iterator->character->getHeight() << endl;
//			myfile << iterator->character->getWeight() << endl;
//			myfile << iterator->character->getGender() << endl;
//		}
//		myfile.close();
//	}
//}
void loadCharacters(string filename)
{
	ifstream myfile;
	myfile.open(filename);
	if (myfile.is_open())
	{
		int height, weight, gender, percentage, count = 0;
		int speed, stamina, strength, IQ, charisma;
		string name;
		Container* iterator = list;
		myfile >> count;
		for (int i = 0; i < count; i++)
		{
			Container* newNode = new Container();
			getline(myfile, name);
			myfile >> weight;
			myfile >> height;
			myfile >> gender;
			myfile >> percentage;
			//have to do all of this so that it does not mess up the count
			newNode->character = new character(name, height, weight, gender, percentage);

			myfile >> speed;
			myfile >> stamina;
			myfile >> strength;
			myfile >> IQ;
			myfile >> charisma;

			newNode->character->setSpeed(speed);
			newNode->character->setStamina(stamina);
			newNode->character->setStrength(strength);
			newNode->character->setIQ(IQ);
			newNode->character->setCharisma(charisma);

			//for the case of the linkedlist being empty
			if (list == NULL)
			{
				newNode->next = NULL;
				list = newNode;
			}
			//for the case of the linkedlist containing characters
			else
			{
				//bring the iterator back to the head 
				iterator = list;
				//find the end of the linkedlist
				while (iterator->next != NULL)
					iterator = iterator->next;
				//add to the tail
				iterator->next = newNode;
			}
			myfile.close();
		}

	}
}
bool saveProgress(string filename, character* ptr)
{
	//if percentage if 0 then no need to save the character because no progress made
	if (ptr->getPercentage() == 0)
		return false;

	Container* head = list;
	int count = 0;
	Container* iterator = head;
	while (iterator != NULL)
	{
		iterator = iterator->next;
		count++;
	}
	ofstream myfile;
	myfile.open(filename);
	iterator = head;
	if (myfile.is_open())
	{
		myfile << count;
		//only for editing existing characters
		while (iterator != NULL)
		{
			//if character is in the list already
			if (ptr->getName() == iterator->character->getName())
			{
				//rewrite over the preexisting stats not changing with the focus on iterating to the statistics thus to edit them
				myfile << ptr->getName() << endl;
				myfile << ptr->getHeight() << endl;
				myfile << ptr->getWeight() << endl;
				myfile << ptr->getGender() << endl;
				//edit the progression of the character 
				myfile << ptr->getPercentage() << endl;
				//character statistics
				//write in the change of stats
				myfile << ptr->getSpeed() << endl;
				myfile << ptr->getStamina() << endl;
				myfile << ptr->getStrength() << endl;
				myfile << ptr->getIQ() << endl;
				myfile << ptr->getCharisma() << endl;
				//you can only create save one character at a time thus why you are closing the file after saving
				myfile.close();
				return true;
			}
			iterator = iterator->next;
		}
		//if the character is not already in the list then create it
		myfile << ptr->getName() << endl;
		myfile << ptr->getHeight() << endl;
		myfile << ptr->getWeight() << endl;
		myfile << ptr->getGender() << endl;
		myfile << ptr->getPercentage() << endl;
		//character statistics
		myfile << ptr->getSpeed() << endl;
		myfile << ptr->getStamina() << endl;
		myfile << ptr->getStrength() << endl;
		myfile << ptr->getIQ() << endl;
		myfile << ptr->getCharisma() << endl;
		myfile.close();
		return true;
	}
	return false;
}
bool loadProgress(string filename, character* ptr)
{
	ifstream myfile;
	myfile.open(filename);
	Container* iterator = list;
	Container* newNode = new Container();
	//temporary values to put into the new created character
	string name;
	int height, weight, gender, percentage, count = 0;
	int speed, stamina, strength, IQ, charisma;

	if (myfile.is_open())
	{
		myfile >> count;
		for (int i = 0; i < count; i++)
		{
			getline(myfile, name);
			if (name == ptr->getName())
			{
				myfile >> height;
				myfile >> weight;
				myfile >> gender;
				myfile >> percentage;
				myfile >> speed;
				myfile >> stamina;
				myfile >> strength;
				myfile >> IQ;
				myfile >> charisma;

				newNode->character = new character(name, height, weight, gender, percentage);
				newNode->character->setSpeed(speed);
				newNode->character->setStamina(stamina);
				newNode->character->setStrength(strength);
				newNode->character->setIQ(IQ);
				newNode->character->setCharisma(charisma);

				//adds the new character to the list
				iterator = list;
				while (iterator->next != NULL)
					iterator = iterator->next;
				//add to the tail
				iterator->next = newNode;
				
				myfile.close();
				return true;
			}
			else
			{
				//so you can get to the beginning of the next character in the list correctly
				myfile >> weight;
				myfile >> height;
				myfile >> gender;
				myfile >> percentage;
				myfile >> speed;
				myfile >> stamina;
				myfile >> strength;
				myfile >> IQ;
				myfile >> charisma;
			}
		}
	}
	return false;
}










