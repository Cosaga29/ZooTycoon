/*************************************************************
*	Author: Martin Edmunds
*	Email: edmundsm@oregonstate.edu
*	Class: CS 162-400
*	Date: 01/27/19
*	Project: Project 2
*
*	Description:
**************************************************************/

#include "Zoo.hpp"


/*
Arrays are initialized with 10 animals each, but when the zoo updates
only the animals up to the count of the animal are updated and used in the
const calculations


*/
Zoo::Zoo(Player& player, std::ostream& pgmOutput) :
	bound_player(player), output(pgmOutput), tigerArraySize(STARTING_CAPACITY),
	penguinArraySize(STARTING_CAPACITY),
	turtleArraySize(STARTING_CAPACITY), dayCount(1),
	tigerCount(0), penguinCount(0), turtleCount(0)
{
	//seed RNG
	srand(time(NULL));


	//initialize dynamic arrays for each animal type
	m_tigers = new Tiger[STARTING_CAPACITY];
	m_penguins = new Penguin[STARTING_CAPACITY];
	m_turtles = new Turtle[STARTING_CAPACITY];

	tigerCost = Tiger::getCost();					//optimization step to pull class cost info into zoo class
	penguinCost = Penguin::getCost();			
	turtleCost = Turtle::getCost();



	buildMenus();
	init();
}

Zoo::~Zoo()
{
	delete[] m_tigers;
	delete[] m_penguins;
	delete[] m_turtles;
}



/*
Function to return the state of the 'pens' of animals. If any of the pens are full
true is returned.

Return:
	bool - state of the pens of the zoo
*/
bool Zoo::isFull() const
{
	if (tigerCount == tigerArraySize || 
		penguinCount == penguinArraySize || 
		turtleCount == turtleArraySize) {
		return true;
	}
	return false;
}


/*
Takes a current pointer to the tiger array, creates an array twice the size, copies all previous tiger instances over
deletes the old animal array, doubles the size of the passed size variable,
and sets the old pointer to the new double arrayed size
*/
void Zoo::resizeTigerArray(Tiger*& animalArray, int& size) {

	//allocate memory for twice the current array size
	Tiger* arr = new Tiger[size * 2];
	
	//copy old elements to new array
	for (int i = 0; i < tigerCount; i++) {
		arr[i] = animalArray[i];
	}

	//delete old tiger array
	delete[] animalArray;

	//double size index of array
	size = size * 2;

	//set pointer to new array of double size
	animalArray = arr;

	//safely set the new pointer to 0
	arr = 0;
}


/*
See resizeTigerArray
*/
void Zoo::resizePenguinArray(Penguin *& animalArray, int &size)
{
	//allocate memory for twice the current array size
	Penguin* arr = new Penguin[size * 2];

	//copy old elements to new array
	for (int i = 0; i < penguinCount; i++) {
		arr[i] = animalArray[i];
	}

	//delete old penguin array
	delete[] animalArray;



	//double size index of array
	size = size * 2;

	//set pointer to new array of double size
	animalArray = arr;

	//safely set the new pointer to 0
	arr = 0;
}


/*
See resizeTigerArray
*/
void Zoo::resizeTurtleArray(Turtle *& animalArray, int &size)
{
	//allocate memory for twice the current array size
	Turtle* arr = new Turtle[size * 2];

	//copy old elements to new array
	for (int i = 0; i < turtleCount; i++) {
		arr[i] = animalArray[i];
	}

	//delete old turtle array
	delete[] animalArray;

	//double size index of array
	size = size * 2;

	//set pointer to new array of double size
	animalArray = arr;

	//safely set the new pointer to 0
	arr = 0;
}



/*
Generates a random number between min and max and returns the value

Param:
	min - min number to roll
	max - max number to roll

Return - random int between min/max
*/
int Zoo::generateRandom(const int& min, const int& max) const
{

	int toReturn = rand();
	//old:(toReturn % (min + max)) - min;
	toReturn = (toReturn % (max - min + 1)) + min;

	return toReturn;

}


/*
Adds a quantity of tigers to a pen in the zoo. Sets them to a certain age.
Checks to see if the animal pen needs to be resized, if so, calls resize method
*/
void Zoo::addTiger(const int &quantity, int age)
{

	for (int i = 0; i < quantity; i++) {
		if (tigerCount < tigerArraySize - 1) {	//if less tigers than capacity
			tigerCount++;
		}
		else {
			resizeTigerArray(m_tigers, tigerArraySize); //resize
			tigerCount++;
		}
		m_tigers[tigerCount - 1].setAge(age);

	}

	

}


/*
Adds a quantity of penguins to a pen in the zoo. Sets them to a certain age.
Checks to see if the animal pen needs to be resized, if so, calls resize method
*/
void Zoo::addPenguin(const int &quantity, int age)
{
	
	for (int i = 0; i < quantity; i++) {
		if (penguinCount < penguinArraySize - 1) {	//if less tigers than capacity
			penguinCount++;
		}
		else {
			resizePenguinArray(m_penguins, penguinArraySize); //resize
			penguinCount++;
		}
		m_penguins[penguinCount - 1].setAge(age);
	}

}


/*
Adds a quantity of turtles to a pen in the zoo. Sets them to a certain age.
Checks to see if the animal pen needs to be resized, if so, calls resize method
*/
void Zoo::addTurtle(const int &quantity, int age)
{

	for (int i = 0; i < quantity; i++) {

		if (turtleCount < turtleArraySize - 1) {	//if less tigers than capacity
			turtleCount++;
		}
		else {
			resizeTurtleArray(m_turtles, turtleArraySize); //resize
			turtleCount++;
		}
		m_turtles[turtleCount - 1].setAge(age);
	}

}


/*
Removes a random tiger from the zoo. The method works by randomly picking
a tiger between 0 and tigercount-1 (an element in the tiger array), sets the age to 1 (bebug purpose)
and returns a true or false value depending on if the animal could be removed or not.
*/
bool Zoo::removeTiger()
{
	if (tigerCount > 0) {
		//generate random number between 0 and (tigerCount - 1)
		int randIndex = generateRandom(0, tigerCount - 1);


		//set to-be-removed animal to default age
		m_tigers[randIndex].setAge(1);

		//swap to-be-removed animal with last 'owned' animal
		m_tigers[randIndex] = m_tigers[tigerCount - 1];

		//decrement tiger count
		--tigerCount;
		
		return true; //animal was able to be removed
	}
	else {
		return false; //animal was unable to be removed
	}
}


/*
See removeTiger()
*/
bool Zoo::removePenguin()
{
	if (penguinCount > 0) {
		//generate random number between 0 and (tigerCount - 1)
		int randIndex = generateRandom(0, (penguinCount - 1));


		//set to-be-removed animal to default age
		m_penguins[randIndex].setAge(1);

		//swap to-be-removed animal with last 'owned' animal
		m_penguins[randIndex] = m_penguins[tigerCount - 1];

		//decrement tiger count
		--penguinCount;

		return true; //animal was able to be removed
	}
	else {
		return false; //animal was unable to be removed
	}

}


/*
See removeTiger()
*/
bool Zoo::removeTurtle()
{
	if (turtleCount > 0) {
		//generate random number between 0 and (tigerCount - 1)
		int randIndex = generateRandom(0, (turtleCount - 1));


		//set to-be-removed animal to default age
		m_turtles[randIndex].setAge(1);

		//swap to-be-removed animal with last 'owned' animal
		m_turtles[randIndex] = m_turtles[turtleCount - 1];

		//decrement tiger count
		--turtleCount;

		return true; //animal was able to be removed
	}
	else {
		return false; //animal was unable to be removed
	}
}


/*
Loops through each pen of the zoo class and incremements the age of all animal-type
objects
*/
void Zoo::ageAnimals()
{

	for (int i = 0; i < tigerCount; i++) {
		m_tigers[i].incrementAge();
	}

	for (int i = 0; i < penguinCount; i++) {
		m_penguins[i].incrementAge();
	}

	for (int i = 0; i < turtleCount; i++) {
		m_turtles[i].incrementAge();
	}

}


/*
Initializes the zoo:
	-gets starting amount of animals from the user (in groups of 1 or 2)
	-makes sure the zoo has at least 1 or 2 of each animal to start the simulation

*/
void Zoo::init() {

	//start game
	bool goodStart = false;
	int userChoice;

	//while user has not purchased at least 1 animal
	while (!goodStart) {

		startMenu.displayMessage("Purchase at least 1 of each animal to continue.");
		startMenu.displayMessage("\tBalance: " + getPlayerMoney());
		switch (startMenu.getUserChoice()) {

			case 1:
				//set starting tigers
				startQuantityMenu.displayMessage("1 or 2?");
				userChoice = startQuantityMenu.getUserChoice();

				if (playerCanBuy(userChoice * tigerCost)) {			//checks to see if the player can afford the quantity of animal type
					addTiger(userChoice, 1);
					bound_player.buy(userChoice * tigerCost);		//purchase action
				}
				else {
					output << "Not enough money" << std::endl;
				}

				break;

			case 2:
				//set starting penguins
				startQuantityMenu.displayMessage("1 or 2?");
				userChoice = startQuantityMenu.getUserChoice();

				if (playerCanBuy(userChoice * penguinCost)) {		//checks to see if the player can afford the quantity of animal type
					addPenguin(userChoice, 1);
					bound_player.buy(userChoice * penguinCost);		//purchase action
				}
				else {
					output << "Not enough money" << std::endl;
				}

				break;

			case 3:
				//set starting turtles
				startQuantityMenu.displayMessage("1 or 2?");
				userChoice = startQuantityMenu.getUserChoice();

				if (playerCanBuy(userChoice * turtleCost)) {		//checks to see if the player can afford the quantity of animal type
					addTurtle(userChoice, 1);
					bound_player.buy(userChoice * turtleCost);		//purchase action
				}
				else {
					output << "Not enough money" << std::endl;
				}

				break;
		}

		if (tigerCount >= 1 && penguinCount >= 1 && turtleCount >= 1) {		//make sure player has at least 1 of each animal
			goodStart = true;
		}
	}
	


}



/*
Helper function to build all the necessary menu prompts that will be needed for the game
*/
void Zoo::buildMenus()
{
	startMenu.addPrompt("Purchase Tiger:   ");
	startMenu.addPrompt("Purchase Penguin: ");
	startMenu.addPrompt("Purchase Turtle:  ");

	startQuantityMenu.addPrompt("Purchase 1");
	startQuantityMenu.addPrompt("Purchase 2");

	dailyBuyPromptMenu.addPrompt("Would you like to buy an adult animal? (y/n)");

	dailyBuyMenu.addPrompt("Purchase adult Tiger:   ");
	dailyBuyMenu.addPrompt("Purchase adult Penguin: ");
	dailyBuyMenu.addPrompt("Purchase adult Turtle:  ");

	repeatMenu.addPrompt("Continue");
	repeatMenu.addPrompt("Exit");


}


/*
Checks to see if the player has enough money to make the purchase

Param:
	cost - purchase to be made

Return:
	bool - truth value of player purchase action
*/
bool Zoo::playerCanBuy(double cost) const
{
	if (bound_player.getBalance() - cost >= 0) {
		return true;
	}
	else {
		return false;
	}
}


/*
Simulate the zoo, each loop in the 'while' statement is one day of the zoo.

A simple day loop consists of the following actions:
	-age the animals
	-player feeds the animals (pays feeding cost)
	-generate a random event to take place
	-calculate daily profit, add to players balance
	-prompt user to purchase 1 adult animal
	
*/
void Zoo::start()
{
	int userChoice = 0;				//current user choice
	bool playerBroke = false;		//determins if player loses game
	char playerBuyChoice;			//y/n store variable for user



	double bonus;
	double dailyProfit;



	//check that the player didn't buy too many animals at the start:
	if (!playerCanBuy(getFeedCost())) {
		output << "GAME OVER: You cannot afford feed cost of " << getFeedCost()
			<< " with current balance of " << bound_player.getBalance();
		return;
	}




	while ((userChoice != repeatMenu.getExitCode())) {	//game loop, exit only if player gives exit code
		
		bonus = 0.0;			//reset profit variables for the day
		dailyProfit = 0.0;


		printAnimalContents();			//debug purposes



		//format and display player balance and day Number
		output << "\n\n\n";
		output << "[DAY: " << dayCount << "]";
		output << "\tYour Balance: " << bound_player.getBalance() << "\n" << std::endl;
		

		//age all the animals
		ageAnimals();



		//user needs to pay feeding cost (calculate feed cost)
		bound_player.buy(getFeedCost());
		output << "You paid " << getFeedCost() << " in feeding costs.\n" << std::endl;



		//get a random number for a random event
		switch (static_cast<EVENT_TYPE>(generateRandom(0, 3))) { //generate event between [sick_event - nothing]

		case SICK_EVENT:
			removeAnimalEvent();			//remove an animal to sickness
			break;


		case ATTENDANCE_EVENT:
			bonus = attendanceBoomEvent();	//calculate bonus money from event
			break;


		case BABY_EVENT:
			animalBirthEvent();
			break;


		case NOTHING:
			output << "[Day] " << dayCount << std::endl;
			output << "\t";
			output << "Nothing eventful happened today." << std::endl;
			break;


		}

		//calculate profit for the day (sum of (animalValue * animalCount) + tiger event bonus
		dailyProfit = (m_tigers[0].getPayoffValue() * tigerCount) + bonus
			+ (m_penguins[0].getPayoffValue() * penguinCount)
			+ (m_turtles[0].getPayoffValue() * turtleCount);


		//display profit for the user
		output << std::endl;
		output << "Profits for day: " << dayCount << "\n"
			<< "\tFrom Tigers:   " << (m_tigers[0].getPayoffValue() * tigerCount) << "\tBonus: " << (bonus) << "\n"
			<< "\tFrom Penguins: " << (m_penguins[0].getPayoffValue() * penguinCount) << "\n"
			<< "\tFrom Turtles:  " << (m_turtles[0].getPayoffValue() * turtleCount) << "\n"
			<< "\tTOTAL:         " << (dailyProfit) << "\n\n" << std::endl;;



		//add the zoo profits to player balance
		bound_player.deposit(dailyProfit);



		//ask player if they would like to buy an adult animal, if they do, ask for animal type
		//add the ADULT animal to the zoo and subtract cost
		playerBuyChoice = validateInputYN(dailyBuyPromptMenu.getPrompt(1));
		if (playerBuyChoice == 'y') {
			switch (dailyBuyMenu.getUserChoice()) {
			case 1:
				output << "\nYou have purchased an adult tiger!\n " << std::endl;
				addTiger(1, ADULT);
				bound_player.buy(m_tigers[0].getCost());
				break;

			case 2:
				output << "\nYou have purchased an adult penguin!\n " << std::endl;
				addPenguin(1, ADULT);
				bound_player.buy(m_penguins[0].getCost());
				break;

			case 3:
				output << "\nYou have purchased an adult turtle!\n " << std::endl;
				addTurtle(1, ADULT);
				bound_player.buy(m_turtles[0].getCost());
				break;
			}

		}


		//check if player has enough money to pay for feeding cost for next round
		if (!playerCanBuy(getFeedCost())) {
			playerBroke = true;
			output << "GAME OVER: You cannot afford feed cost of " << (getFeedCost())
				<< " with current balance of " << bound_player.getBalance();
			return;
		}
		else {
			//check to see if the player would like to exit
			repeatMenu.displayMessage("Would you like to continue playing? ");
			userChoice = repeatMenu.getUserChoice();
		}
		dayCount++;

	}
}


/*
Calculate total feed cost of the zoo

Sum of (number of animals * feed cost per animal)

*/
double Zoo::getFeedCost()
{
	double total = 0;

	//cost of tigers:
	total += (tigerCount * m_tigers[0].getFeedCost());

	//cost of penguins
	total += (penguinCount * m_penguins[0].getFeedCost());

	//cost of turtles
	total += (turtleCount * m_turtles[0].getFeedCost());

	return total;
}


/*
Event that simulates the removal of an animal from the zoo.

The function picks an animal type to remove randomly, if the player does not have any of the 
animal type selected (from the truth value of the remove function), nothing happens.

*/
void Zoo::removeAnimalEvent()
{
	switch (generateRandom(1, 3)) {
		output << "[Day: " << (dayCount) << "]"  "   (Event)" << std::endl;
		output << "\t";

	//tiger death
	case 1:
		if (removeTiger()) {		//if a tiger can be removed, remove it and print
			output << "A sudden sickness has affected the tigers, one has died. " << std::endl;
		}
		else {
			output << "You hear rumors of tigers being affected by a sickness, but you don't own any!" << std::endl;
		}
		break;

	//penguin death
	case 2:
		if (removePenguin()) {		//if a penguin can be removed, remove it and print
			output << "A sudden sickness has affected the penguins, one has died. " << std::endl;
		}
		else {
			output << "You hear rumors of penguins being affected by a sickness, but you don't own any!" << std::endl;
		}
		break;

	//turtle death
	case 3:
		if (removeTurtle()) {		//if a turtle can be removed, remove it and print
			output << "A sudden sickness has affected the turtle, one has died. " << std::endl;
		}
		else {
			output << "You hear rumors of turtles being affected by a sickness, but you don't own any!" << std::endl;
		}
		break;
	}

	output << std::endl;

}




/*
Function that simulates an attendance boom event at the zoo.

Calculates a bonus based on the number of tigers and a random amount (250-500) for each tiger.

for each tiger
	-generate random number
	-add to total

Return:
	double - the calcuated bonus from all tigers
*/
double Zoo::attendanceBoomEvent()
{

	output << "[Day: " << (dayCount) << "]"  "   (Event)" << std::endl;
	output << "\t";

	double bonusReturn = 0.0;
	int tigerBonus;

	//calculate the bonus money from an attendence boom
	if (tigerCount == 0) {
		output << "A boom in attendance occured at your zoo, but the guests wanted to see tigers." << std::endl;
	}
	else {
		output << "A boom in attendance occured at your zoo, each tiger produced extra money!" << std::endl;
		for (int i = 0; i < tigerCount; i++) {
			//for each tiger, generate a random bonus
			tigerBonus = generateRandom(250, 500);
			bonusReturn += tigerBonus;
		}
	}

	output << "\tBonus Money: " << (bonusReturn) << std::endl;

	output << std::endl;

	return bonusReturn;
}



/*
Function that simulates an animal birth at the zoo.

Checks to see if the zoo has an available adult in any pen, if it does the first available
adult between tiger, penguin, and turtle type is returned. -1 is returned for no adults

If no adults, then function simply returns

The function then generates a random number corresponding to an animal type
	The animal type is then checked to see if there is an available adult
	if there is an available adult
		add animals with age 0 depending on the animal birth constant

If the random function picks an animal type that does not have an adult, the function
defaults to the value returned by the zooAdultState function, and that animal type has the birth.
*/
void Zoo::animalBirthEvent()
{
	output << "[Day: " << (dayCount) << "]"  "   (Event)"<< std::endl;
	output << "\t";
	
	int zooAdultState = zooHasAdult();		//get information on available adults in zoo

	if (zooAdultState == -1) {				//no adults available in the zoo
		output << "You hear tales of other zoos having a population boom today..." << std::endl;
		return;
	}


	//pick an animal type to have a baby
	ANIMAL_TYPE animalType = static_cast<ANIMAL_TYPE>(generateRandom(0, 2));


	//check that the zoo contains an adult animal of that type:
	if (hasAdult(animalType)) {
		//generate baby event from randomly picked animal adult
		switch (animalType) {
		case TIGER:
			output << "A tiger has given birth to " << (m_tigers[0].getNumberOfBabies()) << " babie(s)!" << std::endl;
			addTiger(m_tigers[0].getNumberOfBabies(), BABY);		//get baby-factor from class, add then to the pen with age 0
			break;

		case PENGUIN:
			output << "A penguin has given birth to " << (m_penguins[0].getNumberOfBabies()) << " babie(s)!" << std::endl;
			addPenguin(m_penguins[0].getNumberOfBabies(), BABY);	//get baby-factor from class, add then to the pen with age 0
			break;

		case TURTLE:
			output << "A turtle has given birth to " << (m_turtles[0].getNumberOfBabies()) << " babie(s)!" << std::endl;
			addTurtle(m_turtles[0].getNumberOfBabies(), BABY);		//get baby-factor from class, add then to the pen with age 0
			break;
		}



	}
	else {
		//generate a baby event from the guarenteed adult returned from zooAdultState
		switch (zooAdultState) {
		case TIGER:
			output << "A tiger has given birth to " << (m_tigers[0].getNumberOfBabies()) << " babies!" << std::endl;
			addTiger(m_tigers[0].getNumberOfBabies(), BABY);		//get baby-factor from class, add then to the pen with age 0
			break;

		case PENGUIN:
			output << "A penguin has given birth to " << (m_penguins[0].getNumberOfBabies()) << " babies!" << std::endl;
			addPenguin(m_penguins[0].getNumberOfBabies(), BABY);	//get baby-factor from class, add then to the pen with age 0
			break;

		case TURTLE:
			output << "A turtle has given birth to " << (m_turtles[0].getNumberOfBabies()) << " babies!" << std::endl;
			addTurtle(m_turtles[0].getNumberOfBabies(), BABY);		//get baby-factor from class, add then to the pen with age 0
			break;
		}
	}

	output << std::endl;
}



/*
Function to check to see if the zoo has an adult of the given animal type

Loops through each respective animal array and returns true if an adult is found, false if not

Param:
	animalType - type of animal to check adult state for

Return:
	bool - truth value of if an adult animal of that type exists
*/
bool Zoo::hasAdult(ANIMAL_TYPE animalType)
{
	switch (animalType) {
	case TIGER:
		for (int i = 0; i < tigerCount; i++) {
			if (m_tigers[i].isAdult()) {	//check for animal adults
				return true;
			}
		}
		return false;

	case PENGUIN:
		for (int i = 0; i < tigerCount; i++) {
			if (m_penguins[i].isAdult()) {	//check for animal adults
				return true;
			}
		}
		return false;

	case TURTLE:
		for (int i = 0; i < tigerCount; i++) {
			if (m_turtles[i].isAdult()) {	//check for animal adults
				return true;
			}
		}
		return false;
	}

	return false;
}


/*
Function that checks to see if there is at least 1 adult in the zoo.

int - code that tells calling function information about the state of adults in the zoo
	-1 - no adults in the zoo
	 0 - A tiger adult is available
	 1 - No tiger adults, but penguin adults available
	 2 - No tiger adults and no penguin adults, but turtle adult available

*/
int Zoo::zooHasAdult()
{
	if (hasAdult(TIGER)) {
		return TIGER;
	}
	else if (hasAdult(PENGUIN)){
		return PENGUIN;
	}
	else if (hasAdult(TURTLE)) {
		return TURTLE;
	}
	else {
		return -1;
	}
}

