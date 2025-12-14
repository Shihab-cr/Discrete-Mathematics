#include <string>
#include <unordered_map>
#include <iostream>
#include <cmath>
#include <numeric>

using namespace std;

int positiveMod(int x, int y){
    int r = x % y;
    if(r < 0){
        r += y;
    }
    return r;
}

int extendedGCD(int a, int b, int &x, int &y) {
    if (b == 0) {
        x = 1; y = 0;
        return a;
    }
    int x1, y1;
    int g = extendedGCD(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return g;
}

int modInverse(int a, int m) {
    int x, y;
    int g = extendedGCD(a, m, x, y);
    if (g != 1) return -1;
    return positiveMod(x, m);
}

unordered_map<char, int> mapForChars(const string &alphabet){
    unordered_map<char, int> map;
    for(int i = 0; i < alphabet.size(); i++){
        map[alphabet[i]] = i;
    }
    return map;
}

string encrypt(const string &plainText, int a, int b, const string &alphabet){
    int m = alphabet.size();
    unordered_map<char, int> map = mapForChars(alphabet);
    string encryptedText = "";
    for(int i = 0; i < plainText.size(); i++){
        encryptedText += alphabet[positiveMod(a * map[plainText[i]] + b, m)];
    }
    return encryptedText;
}

string decrypt(const string &encryptedText, int a, int b, const string &alphabet){
    int m = alphabet.size();
    unordered_map<char, int> map = mapForChars(alphabet);
    int aInv = modInverse(a, m);
    if(aInv == -1){
        return "No inverse exists for a";
    }
    string decryptedText = "";
    for(int i = 0; i < encryptedText.size(); i++){
        decryptedText += alphabet[positiveMod(aInv*(map[encryptedText[i]]-b),m)];
    }
    return decryptedText;
}

int main() {
    string alphabet = " AEFGILMNOPSTUV";
    int m = alphabet.size(); 

    cout << "Alphabet used: " << alphabet << endl;
    cout << "m = " << m << endl;

    // ====== PART 1: Assigned message inside code ======
    string message = "TAIA MALOSI LE FILI";
    int a = 13, b = 17;

    cout << "\nAssigned message: " << message << endl;
    cout << "Ciphering keys: a=" << a << ", b=" << b << endl;

    if (gcd(a, m) != 1) {
        cout << "Invalid key a. gcd(a, m) != 1\n";
        return 0;
    }

    string cipher = encrypt(message, a, b, alphabet);
    cout << "Ciphered message: " << cipher << endl;

    string decrypted = decrypt(cipher, a, b, alphabet);
    cout << "Deciphered message: " << decrypted << endl;

    // ====== PART 2: User input ======
    cout << "\n--- User Input Mode ---\n";

    cout << "Enter message (only Samoan letters + space): ";
    string userMsg;
    getline(cin, userMsg);

    cout << "Enter key a: ";
    cin >> a;
    cout << "Enter key b: ";
    cin >> b;

    if (gcd(a, m) != 1) {
        cout << "Invalid key a. gcd(a, m) != 1\n";
        return 0;
    }

    cipher = encrypt(userMsg, a, b, alphabet);
    cout << "Ciphered: " << cipher << endl;

    decrypted = decrypt(cipher, a, b, alphabet);
    cout << "Deciphered: " << decrypted << endl;

    return 0;
}

