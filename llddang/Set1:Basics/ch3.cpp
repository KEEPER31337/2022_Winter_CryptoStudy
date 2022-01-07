#include <iostream>
#include <string>
using namespace std;
char hexToS(string str, int n);

int main(){
    string hexStr = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";
    for(int j=0; j < 256; j++){
        string str = "";
        for(int i=0; i<hexStr.size(); i+=2){
            str += hexToS(hexStr.substr(i, 2), j);
        }
        cout << j << " : " << str << "\n\n";
    }

}

char hexToS(string str, int n){
    int tmp = stoi(str, nullptr, 16);
    tmp ^= n;
    return static_cast<char>(tmp);;
}
