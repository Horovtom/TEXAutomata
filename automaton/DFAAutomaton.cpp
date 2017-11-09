//
// Created by horovtom on 8.11.17.
//

#include <sstream>
#include "DFAAutomaton.h"

//region Constructors

DFAAutomaton::DFAAutomaton() {
    cout << "Interactive mode" << endl;
    cout << "Enter the definition of the automaton" << endl;
    interactiveGetStatesSigma();
    interactiveGetStatesTable();
    interactiveGetStartingFinal();
    //TODO: IMPLEMENT
}

void DFAAutomaton::interactiveGetStatesSigma() {
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

void DFAAutomaton::interactiveGetStatesTable() {
    cout << "Now enter the states table for this automaton. Each pointer will be separated by ' '" << endl;

    for (int i = 0; i < numStates; ++i) {
        interactiveLoadStateRow(i);
    }
}

void DFAAutomaton::interactiveLoadStateRow(int i) {
    //Print state name
    cout << states[i] << " ";
    string s;
    vector<int> stateLine;
    for (int j = 0; j < numLetters; ++j) {
        cin >> s;
        int index = getStateIndex(s);
        if (index == -1) return interactiveLoadStateRow(i);
        stateLine.push_back(index);
    }

    statesTable.push_back(stateLine);
}

//region General

const string &DFAAutomaton::fromBy(string state, string letter) {
    int stateIndex = getStateIndex(state);
    int letterIndex = getLetterIndex(letter);
    if (stateIndex == -1 || letterIndex == -1) return NULL;
}

void DFAAutomaton::interactiveGetStartingFinal() {
    int index;
    do {
        cout << "Enter starting state name: ";
        string name;
        cin >> name;
        index = getStateIndex(name);
        if (index == -1) {
            cerr << "Such state was not found! Possible states are: ";
            for (int i = 0; i < states.size(); ++i) {
                cerr << states[i] << " ";
            }
            cerr << endl;
        }
    } while (index == -1);
    initial = index;

    cout << "How many final states: ";
    int howMany;
    cin >> howMany;
    bool right = true;

    do {
        finals.clear();
        cout << "Enter final states names separated by ' '";


        for (int i = 0; i < howMany; ++i) {
            string state;
            cin >> state;
            index = getStateIndex(state);
            if (index == -1) {
                cerr << "There is no such state: " << state << "! Try again!" << endl;
                cin.clear();
                right = false;
                break;
            }
            finals.push_back(index);
        }
    } while(!right);
}


//endregion