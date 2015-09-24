//
// Game.cpp
// Authors: Hunter Wills, Tung Tran
// 
//
//#include "stdafx.h"       //INCLUDE FOR VISUAL STUDIO
#include "Game.h"
#include "FiveCardDraw.h"

//initialize game pointer
shared_ptr<Game> Game::game = nullptr;

//
// Game::instance()
// return a copy of the static Game::game if it is not nullptr
// throw instance_not_available error otherwise
//
shared_ptr<Game> Game::instance()
{
	if (game == nullptr){
		throw errors::instance_not_available;
	}
	else {
		return game; 
	}
}

//
// Game::start_game
// take in a string that represents the name of the game
// if the game pointer is not nullptr, throw game_already_started error
// if not, init game pointer to corresponding game (or throw unknown_game if  
// the game is not recognized)
//
void Game::start_game(const string name)
{
	const string fiveCardDrawName = "FiveCardDraw";
	if (game == nullptr) {
		if (name == fiveCardDrawName) {
			game = make_shared<FiveCardDraw>(FiveCardDraw());
		}
		else{
			throw errors::unknown_game;
		}
	}
	else {
		throw errors::game_already_started;
	}
}

//
// Game::stop_game()
// if there is a game in progress, stop the game by making its pointer point to nullptr
// otherwise, throw no_game_in_progress error
//
void Game::stop_game()
{
	if (game == nullptr) {
		throw errors::no_game_in_progress;
	}
	else {
		game = nullptr;
	}
}

//
// Game::add_player(const string name) 
// add a player with the name passed to the function to the game
// if the player already exists, throw already_playing error
//
void Game::add_player(const string name, bool isAI){
	bool nameInUse = false;
	for (auto it = players.begin(); it < players.end(); it++){
		if (name == (*it)->name){
			nameInUse = true;
			break;
		}
	}
	if (nameInUse) {
		throw errors::already_playing;
	}
	else {
		shared_ptr<Player> player = make_shared<Player>(name);
		player->isAI = isAI;
		players.push_back(player);
	}
}

//
// Game:: find_player
// given the name of the player, go through the list of players and find him/her
// if the player is in the game, return pointer to the player, nullptr otherwise
//
shared_ptr<Player> Game::find_player(const string name)
{
	for (auto it = players.begin(); it < players.end(); it++){
		if (name == (*it)->name){
			return *it;
		}
	}
	return nullptr;
}

//
// Game:: remove_player(const string name)
// given a name of a player, go through list of players in the game and remove 
// that player
//
void Game::remove_player(const string name)
{
	for (auto it = players.begin(); it < players.end(); it++){
		if (name == (*it)->name){
			players.erase(it);
			break;
		}
	}
}

int Game::before_turn(Player & player){
	return 0;
}
int Game::turn(Player & player){
	return 0;
}
int Game::after_turn(Player & player){
	return 0;
}
int Game::before_round(){
	cout << "g" << endl;
	return 0;
}
int Game::round(){
	return 0;
}
int Game::after_round(){
	return 0;
}
int Game::numPlayers(){
	return players.size();
}
