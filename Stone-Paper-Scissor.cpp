#include <iostream>
#include <cstdlib>
using namespace std;

enum enGameChoice { Stone = 1, Paper = 2, Scissors = 3 };
enum enWinner { Player = 1, Computer = 2, Draw = 3};

struct stRoundInfo {
	short roundnumber = 0; 
	enGameChoice playerchoice;
	enGameChoice computerchoice;
	enWinner winner;
	string winnername;
};

struct stGameResults {
	short gamerounds = 0;
	short playerwintimes = 0;
	short computerwintimes = 0;
	short drawtimes = 0;
	enWinner gamewinner;
	string winnername;
};

void getscreencolor(enWinner Winner)
{
	switch (Winner)
	{
	case enWinner::Player:
		system("color 2F");
		break;

	case enWinner::Computer:
		system("color 4F");
		break;

	case enWinner::Draw:
		system("color 6F");
		break;
	}
}

int randomnumber(int from, int to)
{
	int randnum = rand() % (to - from + 1) + from;

	return randnum;
}

int howManyRounds()
{
	short rounds;
	do
	{
		cout << "How Many Rounds you want from 1 to 10?\n";
		cin >> rounds;
	} while (rounds < 1 || rounds > 10);

	return rounds;
}

enGameChoice readPlayerChoice()
{
	short choice = 0;

	do {
		cout << "\n Your Choice [1]Stone, [2]Paper, [3] Scissors ?\n";
		cin >> choice;

	} while (choice < 1 || choice > 3);

	return (enGameChoice)choice;
}

enGameChoice getComputerChoice()
{
	return (enGameChoice)randomnumber(1, 3);
}

enWinner whoWonTheRound(stRoundInfo roundInfo)
{
	if (roundInfo.playerchoice == roundInfo.computerchoice)
		return enWinner::Draw;

	switch (roundInfo.playerchoice)
	{
	case enGameChoice::Stone:
		return roundInfo.computerchoice == enGameChoice::Paper ? enWinner::Computer : enWinner::Player;

	case enGameChoice::Paper:
		return roundInfo.computerchoice == enGameChoice::Scissors ? enWinner::Computer : enWinner::Player;
	
	case enGameChoice::Scissors:
		return roundInfo.computerchoice == enGameChoice::Stone ? enWinner::Computer : enWinner::Player;
	}
}

string getWinnerName(enWinner Winner)
{
	string arrwinnerName[3] = { "Player", "Computer", "No-Winner" };

	return arrwinnerName[Winner - 1];
}

string getchoice(enGameChoice gameChoice)
{
	string arrchoicename[3] = { "Stone", "Paper", "Scissors" };

	return arrchoicename[gameChoice - 1];
}

void printRoundResults(stRoundInfo roundInfo)
{
	cout << "Player Choice :" << getchoice(roundInfo.playerchoice) << endl;
	cout << "Computer Choice :" << getchoice(roundInfo.computerchoice) << endl;
	cout << "Round Winner :" << roundInfo.winnername << endl;

	getscreencolor(roundInfo.winner);

}

enWinner whoWonTheGame( short playerwintimes, short computerwintimes)
{
	if (playerwintimes > computerwintimes)
		return enWinner::Player;

	else if (computerwintimes > playerwintimes)
		return enWinner::Computer;

	else
		return enWinner::Draw;
}

stGameResults fillgameresults(short howmanyrounds, short playerwintimes, short computerwintimes, short drawtimes)
{
	stGameResults gameResults;
	gameResults.gamerounds = howmanyrounds;
	gameResults.playerwintimes = playerwintimes;
	gameResults.computerwintimes = computerwintimes;
	gameResults.drawtimes = drawtimes;
	gameResults.gamewinner = whoWonTheGame(playerwintimes, computerwintimes);
	gameResults.winnername = getWinnerName(gameResults.gamewinner);

	return gameResults;
}


stGameResults playgame(short howmanyrounds)
{
	stRoundInfo roundInfo;
	short playerwintimes = 0, computerwintimes = 0, drawtimes = 0;

	for (int gamerounds = 1; gamerounds <= howmanyrounds; gamerounds++)
	{
		cout << "\n-----------------------Round[" << gamerounds << "] -----------------------------\n";
		roundInfo.roundnumber = gamerounds;
		roundInfo.playerchoice = readPlayerChoice();
		roundInfo.computerchoice = getComputerChoice();
		roundInfo.winner = whoWonTheRound(roundInfo);
		roundInfo.winnername = getWinnerName(roundInfo.winner);

		if (roundInfo.winner == enWinner::Player)
			playerwintimes++;
		else if (roundInfo.winner == enWinner::Computer)
			computerwintimes++;
		else
			drawtimes++;

		printRoundResults(roundInfo);
	}

	return fillgameresults(howmanyrounds, playerwintimes, computerwintimes, drawtimes);
}



string Tabs(short howmanyspace)
{
	
	return string(howmanyspace, '\t');
}

void showgameoverscreen()
{
	cout << Tabs(3) << "-------------------------------------------------------------------------------\n";
	cout << Tabs(3) << "                                  * * * GAME OVER * * *                        \n";
	cout << Tabs(3) << "-------------------------------------------------------------------------------\n";
}


void showFinalGameResults(stGameResults gameResults)
{
	cout << Tabs(3) << "----------------------Game Results-------------------------\n";
	cout << Tabs(2) << "Game Rounds :" << gameResults.gamerounds << endl;
	cout << Tabs(2) << "Player Win Times:" << gameResults.playerwintimes << endl;
	cout << Tabs(2) << "Computer Win Times :" << gameResults.computerwintimes << endl;
	cout << Tabs(2) << "Draw Times :" << gameResults.drawtimes << endl;
	cout << Tabs(2) << "Final Winner :" << gameResults.winnername << endl;

	getscreencolor(gameResults.gamewinner);
}

void resetScreen()
{
	system("cls");
	system("color 0F");
}

void startgame()
{
	char playagain = 'Y';

	do
	{

		resetScreen();
		stGameResults gameResults = playgame(howManyRounds());
		showgameoverscreen();
		showFinalGameResults(gameResults);
		 
		cout << "\nDo you want to play again?\n";
		cin >> playagain;

	} while (playagain == 'y' || playagain == 'Y');
}


int main()
{
	srand((unsigned)time(NULL));

	startgame();

	return 0;
}