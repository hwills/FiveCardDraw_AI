//
// main.cpp
// Authors: Hunter Wills, Tung Tran
// 
//
//#include "stdafx.h"       //INCLUDE FOR VISUAL STUDIO
#include "FiveCardDraw.h"

int main(int argc, char * argv[])
{
	try{
		if (argc < req_args){
			//user entered too few arguments
			throw errors::usageError;
		}
		else{
				//user entered proper arguments, start the game
				Game::start_game(argv[gameNameIndex]);
				shared_ptr<Game> game = Game::instance();
				const int AIOffset = 1;
				const int beginIndex = 0;
				
				//adding players who want to join from the argument list
				for (int i = firstPlayerIndex; i < argc; ++i){
					string playerName = argv[i];
					bool isAI = ((playerName[playerName.size() - AIOffset]) == ('*'));	//if the last character in the player's name is a '*' then we make the player into an AI
					if (isAI)
					{
						playerName = playerName.substr(beginIndex, playerName.size() - AIOffset);
					}
					game->add_player(playerName, isAI);
					
				}

				//playing game
				while (game->numPlayers() >= req_players){
					game->before_round();
					game->round();
					game->after_round();
				}
		
		}
	}
	catch (errors e){
		switch (e) {
		case (errors::fileOpenError) :
			usage_message(argv[programNameIndex], "File Open Error");
			break;
		case (errors::cardReadError) :
			usage_message(argv[programNameIndex], "Card Read Error!");
			break;
		case (errors::usageError) :
			usage_message(argv[programNameIndex], "Not enough arguments! Please supply the game name and at least two players (different names)");
			break;
		case (errors::shuffleUsageError) :
			usage_message(argv[programNameIndex], "Problem using shuffle!");
			break;
		case (errors::wrongArgsError) :
			usage_message(argv[programNameIndex], "Wrong Argument Error");
			break;
		case (errors::noArgsError) :
			usage_message(argv[programNameIndex], "Why don't you pass me more arguments :(");
			break;
		case (errors::manyArgsError) :
			usage_message(argv[programNameIndex], "Too many arguments. Computer will self destruct in 10...");
			break;
		case (errors::not_enough_cards) :
			usage_message(argv[programNameIndex], "Woah there buddy, we need more cards!");
			break;
		case (errors::index_out_of_bounds) :
			usage_message(argv[programNameIndex], "That index is wayyyyy out of bounds!");
			break;
		case (errors::instance_not_available) :
			usage_message(argv[programNameIndex], "Your instance is not available at this time please call 555-1212 for help.");
			break;
		case (errors::unknown_game) :
			usage_message(argv[programNameIndex], "I have no idea what kind of game you are trying to play, but I know FiveCardDraw, so we should do that.");
			break;
		case (errors::game_already_started) :
			usage_message(argv[programNameIndex], "YOU CAN'T PLAY TWO GAMES AT ONCE! (unless you are Chuck Norris, but you aren't Chuck Norris.)");
			break;
		case (errors::no_game_in_progress) :
			usage_message(argv[programNameIndex], "You have yet to begin any games at all!? What do you want me to do?");
			break;
		case (errors::already_playing) :
			usage_message(argv[programNameIndex], "Dude, we are already playing a game. Don't go trying to start up another one.");
			break;
		}
		return e;
	}
	catch (...){
		usage_message(argv[programNameIndex], "Unexpected error caught!");
		return errors::usageError;
	}
	return errors::noError;
}

