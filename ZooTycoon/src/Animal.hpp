#ifndef ANIMAL_HPP
#define ANIMAL_HPP

/*************************************************************
*	Author: Martin Edmunds
*	Email: edmundsm@oregonstate.edu
*	Class: CS 162-400
*	Date: 01/27/19
*	Project: Project 2
*
*	Description: Base class for Tigers, penguins, and turtles to be used
*	in the zoo class. Consists of an animal with an age and constants that
*	depenend on the implementing subclass.
**************************************************************/

#include <iostream>
#define BASE_FOOD_COST 10
#define ADULT_AGE		3


class Animal {

protected:

	int age;
	double cost;
	int number_of_babies;
	double base_food_cost;
	double payoff;


public:

	Animal();

	Animal(int, double, int, double, double);

	Animal(int, double, int, double);

	void incrementAge();

	int getAge() const;

	double getPayoff() const;

	void setAge(const int&);

	bool isAdult() const;

	int getNumberOfBabies() const;

};




#endif