

#include <iostream>
using namespace std;

enum enGameChoice { Stone = 1, Paper = 2, Scissors = 3 };
enum enWinner { Player1 = 1, Computer = 2, Drow = 3 };

struct stRoundInfo
{
    short RoundNumber = 0;
    enGameChoice Player1Choice;
    enGameChoice ComputerChoice;
    enWinner Winner;
    string WinnerName;
};
struct stGameResults
{
    short GameRound = 0;
    short Player1WinTimes = 0;
    short Computer2WinTimes = 0;
    short DrowTimes = 0;
    enWinner GameWinner;
    string WinnerName = "";
};
int RandomNumber(int From, int To)
{
    int randNum = rand() % (To - From) + From + 1;
    return randNum;
}
string WinnerName(enWinner Winner)
{
    string arrWinnerName[3] = { "Player1", "Computer","No Winner" };
    return arrWinnerName[Winner - 1];
}
string ChoiceName(enGameChoice Choice)
{
    string arrWinnerName[3] = { "Stone", "Paper","Scissors" };
    return arrWinnerName[Choice - 1];
}
enWinner WhoWonTheRound(stRoundInfo RoundInfo)
{
    if (RoundInfo.Player1Choice == RoundInfo.ComputerChoice)
    {
        return enWinner::Drow;
    }
    switch (RoundInfo.Player1Choice)
    {
    case enGameChoice::Stone:
        if (RoundInfo.ComputerChoice == enGameChoice::Paper)
        {
            return enWinner::Computer;
        }
        break;
    case enGameChoice::Paper:
        if (RoundInfo.ComputerChoice == enGameChoice::Scissors)
        {
            return enWinner::Computer;
        }
        break;
    case enGameChoice::Scissors:
    {
        if (RoundInfo.ComputerChoice == enGameChoice::Stone)
        {
            return enWinner::Computer;
        }
        break;
    }
    }
    return enWinner::Player1;
}
void SetWinnerScreenColor(enWinner Winner)
{
    switch (Winner)
    {
    case enWinner::Player1:
        system("color 2F");
        break;
    case enWinner::Computer:
        system("color 4F");
        cout << "\a";
        break;
    default:
        system("color 6F");
        break;
    }
}
void PrintRoundResults(stRoundInfo RoundInfo)
{
    cout << "\n_____________________Round [" << RoundInfo.RoundNumber << "]__________________\n\n";
    cout << "Player1 Choice: " << ChoiceName(RoundInfo.Player1Choice) << endl;
    cout << "Computer Choice: " << ChoiceName(RoundInfo.ComputerChoice) << endl;
    cout << "Round Winner: [" << WinnerName(RoundInfo.Winner)<<"]" << endl;
    cout << "________________________________________________\n" << endl;
    SetWinnerScreenColor(RoundInfo.Winner);
}
enWinner WhoWonTheGame(short Player1WinTimes, short ComputerWinTimes)
{
    if (Player1WinTimes > ComputerWinTimes)
        return enWinner::Player1;
    else if (ComputerWinTimes > Player1WinTimes)
        return enWinner::Computer;
    else
        enWinner::Drow;
}
stGameResults FillGameResults(int GameRounds, short Player1WinTimes, short ComputerWinTimes, short DrowTimes)
{
    stGameResults GameResults;
    GameResults.GameRound = GameRounds;
    GameResults.Computer2WinTimes = ComputerWinTimes;
    GameResults.DrowTimes = DrowTimes;
    GameResults.Player1WinTimes = Player1WinTimes;
    GameResults.GameWinner = WhoWonTheGame(Player1WinTimes, ComputerWinTimes);
    GameResults.WinnerName = WinnerName(GameResults.GameWinner);
    return GameResults;
}
enGameChoice ReadPlayerChoice()
{
    short Choice = 1;
    do
    {
        cout << "\nYour Choice: [1]:Stone , [2]:Paper , [3]:Scissors?";
        cin >> Choice;
    } while (Choice < 1 || Choice>3);
    return (enGameChoice)Choice;
}
enGameChoice GetComputerChoice()
{
    return (enGameChoice)RandomNumber(1, 3);
}
stGameResults PlayGame(short HowManyRounds)
{
    stRoundInfo RoundInfo;
    short PLayer1WinTimes = 0, ComputerWinTimes = 0, DrowTimes = 0;
    for (short GameRound = 1;GameRound <= HowManyRounds;GameRound++)
    {
        cout << "\nRound [" << GameRound << "]: begins\n";
        RoundInfo.RoundNumber = GameRound;
        RoundInfo.Player1Choice = ReadPlayerChoice();
        RoundInfo.ComputerChoice = GetComputerChoice();
        RoundInfo.Winner = WhoWonTheRound(RoundInfo);
        RoundInfo.WinnerName = WinnerName(RoundInfo.Winner);

        if (RoundInfo.Winner == enWinner::Player1)
            PLayer1WinTimes++;
        else if (RoundInfo.Winner == enWinner::Computer)
            ComputerWinTimes++;
        else
            DrowTimes++;
        PrintRoundResults(RoundInfo);
    }
    return FillGameResults(HowManyRounds, PLayer1WinTimes, ComputerWinTimes, DrowTimes);
}
string Tabs(short NumberOfTabs)
{
    string t = "";
    for (int i = 1;i <= NumberOfTabs;i++)
    {
        t = t + "\t";
        cout << t;
    }
    return t;
}
void ShowGameOverScreen()
{
    cout << Tabs(2) << "______________________________________________\n\n";
    cout << Tabs(2) << "                 +++ GameOver+++              \n";
    cout << Tabs(2) << "______________________________________________\n\n";
}
void ShowFinalResults(stGameResults GameResults)
{
    cout << Tabs(2) << "_________________[Game Results]_______________\n\n";
    cout << Tabs(2) << "Game Rounds                : " << GameResults.GameRound << endl;
    cout << Tabs(2) << "Player1 Won Times          : " << GameResults.Player1WinTimes << endl;
    cout << Tabs(2) << "Computer Won Times         : " << GameResults.Computer2WinTimes << endl;
    cout << Tabs(2) << "Drow Times                 : " << GameResults.DrowTimes << endl;
    cout << Tabs(2) << "Final Winner               : " << GameResults.WinnerName << endl;
    cout << Tabs(2) << "______________________________________________\n";

    SetWinnerScreenColor(GameResults.GameWinner);
}
short ReadHowManyRounds()
{
    short GameRounds = 1;
    do
    {
        cout << "How Many Rounds 1 To 10 ?\n";
        cin >> GameRounds;
    } while (GameRounds < 1 || GameRounds>10);
    return GameRounds;
}
void ResetScreen()
{
    system("cls");
    system("color 0F");
}

void StartGame()
{
    char PlatAgain = 'Y';
    do
    {
        ResetScreen();
        stGameResults GameResults = PlayGame(ReadHowManyRounds());
        ShowGameOverScreen();
        ShowFinalResults(GameResults);
        cout << endl << Tabs(3) << "Do You Want To Play Again ? Y/N? ";
        cin >> PlatAgain;
    } while (PlatAgain == 'Y' || PlatAgain == 'y');
}
int main()
{
    srand((unsigned)time(NULL));

    StartGame();
    return 0;
}


