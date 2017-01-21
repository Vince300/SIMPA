package learner.mealy.combinatorial;

import automata.Automata;
import drivers.mealy.MealyDriver;

/**
 * An CombinatorialLearner that is capable of remembering its last conjecture (the one that will be output to dot).
 */
public class CombinatorialLearnerWithOutput extends CombinatorialLearner {
    private Automata lastConjecture;

    /**
     * Intercepts createConjecture calls from CombinatorialLearner to grab the reference to the last created conjecture.
     *
     * @return
     */
    @Override
    public Automata createConjecture() {
        return (lastConjecture = super.createConjecture());
    }

    public CombinatorialLearnerWithOutput(MealyDriver driver) {
        super(driver);
    }

    public Automata getLastConjecture() {
        return lastConjecture;
    }
}
