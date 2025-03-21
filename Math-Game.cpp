#include <string>
//#include<math.h>
#include <iostream>
#include <iomanip>
#include <cstdlib>
using namespace std;
enum enQuestionLevel { eEasy = 1, eMid = 2, eHard = 3, eMix = 4 };
enum enQuestionType { eSum = 1, eSub = 2, eMul = 3, eDiv = 4, eMixOp = 5 };
struct stGameInfo {
	short QuestionsNumber = 0;
	enQuestionLevel QuestionLevel = eEasy;
	enQuestionType QuestionType = eSum;
	short RightAnswers = 0;
	short WrongAnswers = 0;
};
struct stQuestionInfo {
	enQuestionType QuestionType = eSum;
	short Number1 = 0;
	short Number2 = 0;

	short GeneratedAnswer = 0;
};
stGameInfo GameInfo;
int RandomNumber(int From, int To)
{
	// Generate a random number between 0 and (To - From) using rand(),
	// then add From to shift the range to [From, To].
	int randNum = rand() % (To - From + 1) + From;
	return randNum;  // Return the generated random number.
}
short ReadQuestionsNumber() {
	short QuestionsNumber = 0;
	do
	{
		cout << "\nEnter How many numbers you want to generat : ";
		cin >> QuestionsNumber;
	} while (QuestionsNumber <= 0 || QuestionsNumber > 100);
	return QuestionsNumber;
}
enQuestionLevel ReadQuestionsLevel() {
	short QuestionLevel = 1;
	do
	{
		cout << "\nEnter the question level :[1] Easy,[2] Mid,[3] Hard,[4] Mix ?";
		cin >> QuestionLevel;
	} while (QuestionLevel <= 0 || QuestionLevel > 4);
	return (enQuestionLevel)QuestionLevel;
}
enQuestionType ReadQuestionsType() {
	short QuestionsType = 0;
	do
	{
		cout << "\nEnter the question type : [1] Sum,[2] Sub,[3] Mul,[4] Div,[5] Mix ?";
		cin >> QuestionsType;
	} while (QuestionsType <= 0 || QuestionsType > 5);
	return (enQuestionType)QuestionsType;
}
short GetResult(short& Number1, short& Number2, enQuestionType& QuestionType) {
	switch (QuestionType) {
	case eSum:
		return Number1 + Number2;
		break;
	case eSub:
		return Number1 - Number2;
		break;
	case eMul:
		return Number1 * Number2;
		break;
	case eDiv:
		return (Number2 == 0) ? 0 : Number1 / Number2;
		break;
	}
}
stQuestionInfo FillQuestion(stGameInfo Info) {
	stQuestionInfo Questioninfo;
	if (Info.QuestionLevel == eMix)
		Info.QuestionLevel = (enQuestionLevel)RandomNumber(1, 3);
	if (Info.QuestionType == eMixOp)
		Info.QuestionType = (enQuestionType)RandomNumber(1, 4);
	Questioninfo.QuestionType = Info.QuestionType;
	switch (Info.QuestionLevel) {
	case eEasy:
		Questioninfo.Number1 = RandomNumber(1, 10);
		Questioninfo.Number2 = RandomNumber(1, 10);
		Questioninfo.GeneratedAnswer = GetResult(Questioninfo.Number1, Questioninfo.Number2, Questioninfo.QuestionType);
		return Questioninfo;

	case eMid:
		Questioninfo.Number1 = RandomNumber(10, 30);
		Questioninfo.Number2 = RandomNumber(10, 30);
		Questioninfo.GeneratedAnswer = GetResult(Questioninfo.Number1, Questioninfo.Number2, Questioninfo.QuestionType);
		return Questioninfo;
	case eHard:
		Questioninfo.Number1 = RandomNumber(30, 100);
		Questioninfo.Number2 = RandomNumber(30, 100);
		Questioninfo.GeneratedAnswer = GetResult(Questioninfo.Number1, Questioninfo.Number2, Questioninfo.QuestionType);
		return Questioninfo;
	}

}
void GeneratQuestion(stQuestionInfo Questions[], short& QuestionsNumber) {
	for (short i = 0;i < QuestionsNumber;i++)
	{
		Questions[i] = FillQuestion(GameInfo);
	}
}
string GetOpTypeString(enQuestionType& OpType) {
	string Opt[] = { "+","-","*","/" };
	return Opt[OpType - 1];
}
void ComparePlyAnswerWithGeneratdOne(short& PlayerAnswer, short& Result) {
	if (PlayerAnswer == Result)
	{
		GameInfo.RightAnswers++;
		system("color 2f");

	}
	else
	{
		GameInfo.WrongAnswers++;
		system("color 4f");
		cout << "\nThe right answer is : " << Result;
	}
}

string GetFinalResult() {
	return (GameInfo.RightAnswers >= GameInfo.WrongAnswers) ? "Pass" : "Fail";
}
string QuestionsLevelString() {
	string QueLevel[] = { "Easy","Mid","Hard","Mix" };
	return QueLevel[GameInfo.QuestionLevel - 1];
}
string QuestionsTypeString() {
	string QueType[] = { "Sum","Sub","Mul","Div","Mix" };
	return QueType[GameInfo.QuestionType - 1];
}
void GameOver() {
	cout << endl << endl << "\t\t\t_____________________________________________________________________" << endl;
	cout << "\t\t\t                        + + + Game Over + + + " << endl;
	cout << "\t\t\t_____________________________________________________________________" << endl << endl;
	cout << "\t\t\t                           Final Result Is " << GetFinalResult() << endl;
	cout << "\t\t\tNumber Of Questions     : " << GameInfo.QuestionsNumber << endl;
	cout << "\t\t\tQuestions Level         : " << QuestionsLevelString() << endl;
	cout << "\t\t\tQuestions Type          : " << QuestionsTypeString() << endl;
	cout << "\t\t\tNumber Of Right Answers : " << GameInfo.RightAnswers << endl;
	cout << "\t\t\tNumber Of Wrong Answers : " << GameInfo.WrongAnswers << endl;
	cout << "\t\t\t_____________________________________________________________________" << endl;
}
void StartQuestions(stQuestionInfo Questions[]) {
	short Counter = 1;
	short PlayerAnswer = 0;
	while (Counter <= GameInfo.QuestionsNumber)
	{
		cout << "\nQuestion [" << Counter << "/" << GameInfo.QuestionsNumber << "] : " << endl;
		cout << Questions[Counter - 1].Number1 << endl;
		cout << "\t" << GetOpTypeString(Questions[Counter - 1].QuestionType) << endl;
		cout << Questions[Counter - 1].Number2 << endl;
		cin >> PlayerAnswer;
		ComparePlyAnswerWithGeneratdOne(PlayerAnswer, Questions[Counter - 1].GeneratedAnswer);
		Counter++;
	}
}
void PreaparGame() {
	GameInfo.QuestionsNumber = ReadQuestionsNumber();
	GameInfo.QuestionLevel = ReadQuestionsLevel();
	GameInfo.QuestionType = ReadQuestionsType();
	stQuestionInfo Questions[100];
	GeneratQuestion(Questions, GameInfo.QuestionsNumber);
	StartQuestions(Questions);
	GameOver();
}
void ResetGame() {
	GameInfo.QuestionsNumber = 0;
	GameInfo.QuestionLevel = eEasy;
	GameInfo.QuestionType = eSum;
	GameInfo.RightAnswers = 0;
	GameInfo.WrongAnswers = 0;
}
void Start() {
	char PlayAgain = 'Y';
	do
	{
		system("cls");
		system("color 0f");
		PreaparGame();
		cout << "\nDo you wanna play new round ? [Y/N] ";
		cin >> PlayAgain;
	} while (toupper(PlayAgain) == 'Y');
	GameOver();

}
int main()
{

	srand((unsigned)time(NULL));
	Start();
}

