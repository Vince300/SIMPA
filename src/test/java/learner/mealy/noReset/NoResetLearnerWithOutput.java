package learner.mealy.noReset;

import drivers.Driver;
import drivers.mealy.MealyDriver;
import learner.mealy.LmConjecture;
import learner.mealy.noReset.dataManager.DataManager;

/**
 * An NoResetLearner that is capable of remembering its last conjecture (the one that will be output to dot).
 */
public class NoResetLearnerWithOutput extends NoResetLearner {
    public NoResetLearnerWithOutput(MealyDriver driver) {
        super(driver);
    }

    public LmConjecture getLastConjecture() {
        return DataManager.instance.getConjecture();
    }
}
