package simpa.hit.testing.core;

import simpa.hit.drivers.Driver;
import simpa.hit.learner.mealy.LmConjecture;
import simpa.hit.learner.mealy.table.LmLearner;

/**
 * An LmLearner that is capable of remembering its last conjecture (the one that will be output to dot).
 */
public class LmLearnerWithOutput extends LmLearner {
    private LmConjecture lastConjecture;

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
