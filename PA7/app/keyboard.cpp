#include "keyboard.h"

Keyboard::Keyboard()
{

}

/**
 * TODO: TASK 2.2
 *
 * Set keys[index] to key, where index = 0 if keyChar = 'A', etc.
 * Connect the key's clicked() signal with this Keyboard's keyOnScreenPressed() slot.
 */
void Keyboard::addKey(Key *key, const char keyChar) {

}

/**
 * TODO: TASK 2.2
 *
 * Set delKey to key.
 * Connect the key's clicked() signal with this Keyboard's delKeyPressed() slot.
 */
void Keyboard::addDelKey(QPushButton *key) {

}

/**
 * TODO: TASK 2.2
 *
 * Set enterKey to key.
 * Connect the key's clicked() signal with this Keyboard's enterKeyPressed() slot.
 */
void Keyboard::addEnterKey(QPushButton *key) {

}

void Keyboard::setCurrentRound(WordleRound *wr) {
    curRound = wr;
}

// Helper function to get the lowercase letter from a Key
QChar getKeyChar(Key* key) {
    return key->text().at(0).toLower();
}

void Keyboard::keyOnScreenPressed() const {
    keyPressed(getKeyChar(qobject_cast<Key*>(this->sender())));
}

void Keyboard::keyPressed(const QChar& key) const {
    curRound->registerKey(key);
}

void Keyboard::delKeyPressed() const {
    curRound->registerDelKey();
}

void Keyboard::enterKeyPressed() const {
    curRound->registerEnterKey();
}

/**
 * TODO: TASK 2.3
 *
 * Find the Key corresponding to the letter received,
 * get its current color with getColor().
 * If the new color would be "weaker" than the current color, return.
 * Otherwise, set the new color to Key.
 *
 * Hint: convert QChar to char using toLatin1()
 */
void Keyboard::updateKeyColor(const QChar& key, const QColor& color) {

}

void Keyboard::resetKeyColor() {
    for (int i = 0; i < NUM_LETTERS; ++i) {
        keys[i]->reset();
    }
}
