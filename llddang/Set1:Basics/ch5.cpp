#include <iostream>
#include <string>
using namespace std;

int main(){
    string str = "Burning 'em, if you ain't quick and nimble\nI go crazy when I hear a cymbal";
    string key = "ICE";

    for(int i=0; i<str.size(); i++){
        int a = str[i];
        int b = key[i==0 ? 0 : i%3];
        b ^= a;
        cout << std::hex << b;
        if(i == 37){
            cout << "\n";
            cout << "b3637272a2b2e63622c2e69692a23693a2a3c6324202d623d63343c2a26226324272765272a";
            cout << "\n\n";
        }
    }
    cout << "\n";
    cout << "282b2f2043a652e2c652a3124333a653e2b2027630c692b20283165286326302e27282f";
}
