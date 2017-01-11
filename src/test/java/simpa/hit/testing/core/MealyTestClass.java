package simpa.hit.testing.core;

import simpa.hit.automata.mealy.Mealy;

/**
 * A base class for test cases about Mealy automata.
 */
public abstract class MealyTestClass {
    /**
     * Performs a sequence checks to verify that the two given automata are equivalent
     *
     * @param expected   Expected automaton
     * @param conjecture Actual automaton
     */
    protected boolean checkEquivalence(Mealy expected, Mealy conjecture) {
        System.err.println("warning: not yet implemented");
        return true;
    }
}
