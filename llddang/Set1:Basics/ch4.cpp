#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

vector<string> readFile  (string);
string         findCipher(vector<string>);
string         hexToStr  (string);
string         fixedXor  (string,int);
double         letterFreq(string);

int main(){
    string filePath = "set1_ch4.txt";
    vector<string> fileData = readFile(filePath);

    string plainText = findCipher(fileData);
    cout << plainText << endl;

    return 0;
}

vector<string> readFile(string filePath){
    vector<string> fileData;

    ifstream openFile(filePath.data());
    if(openFile.is_open()){
        string someStr;
        while(getline(openFile, someStr))
            fileData.push_back(someStr);
    }
    return fileData;
}

string findCipher(vector<string> fileData){
    double bestScore = 0;
    string answer = "";
    string xorValue;

    for(string str:fileData){
        for(int i=0; i<256; i++){
            string tmp = hexToStr(str);
            string result = fixedXor(tmp, i);
            double score = letterFreq(result);
            if( bestScore < score ){
                bestScore = score;
                answer = result;
                xorValue = i;
            }
        }
    }

    return answer;
}

string hexToStr(string hexStr){
    string result="";

    for(int i = 0; i < hexStr.size(); i+=2){
        string tmpStr = hexStr.substr(i, 2);
        int tmp = stoi(tmpStr, nullptr, 16);
        result += tmp;
    }

    return result;
}

string fixedXor(string str, int n){
    string result="";

    for(int i = 0; i < str.size(); i++){
        result += (str[i] ^ n);
    }

    return result;
}

double letterFreq(string str){
    double score = 0.0;
    double frequencyTable[] = {8.2, 1.5, 2.8, 4.3, 13, 2.2, 2, 6.1, 7, 0.15,
                               0.77, 4, 2.5, 6.7, 7.5, 1.9, 0.095, 6, 6.3, 9.1,
                               2.8, 0.98, 2.4, 0.15, 2, 0.074};

    for(int i = 0; i < str.size(); i++){
        if(str[i] == ' ')                      score += 20;
        else if(65 <= str[i] && str[i] <= 90)  score += frequencyTable[str[i] - 65];
        else if(97 <= str[i] && str[i] <= 122) score += frequencyTable[str[i] - 97];
    }

    return score;
}
