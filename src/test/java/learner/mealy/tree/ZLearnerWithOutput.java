package learner.mealy.tree;

import drivers.Driver;
import learner.mealy.LmConjecture;

/**
 * An ZLearner that is capable of remembering its last conjecture (the one that will be output to dot).
 */
public class ZLearnerWithOutput extends ZLearner {
    private LmConjecture lastConjecture;

    /**
     * Intercepts createConjecture calls from ZLearner to grab the reference to the last created conjecture.
     *
     * @return
     */
    @Override
    public LmConjecture createConjecture() {
        return (lastConjecture = super.createConjecture());
    }

    public ZLearnerWithOutput(Driver driver) {
        super(driver);
    }

    public LmConjecture getLastConjecture() {
        return lastConjecture;
    }
}
