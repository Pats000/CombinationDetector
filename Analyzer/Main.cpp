// Main Function that calls class functions. Main function takes txt file input from user who activates it from cmd or if no txt file given it will take default.
#include "Main.h"

using namespace std;
int main(int argc, char** argv)
{
    TimeClass Time;
    Time.TimerStart();
    string input = (argc < 2) ? "test.txt" : argv[1];
    AnalyzeFileData ReadFileData(input);
    ReadFileData.GetDataFrequency();
    ReadFileData.GetDataGraph();
    Time.TimerStop();
    cout << "\nExecution time: " << Time.TimerResult() <<" with data reading chunk size of "<<ReadFileData.GetDataReadingSize() <<" bytes" << endl;
    return 1;
}