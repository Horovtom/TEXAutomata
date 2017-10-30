# TEXAutomata
Generates TIKZ code from table

The final product might need some refactoring. At least laying out states so that they are in least tangled configuration by relative positioning.
\node[state]    (1) [_ of=0] {$1$};
replace _ with below/right/left/above and their combinations. You can as well substitute 0 with another previously declared number.
You can freely change the order of \node declarations.
