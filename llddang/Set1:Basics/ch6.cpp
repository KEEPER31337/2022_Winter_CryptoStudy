#include <iostream>
#include <fstream>
#include <string>
#include <bitset>
#include <vector>
using namespace std;

string base64Decoder  (string);
string base64Encoder  (string);
string hex_to_binary  (string);
int    hammingDistance(string, string);
int    findKeySize    (string);
void   transposeString(string, int);
string getKey();
string xorCombination (string,string);
string base64table = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

vector<vector<char>> trans;

int main(){
    string enStr = "";
    string readFilePath = "thisfile.txt";
    ifstream readFile(readFilePath.data());
    if(readFile.is_open()){
        string line;
        while(getline(readFile, line)){
            enStr += line;
        }
        readFile.close();
    }

    string xorStr = base64Decoder(enStr);
    int keysize = findKeySize(xorStr);
    transposeString(xorStr, keysize);
    string key = getKey();
    cout << "key : " << key << "\n";
    string writeFilePath = "thisfile2.txt";
    ofstream writeFile(writeFilePath.data());
    if(writeFile.is_open()){
        string str = xorCombination(xorStr, key);
        writeFile << str;
        writeFile.close();
    }
}

string getKey(){
    string common = "ETAOIN SHRDLUetaoinshrdlu";
    string key = "";

    for(auto vec:trans){
        int highScore = 0;
        int keyChar;
        for(int i=0; i<256; i++){
            string str = "";
            int score = 0;
            for(char ch : vec){
                str += ch^i;
            }
            for(int j=0; j<str.size(); j++){
                for(int k=0; k<common.size(); k++){
                    if(str[j] == common[k]){
                        score++;
                        break;
                    }
                }
            }
            if(highScore < score){
                highScore = score;
                keyChar = i;
            }
        }
        key += keyChar;
    }
    return key;
}

void transposeString(string str, int keysize){
    for(int i=0; i<keysize; i++){
        vector<char> a;
        trans.push_back(a);
    }

    for(int i=0; i<str.size(); i++){
        int site = i%keysize;
        trans[site].push_back(str[i]);
    }
}

int hammingDistance(string strA, string strB){
    int hamming = 0;
    for(int j=0; j<strA.size(); j++){
        int intA = strA[j];
        int intB = strB[j];

        int x = intA ^ intB;
        while(x > 0){
            hamming += x & 1;
            x >>= 1;
        }
    }
    return hamming;
}

int findKeySize(string xorStr){
    double hammingMin = 100;
    int keysize;
    for(int keylen=2; keylen<=40; keylen++){
        double sum = 0.0;
        int len = 0;
        int start = 0;
        int ende = start + keylen;
        while(1){
            string strA, strB;
            try {
                strA = xorStr.substr(start, keylen);
                strB = xorStr.substr(ende, keylen);
            } catch (const std::out_of_range& e) {
                break;
            }
            int distance = hammingDistance(strA, strB);
            sum += (double)distance / keylen;
            len++;
            start = ende + keylen;
            ende = start + keylen;
        }
        double hamming = sum / len;
        if(hamming < hammingMin){
            hammingMin = hamming;
            keysize = keylen;
        }
        //cout << "[+] keysize : " << keylen << "\n";
        //cout << "[+] Hamming : " << hamming << "\n\n";
    }

    //cout << "\t[+] keysize : " << keysize << "\n";
    //cout << "\t[+] Hamming : " << hammingMin << "\n\n";
    return keysize;
}

string xorCombination(string str, string key){
    string result="";
    for(int i=0; i<str.size(); i++){
        int a = str[i];
        int b = key[i==0 ? 0 : i%key.size()];
        b ^= a;
        result += static_cast<char>(b);
    }
    return result;
}

string base64Decoder(string base64Str){
    string bin = "";
    for(int i=0; i<base64Str.size(); i++){
        if(base64Str[i] == '=') continue;
        int j=0;
        for(; j<64; j++){
            if(base64table[j] == base64Str[i]) break;
        }
        string binary;
        for(int k = 0; k < 6; k++){
            if((j%2) == 1)
                binary = "1" + binary;
            else
                binary = "0" + binary;
            j /= 2;
        }
        bin += binary;
    }
    if(base64Str[base64Str.size()-2] == '=')
        bin.erase(bin.size()-6, 4);
    else if(base64Str[base64Str.size()-1] == '=')
        bin.erase(bin.size()-6, 2);

    string result = "";
    for(int i=0; i < bin.size(); i+=8){
        string str = bin.substr(i,8);
        int a = stoi(str, nullptr, 2);
        result += a;
    }
    return result;
}

string base64Encoder(string bin){
    string base64Str = "";
    if(bin.size() % 6 == 0){
        for(int i=0; i<bin.size(); i+=6){
            string tmp = bin.substr(i, 6);
            int site = stoi(tmp, 0, 2);
            base64Str += base64table[site];
        }
    } else {
        int i=0;
        for(; i<bin.size()-6; i+=6){
            string tmp = bin.substr(i, 6);
            int site = stoi(tmp, 0, 2);
            base64Str += base64table[site];
        }
        int rest = bin.size() % 6;
        string tmp = bin.substr(i, rest);
        int site = stoi(tmp, 0, 2);
        base64Str += base64table[site];
        if     (rest == 2) base64Str += "==";
        else if(rest == 4) base64Str += "=";
    }
    return base64Str;
}


string hex_to_binary(string hexStr){
    string bin = "";
    for(int i=0; i < hexStr.size(); i+=2){
        string str = hexStr.substr(i, 2);
        int a = stoi(str, nullptr, 16);
        string binary = "";
        for(int i = 0; i < 8; i++){
            if((a%2) == 1)
                binary = "1" + binary;
            else
                binary = "0" + binary;
            a /= 2;
        }
        bin += binary;
    }
    return bin;
}
