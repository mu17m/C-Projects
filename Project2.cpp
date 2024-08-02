
#include <iostream>
using namespace std;

short EnterNumber(string Messege) {
    short Num = 0;
    do {
        cout << Messege;
        cin >> Num;
    } while (Num < 0);
    return Num;
}
int RandomNumber(int From, int To) {
    int RanNum;
    RanNum = rand() % (To - From + 1) + From;
    return RanNum;
}
enum enQuestionLevel { Easy = 1, Med = 2, Hard = 3, Mix = 4 };
enum enOpeartionType { Add = 1, Sub = 2, Mul = 3, Div = 4 };
struct stGameInfo {
    int QuestionsNumber;
    enQuestionLevel QuestionLevel;
    enOpeartionType OpeartionType;
    short NumberOfRight = 0;
    short NumberOfWrong = 0;
};

enQuestionLevel ReadQuestionLevel() {
    short QuestionLevel= 0;
    do {
        cout << "Enter questions level [1] Easy, [2] Med, [3] Hard, [4] Mix ? ";
        cin >> QuestionLevel;
    } while (QuestionLevel < 1 || QuestionLevel > 4);
    return (enQuestionLevel)QuestionLevel;
}
enOpeartionType ReadOperationType() {
    short OperationType = 0;
    do {
        cout << "Enter Opeartion Type [1] Add, [2] Sub, [3] Mul, [4] Div ? ";
        cin >> OperationType;
    } while (OperationType < 1 || OperationType > 4);
    return (enOpeartionType)OperationType;
}
string type(enQuestionLevel QuestionLevel) {
    string QL[3] = { "Easy", "Mid", "Hard" };
    return QL[QuestionLevel - 1];
}
string operation(enOpeartionType OperationType) {
    string OT[4] = { "+", "-", "*", "/" };
    return OT[OperationType - 1];
}

void FinalResult(stGameInfo GameInfo) {
    string Result;
    if (GameInfo.NumberOfRight > GameInfo.NumberOfWrong) {
        Result = "Pass :-)\n";
    }
    else Result = "Fail :-(\n";
    cout << "_______________________\n";
    cout << "Final Result is " << Result;
    cout << "_______________________\n" << endl;

    cout << "Number of questions: " << GameInfo.QuestionsNumber << endl;
    cout << "Questions Level: " << type(GameInfo.QuestionLevel) << endl;
    cout << "Operation type: " << operation(GameInfo.OpeartionType) << endl;
    cout << "Number of Right answers: " << GameInfo.NumberOfRight << endl;
    cout << "Number of Wrong answers: " << GameInfo.NumberOfWrong << endl;
    cout << "\n_______________________\n";
}
void CheckAnswer(int RanNum1, int RanNum2, enOpeartionType OT, stGameInfo& GameInfo) {
    GameInfo.NumberOfRight ;
    GameInfo.NumberOfWrong ;
    int opeartion = 0;
    switch (OT)
    {
    case Add:
        opeartion = RanNum1 + RanNum2;
        break;
    case Sub:
        opeartion = RanNum1 - RanNum2;
        break;
    case Mul:
        opeartion = RanNum1 * RanNum2;
        break;
    case Div:
        opeartion = RanNum1 / RanNum2;
        break;
    }
    int answer;
    cin >> answer;
    if (opeartion == answer) {
        cout << "Right answer :-)\n" << endl;
        GameInfo.NumberOfRight++;
    }
    else {
     cout << "Wrong answer :-(" << endl << "The right answer is: " << opeartion << endl;
     GameInfo.NumberOfWrong++;
    }
}
void equation(stGameInfo& GameInfo) {
    switch (GameInfo.OpeartionType)
    {
    case Add:
        if (GameInfo.QuestionLevel == enQuestionLevel::Easy) {
            int RanNum1 = RandomNumber(1, 10);
            int RanNum2 = RandomNumber(1, 10);
            cout << "\n" << RanNum1 << endl;
            cout << RanNum2 << " " << operation(enOpeartionType::Add) << endl;
            cout << "_______________\n";
            CheckAnswer(RanNum1, RanNum2, enOpeartionType::Add, GameInfo);
        }
        else if (GameInfo.QuestionLevel == enQuestionLevel::Med) {
            int RanNum1 = RandomNumber(10, 50);
            int RanNum2 = RandomNumber(10, 50);
            cout << "\n" << RanNum1 << endl;
            cout << RanNum2 << " " << operation(enOpeartionType::Add) << endl;
            cout << "_______________\n";
            CheckAnswer(RanNum1, RanNum2, enOpeartionType::Add, GameInfo);
        }
        else if (GameInfo.QuestionLevel == enQuestionLevel::Hard) {
            int RanNum1 = RandomNumber(30, 100);
            int RanNum2 = RandomNumber(30, 100);
            cout << "\n" << RanNum1 << endl;
            cout << RanNum2 << " " << operation(enOpeartionType::Add) << endl;
            cout << "_______________\n";
            CheckAnswer(RanNum1, RanNum2, enOpeartionType::Add, GameInfo);
        }
        else {
            int RanNum1 = RandomNumber(1, 100);
            int RanNum2 = RandomNumber(1, 100);
            enOpeartionType RanOp = (enOpeartionType)RandomNumber(1, 4);
            cout << "\n" << RanNum1 << endl;
            cout << RanNum2 << " " << operation(RanOp) << endl;
            cout << "_______________\n";
            CheckAnswer(RanNum1, RanNum2, RanOp, GameInfo);
        }
        break;
        //Subtract
    case Sub:
        if (GameInfo.QuestionLevel == enQuestionLevel::Easy) {
            int RanNum1 = RandomNumber(1, 10);
            int RanNum2 = RandomNumber(1, 10);
            cout << "\n" << RanNum1 << endl;
            cout << RanNum2 << " " << operation(enOpeartionType::Sub) << endl;
            cout << "_______________\n";
            CheckAnswer(RanNum1, RanNum2, enOpeartionType::Sub, GameInfo);
        }
        else if (GameInfo.QuestionLevel == enQuestionLevel::Med) {
            int RanNum1 = RandomNumber(10, 50);
            int RanNum2 = RandomNumber(10, 50);
            cout << "\n" << RanNum1 << endl;
            cout << RanNum2 << " " << operation(enOpeartionType::Sub) << endl;
            cout << "_______________\n";
            CheckAnswer(RanNum1, RanNum2, enOpeartionType::Sub, GameInfo);
        }
        else if (GameInfo.QuestionLevel == enQuestionLevel::Hard) {
            int RanNum1 = RandomNumber(30, 100);
            int RanNum2 = RandomNumber(30, 100);
            cout << "\n" << RanNum1 << endl;
            cout << RanNum2 << " " << operation(enOpeartionType::Sub) << endl;
            cout << "_______________\n";
            CheckAnswer(RanNum1, RanNum2, enOpeartionType::Sub, GameInfo);
        }
        else {
            int RanNum1 = RandomNumber(1, 100);
            int RanNum2 = RandomNumber(1, 100);
            enOpeartionType RanOp = (enOpeartionType)RandomNumber(1, 4);
            cout << "\n" << RanNum1 << endl;
            cout << RanNum2 << " " << operation(RanOp) << endl;
            cout << "_______________\n";
            CheckAnswer(RanNum1, RanNum2, RanOp, GameInfo);
        }
        break;
    case Mul:
        if (GameInfo.QuestionLevel == enQuestionLevel::Easy) {
            int RanNum1 = RandomNumber(1, 10);
            int RanNum2 = RandomNumber(1, 10);
            cout << "\n" << RanNum1 << endl;
            cout << RanNum2 << " " << operation(enOpeartionType::Mul) << endl;
            cout << "_______________\n";
            CheckAnswer(RanNum1, RanNum2, enOpeartionType::Mul, GameInfo);
        }
        else if (GameInfo.QuestionLevel == enQuestionLevel::Med) {
            int RanNum1 = RandomNumber(10, 50);
            int RanNum2 = RandomNumber(10, 50);
            cout << "\n" << RanNum1 << endl;
            cout << RanNum2 << " " << operation(enOpeartionType::Mul) << endl;
            cout << "_______________\n";
            CheckAnswer(RanNum1, RanNum2, enOpeartionType::Mul, GameInfo);
        }
        else if (GameInfo.QuestionLevel == enQuestionLevel::Hard) {
            int RanNum1 = RandomNumber(30, 100);
            int RanNum2 = RandomNumber(30, 100);
            cout << "\n" << RanNum1 << endl;
            cout << RanNum2 << " " << operation(enOpeartionType::Mul) << endl;
            cout << "_______________\n";
            CheckAnswer(RanNum1, RanNum2, enOpeartionType::Mul, GameInfo);
        }
        else {
            int RanNum1 = RandomNumber(1, 100);
            int RanNum2 = RandomNumber(1, 100);
            enOpeartionType RanOp = (enOpeartionType)RandomNumber(1, 4);
            cout << "\n" << RanNum1 << endl;
            cout << RanNum2 << " " << operation(RanOp) << endl;
            cout << "_______________\n";
            CheckAnswer(RanNum1, RanNum2, RanOp, GameInfo);
        }

        break;
    case Div:
        if (GameInfo.QuestionLevel == enQuestionLevel::Easy) {
            int RanNum1 = RandomNumber(1, 10);
            int RanNum2 = RandomNumber(1, 10);
            cout << "\n" << RanNum1 << endl;
            cout << RanNum2 << " " << operation(enOpeartionType::Div) << endl;
            cout << "_______________\n";
            CheckAnswer(RanNum1, RanNum2, enOpeartionType::Div, GameInfo);
        }
        else if (GameInfo.QuestionLevel == enQuestionLevel::Med) {
            int RanNum1 = RandomNumber(10, 50);
            int RanNum2 = RandomNumber(10, 50);
            cout << "\n" << RanNum1 << endl;
            cout << RanNum2 << " " << operation(enOpeartionType::Div) << endl;
            cout << "_______________\n";
            CheckAnswer(RanNum1, RanNum2, enOpeartionType::Div, GameInfo);
        }
        else if (GameInfo.QuestionLevel == enQuestionLevel::Hard) {
            int RanNum1 = RandomNumber(30, 100);
            int RanNum2 = RandomNumber(30, 100);
            cout << "\n" << RanNum1 << endl;
            cout << RanNum2 << " " << operation(enOpeartionType::Div) << endl;
            cout << "_______________\n";
            CheckAnswer(RanNum1, RanNum2, enOpeartionType::Div, GameInfo);
        }
        else {
            int RanNum1 = RandomNumber(1, 100);
            int RanNum2 = RandomNumber(1, 100);
            enOpeartionType RanOp = (enOpeartionType)RandomNumber(1, 4);
            cout << "\n" << RanNum1 << endl;
            cout << RanNum2 << " " << operation(RanOp) << endl;
            cout << "_______________\n";
            CheckAnswer(RanNum1, RanNum2, RanOp, GameInfo);
        }
        break;
  }
}
void ShowCase() {
    stGameInfo GameInfo;
    
    GameInfo.QuestionsNumber = EnterNumber("How many questions do you want to answer ? ");
    GameInfo.QuestionLevel = ReadQuestionLevel();
    GameInfo.OpeartionType = ReadOperationType();
    bool right;
    for (int i = 1; i <= GameInfo.QuestionsNumber; i++) {
        cout << "\n\nQueation[" << i << "/" << GameInfo.QuestionsNumber << "]\n";
        equation(GameInfo);
    }
    FinalResult(GameInfo);


}

int main()
{
    srand((unsigned)time(NULL));
    char PlayAgain = 'y';
    do {
        ShowCase();
        cout << "\nDo you want to play again ? Y/N";
        cin >> PlayAgain;
    } while (PlayAgain == 'y' || PlayAgain == 'Y');

}
