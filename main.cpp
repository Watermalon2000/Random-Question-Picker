#include "questionpicker.h"

int main(){
    srand(time(0));

    string oFileName;

    cout << "Welcome to the random question picker.\n";
    cout << "What is the name of the file you want to save it to: ";
    cin >> oFileName;

    QuestionPicker qp(oFileName);

    qp.Activate();
    //qp.OutputUsed();
    return 0;
}
