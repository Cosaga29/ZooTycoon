/*************************************************************
*	Author: Martin Edmunds
*	Email: edmundsm@oregonstate.edu
*	Class: CS 162-400
*	Date: 01/27/19
*	Project: Project 2
*
*	Description:
**************************************************************/

#ifndef PLAYER_HPP
#define PLAYER_HPP

class Player {

private:

	double balance;



public:

	Player();

	Player(double);

	double getBalance() const;	//return the players money

	void buy(double);			//player buys something, withdraw money 

	void deposit(double);		//perform a deposit action

};


#endif