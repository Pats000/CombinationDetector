#include "AnalyzeFileData.h"
//By running constructor the whole process is activated automatically
AnalyzeFileData::AnalyzeFileData(string fileName) : fileName(fileName) {
    FileData.TotalAmount = 0;
    OpenFile();
    ReadFile();
    OrganizeStruct();
}
//Destructor closes the file
AnalyzeFileData::~AnalyzeFileData() {
    if (file.is_open()) {
        file.close(); 
    }
}
//Function for opening the specific txt file
void AnalyzeFileData::OpenFile() {
    file.open(fileName);
    if (!file.is_open()) {
        cerr << "ERROR: Could not open file " << fileName << endl;
        exit(1);
    }
}
/*
Function that reads the data from txt file in chunks.Chunk size is declared as a private member of the class.
After chunk of data is read from file program will give the chunk to Analyze function where the data chunk will be
analyzed for keywords.
 */
void AnalyzeFileData::ReadFile() {
    char BUFFER[BUFFER_SIZE+1] = { 0 };
    vector<char> vBUFFER;
    char ch;
    while (true) {
        file.read(BUFFER, BUFFER_SIZE);
        streamsize bytesRead = file.gcount();
        //BUFFER[bytesRead] = '\0';
        //cout << bytesRead << endl;
       // cout << BUFFER << endl;
        if (bytesRead == 0) {
            return;
        }
        for (streamsize i = 0; i < bytesRead; i++) {
            vBUFFER.push_back(BUFFER[i]);
        }
        if (BUFFER[bytesRead - 1] != ' ' && bytesRead == BUFFER_SIZE) {
            while (file.get(ch)) {
                if (ch == ' ') break;
                vBUFFER.push_back(ch);
            }
        }
        this->Analyze(vBUFFER);
        vBUFFER.clear();
    }
}
/*
Function that analyzes the data chunk by extracting word combinations. When combination is found then the function calls SaveData function where combination is saved
into struct
*/
void AnalyzeFileData::Analyze(vector<char>vBUFFER) {
    int StringLen = 0;
    string sCombination;
    string sCombinationCopy;
    for(const auto& value : vBUFFER) {
        if (value == '\n') return;
        if (value == ' ') {
            sCombination.clear();
        }
        else {
            sCombination += value;
        }
        if (sCombination.length() == 4) {
            SaveData(sCombination);
        }
        else if (sCombination.length() > 4) {
            sCombinationCopy = sCombination;
            while (sCombinationCopy.length() >= 4)
            {
                
                SaveData(sCombinationCopy);
                sCombinationCopy.erase(0, 1);
            }
        }
    }
}
/*
Function that saves combinations into vector pair present inside struct.
*/
void AnalyzeFileData::SaveData(string sCombination) {

    FileData.TotalAmount++; 

    auto it = find_if(FileData.vData.begin(), FileData.vData.end(),
        [&sCombination](const pair<string, float>& VecPair) {
            return VecPair.first == sCombination;
        });
    if (it != FileData.vData.end()) {
        it->second++;
    }
    else {
        FileData.vData.emplace_back(sCombination, 1);
    }
}
/*
Function organizes struct to descending order.
*/
void AnalyzeFileData::OrganizeStruct(){
    
    std::sort(FileData.vData.begin(), FileData.vData.end(),
        [](const pair<string, float>& a, const pair<string, float>& b) {
            return a.second > b.second;
        });
}
/*
Public function that displays the data by frequency
*/
void AnalyzeFileData::GetDataFrequency() {
    cout << "\n\nFrequency:" << endl;
    int count = 0;
    for (const auto& StructData : FileData.vData) {
        if (count == DisplayDataAmount) return;
        cout << StructData.first << ": " << setprecision(4) <<(StructData.second / FileData.TotalAmount) * 100 <<'%'<< endl;
        count++;
    }
}
/*
Public function that displays the data by graph
*/
void AnalyzeFileData::GetDataGraph() {
    cout << "\n\nBar Chart:" << endl;
    int count = 0;
    for (const auto& StructData : FileData.vData) {
        if (count == DisplayDataAmount) return;
        float percentage = (StructData.second / FileData.TotalAmount) * 100;
        int barWidth = (percentage / 100) * maxBarWidth;
        cout << StructData.first << ":\t\t" << string(barWidth, '|') << endl;
        count++; 
    }
}
/*
Public function that returns the chunk size currently being used
*/
int AnalyzeFileData::GetDataReadingSize() {
    return BUFFER_SIZE;
}