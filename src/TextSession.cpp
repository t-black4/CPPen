#include "TextSession.h"
#include <string>

TextSession::TextSession() {
    if (Lines.empty()) {
        Lines.push_back(std::vector<char>()); // Initialize with one empty line
    }
    cursorX = 0;
    cursorY = 0;
}

TextSession::~TextSession() {
    // Destructor: Clean up resources if necessary
}



void TextSession::inputText(char ch) {
    // Ensure Lines is not empty and cursorY is valid for basic operations
    if (Lines.empty()) {
        Lines.push_back(std::vector<char>());
        cursorY = 0;
        cursorX = 0;
    }

    // Ensure cursorY is within bounds, resize if necessary (should be rare if logic is correct)
    if (static_cast<size_t>(cursorY) >= Lines.size()) {
        Lines.resize(cursorY + 1, std::vector<char>());
    }
    // Ensure cursorX is within bounds of the current line for insertion/deletion
    if (static_cast<size_t>(cursorX) > Lines[cursorY].size()) {
        cursorX = Lines[cursorY].size();
    }

    if (ch == '\0') { // Backspace
        if (cursorX > 0) {
            // Backspace within the current line
            cursorX--;
            Lines[cursorY].erase(Lines[cursorY].begin() + cursorX);
        } else if (cursorY > 0) {
            // Backspace at the beginning of a line (cursorX is 0)
            // Store the size of the previous line for new cursorX
            size_t prevLineSize = Lines[cursorY - 1].size();
            // Append current line's content to the previous line
            Lines[cursorY - 1].insert(Lines[cursorY - 1].end(), Lines[cursorY].begin(), Lines[cursorY].end());
            // Remove the current line
            Lines.erase(Lines.begin() + cursorY);
            // Move cursor to the end of the merged line
            cursorY--;
            cursorX = static_cast<int>(prevLineSize);
        }
        // If cursorX is 0 and cursorY is 0, do nothing (cannot backspace further)
    } else if (ch == '\n') { // Newline
        std::vector<char> newLineFragment;
        // If cursor is within the current line, split it
        if (static_cast<size_t>(cursorX) < Lines[cursorY].size()) {
            newLineFragment.assign(Lines[cursorY].begin() + cursorX, Lines[cursorY].end());
            Lines[cursorY].erase(Lines[cursorY].begin() + cursorX, Lines[cursorY].end());
        }
        // Insert the new line fragment (or an empty line) after the current one
        cursorY++;
        Lines.insert(Lines.begin() + cursorY, newLineFragment);
        cursorX = 0;
    } else { // Regular character
        // Insert character at Lines[cursorY][cursorX]
        Lines[cursorY].insert(Lines[cursorY].begin() + cursorX, ch);
        cursorX++;
    }
}

std::string TextSession::getDisplayString() const {
    std::string displayString;
    for (size_t i = 0; i < Lines.size(); ++i) {
        for (char ch_in_line : Lines[i]) {
            displayString += ch_in_line;
        }
        if (i < Lines.size() - 1) { // Add newline only if it's not the last line
            displayString += '\n';
        }
    }
    return displayString;
}

