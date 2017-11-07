//
// Created by horovtom on 6.11.17.
//

#ifndef TEXAUTOMATA_AUTOMATON_H
#define TEXAUTOMATA_AUTOMATON_H
#define INTERACTIVE_MAXINPUTS 10

#include <iostream>
#include <vector>
#include <map>

using namespace std;

class Automaton {
private:
    unsigned int numStates, numLetters;
    vector<string> states;
    vector<string> letters;
    map<int, map<int, vector<int>>> statesTable;
    vector<int> initials;
    vector<int> finals;
    map<int, vector<int>> epsilons;

public:
    //region Getters
    const vector<string>& getStates();
    const vector<string>& getLetters();
    /**
     * @return null if state or letter does not exist, target state otherwise
     */
    const string& fromBy(string state, string letter);
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
    void convertToNFA();

    /**
     * Converts this automaton to DFA (definitizes all the transitions)
     */
    void convertToDFA();

    /**
     * Reduces this automaton
     */
    void reduce();

    bool isENFA();

    bool isNFA();

    bool isDFA();

    bool isReduced();

    bool acceptsWord(string word[]);

    string getRegex();

    bool equals(Automaton a);

    /**
     * Used to get definition from user from command line
     * Only interactive mode
     */
    Automaton();

    /**
     * Used primarily to define DFA automatons
     */
    Automaton(
        vector<string> states,
        vector<string> letters,
        map<string, map<string, string>> stateTransitions,
        string startingState,
        vector<string> finishingStates
    );

    /**
     * Shorter way to define DFA automatons
     */
    Automaton(
        map<string, map<string, string>> stateTransitions,
        string startingState,
        vector<string> finishingStates
    );

    /**
     * Used primarily to define NFA automatons
     */
    Automaton(
        vector<string> states,
        vector<string> letters,
        map<string, map<string, vector<string>>> stateTransitions,
        vector<string> startingStates,
        vector<string> finishingStates
    );

    /**
     * Shorter way to define NFA automatons
     */
    Automaton(
        map<string, map<string, vector<string>>> stateTransitions,
        vector<string> startingStates,
        vector<string> finishingStates
    );

    /**
     * Used primarily to define ε-NFA automatons
     */
    Automaton(
        vector<string> states,
        vector<string> letters,
        map<string, map<string, vector<string>>> stateTransitions,
        vector<string> startingStates,
        vector<string> finishingStates,
        map<string, vector<string>> epsilons
    );

    /**
     * Shorter way to define ε-NFA automatons
     */
    Automaton(
        map<string, map<string, vector<string>>> stateTransitions,
        vector<string> startingStates,
        vector<string> finishingStates,
        map<string, vector<string>> epsilons
    );

    void interactiveDFADef();

    void interactiveNFADef();

    void interactiveENFADef();

    void interactiveGetStatesSigma();

    void throwError(string errorMsg, int returnVal);

    void interactiveGetStatesTable();
};




#endif //TEXAUTOMATA_AUTOMATON_H
