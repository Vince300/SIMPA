package learner.mealy.table;

import drivers.Driver;
import learner.mealy.LmConjecture;

/**
 * An LmLearner that is capable of remembering its last conjecture (the one that will be output to dot).
 */
public class LmLearnerWithOutput extends LmLearner {
    private LmConjecture lastConjecture;

    /**
     * Intercepts createConjecture calls from LmLearner to grab the reference to the last created conjecture.
     *
     * @return
     */
    @Override
    public LmConjecture createConjecture() {
        return (lastConjecture = super.createConjecture());
    }

    public LmLearnerWithOutput(Driver driver) {
        super(driver);
    }

    public LmConjecture getLastConjecture() {
        return lastConjecture;
    }
}
