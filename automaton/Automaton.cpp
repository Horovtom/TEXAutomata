//
// Created by horovtom on 6.11.17.
//

#include "Automaton.h"

//region Manual Definition

Automaton::Automaton() {
    cout << "Interactive mode" << endl;
    cout << "Enter the definition of the automaton" << endl;
    int i = INTERACTIVE_MAXINPUTS;
    while (i--) {
        cout << "What automaton is this?" << endl << "1: DFA" << endl << "2: NFA" << endl << "3: ε-NFA" << endl;
        int res;
        cin >> res;
        switch (res) {
            case 1:
                interactiveDFADef();
                return;
            case 2:
                interactiveNFADef();
                return;
            case 3:
                interactiveENFADef();
                return;
            default:
                cerr << "Unrecognized option " << res << " please, enter valid option!" << endl;
                break;
        }
    }
    throwError("Exceeded maximum number of invalid inputs!", -1);
}

void Automaton::interactiveDFADef() {
    interactiveGetStatesSigma();
    interactiveGetStatesTable();
    //TODO: IMPLEMENT
}

void Automaton::interactiveNFADef() {
    //TODO: IMPLEMENT
}

void Automaton::interactiveENFADef() {
    //TODO: IMPLEMENT
}

void Automaton::interactiveGetStatesSigma() {
    int i = INTERACTIVE_MAXINPUTS;
    while (i--) {
        cout << "Number of states: ";
        cin >> numStates;
        if (numStates > 0) break;
        if (i == 0) throwError("Exceeded maximum number of invalid inputs!", -2);
        cerr << "Number of states must be positive!" << endl;
    }

    cout << "Enter " << numStates << " state names, separated by ' '" << endl;
    string loaded;
    for (int j = 0; j < numStates; ++j) {
        cin >> loaded;
        states.push_back(loaded);
    }

    i = INTERACTIVE_MAXINPUTS;
    while (i--) {
        cout << "Number of letters: ";
        cin >> numLetters;
        if (numLetters > 0) break;
        if (i == 0) throwError("Exceeded maximum number of invalid inputs!", -2);
        cerr << "Number of states must be positive!" << endl;
    }

    cout << "Enter " << numLetters << " letter names, separated by ' '" << endl;
    for (int j = 0; j < numLetters; ++j) {
        cin >> loaded;
        letters.push_back(loaded);
    }
}

void Automaton::interactiveGetStatesTable() {
    //TODO: IMPLEMENT
}

//endregion

//region Getters
const vector<string> &Automaton::getStates() {
    return states;
}

const vector<string> &Automaton::getLetters() {
    return letters;
}

const string &Automaton::fromBy(string state, string letter) {
    //TODO: IMPLEMENT
}
//endregion

//region General

void Automaton::throwError(string errorMsg, int returnVal) {
    cerr << errorMsg << endl << "Terminating!" << endl;
    exit(returnVal);
}



//endregion