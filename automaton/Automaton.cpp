//
// Created by horovtom on 6.11.17.
//

#include "Automaton.h"

//region Manual Definition


//endregion

//region Getters
const vector<string> &Automaton::getStates() {
    return states;
}

const vector<string> &Automaton::getLetters() {
    return letters;
}


//endregion

//region General

void Automaton::throwError(string errorMsg, int returnVal) {
    cerr << errorMsg << endl << "Terminating!" << endl;
    exit(returnVal);
}

int Automaton::getLetterIndex(string letterName) {
    for (int i = 0; i < numLetters; ++i) {
        if (letters[i] == letterName) return i;
    }
    return -1;
}

int Automaton::getStateIndex(string stateName) {
    for (int i = 0; i < states.size(); ++i) {
        if (states[i] == stateName) {
            return i;
        }
    }
    return -1;
}

//endregion