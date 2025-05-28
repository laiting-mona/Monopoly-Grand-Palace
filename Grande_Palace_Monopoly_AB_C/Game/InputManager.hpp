/**
 * @file InputManager.hpp
 * @brief InputManager 工具類別，用於非阻塞地讀取鍵盤輸入。
 */
#ifndef INPUTMANAGER_HPP
#define INPUTMANAGER_HPP

#include <cctype>
#ifdef _WIN32
#  include <conio.h>  // Windows: _getch()
#else
#  include <termios.h>
#  include <unistd.h>
#endif

 /**
  * @brief Utility class to manage keyboard input without requiring the Enter key.
  */
class InputManager {
public:
    /**
     * @brief Get a single character input without pressing Enter (converts to uppercase if letter).
     * @return The character pressed by the user, in uppercase if it is an alphabet.
     */
    static char getKey() {
        int ch;
        while (true) {
#ifdef _WIN32
            ch = _getch();
            if (ch == 0 || ch == 0xE0) {
                (void)_getch();
                continue;
            }
#else
            struct termios oldt, newt;
            tcgetattr(STDIN_FILENO, &oldt);
            newt = oldt;
            newt.c_lflag &= ~(ICANON | ECHO);
            tcsetattr(STDIN_FILENO, TCSANOW, &newt);
            ch = getchar();
            tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
            if (ch == 27) { // handle escape sequences for arrow keys
                getchar();
                getchar();
                continue;
            }
#endif
            if (std::isalnum(ch) || std::ispunct(ch) || ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t') {
                return std::isalpha(ch) ? std::toupper(ch) : ch;
            }
        }
    }

    /**
     * @brief Get a single digit key press without Enter and return its integer value.
     * @return The integer value of the digit pressed (0-9).
     */
    static int getKeyInt() {
        int ch;
        while (true) {
#ifdef _WIN32
            ch = _getch();
            if (ch == 0 || ch == 0xE0) {
                (void)_getch();
                continue;
            }
#else
            struct termios oldt, newt;
            tcgetattr(STDIN_FILENO, &oldt);
            newt = oldt;
            newt.c_lflag &= ~(ICANON | ECHO);
            tcsetattr(STDIN_FILENO, TCSANOW, &newt);
            ch = getchar();
            tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
            if (ch == 27) { // handle escape sequences
                getchar();
                getchar();
                continue;
            }
#endif
            if (std::isdigit(ch)) {
                return ch - '0'; // Convert char digit to int value
            }
        }
    }
};

#endif // INPUTMANAGER_HPP