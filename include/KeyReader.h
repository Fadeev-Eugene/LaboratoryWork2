#ifndef KEYREADER_H
#define KEYREADER_H

#include <termios.h>

class KeyReader {
public:
    KeyReader();
    ~KeyReader();
    char readKey();

private:
    termios m_originalTermSettings;
};

#endif
