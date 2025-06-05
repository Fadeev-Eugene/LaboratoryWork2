#include "KeyReader.h"
#include <termios.h>
#include <unistd.h>

KeyReader::KeyReader() {
    tcgetattr(STDIN_FILENO, &m_originalTermSettings);
    

    termios newSettings = m_originalTermSettings;
    newSettings.c_lflag &= ~(ICANON | ECHO); 
    tcsetattr(STDIN_FILENO, TCSANOW, &newSettings);
}

KeyReader::~KeyReader() {
    tcsetattr(STDIN_FILENO, TCSANOW, &m_originalTermSettings);
}

char KeyReader::readKey() {
    char ch = 0;
    if (read(STDIN_FILENO, &ch, 1) != 1) ch = 0;
    return ch;
}
