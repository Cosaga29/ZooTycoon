/*************************************************************
*	Author: Martin Edmunds
*	Email: edmundsm@oregonstate.edu
*	Class: CS 162-400
*	Date: 01/27/19
*	Project: Project 2
*
*	Description:
**************************************************************/

#include "Player.hpp"

Player::Player() :
	balance(100000) {}

Player::Player(double value) :
	balance(value) {}

double Player::getBalance() const
{
	return balance;
}

void Player::buy(double value)
{
	balance -= value;
}

void Player::deposit(double value)
{
	balance += value;
}
