#ifndef UTILS_H
#define UTILS_H

#include <bits/stdc++.h>
#ifdef _WIN32
    #include <windows.h>
    #define SLEEP(ms) Sleep(ms)
#else
    #include <unistd.h>
    #define SLEEP(ms) usleep(ms * 1000)
#endif
using namespace std;

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"
#define BOLD    "\033[1m"

inline void slowPrint(const string &text, int delay = 8) {
    for (int i = 0; i < (int)text.size(); i++) {
        cout << text[i] << flush;
        SLEEP(delay);  // works on both Windows and Linux
    }
}

inline void line() {
    cout << WHITE << "------------------------------------------------------------" << RESET << endl;
}

#endif
