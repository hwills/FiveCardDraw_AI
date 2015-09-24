//
// FiveCardDraw.cpp
// Authors: Hunter Wills, Tung Tran
// 
//

//#include "stdafx.h"       //INCLUDE FOR VISUAL STUDIO
#include "FiveCardDraw.h"
#include "Card.h"
#include <set>

using namespace std;
//
// FiveCardDraw::FiveCardDraw()
// default constructor
// initialize dealer_index to be the first player and push 52 cards to the main_deck
//
FiveCardDraw::FiveCardDraw() : dealer_index(0)
{
	int i;
	for (i = 0; i < numRanks; i++){
		int j;
		for (j = 0; j < numSuits; j++) {
			Card card((Card::rank)i, (Card::suit)j);
			main_deck.addCard(card);
		}
	}
}

//
// FiveCardDraw:: before_turn(Player & player)
// after dealing the cards to the players, print the names of the players and their hands
// then ask each player if they want to discard any card in their hand, if so, discard the 
// cards requested
//
int FiveCardDraw::before_turn(Player & player){
	if (player.isAI)
	{
		cout << endl;
		cout << "AI Player Taking Turn: " << player.name << endl;
		cout << "AI PLAYER'S HAND: " << endl << player.hand << endl;
		int handType = poker_type(player.hand);
		if (handType == poker_ranks::straightFlush || handType == poker_ranks::fullHouse || handType == poker_ranks::striaght || handType == poker_ranks::flush)
		{
			//receive no cards
		}
		else if (handType == poker_ranks::fourOfAKind || handType == poker_ranks::twoPairs || handType == poker_ranks::threeOfAKind || handType == poker_ranks::onePair)
		{
			//discard unmatched cards
			vector<int> cardCounts;
			const int firstPosition = 0;
			const int endPosition = 4;
			const int onlyOne = 1;
			const int nextCard = 1;
			for (auto it = player.hand.getCards().begin(); it != player.hand.getCards().end(); ++it)
			{
				int i = rank_count(&player.hand.getCards()[firstPosition], &player.hand.getCards()[endPosition] + nextCard, *it);
				cardCounts.push_back(i);
			}
			size_t offset = 0;
			size_t index = 0;
			for (auto it = cardCounts.begin(); it != cardCounts.end(); ++it)
			{
				if ((*it) == onlyOne)
				{
					size_t ri = index - offset;
					discard_deck.addCard(player.hand[ri]);
					player.hand.remove_card(ri);
					offset++;
				}
				index++;
			}
		}
		else
		{
			vector<int> toRemove;
			const int endPosition = 4;
			if (player.hand[endPosition].cardRank == Card::rank::ACE)
			{
				toRemove = { 0, 1, 2, 3 };
			}
			else
			{
				toRemove = { 0, 1, 2 };
			}
			const size_t firstCard = 0;
			for (auto it = toRemove.begin(); it != toRemove.end(); ++it)
			{
				size_t ri = firstCard;
				discard_deck.addCard(player.hand[ri]);
				player.hand.remove_card(ri);
			}
			//if has ace, discard other four cards
			//else discard three lowest
		}
	}
	else
	{
		cout << endl;
		cout << "CURRENT PLAYER: " << player.name << endl;
		cout << "YOUR HAND: " << endl << player.hand << endl;

		const vector<size_t> validIndex = { 0, 1, 2, 3, 4 };
		// removeIndex contains the indecies of the cards the current player want to discard
		set<size_t> removeIndex; //so it stays sorted and not duplicated
		string response;
		bool validResponse = false;
		while (!validResponse) {
			removeIndex.clear();
			cout << "Which cards do you want to discard?" << endl;
			getline(cin, response);
			validResponse = true;
			if (response == "") {
				//player doesn't want to change cards, do nothing
			}
			else {
				istringstream iss(response);
				string word;
				//going through the response to see if it is valid or not
				while (iss >> word && validResponse) {
					if (word.size() == 1 && isdigit(word[0])){
						size_t num = std::stoul(word, nullptr, 0);
						validResponse = false;
						for (auto it = validIndex.begin(); it != validIndex.end(); ++it) {
							if (num == *it) {
								validResponse = true;
								removeIndex.insert(num);
								break;
							}
						}
					}
					else{
						validResponse = false;
					}
				}
				if (validResponse) {
					// player gives a valid response, discard the card requested and deal them more card
					size_t offset = 0;
					for (auto it = removeIndex.begin(); it != removeIndex.end(); ++it) {
						size_t ri = *it - offset;
						discard_deck.addCard(player.hand[ri]);
						player.hand.remove_card(ri);
						offset++;
					}
				}
			}
		}
	}
	return errors::noError;
}

//
// FiveCardDraw::turn(Player & player)
// after a player discards their cards, deal him/her other cards to complete a hand
// throw not_enough_cards if both the main_deck and the discard_deck is out of cards
//
int FiveCardDraw::turn(Player &player){
	int num = player.hand.size();
	const int cardsPerPlayer = 5;
	const int empty = 0;
	while (num < cardsPerPlayer) {
		if (main_deck.size()==empty) {
			if (discard_deck.size() == empty) {
				return errors::not_enough_cards;
			}
			else {
				discard_deck.shuffle();
				player.hand << discard_deck;
			}
		}
		else {
			player.hand << main_deck;
		}
		num++;
	}
	return errors::noError;
}

//
// FiveCardDraw::after_turn(Player & player)
// print out players' name and their hands after a turn
//
int FiveCardDraw::after_turn(Player & player) {
	cout << player.name << endl;
	cout << player.hand << endl;
	return errors::noError;
}

//
// FiveCardDraw::before_round()
// shuffle the main_deck and deal cards to players (each has 5 cards)
//
int FiveCardDraw::before_round()
{
	cout << endl;
	cout << "The round is about to begin! Prepare to play some Five Card Draw!" << endl;
	main_deck.shuffle();
	int nextPlayer = 1;
	const unsigned int cardsPerPlayer = 5;
	int dealToIndex = dealer_index;
	if (players.size()*cardsPerPlayer > main_deck.size()){
		throw errors::not_enough_cards;
	}
	for (unsigned int j = 0; j < players.size(); ++j)
	{
		dealToIndex = (dealToIndex + nextPlayer) % players.size();
		while ((*players[dealToIndex]).hand.size() < cardsPerPlayer)
		{
			players[dealToIndex]->hand << main_deck;
		}
	}

	unsigned int i = 0;
	dealToIndex = dealer_index; 
	while (i < players.size())	
	{
		dealToIndex = (dealToIndex + nextPlayer) % players.size();
		before_turn(*players[dealToIndex]);
		i++;
	}
	return errors::noError;
}

//
// FiveCardDraw::round() 
// loop through the list of players and call after_turn on each of them
//
int FiveCardDraw::round()
{
	cout << endl;
	cout << "Here is what each player has after drawing their brand new CARDS!" << endl;
	unsigned int nextPlayer = 1;
	unsigned int i = 0;
	int dealToIndex = dealer_index; 
	while (i < players.size())
	{
		dealToIndex = (dealToIndex + nextPlayer) % players.size();
		int turnResult = turn(*players[dealToIndex]);
		if (turnResult!= errors::noError)
		{
			return turnResult;
		}
		after_turn(*players[dealToIndex]);
		i++;
	}
	return errors::noError;
}

//
// FiveCardDraw::after_round()
// sort and print out players by their hand strength (strongest to weakest)
// retrieve the cards from players for next game
// letting players to drop out of the game and other players to join
//
int FiveCardDraw::after_round()
{
	cout << endl;
	cout << "The round has come to a close here are the post round stats: " << endl;
	const int empty = 0;
	vector<shared_ptr<Player>> tmpPlayers(players);
	sort(tmpPlayers.begin(), tmpPlayers.end(), player_rank);
	for (auto it = tmpPlayers.begin(); it != tmpPlayers.end(); ++it)
	{
		if (poker_rank((*it)->hand, (*tmpPlayers.begin())->hand) == poker_rank((*tmpPlayers.begin())->hand, (*it)->hand))
		{
			(*it)->win++;
		}
		else
		{
			(*it)->lose++;
		}
		cout << *(*it) << endl;
		cout << (*it)->hand << endl;
	}

	vector<string> toRemove;

	for (auto it = tmpPlayers.begin(); it != tmpPlayers.end(); ++it)
	{
		if ((*it)->isAI){
			const int winnerStay = 8;
			const int loserStay = 0;
			const int middleStay = 4;
			int stayChance = rand() % 10;
			if (poker_rank((*it)->hand, (*tmpPlayers.begin())->hand) == poker_rank((*tmpPlayers.begin())->hand, (*it)->hand))
			{
				//one of the winners so 90% stay
				if (stayChance > winnerStay){
					cout << (*it)->name << " is leaving the table." << endl;
					ofstream ofs;
					ofs.open((*it)->name);
					ofs << (*it)->name << endl;
					ofs << (*it)->win << endl;
					ofs << (*it)->lose << endl;
					ofs.close();
					toRemove.push_back((*it)->name);
				}
			}
			else if (poker_rank((*it)->hand, (*(tmpPlayers.end() - 1))->hand) == poker_rank((*(tmpPlayers.end() - 1))->hand, (*it)->hand))
			{
				//one of the worst losers so 10% stay;
				if (stayChance > loserStay){
					cout << (*it)->name << " is leaving the table." << endl;
					ofstream ofs;
					ofs.open((*it)->name);
					ofs << (*it)->name << endl;
					ofs << (*it)->win << endl;
					ofs << (*it)->lose << endl;
					ofs.close();
					toRemove.push_back((*it)->name);
				}
			}
			else
			{
				//one of the middle players so 50% stay
				if (stayChance > middleStay){
					cout << (*it)->name << " is leaving the table." << endl;
					ofstream ofs;
					ofs.open((*it)->name);
					ofs << (*it)->name << endl;
					ofs << (*it)->win << endl;
					ofs << (*it)->lose << endl;
					ofs.close();
					toRemove.push_back((*it)->name);
				}
			}
		}
	}

	for (auto it = toRemove.begin(); it != toRemove.end(); ++it)
	{
		remove_player(*it);
	}

	for (auto it = players.begin(); it != players.end(); ++it)
	{
		for (auto i = 0; i < (*it)->hand.size(); ++i)
		{
			main_deck.addCard((*it)->hand[i]);
			(*it)->hand.remove_card(i);
		}
	}

	while (discard_deck.size() != empty)
	{
		main_deck << discard_deck;
	}

	string response = "";
	string saidNo = "no";
	cout << "Anybody wanna call it quits?" << endl;
	getline(cin, response);
	while (response != saidNo)
	{
		istringstream iss(response);
		string word;
		while (iss >> word) {
			shared_ptr<Player> p = find_player(word);
			if (p != nullptr) {
				ofstream ofs;
				ofs.open(word);
				ofs << p->name << endl;
				ofs << p->win << endl;
				ofs << p->lose << endl;
				ofs.close();
				remove_player(word);
			}
		}
		cout << "Anybody wanna call it quits?" << endl;
		getline(cin, response);
	}

	string response2 = "";
	cout << "Anybody wanna join?" << endl;
	getline(cin, response2);
	while (response2 != saidNo)
	{
		istringstream iss2(response2);
		string word;
		const int AIOffset = 1;
		const int beginIndex = 0;
		while (iss2 >> word) {
			try{
				bool isAI = word[word.size() - AIOffset] == '*';	//if the last character in the player's name is a '*' then we make the player into an AI
				if (isAI)
				{
					word = word.substr(beginIndex, word.size() - AIOffset);
				}
				add_player(word, isAI);
			}
			catch (...){
			}
		}
		cout << "Anybody wanna join?" << endl;
		getline(cin, response2);
	}

	int nextPlayer = 1;
	if (players.size() != 0)
	{
		dealer_index = (dealer_index + nextPlayer) % players.size();
	}
	return errors::noError;
}
