package learner.mealy.rivestSchapire;

import automata.mealy.Mealy;
import drivers.mealy.MealyDriver;

/**
 * An RivestSchapireLearner that is capable of remembering its last conjecture (the one that will be output to dot).
 */
public class RivestSchapireLearnerWithOutput extends RivestSchapireLearner {
    private Mealy lastConjecture;

    /**
     * Intercepts createConjecture calls from RivestSchapireLearner to grab the reference to the last created conjecture.
     *
     * @return
     */
    @Override
    public Mealy createConjecture() {
        return (lastConjecture = super.createConjecture());
    }

    public RivestSchapireLearnerWithOutput(MealyDriver driver) {
        super(driver);
    }

    public Mealy getLastConjecture() {
        return lastConjecture;
    }
}
