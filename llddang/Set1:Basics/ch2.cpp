#include <iostream>
#include <string>
using namespace std;
int strToB(string str);

int main(){
    string hexStrA = "1c0111001f010100061a024b53535009181c";
    string hexStrB = "686974207468652062756c6c277320657965";
    string xorStr = "";
    for(int i=0; i<hexStrA.size(); i+=4){
        int A = strToB(hexStrA.substr(i, 4));
        int B = strToB(hexStrB.substr(i, 4));
        int C = A ^ B;
        cout << hex << C;
    }
}

int strToB(string str){
    return stoi(str, nullptr, 16);
}
