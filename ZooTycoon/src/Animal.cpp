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

#include "Animal.hpp"


/*Default constructor*/
Animal::Animal() :
	age(1), cost(5000), number_of_babies(2), base_food_cost(5.0), payoff(0.20) {}


/*Argument constructors (NOT USED IN PROJECT)*/
Animal::Animal(int age, double cost, int number_of_babies, double base_food_cost, double payoff) :
	age(age), cost(cost), number_of_babies(number_of_babies), base_food_cost(base_food_cost), payoff(payoff) {}


/*Argument constructors (NOT USED IN PROJECT)*/
Animal::Animal(int age, double cost, int number_of_babies, double base_food_cost) :
	age(age), cost(cost), number_of_babies(number_of_babies), base_food_cost(base_food_cost) {}


/*
Incrememnts age of animal
*/
void Animal::incrementAge()
{
	++age;
}

int Animal::getAge() const
{
	return age;
}

double Animal::getPayoff() const
{
	return payoff * cost;
}

void Animal::setAge(const int &value)
{
	age = value;
}


/*
Checks to see if animal has an age of >= 3
*/
bool Animal::isAdult() const
{
	return age >= ADULT_AGE;
}

int Animal::getNumberOfBabies() const
{
	return number_of_babies;
}

