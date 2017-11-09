//
// Created by horovtom on 6.11.17.
//

#ifndef TEXAUTOMATA_AUTOMATON_H
#define TEXAUTOMATA_AUTOMATON_H
#define INTERACTIVE_MAXINPUTS 10

#include <iostream>
#include <vector>
#include <map>
#include "DFAAutomaton.h"

using namespace std;

virtual class Automaton {
protected:
    unsigned int numStates, numLetters;
    vector<string> states;
    vector<string> letters;
//    map<int, map<int, vector<int>>> statesTable;
//    vector<int> initials;
//    vector<int> finals;
//    map<int, vector<int>> epsilons;

/**
 * @return -1 if letter does not exist, its index otherwise.
 */
    int getLetterIndex(string letterName);


    /**
     * @return -1 if state does not exist, its index otherwise
     */
    int getStateIndex(string stateName);

public:
    //region Getters
    const vector<string>& getStates();
    const vector<string>& getLetters();
//    /**
//     * @return null if state or letter does not exist, target state otherwise
//     */
//    const string& fromBy(string state, string letter);
    //endregion

    /**
     * Prints automaton table to the console
     */
    void printAutomatonTable();

    /**
     * @return Automaton table formatted as a string
     */
    string getAutomatonTable();

    /**
     * Prints automaton table to the console in TEX format
     */
    void printAutomatonTableTEX();

    /**
     * @return Automaton table for TEX as a string
     */
    string getAutomatonTableTEX();

    /**
     * Prints automaton TEX Tikz format to the console
     */
    void printAutomatonTEX();

    /**
     * @return Automaton TEX Tikz format as a string
     */
    string getAutomatonTEX();

    /**
     * Converts this automaton to NFA (gets rid of epsilon-transitions)
     */
    NFAAutomaton convertToNFA();

    /**
     * Converts this automaton to DFA (definitizes all the transitions)
     */
    DFAAutomaton convertToDFA();

    /**
     * Reduces this automaton
     */
    DFAAutomaton reduce();

    bool isReduced();

    bool acceptsWord(string word[]);

    string getRegex();

    bool equals(Automaton a);

    void throwError(string errorMsg, int returnVal);

//    /**
//     * Used to get definition from user from command line
//     * Only interactive mode
//     */
//    Automaton();


//
//    /**
//     * Used primarily to define NFA automatons
//     */
//    Automaton(
//        vector<string> states,
//        vector<string> letters,
//        map<string, map<string, vector<string>>> stateTransitions,
//        vector<string> startingStates,
//        vector<string> finishingStates
//    );
//
//    /**
//     * Shorter way to define NFA automatons
//     */
//    Automaton(
//        map<string, map<string, vector<string>>> stateTransitions,
//        vector<string> startingStates,
//        vector<string> finishingStates
//    );
//
//    /**
//     * Used primarily to define ε-NFA automatons
//     */
//    Automaton(
//        vector<string> states,
//        vector<string> letters,
//        map<string, map<string, vector<string>>> stateTransitions,
//        vector<string> startingStates,
//        vector<string> finishingStates,
//        map<string, vector<string>> epsilons
//    );
//
//    /**
//     * Shorter way to define ε-NFA automatons
//     */
//    Automaton(
//        map<string, map<string, vector<string>>> stateTransitions,
//        vector<string> startingStates,
//        vector<string> finishingStates,
//        map<string, vector<string>> epsilons
//    );
//
//    void interactiveDFADef();
//
//    void interactiveNFADef();
//
//    void interactiveENFADef();
//
//    void interactiveGetStatesSigma();



//    void interactiveGetStatesTable();
};




#endif //TEXAUTOMATA_AUTOMATON_H
