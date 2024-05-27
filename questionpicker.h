#include <iostream>
#include <fstream>
#include <time.h>
#include <math.h>
#include <cstdlib>

using namespace std;

class QuestionPicker{
    public:
        QuestionPicker(string fileName);
        ~QuestionPicker();
        void Activate();
        void OutputUsed();

    private:
        int questionCount;
        int numVersesUsed;
        int digSiteUse[20];
        int questionCondition[6];
        int verseType[3];
        int verseNum[9];
        int questionType;
        int questionsUsed[2][75];
        int situationUsed;
        int** questionAmount;
        ofstream outputFile;

        int fileLines(string f);
        void PickQuestion(const int questionType, const int x);
};
