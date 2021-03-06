#ifndef TURTLE_HPP
#define TURTLE_HPP

/*************************************************************
*	Author: Martin Edmunds
*	Email: edmundsm@oregonstate.edu
*	Class: CS 162-400
*	Date: 01/27/19
*	Project: Project 2
*
*	Description: Turtle class, defines age, cost, babies, foodx,
*	payoff value for the turtle class. The payoff value is precalculates
*	and stored as a variable to improve run-time speed.

INHERITS FROM ANIMAL
**************************************************************/

#include "Animal.hpp"


#define		DEFAULT_TURTLE_AGE					1
#define		DEFAULT_TURTLE_COST					100
#define		DEFAULT_TURTLE_BABIES				10
#define		DEFAULT_TURTLE_FOOD_MULTIPLIER		0.5
#define		DEFAULT_TURTLE_PAYOFF				0.05

class Turtle : public Animal {


private:

	double feedCost;		//feed_multiplier * food_base_constant
	double payoffValue;		//default payoff  * default cost




public:

	Turtle();

	double getFeedCost() const;

	double getPayoffValue() const;

	void printTurtle() {
		std::cout << "Turtle: " << this << " Age: " << this->age << std::endl;
	}

	static double getCost();



};


#endif