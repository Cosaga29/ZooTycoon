#ifndef TIGER_HPP
#define TIGER_HPP

/*************************************************************
*	Author: Martin Edmunds
*	Email: edmundsm@oregonstate.edu
*	Class: CS 162-400
*	Date: 01/27/19
*	Project: Project 2
*
*	Description: Tiger class, defines age, cost, babies, foodx,
*	payoff value for the tiger class. The payoff value is precalculates
*	and stored as a variable to improve run-time speed.

INHERITS FROM ANIMAL
**************************************************************/


#include "Animal.hpp"


#define		DEFAULT_TIGER_AGE					1
#define		DEFAULT_TIGER_COST					10000
#define		DEFAULT_TIGER_BABIES				1
#define		DEFAULT_TIGER_FOOD_MULTIPLIER		5
#define		DEFAULT_TIGER_PAYOFF				0.2

class Tiger	: public Animal{



private:

	double feedCost;		//feed_multiplier * food_base_constant
	double payoffValue;		//default payoff  * default cost


public:

	Tiger();

	double getFeedCost() const;

	double getPayoffValue() const;

	void printTiger() {
		std::cout << "Tiger " << this << " Age: " << this->age << std::endl;
	}

	static double getCost();


};


#endif