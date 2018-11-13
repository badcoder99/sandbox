#include <algorithm>
#include <cctype>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <set>
#include <string>
#include <utility>
#include <vector>
using namespace std;

constexpr int Tempo = 45;
constexpr int MS_SEC = 1000;
constexpr int SEC_MIN = 60;

int main() {
   ifstream in("mario.txt");
   string note;
   int beat, count, last;
   set<string> s;
   vector<pair<string, int>> v;
   auto f = [](int beat) {
      return (SEC_MIN * MS_SEC) / (Tempo * beat); 
   };

   while (in >> note >> beat) {
      if (note.front() == ';') {
         continue;
      }
      transform(begin(note), end(note), begin(note), toupper);
      s.insert(note);
      v.emplace_back("NOTE_" + note, f(beat));
   }
   cout << "#include \"notes.h\"" << endl << endl;
   cout << "const int SONG_LEN = " << v.size() << ";" << endl << endl; 
   count = 0, last = 0;
   cout << "const int SONG_FREQ[] = {" << endl;
   for (auto x : v) {
      if (count == 0) {
         cout << "  ";
      }
      cout << x.first << (++last == v.size() ? "\n};\n" : ", ");
      if (++count == 8 && last != v.size()) {
         cout << endl;
         count = 0;
      }
   }
   cout << endl;
   count = 0, last = 0;
   cout << "const int SONG_DUR[] = {" << endl;
   for (auto x : v) {
      if (count == 0) {
         cout << "  ";
      }
      cout << x.second << (++last == v.size() ? "\n};\n" : ", ");
      if (++count == 8 && last != v.size()) {
         cout << endl;
         count = 0;
      }
   }
   cout << endl;
   count = 0, last = 0;
   cout << "const byte SONG_LED[] = {" << endl;
   for (auto x : v) {
      if (count == 0) {
         cout << "  ";
      }
      try {
         char c = x.first.at(5);
         if (c == 'R') {
            cout << 0;
         }
         else {
            cout << c + 1 - 'A';
         }
      }
      catch (out_of_range&) { }
      cout << (++last == v.size() ? "\n};\n" : ", ");
      if (++count == 8 && last != v.size()) {
         cout << endl;
         count = 0;
      }
   }
   cout << endl;
   count = 0, last = 0;
   cout << "const bool SONG_SHARP[] = {" << endl;
   for (auto x : v) {
      if (count == 0) {
         cout << "  ";
      }
      try {
         int n = x.first.size();
         char c = x.first.at(n - 2);
         
         cout << boolalpha << (c == 'S');
      }
      catch (out_of_range&) { }
      cout << (++last == v.size() ? "\n};\n" : ", ");
      if (++count == 8 && last != v.size()) {
         cout << endl;
         count = 0;
      }
   }
}

