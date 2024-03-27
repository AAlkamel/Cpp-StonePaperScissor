#include <iostream>
#include <string>
using namespace std;

enum eGameWinner
{
  Player,
  Computer,
  NoWin
};

enum eGameOptions
{
  Stone,
  Paper,
  Scissors
};

struct sRoundInfo
{

  short roundNumber = 0;
  eGameOptions playerChoice;
  eGameOptions computerChoice;
  eGameWinner winner;
  string winnerName;
};

struct sGameInfo
{
  short gameRounds = 0;
  short playerWinTimes = 0;
  short computerWinTimes = 0;
  short DrawTimes = 0;
  eGameWinner winner;
  string winnerName;
};

int ReadNumberBetween2Numbers(int from, int to)
{
  int num = 0;
  do
  {
    cout << "How many rounds the game will be?\n"
         << "enter number between [ " << from << " : " << to << " ]\n";
    cin >> num;
  } while (num < from || num > to);
  return num;
}

char doYouPlayAgain()
{
  char again;
  cout << "\nIf you want to play again [y:n]?\n";
  cin >> again;
  return again;
}

int RandomNumber(int From, int To)
{
  int randNum = rand() % (To - From + 1) + From;
  return randNum;
}

eGameWinner CheckRoundResult(eGameOptions playerChoice, eGameOptions computerChoice)
{
  if (playerChoice == computerChoice)
    return eGameWinner::NoWin;
  switch (playerChoice)
  {
  case eGameOptions::Stone:
    if (computerChoice == eGameOptions::Paper)
      return eGameWinner::Computer;
    break;
  case eGameOptions::Paper:
    if (computerChoice == eGameOptions::Scissors)
      return eGameWinner::Computer;
    break;
  case eGameOptions::Scissors:
    if (computerChoice == eGameOptions::Stone)
      return eGameWinner::Computer;
    break;
  }
  return eGameWinner::Player;
}
eGameWinner GetGameWinner(short computerWinTimes, short playerWinTimes)
{
  if (computerWinTimes == playerWinTimes)
    return eGameWinner::NoWin;
  if (computerWinTimes > playerWinTimes)
    return eGameWinner::Computer;

  return eGameWinner::Player;
}

eGameOptions GetComputerChoice()
{
  return eGameOptions(RandomNumber(0, 2));
}

eGameOptions GetPlayerChoice()
{
  short Choice = 1;
  do
  {
    cout << "\nYour Choice: [1]:Stone, [2]:Paper, [3]:Scissors ? ";
    cin >> Choice;
  } while (Choice < 1 || Choice > 3);
  return eGameOptions(Choice - 1);
}

string GetWinnerName(eGameWinner winner)
{
  switch (winner)
  {
  case eGameWinner::Computer:
    return "Computer";
    break;
  case eGameWinner::Player:
    return "Player";
    break;
  case eGameWinner::NoWin:
    return "Draw";
    break;
  }
}

string GetChoiceName(eGameOptions choice)
{
  switch (choice)
  {
  case eGameOptions::Stone:
    return "Stone";
    break;
  case eGameOptions::Paper:
    return "Paper";
    break;
  case eGameOptions::Scissors:
    return "Scissors";
    break;
  }
}

void SetWinnerScreenColor(eGameWinner Winner)
{
  switch (Winner)
  {
  case eGameWinner::Player:
    system("color 2F"); // turn screen to Green
    break;
  case eGameWinner::Computer:
    system("color 4F"); // turn screen to Red
    cout << "\a";
    break;
  default:
    system("color 6F");
    // turn screen to Yellow
    break;
  }
}

void ResetScreen()
{
  system("cls");
  system("color 0F");
}

void PrintRoundResults(sRoundInfo RoundInfo)
{
  cout << "\n____________Round [" << RoundInfo.roundNumber + 1 << "] ____________\n\n";
  cout << "Player  Choice: " << GetChoiceName(RoundInfo.playerChoice) << endl;
  cout << "Computer Choice: " << GetChoiceName(RoundInfo.computerChoice) << endl;
  cout << "Round Winner   : [" << RoundInfo.winnerName << "] \n";
  cout << "__________________________________\n"
       << endl;
  SetWinnerScreenColor(RoundInfo.winner);
}

sRoundInfo PlayRound(short roundIndex)
{
  sRoundInfo roundInfo;
  roundInfo.roundNumber = roundIndex;
  roundInfo.computerChoice = GetComputerChoice();
  roundInfo.playerChoice = GetPlayerChoice();
  roundInfo.winner = CheckRoundResult(roundInfo.playerChoice, roundInfo.computerChoice);
  roundInfo.winnerName = GetWinnerName(roundInfo.winner);
  PrintRoundResults(roundInfo);
  return roundInfo;
}

void ShowGameOverScreen()
{
  cout << "\t\t"
       << "__________________________________________________________\n\n";
  cout << "\t\t"
       << "                 +++ G a m e  O v e r +++\n";
  cout << "\t\t"
       << "__________________________________________________________\n\n";
}
void ShowFinalGameResults(sGameInfo GameResults)
{
  cout << "\t\t"
       << "_____________________ [Game Results ]_____________________\n\n";
  cout << "\t\t"
       << "Game Rounds        : " << GameResults.gameRounds << endl;
  cout << "\t\t"
       << "Player1 won times  : " << GameResults.playerWinTimes << endl;
  cout << "\t\t"
       << "Computer won times : " << GameResults.computerWinTimes << endl;
  cout << "\t\t"
       << "Draw times         : " << GameResults.DrawTimes << endl;
  cout << "\t\t"
       << "Final Winner       : " << GameResults.winnerName << endl;
  cout << "\t\t"
       << "___________________________________________________________\n";
  SetWinnerScreenColor(GameResults.winner);
}

void PlayRounds(short roundsCount, sGameInfo &GameInfo)
{
  sRoundInfo GameRound;
  short playerWinTimes = 0, computerWinTimes = 0, drawTimes = 0;
  for (short i = 0; i < roundsCount; i++)
  {
    GameRound = PlayRound(i);

    switch (GameRound.winner)
    {
    case eGameWinner::NoWin:
      drawTimes++;
      break;
    case eGameWinner::Computer:
      computerWinTimes++;
      break;
    case eGameWinner::Player:
      playerWinTimes++;
      break;
    }
  }

  GameInfo.computerWinTimes = computerWinTimes;
  GameInfo.DrawTimes = drawTimes;
  GameInfo.playerWinTimes = playerWinTimes;
  GameInfo.gameRounds = roundsCount;
  GameInfo.winner = GetGameWinner(computerWinTimes, playerWinTimes);
  GameInfo.winnerName = GetWinnerName(GameInfo.winner);
}

void StartGame()
{
  char again = 'n';
  do
  {
    ResetScreen();
    short roundsCount = ReadNumberBetween2Numbers(1, 10);
    sGameInfo GameInfo;
    PlayRounds(roundsCount, GameInfo);
    ShowGameOverScreen();
    ShowFinalGameResults(GameInfo);
    again = doYouPlayAgain();
  } while (again == 'y' || again == 'Y');
}
int main()
{
  srand((unsigned)time(NULL));
  StartGame();
  return 0;
}