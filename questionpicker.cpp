#include "questionpicker.h"


string Folder = "Questions\\";

//Sets up Question Picker object
QuestionPicker::QuestionPicker(string fileName){
    //Number of question that you are on
    questionCount = 0;

    numVersesUsed = 0;

    //Fills with 0's the array of how many times questions from each dig site has come up
    for(int i = 0; i < 20; i++){
        digSiteUse[i] = 0;
    }

    //
    for(int i = 0; i < 5; i++){
        questionCondition[i] = 0;
    }

    //Holds which verse type has been used
    for(int i = 0; i < 3; i++){
        verseType[i] = 0;
    }

    //Holds which verses have been used
    for(int i = 0; i < 9; i++){
        verseNum[i] = 0;
    }

    //Holds which questions have been used
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 75; j++){
            questionsUsed[i][j] = 0;
        }
    }

    //Opens the file the user typed in
    outputFile.open ((fileName + ".txt").c_str());

    //holds the number of each type of question is available
    questionAmount = new int*[7];
    questionAmount[0] = new int[fileLines("F Rapid Fire.txt")/3];
    questionAmount[1] = new int[fileLines("G General.txt")/6];
    questionAmount[2] = new int[fileLines("A According To.txt")/6];
    questionAmount[3] = new int[fileLines("QVR Memory.txt")/4];
    questionAmount[4] = new int[fileLines("X Context.txt")/6];
    questionAmount[5] = new int[fileLines("S Situation.txt")/6];
    questionAmount[6] = new int[fileLines("I Book and Chapter.txt")/6];

    //Fills array with zeros and prints out the number of each type
    for(int i = 0; i < fileLines("F Rapid Fire.txt")/3; i++){
        questionAmount[0][i] = 0;
    }

    cout << "Rapid Fire Length: " << fileLines("F Rapid Fire.txt")/3 << endl;

    for(int i = 0; i < fileLines("G General.txt")/6; i++){
        questionAmount[1][i] = 0;
    }

    cout << "General Length: " << fileLines("G General.txt")/6 << endl;

    for(int i = 0; i < fileLines("A According To.txt")/6; i++){
        questionAmount[2][i] = 0;
    }

    cout << "According To Length: " << fileLines("A According To.txt")/6 << endl;

    for(int i = 0; i < fileLines("QVR Memory.txt")/4; i++){
        questionAmount[3][i] = 0;
    }

    cout << "Memory Length: " << fileLines("QVR Memory.txt")/4 << endl;

    for(int i = 0; i < fileLines("X Context.txt")/6; i++){
        questionAmount[4][i] = 0;
    }

    cout << "Context Length: " << fileLines("X Context.txt")/6 << endl;

    for(int i = 0; i < fileLines("S Situation.txt")/6; i++){
        questionAmount[5][i] = 0;
    }

    cout << "Situation Length: " << fileLines("S Situation.txt")/6 << endl;

    /*for(int i = 0; i < fileLines("I Book and Chapter.txt")/6; i++){
        questionAmount[6][i] = 0;
    }

    cout << "Book and Chapter Length: " << fileLines("I Book and Chapter.txt")/6 << endl;*/

}

void QuestionPicker::OutputUsed(){
    cout << endl << endl;
    for(int i = 0; i < fileLines("F Rapid Fire.txt")/3; i++){
        cout << questionAmount[0][i] << " ";
    }
    cout << endl << endl;

    for(int i = 0; i < fileLines("G General.txt")/6; i++){
        cout << questionAmount[1][i] << " ";
    }
    cout << endl << endl;

    for(int i = 0; i < fileLines("A According To.txt")/6; i++){
        cout << questionAmount[2][i] << " ";
    }
    cout << endl << endl;

    for(int i = 0; i < fileLines("QVR Memory.txt")/4; i++){
        cout << questionAmount[3][i] << " ";
    }
    cout << endl << endl;

    for(int i = 0; i < fileLines("X Context.txt")/6; i++){
        cout << questionAmount[4][i] << " ";
    }
    cout << endl << endl;

    for(int i = 0; i < fileLines("S Situation.txt")/6; i++){
        cout << questionAmount[5][i] << " ";
    }
    cout << endl << endl;

    for(int i = 0; i < fileLines("I Book and Chapter.txt")/6; i++){
        cout << questionAmount[6][i] << " ";
    }
    cout << endl;
}

//Removes all the things that need it for the Question Picker object
QuestionPicker::~QuestionPicker(){
    for(int i = 0; i < 7; i++){
        delete questionAmount[i];
    }
    delete [] questionAmount;
}


void QuestionPicker::Activate(){

    //First Round
    outputFile << "\t\t\tRound 1\n";
    //twenty question in the first round
    for(int x = 1; x <= 20; x++){
        //First and last question are general
        if(x == 1 || x == 20){
            questionType = 1;
        }else{
            //Picks a random number to determine question type until it fits all criteria
            do{
                questionType = rand() %  21;
            }while( (questionType < 11 && questionCondition[0] > 9) || (questionType < 15 && questionType >= 11 && questionCondition[1] > 3) ||
                    (questionCondition[2] > 2 && questionType < 18 && questionType >= 15) || (questionType == 18 && questionCondition[3] == 1) ||
                    (questionCondition[4] == 1 && (questionType == 19 || questionType == 20) ) );
                    //No more then 10 general questions, 4 according to, 3 verse questions, 1 context and 1 situation or book and chapter
        }

        PickQuestion(questionType, x);
    }

    //cout << "You made it to the rapid round.\n";
    outputFile << "\n\n\t\t\tRapid Fire\n";
    questionType = -1;
    for(int x = 1; x <= 10; x++){
        PickQuestion(questionType, x);
    }

    //cout << "You made it to the second round.\n";
    questionCondition[0] = 0;
    questionCondition[1] = 0;
    questionCondition[2] = 0;
    questionCondition[3] = 0;
    questionCondition[4] = 0;

    verseType[0] = 0;
    verseType[1] = 0;
    verseType[2] = 0;

    /*if(questionCondition[4] == 1){
        situationUsed = 1;
    }else if(questionCondition[5] == 1){
        situationUsed = 0;
    }*/

    //Second Round
    outputFile << "\n\n\t\t\tRound 2\n";
    for(int x = 1; x <= 20; x++){
        if(x == 1 || x == 20){
            questionType = 1;
        }else{
            do{
                questionType = rand() %  21;
            }while( (questionType < 11 && questionCondition[0] > 9) || (questionType < 15 && questionType >= 11 && questionCondition[1] > 3) ||
                    (questionCondition[2] > 2 && questionType < 18 && questionType >= 15) || (questionType == 18 && questionCondition[3] == 1) ||
                    (questionCondition[4] == 1 && (questionType == 19 || questionType == 20) ) );
        }

        PickQuestion(questionType, x);
    }

    //cout << "You made it to the replacement round.\n";
    questionCondition[0] = 0;
    questionCondition[1] = 0;
    questionCondition[2] = 0;
    questionCondition[3] = 0;
    questionCondition[4] = 0;

    verseType[0] = 0;
    verseType[1] = 0;
    verseType[2] = 0;

    //Replacement Round
    outputFile << "\n\n\t\t\tReplacement Round\n";
    for(int x = 1; x <= 20; x++){
        PickQuestion(x, x);
    }

    questionType = -1;
    for(int x = 1; x <= 5; x++){
        PickQuestion(questionType, x + 20);
    }

    outputFile.close();
    /*
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 70; j++){
            if(questionsUsed[i][j] < 10){
                cout << questionsUsed[i][j] << "  ";
            }else if(questionsUsed[i][j] >= 10){
                cout << questionsUsed[i][j] << " ";
            }
        }
        cout << endl;
    }*/
}

void QuestionPicker::PickQuestion(const int questionType, const int x){\
    //Determines which file the search in based on type
    ifstream inputFile;

    //Array holds two possible question numbers
    int questionNum[2];
    //What round is this
    int roundNumber;
    //How many lines are in the input file
    int numLines;
    //what dig sites do the possible questions come from
    int digSite[2];
    //What type of question is it
    int questionCatagory;

    //Text of question
    string question[2];
    //Text of answer
    string answer[8];
    //name of the file
    string iFileName;

    //Calculate which round this is
    if(questionCount < 20){
        roundNumber = 0;
    }else if(questionCount < 30){
        roundNumber = 1;
    }else if(questionCount < 50){
        roundNumber = 2;
    }else if(questionCount < 70){
        roundNumber = 3;
    }

    //Find the question type and output the number and type at beginning of the question
    if(questionType == -1){
        outputFile << x << ". ";
        iFileName = "F Rapid Fire.txt";
        questionsUsed[0][questionCount] = 0;
        questionCatagory = 0;
    }else if(questionType < 11){
        outputFile << x << ". " << "G. ";
        iFileName = "G General.txt";
        questionCondition[0]++;
        questionsUsed[0][questionCount] = 1;
        questionCatagory = 1;
    }else if(questionType < 15){
        outputFile << x << ". " << "A. ";
        iFileName = "A According To.txt";
        questionCondition[1]++;
        questionsUsed[0][questionCount] = 2;
        questionCatagory = 2;
    }else if(questionType < 18){
        iFileName = "QVR Memory.txt";
        questionCondition[2]++;
        questionsUsed[0][questionCount] = 3;
        questionCatagory = 3;
    }else if(questionType == 18){
        outputFile << x << ". " << "X. ";
        iFileName = "X Context.txt";
        questionCondition[3]++;
        questionsUsed[0][questionCount] = 4;
        questionCatagory = 4;
    }else if(questionType == 19 || questionType == 20){ //Means that neither has been used
            outputFile << x << ". " << "S. ";
            iFileName = "S Situation.txt";
            questionCondition[4]++;
            questionsUsed[0][questionCount] = 5;
            questionCatagory = 5;
    }
        /*else if(questionType == 20){
            outputFile << x << ". " << "I. ";
            iFileName = "I Book and Chapter.txt";
            questionCondition[5]++;
            questionsUsed[0][questionCount] = 6;
            questionCatagory = 6;
        }*/
        
    inputFile.open((Folder + iFileName).c_str());

    numLines = fileLines(iFileName);
    bool bad = false;
    bool tryOnce = false;
    do{ //Go until find one that are good and do not match
        if(questionType >= 15 && questionType < 18){ //Memory type
            bool check = false;
            do{
                //Pick random number for question
                questionNum[0] = rand() % int(numLines/4.0) + 1;
                check = false;
                int numTimes = 0;
                for(int b = 0; b < 9; b++){ //If it is a verse that has been used before try again
                    if(questionNum[0] == verseNum[b] && numVersesUsed < numLines/4.0){
                        check = true;
                        break;
                    }else if(questionNum[0] == verseNum[b]){
                        numTimes++;
                    }
                }
                if(numTimes >= 2){
                    check = true;
                }
            }while(check);
            do{
                questionNum[1] = rand() % int(numLines/4.0) + 1;
                check = false;
                int numTimes = 0;
                for(int b = 0; b < 9; b++){ //If it is a verse that has been used before try again
                    if(questionNum[1] == verseNum[b] && numVersesUsed < numLines/4.0){
                        check = true;
                        break;
                    }else if(questionNum[1] == verseNum[b]){
                        numTimes++;
                    }
                }
                if(numTimes >= 2){
                    check = true;
                }
            }while(check);
        }else if(questionType == -1){ //Rapid fire question picker
            questionNum[0] = rand() % int(numLines/3.0) + 1;
            questionNum[1] = rand() % int(numLines/3.0) + 1;
        }else{ //All other type of question picker
            questionNum[0] = rand() % int(numLines/6.0) + 1;
            questionNum[1] = rand() % int(numLines/6.0) + 1;
        }
        bad = false;

        if(questionNum[0] == questionNum[1] && ( questionType < 15 || questionType >= 18)){
            bad = true;
        }else{

            //Make sure the question has not been used before
            for(int i = 0; i < 70; i++){
                if(questionsUsed[0][i] == questionCatagory && (questionsUsed[1][i] == questionNum[0] || questionsUsed[1][i] == questionNum[1]) ){
                    if(i < 20 && roundNumber == 0){ //If it was in this round pick a new number
                        bad = true;
                    }else if(i < 30 && i >= 20 && roundNumber == 1){
                        bad = true;
                    }else if(i < 50 && i >= 30 && roundNumber == 2){
                        bad = true;
                    }else if(i < 75 && i >= 50 && roundNumber == 3){
                        bad = true;
                    }else{ //if it was a different round try one more time to get a different result
                        if(!tryOnce){
                            bad = true;
                            tryOnce = true;
                        }
                    }
                }
            }

            //Never use a question more then twice
            if(questionAmount[questionCatagory][questionNum[0]-1] > 1 || questionAmount[questionCatagory][questionNum[1]-1] > 1){
                bad = true;
            }
        }
    }while(bad);

    /*
    cout << "questionCatagory: " << questionCatagory << endl;
    cout << "questionNum: " << questionNum[0] << " " << questionNum[1] << endl;
    */

    //Find the higher of the two numbers
    int higher;
    if(questionNum[0] >= questionNum[1]){
        higher = questionNum[0];
    }else{
        higher = questionNum[1];
    }

    //Read through the file until you get both question and answers
    for(int y = 0; y < higher; y++){
        if(questionType == -1){  //Rapid fire question only need three lines, dig site question and answer
            if(y == questionNum[0]-1){ //If is smaller numbered question
                inputFile >> digSite[0];
                inputFile.ignore(500, '\n');
                getline(inputFile, question[0]);
                getline(inputFile, answer[0]);

            }else if(y == questionNum[1]-1){ //Larger number question
                inputFile >> digSite[1];
                inputFile.ignore(500, '\n');
                getline(inputFile, question[1]);
                getline(inputFile, answer[1]);
            }else{ //Neither of the question we are after and can thus be ignored
                inputFile.ignore(500, '\n');
                inputFile.ignore(500, '\n');
                inputFile.ignore(500, '\n');
            }

            //At the very end output the properly formatted output and track which one was used
            if(y ==  higher-1){
                if(digSiteUse[digSite[0]-1] <= digSiteUse[digSite[1]-1]){
                    outputFile << question[0] << endl << "\t" << "A. " <<answer[0] << endl << endl;
                    digSiteUse[digSite[0]-1]++;
                    questionsUsed[1][questionCount] = questionNum[0];
                    questionAmount[questionCatagory][questionNum[0]-1]++;
                }else{
                    outputFile << question[1] << endl << "\t" << "A. " <<answer[1] << endl << endl;
                    digSiteUse[digSite[1]-1]++;
                    questionsUsed[1][questionCount] = questionNum[1];
                    questionAmount[questionCatagory][questionNum[1]-1]++;
                }
            }
        }else if(questionType >= 15 && questionType < 18){ //Memory verse type needs 4 lines dig site and three lines of text, held in answer for convinience
            if(y == questionNum[0]-1 && questionNum[0] == questionNum[1] ){
                inputFile >> digSite[0];
                inputFile.ignore(500, '\n');
                getline(inputFile, answer[0]);
                getline(inputFile, answer[1]);
                getline(inputFile, answer[2]);
            }else if(y == questionNum[0]-1){
                inputFile >> digSite[0];
                inputFile.ignore(500, '\n');
                getline(inputFile, answer[0]);
                getline(inputFile, answer[1]);
                getline(inputFile, answer[2]);
            }else if(y == questionNum[1]-1){
                inputFile >> digSite[1];
                inputFile.ignore(500, '\n');
                getline(inputFile, answer[3]);
                getline(inputFile, answer[4]);
                getline(inputFile, answer[5]);
            }else{
                inputFile.ignore(500, '\n');
                inputFile.ignore(500, '\n');
                inputFile.ignore(500, '\n');
                inputFile.ignore(500, '\n');
            }

            if(y == higher-1){
                if(digSiteUse[digSite[0]-1] <= digSiteUse[digSite[1]-1] || questionNum[0] == questionNum[1]){ //Which is from the dig site that has been used less
                    int found;
                    for(int j = 0; j < 9; j++){
                        if(verseNum[j] == 0){
                            found = j;
                            break;
                        }
                    }
                    verseNum[found] = questionNum[0];
                    questionsUsed[1][questionCount] = questionNum[0];
                    //Complicated rotation to make sure all verse types are used
                    if( (questionType == 15 && verseType[0] != 1) || (questionType == 17 && verseType[2] == 1 && verseType[0] != 1) ||
                        (questionType == 16 && verseType[1] == 1 && verseType[2] == 1) ){
                        outputFile << x << ". Q. Quote " << answer[2] << "\n\t" << answer[0] << " " << answer[1] << endl << endl;
                        verseType[0]++;

                    }else if( (questionType == 16 && verseType[1] != 1) || (questionType == 15 && verseType[0] == 1 && verseType[1] != 1) ||
                             (questionType == 17 && verseType[0] == 1 && verseType[2] == 1) ){
                        outputFile << x << ". V. Finish this verse: " << answer[0] << "\n\t" << answer[1] << " " << answer[2] << endl << endl;
                        verseType[1]++;
                    }else if ( (questionType == 17 && verseType[2] != 1) || (questionType == 16 && verseType[1] == 1 && verseType[2] != 1) ||
                              (questionType == 15 && verseType[0] == 1 && verseType[1] == 1)){
                        outputFile << x << ". R. Finish this verse and give the reference: " << answer[0] << "\n\t" << answer[1] << " ";
                        outputFile << answer[2] << endl << endl;
                        verseType[2]++;
                    }
                    numVersesUsed++;
                    digSiteUse[digSite[0]-1]++;
                    questionAmount[questionCatagory][questionNum[0]-1]++;
                    //cout << "I did this Thing!" << questionCatagory << endl << endl;
                }else{ //Same but using the second choose verse
                    int found;
                    for(int j = 0; j < 9; j++){
                        if(verseNum[j] == 0){
                            found = j;
                            break;
                        }
                    }
                    verseNum[found] = questionNum[1];
                    questionsUsed[1][questionCount] = questionNum[1];
                    if( (questionType == 15 && verseType[0] != 1) || (questionType == 17 && verseType[2] == 1 && verseType[0] != 1) ||
                        (questionType == 16 && verseType[1] == 1 && verseType[2] == 1) ){
                        outputFile << x << ". Q. Quote " << answer[5] << "\n\t" << answer[3] << " " << answer[4] << endl << endl;
                        verseType[0]++;
                    }else if( (questionType == 16 && verseType[1] != 1) || (questionType == 15 && verseType[0] == 1 && verseType[1] != 1) ||
                             (questionType == 17 && verseType[0] == 1 && verseType[2] == 1) ){
                        outputFile << x << ". V. Finish this verse: " << answer[3] << "\n\t" << answer[4] << " " << answer[5] << endl << endl;
                        verseType[1]++;
                    }else if ( (questionType == 17 && verseType[2] != 1) || (questionType == 16 && verseType[1] == 1 && verseType[2] != 1) ||
                              (questionType == 15 && verseType[0] == 1 && verseType[1] == 1)){
                        outputFile << x << ". R. Finish this verse and give the reference: " << answer[3] << "\n\t" << answer[4] << " ";
                        outputFile << answer[5] << endl << endl;
                        verseType[2]++;
                    }
                    numVersesUsed++;
                    digSiteUse[digSite[1]-1]++;
                    questionAmount[questionCatagory][questionNum[1]-1]++;
                    //cout << "I did this Thing!" << questionCatagory << endl << endl;
                }
            }
        }else{ //Else it is of other type which has 6 lines, dig site, question and four for answers
            if(y == questionNum[0]-1){
                inputFile >> digSite[0];
                inputFile.ignore(500, '\n');
                getline(inputFile, question[0]);
                getline(inputFile, answer[0]);
                getline(inputFile, answer[1]);
                getline(inputFile, answer[2]);
                getline(inputFile, answer[3]);
            }else if(y == questionNum[1]-1){
                inputFile >> digSite[1];
                inputFile.ignore(500, '\n');
                getline(inputFile, question[1]);
                getline(inputFile, answer[4]);
                getline(inputFile, answer[5]);
                getline(inputFile, answer[6]);
                getline(inputFile, answer[7]);
            }else{
                inputFile.ignore(500, '\n');
                inputFile.ignore(500, '\n');
                inputFile.ignore(500, '\n');
                inputFile.ignore(500, '\n');
                inputFile.ignore(500, '\n');
                inputFile.ignore(500, '\n');
            }

            //Mark correct answer and make all of above the bottom answer while randomizing other answers
            int select1;
            int select2;
            string temp;
            if(y ==  higher-1){
                if(digSiteUse[digSite[0]-1] <= digSiteUse[digSite[1]-1]){
                    //set all of the above to -1 so we know if it is not one of the answers
                    int allAbove = -1;
                    //Look for all of the above
                    for(int i = 0; i < 4; i++){
                        if(answer[i] == "All of the above" || answer[i] == "All of the above." || answer[i] == "All of the above " || answer[i] == "All of the above  "){
                            allAbove = i;
                        }
                    }
                    //Mark the top answer as correct
                    answer[0] += " Correct Answer";
                    questionsUsed[1][questionCount] = questionNum[0];
                    //If all of the above is not one of the options mix all four around 15 times
                    if(allAbove == -1){
                        for(int z = 0; z < 15; z++){
                            do{
                                select1 = rand() %  4;
                                select2 = rand() %  4;
                            }while(select1 == select2);
                            temp = answer[select1];
                            answer[select1] = answer[select2];
                            answer[select2] = temp;
                        }
                    }else{  //else put all of the above at the bottom and mix the other three around 10 times
                        temp = answer[allAbove];
                        answer[allAbove] = answer[3];
                        answer[3] = temp;
                        for(int z = 0; z < 10; z++){
                            do{
                                select1 = rand() %  3;
                                select2 = rand() %  3;
                            }while(select1 == select2);
                            temp = answer[select1];
                            answer[select1] = answer[select2];
                            answer[select2] = temp;
                        }
                    }
                    //Output
                    outputFile << question[0] << endl << "\t" << "1. " <<answer[0] << endl << "\t" << "2. "  <<answer[1] << endl;
                    outputFile << "\t" << "3. " << answer[2] << endl << "\t" << "4. " << answer[3] << endl << endl;
                    digSiteUse[digSite[0]-1]++;
                    questionAmount[questionCatagory][questionNum[0]-1]++;
                }else{ //Same but for the second chosen question
                    int allAbove = -1;
                    for(int i = 4; i < 8; i++){
                        if(answer[i] == "All of the above" || answer[i] == "All of the above." || answer[i] == "All of the above "){
                            allAbove = i;
                        }
                    }
                    answer[4] += " Correct Answer";
                    questionsUsed[1][questionCount] = questionNum[1];
                    if(allAbove == -1){
                        for(int z = 0; z < 10; z++){
                            do{
                                select1 = rand() %  4 + 4;
                                select2 = rand() %  4 + 4;
                            }while(select1 == select2);
                            temp = answer[select1];
                            answer[select1] = answer[select2];
                            answer[select2] = temp;
                        }
                    }else if(allAbove <= 4){
                        temp = answer[allAbove];
                        answer[allAbove] = answer[7];
                        answer[7] = temp;
                        for(int z = 0; z < 10; z++){
                            do{
                                select1 = rand() %  3 + 4;
                                select2 = rand() %  3 + 4;
                            }while(select1 == select2);
                            temp = answer[select1];
                            answer[select1] = answer[select2];
                            answer[select2] = temp;
                        }
                    }
                    outputFile << question[1] << endl << "\t" << "1. " <<answer[4] << endl << "\t" << "2. "  <<answer[5] << endl;
                    outputFile << "\t" << "3. " << answer[6] << endl << "\t" << "4. " << answer[7] << endl << endl;
                    digSiteUse[digSite[1]-1]++;
                    questionAmount[questionCatagory][questionNum[1]-1]++;
                }
            }
        }
    }

    //Increase the question number that we are on
    questionCount++;
    //Close the input file
    inputFile.close();
    //cout << endl;
}

//Finds the number of lines in a question file
int QuestionPicker::fileLines(string f){
    string line;
    int numLines = 0;
    ifstream file;
    file.open((Folder + f).c_str());
    while(getline(file, line)){
        ++numLines;
    }
    file.close();
    return numLines;
}
