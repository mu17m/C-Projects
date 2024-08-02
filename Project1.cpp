
#include <iostream>
using namespace std;

int EnterNumber(string Messege) {
    int Num;
    do {
        cout << Messege;
        cin >> Num;
    } while (Num < 0);
    return Num;
}
int RandomNumber(int From, int To) {
    int RanNum = 0;
    RanNum = rand() % (To - From + 1) + From;
    return RanNum;
}
enum enGameChoice{Stone=1, Paper=2, Scissor=3};
enum enWinner { Player = 1, Computer = 2, Draw=3};
struct stRoundInfo
{
    int RoundsNumber;
    short PlayerWinTimes=0;
    short ComputerWinTimes=0;
    short DrawTimes=0;
    enGameChoice PlayerChoice;
    enGameChoice ComputerChoice;
    enWinner Winner;
    string WinnerName;
};

enGameChoice ReadPlayerChoice() {
    short Choice = 1;
    do {
        cout << "\nYour Choice: [1]:Stone, [2]:Paper, [3]:Scissor ?";
        cin >> Choice;
    } while (Choice < 1 || Choice > 3);
    return (enGameChoice)Choice;
}
enGameChoice GetComputerChoice() {
    return (enGameChoice)RandomNumber(1, 3);
}
enWinner Winner(stRoundInfo RoundInfo) {
    if (RoundInfo.PlayerChoice == RoundInfo.ComputerChoice) {
        return Draw;
    }
    switch (RoundInfo.PlayerChoice)
    {
    case enGameChoice::Stone :
        if (RoundInfo.ComputerChoice == enGameChoice::Paper) {
            return enWinner::Computer;
        }
        break;
    case enGameChoice::Paper:
        if (RoundInfo.ComputerChoice == enGameChoice::Scissor) {
            return enWinner::Computer;
            break;
        }
    case enGameChoice::Scissor:
        if (RoundInfo.ComputerChoice == enGameChoice::Stone) {
            return enWinner::Computer;
        }
    }
    return enWinner::Player;
}
enWinner WhoWinnerGame(short Player, short Computer) {
    if (Player > Computer) {
        return enWinner::Player;
    }
    else if (Player < Computer) {
        return enWinner::Computer;
    }
    else return enWinner::Draw;
}
string WinnerName(enWinner Winner) {
    string WinnerNamestring[3] = { "Player", "Computer", "No Winner" };
    return WinnerNamestring[Winner - 1];
};
string ChoiceName(enGameChoice cho) {
    string Choice[3] = { "Stone", "Paper", "Scissor" };
    return Choice[cho - 1];
}

void PrintRoundInfo(stRoundInfo RoundInfo) {
  
    cout << "\n_________________Round[" << RoundInfo.RoundsNumber << "]_________________\n\n";
    cout << "Player Choice: " << ChoiceName(RoundInfo.PlayerChoice) << endl;
    cout << "Computer Choice: " << ChoiceName(RoundInfo.ComputerChoice) << endl;
    cout << "Round Winner: " << RoundInfo.WinnerName << endl;
    cout << "_________________\n"<<endl;
}
void Result(stRoundInfo RoundInfo) {
    cout << "\n--------------------------------------\n";
    cout << "+++Game Over+++\n";
    cout << "--------------------------------------\n";
    cout << "\n-------------------[ Game Result ]-------------------\n\n";
    cout << "Game Rounds: " << RoundInfo.RoundsNumber << endl;
    cout << "Player won times: "<<RoundInfo.PlayerWinTimes<<endl;
    cout << "Computer won times: " <<RoundInfo.ComputerWinTimes<< endl;
    cout << "Draw times: "<<RoundInfo.DrawTimes<< endl;
    cout << "Final winner: "<<WinnerName(WhoWinnerGame(RoundInfo.PlayerWinTimes, RoundInfo.ComputerWinTimes)) << endl;
    cout << "\n--------------------------------------\n";

}
void ShowCase(int Rounds) {
         stRoundInfo RoundInfo;
     
         for (int i = 1; i <= Rounds; i++) {
         cout << "\nRound [" << i << "] begins:\n";
         RoundInfo.RoundsNumber = i;
         RoundInfo.PlayerChoice = ReadPlayerChoice();
         RoundInfo.ComputerChoice = GetComputerChoice();
         RoundInfo.Winner = Winner(RoundInfo);
         RoundInfo.WinnerName = WinnerName(RoundInfo.Winner);

         if (RoundInfo.Winner == enWinner::Player) {
             RoundInfo.PlayerWinTimes++;
         }
         else if (RoundInfo.Winner == enWinner::Computer) {
             RoundInfo.ComputerWinTimes++;
         }
         else RoundInfo.DrawTimes++;
         PrintRoundInfo(RoundInfo);
     }
         Result(RoundInfo);
}




int main()
{
    bool PlayAgain = 0;
    do {
    int Rounds;
    Rounds = EnterNumber("How Many Rounds 1 to 10 ? \n");
    ShowCase(Rounds);
    cout << "Do you want to play again? [1]:Yes, [0]:No ?";
    cin >> PlayAgain;
    } while (PlayAgain == 1);
}
