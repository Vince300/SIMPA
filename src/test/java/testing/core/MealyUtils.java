package testing.core;

import automata.Automata;
import automata.State;
import automata.mealy.Mealy;
import automata.mealy.MealyTransition;
import com.google.common.collect.BiMap;
import com.google.common.collect.HashBiMap;
import com.google.common.collect.HashMultimap;
import com.google.common.collect.Multimap;

import java.util.*;
import java.util.stream.Stream;

/**
 * Utilities for Mealy automaton testing
 */
public class MealyUtils {
    private Map<Automata, Map<String, BiMap<String, String>>> stateMapCache;
    private Map<Automata, Map<String, Multimap<String, MealyTransitionCheck>>> transitionMapCache;

    private static class AutomatonInstance {
        private String initialStateKey;
        private BiMap<String, String> stateMapCache;

        public String getInitialStateKey() {
            return initialStateKey;
        }

        public BiMap<String, String> getStateMapCache() {
            return stateMapCache;
        }

        public AutomatonInstance(String initialStateKey, BiMap<String, String> stateMapCache) {
            this.initialStateKey = initialStateKey;
            this.stateMapCache = stateMapCache;
        }
    }

    /**
     * Initialize a new equality tester
     */
    public MealyUtils() {
        stateMapCache = new HashMap<>();
        transitionMapCache = new HashMap<>();
    }

    /**
     * Performs a sequence checks to verify that the two given automata are equivalent
     *
     * @param expected   Expected automaton
     * @param conjecture Actual automaton
     */
    public boolean checkEquivalence(Mealy expected, Mealy conjecture) throws RuntimeException {
        System.err.println("warning: only tests equality for now");
        return checkEquality(expected, conjecture);
    }

    /**
     * Performs a sequence checks to verify that the two given automata are equivalent
     *
     * @param expected   Expected automaton
     * @param conjecture Actual automaton
     */
    public boolean checkEquality(Mealy expected, Mealy conjecture) {

        // Try establishing a mapping of the expected states to the conjecture state
        for (AutomatonInstance expectedInstance : allStateMaps(expected)) {
            BiMap<String, String> expectedStateMap = expectedInstance.getStateMapCache();

            for (AutomatonInstance conjectureInstance : allStateMaps(conjecture)) {
                BiMap<String, String> conjectureStateMap = conjectureInstance.getStateMapCache();
                boolean returnValue = true;

                // If size differs, they cannot be equal
                if (expectedStateMap.size() != conjectureStateMap.size()) {
                    continue;
                }

                // Create transition lookup maps
                Multimap<String, MealyTransitionCheck> expectedTransitionMap = buildTransitionMap(expected, expectedInstance.getInitialStateKey());
                Multimap<String, MealyTransitionCheck> conjectureTransitionMap = buildTransitionMap(conjecture, conjectureInstance.getInitialStateKey());

                // expected -> conjecture
                for (String input : expectedTransitionMap.keySet()) {
                    for (MealyTransitionCheck check : expectedTransitionMap.get(input)) {
                        MealyTransition transition = check.getTransition();
                        String sourceState = expectedStateMap.get(transition.getFrom().getName());
                        String destState = expectedStateMap.get(transition.getTo().getName());

                        // look for the corresponding check in the other
                        MealyTransitionCheck target = null;

                        // the list of target transitions with the same input
                        Collection<MealyTransitionCheck> targetChecks = conjectureTransitionMap.get(input);

                        if (targetChecks != null) {
                            for (MealyTransitionCheck targetCheck : targetChecks) {
                                MealyTransition targetTransition = targetCheck.getTransition();

                                // check the output
                                if (targetTransition.getOutput().equals(transition.getOutput())) {
                                    // check the source state
                                    String targetSourceState = conjectureStateMap.get(targetTransition.getFrom().getName());
                                    if (sourceState.equals(targetSourceState)) {
                                        // check the destination state
                                        String targetDestState = conjectureStateMap.get(targetTransition.getTo().getName());
                                        if (destState.equals(targetDestState)) {
                                            target = targetCheck;
                                            break;
                                        }
                                    }
                                }
                            }
                        }

                        if (target == null) {
                            System.err.format("could not find matching transition for %s%n", transition);
                            returnValue = false;
                        } else {
                            if (target.isWalked()) {
                                throw new RuntimeException(String.format("equality check exception, target transition %s already walked for %s", target, transition));
                            }

                            target.setWalked(true);
                        }
                    }
                }

                // conjecture -> expected
                for (String input : conjectureTransitionMap.keySet()) {
                    for (MealyTransitionCheck check : conjectureTransitionMap.get(input)) {
                        if (!check.isWalked()) {
                            System.err.format("extra transition %s%n", check.getTransition());
                            returnValue = false;
                        }
                    }
                }

                // we found a match
                if (returnValue)
                    return true;
                // else continue searching
            }
        }

        return false;
    }

    /**
     * Build a lookup map for transitions of an automaton, based on the input value.
     *
     * @param automaton
     * @param key Initial state name for the current automaton
     * @return Multimap with inputs as keys, matching transitions as values
     */
    private Multimap<String, MealyTransitionCheck> buildTransitionMap(Mealy automaton, String key) {
        Map<String, Multimap<String, MealyTransitionCheck>> cache = transitionMapCache.computeIfAbsent(automaton, k -> new HashMap());

        Multimap<String, MealyTransitionCheck> transitionMap = null;

        if (!cache.containsKey(key)) {
            transitionMap = HashMultimap.create();

            for (MealyTransition transition : automaton.getTransitions()) {
                transitionMap.put(transition.getInput(), new MealyTransitionCheck(transition));
            }

            cache.put(key, transitionMap);
        } else {
            transitionMap = cache.get(key);

            for (MealyTransitionCheck mealyTransitionCheck : transitionMap.values()) {
                mealyTransitionCheck.reset();
            }
        }

        return transitionMap;
    }

    /**
     * Returns a collection of all possible state maps for the given automaton.
     * This is a singleton if an initial state has been defined.
     *
     * @param automaton
     * @return
     */
    private Iterable<AutomatonInstance> allStateMaps(Mealy automaton) {
        State currentState = automaton.getInitialState();

        if (currentState == null) {
            Stream<AutomatonInstance> stream = automaton.getStates().stream()
                    .map(initialState -> new AutomatonInstance(initialState.getName(), buildStateMap(automaton, initialState)));
            return stream::iterator;
        } else {
            return Collections.singleton(new AutomatonInstance(currentState.getName(), buildStateMap(automaton, currentState)));
        }
    }

    /**
     * Assigns a lexicographic order to the states of the given automaton and initial state.
     *
     * @param automaton
     * @param currentState
     * @return Bidirectional map whose keys are the original state names, and values the assigned states
     */
    private BiMap<String, String> buildStateMap(Mealy automaton, State currentState) {
        Map<String, BiMap<String, String>> cache = stateMapCache.computeIfAbsent(automaton, k -> new HashMap<>());

        if (!cache.containsKey(currentState.getName())) {
            BiMap<String, String> stateMap = HashBiMap.create(automaton.getStateCount());
            buildStateMap(stateMap, automaton, currentState, 0);
            cache.put(currentState.getName(), stateMap);
        }

        return cache.get(currentState.getName());
    }

    /**
     * Bimap main recursive function, see {@link #buildStateMap(Mealy, State) buildStateMap}
     *
     * @param stateMapExpected
     * @param expected
     * @param state
     * @param counter
     * @return
     */
    private int buildStateMap(Map<String, String> stateMapExpected, Mealy expected, State state, int counter) {
        // skip infinite loop
        if (stateMapExpected.containsKey(state.getName()))
            return counter;

        // we start with the current state
        stateMapExpected.put(state.getName(), String.format("S%d", counter));

        // increment the counter
        counter++;

        // walk all possible transitions, sorted by (input, output)
        List<MealyTransition> transitionFrom = new ArrayList<>(expected.getTransitionFrom(state));

        transitionFrom.sort((o1, o2) -> {
            int cmp = o1.getInput().compareTo(o2.getInput());
            if (cmp == 0)
                return o1.getOutput().compareTo(o2.getOutput());
            return cmp;
        });

        for (MealyTransition mealyTransition : transitionFrom) {
            // update the counter with the result of the last one
            counter = buildStateMap(stateMapExpected, expected, mealyTransition.getTo(), counter);
        }

        // return current counter
        return counter;
    }

    /**
     * A class that represents the check state of a given transition in a Mealy automaton.
     */
    private static class MealyTransitionCheck {
        private MealyTransition transition;
        private boolean walked;

        /**
         * Creates a new check state for the given transition.
         *
         * @param transition Transition to create a check state from
         */
        public MealyTransitionCheck(MealyTransition transition) {
            this.transition = transition;
        }

        /**
         * @return Transition associated with this state
         */
        public MealyTransition getTransition() {
            return transition;
        }

        /**
         * @return true if this transition has been walked by the algorithm, false otherwise
         */
        public boolean isWalked() {
            return walked;
        }

        /**
         * Defines the value of the walked flag.
         *
         * @param walked New value for the walked flag
         */
        public void setWalked(boolean walked) {
            this.walked = walked;
        }

        @Override
        public String toString() {
            return String.format("[%b] %s", walked, transition);
        }

        /**
         * Resets the state of this check
         */
        public void reset() {
            walked = false;
        }
    }
}
