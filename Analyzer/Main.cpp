// Main Function that calls class functions. Main function takes txt file input from user who activates it from cmd. 
#include "Main.h"

using namespace std;
int main(int argc, char** argv)
//int main()
{
    string input = argv[1];
    TimeClass Time;
    Time.TimerStart();
    //string input = "test.txt";
    AnalyzeFileData ReadFileData(input);
    ReadFileData.GetDataFrequency();
    ReadFileData.GetDataGraph();
    Time.TimerStop();
    cout << "\nExecution time: " << Time.TimerResult() <<" with data reading chunk size of "<<ReadFileData.GetDataReadingSize() <<" bytes" << endl;
    return 1;
}