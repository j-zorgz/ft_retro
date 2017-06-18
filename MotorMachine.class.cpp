#include "MotorMachine.class.hpp"
#include <iostream>
#include <unistd.h>
#include <fstream>

MotorMachine::MotorMachine(void) : _tab(NULL), _amount(0){
}

MotorMachine::MotorMachine(MotorMachine const & src) : _amount(src._amount){
	if (this->_tab)
		delete [] this->_tab;
	this->_tab = new AMovable*[src._amount];
	for (unsigned int i = 0; i < src._amount; i++) {
		this->_tab[i] = src._tab[i]->clone();
	}
}

MotorMachine::~MotorMachine(void) {
	if (this->_tab)
		delete [] this->_tab;
}

MotorMachine & MotorMachine::operator=(MotorMachine const & rhs) {
	if (this->_tab)
		delete [] this->_tab;
	this->_amount = rhs._amount;
	this->_tab = new AMovable*[rhs._amount];
	for (unsigned int i = 0; i < rhs._amount; i++) {
		this->_tab[i] = rhs._tab[i]->clone();
	}
	return (*this);
}

void	MotorMachine::moveAll(RenderMachine &render) {
	std::fstream log("log", std::fstream::out | std::fstream::app);
	for (unsigned int i = 0; i < this->_amount; i++) {
		(this->_tab[i])->move();
		for (unsigned int y = 0; y < this->_amount; y++) {
			if (y != i && this->_tab[i] != NULL && this->_tab[y] != NULL){
				if ((this->_tab[i])->doesCollide(this->_tab[y])){
					AMovable* 	ptr = this->_tab[y];
					this->_tab[i]->takeDamage(this->_tab[y]->getDamage());
					this->_tab[y]->takeDamage(this->_tab[i]->getDamage());
					if (this->_tab[i]->getHealth() == 0){
						log << "trying to remove item at " << this->_tab[i] << ". (first if)" << std::endl;
						AMovable*	ptr2 = this->_tab[i];
						render.removePrintable(this->_tab[i]);
						this->removeMovable(this->_tab[i]);
						delete ptr2;
					}
					if (ptr->getHealth() == 0){
						log << "trying to remove item at " << ptr << ". (second if)" << std::endl;
						render.removePrintable(ptr);
						this->removeMovable(ptr);
						delete ptr;
					}
				}
			}
		}
	}
	log.close();
}

void	MotorMachine::moveAllExcept(AMovable *obj, RenderMachine &render) {
	std::fstream log("log", std::fstream::out | std::fstream::app);
	for (unsigned int i = 0; i < this->_amount; i++) {
		// std::cout << "i : " << i << std::endl;
		if (this->_tab[i] != obj && this->_tab[i] != NULL){
			(this->_tab[i])->move();
			for (unsigned int y = 0; y < this->_amount; y++) {
				if (y != i && this->_tab[i] != NULL && this->_tab[y] != NULL){
					if ((this->_tab[i])->doesCollide(this->_tab[y])){
						AMovable* 	ptr = this->_tab[y];
						this->_tab[i]->takeDamage(this->_tab[y]->getDamage());
						this->_tab[y]->takeDamage(this->_tab[i]->getDamage());
						if (this->_tab[i]->getHealth() == 0){
							log << "trying to remove item at " << this->_tab[i] << ". (first if)" << std::endl;
							AMovable*	ptr2 = this->_tab[i];
							render.removePrintable(this->_tab[i]);
							this->removeMovable(this->_tab[i]);
							delete ptr2;
						}
						if (ptr->getHealth() == 0){
							log << "trying to remove item at " << ptr << ". (second if)" << std::endl;
							render.removePrintable(ptr);
							this->removeMovable(ptr);
							delete ptr;
						}
					}
				}
			}
		}
	}
	log.close();
}

void	MotorMachine::addMovable(unsigned int idx, AMovable *obj) { // TO DO : Tester quand les iprintable seront fonctionels.
	if (idx > this->_amount + 1) {
		std::cout << "There was an error while trying to ADD a movable on the MotorMachine at position " << idx << ". There are only " << this->_amount << " movables in the table." << std::endl;
		return ;
	}
	// std::cout << "id : " << idx << std::endl;
	if (this->_amount == 0) {
		if (this->_tab != NULL) { //_tab is supposed to be null if _amount == 0, but still..
			delete [] this->_tab;
		}
		this->_tab = new AMovable*[1];
		this->_tab[0] = obj;
		this->_amount = 1;
		return ;
	}

	AMovable **new_tab = new AMovable*[this->_amount + 1];
	unsigned int i;

	for (i = 0; i < idx; i++) {
		new_tab[i] = this->_tab[i];
	}
	new_tab[i] = obj;
	i++;
	for (; i < this->_amount; i++) {
		new_tab[i] =this->_tab[i - 1];
	}
	delete [] this->_tab;
	this->_tab = new_tab;
	this->_amount++;
}

void	MotorMachine::addMovable(AMovable *obj) {
	this->addMovable(this->_amount, obj);
}

void	MotorMachine::removeMovable(unsigned int idx) {
	if (idx >= this->_amount) {
		std::cout << "There was an error while trying to REMOVE a movable on the MotorMachine at position " << idx << ". There are only " << this->_amount << " movables in the table." << std::endl;
		return ;
	}

	AMovable		**new_tab = new AMovable*[this->_amount - 1];
	unsigned int	i;

	for (i = 0; i < idx ; i++) {
		new_tab[i] = this->_tab[i];
	}
	i++;
	for (; i < this->_amount; i++) {
		new_tab[i - 1] = this->_tab[i];
	}
	if (this->_tab)
		delete [] this->_tab;
	else
		std::cout << "You aren't supposed to be here. There probably was an error.. " << std::endl;
	this->_tab = new_tab;
	this->_amount--;
}

void	MotorMachine::removeMovable(AMovable *obj) {
	for (unsigned int i = 0; i < this->_amount; i++) {
		if (this->_tab[i] == obj) {
			std::cout << "Object found at position " << i <<std::endl;
			this->removeMovable(i);
			return ;
		}
	}
	std::cout << "There was an error while trying to REMOVE a movable." << std::endl;
}

AMovable	*MotorMachine::getMovable(unsigned int idx) {
	if (idx >= this->_amount) {
		std::cout << "There was an error while trying to GET a movable on the MotorMachine at position " << idx << ". There are only " << this->_amount << " printables in the table. Returning NULL." << std::endl;
		return NULL;
	}
	return (this->_tab[idx]);
}

unsigned int	MotorMachine::getAmount(void) const {
	return (this->_amount);
}

void					MotorMachine::describe() {
	for (unsigned int i = 0; i < this->_amount; i++) {
		std::cout << "[" << i << "] : " << this->_tab[i] << std::endl;
	}
}
