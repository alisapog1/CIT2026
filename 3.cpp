#include <iostream>
#include <string>
#include <sstream>
#include <cctype>
#include <set>
#include <algorithm>

using namespace std;

string toLower(string s) {
    transform(s.begin(), s.end(), s.begin(), ::tolower);
    return s;
}

int main() {
    cout << "Введите текст: ";
    
    string text;
    getline(cin, text);

    set<string> question, statement, exclamation;
    string sentence;
    char lastDelim = '.';

    for (size_t i = 0; i < text.length(); i++) {
        sentence += text[i];
        
        if (text[i] == '.' || text[i] == '?' || text[i] == '!') {
            lastDelim = text[i];
            
            stringstream ss(sentence);
            string word;
            while (ss >> word) {
                word.erase(remove_if(word.begin(), word.end(), ::ispunct), word.end());
                
                if (!word.empty()) {
                    word = toLower(word);
                    
                    if (lastDelim == '?') question.insert(word);
                    else if (lastDelim == '.') statement.insert(word);
                    else exclamation.insert(word);
                }
            }
            
            sentence.clear();
        }
    }

    set<string> result;
    for (const string& w : question) {
        if (statement.count(w) && !exclamation.count(w)) {
            result.insert(w);
        }
    }

    cout << "\nРезультат:" << endl;
    if (result.empty()) {
        cout << "Нет подходящих слов" << endl;
    } else {
        for (const string& w : result) {
            cout << w << endl;
        }
    }

    return 0;
}