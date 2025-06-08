


#include <vector>
#include <string>

class TextSession {
public:
    TextSession();
    ~TextSession();

    void inputText(char ch);
    std::string getDisplayString() const;
    int getcursorX() const { return cursorX; }  
    int getcursorY() const { return cursorY; }
    void setcursorX(int x) { cursorX = x; }
    void setcursorY(int y) { cursorY = y; }
private:
    int cursorX = 0;
    int cursorY = 0;
    std::vector<std::vector<char>> Lines;
};