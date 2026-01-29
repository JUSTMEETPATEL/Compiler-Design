# BASIC VIVA QUESTIONS – NFA to DFA Conversion

## 1. What is an NFA?
An **NFA (Non-Deterministic Finite Automaton)** is a finite automaton in which multiple transitions for the same input symbol are allowed, including ε (epsilon) transitions.

---

## 2. What is a DFA?
A **DFA (Deterministic Finite Automaton)** is a finite automaton where for each state and input symbol, there is exactly one transition.

---

## 3. Why do we convert NFA to DFA?
DFAs are easier to implement and are required for practical applications such as lexical analyzers and pattern matching.

---

## 4. Are NFA and DFA equivalent?
Yes. For every NFA, there exists an equivalent DFA that accepts the same language.

---

## 5. What is ε-closure?
ε-closure of a state is the set of states reachable from that state using only ε (epsilon) transitions, including the state itself.

---

## 6. What is the move function?
The move function returns the set of states reachable from a given state on a particular input symbol.

---

## 7. What method is used to convert NFA to DFA?
The **subset construction method** (also called the powerset construction) is used.

---

## 8. What does each DFA state represent?
Each DFA state represents a **set of NFA states**.

---

## 9. How is ε-closure implemented in your program?
By using a stack-based traversal that recursively finds all states reachable through ε transitions.

---

## 10. What is the start state of the DFA?
The ε-closure of the NFA’s start state.

---

## 11. How is the final state of DFA determined?
Any DFA state that contains at least one final state of the NFA is considered a final state.

---

## 12. What data structure is used to store transitions?
Arrays are used to store NFA transitions and DFA state sets.

---

## 13. Can every NFA be converted to DFA?
Yes, every NFA can be converted into an equivalent DFA.

---

## 14. Does NFA to DFA conversion increase states?
Yes. In the worst case, the DFA can have up to **2ⁿ states** for an NFA with **n states**.

---

## 15. What is the advantage of DFA over NFA?
DFA has predictable transitions and faster execution since only one transition exists per input symbol.

---

## 16. What are real-world applications of DFA?
- Lexical analysis in compilers  
- Regular expression matching  
- Network protocol design  
- Text searching algorithms  

---

## 17. Can DFA have ε transitions?
No, DFA cannot have ε transitions.

---

## 18. What happens if no transition exists for an input symbol in DFA?
The automaton moves to a **dead (trap) state**.

---

## 19. What is a dead state?
A dead state is a non-accepting state from which no accepting state can be reached.

---

## 20. What language does your NFA accept?
The language **(a/b)\*abb**, i.e., all strings ending with **"abb"**.
