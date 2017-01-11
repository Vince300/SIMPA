package simpa.hit.learner.mealy.table;

import org.junit.Test;
import simpa.hit.testing.core.DotDriverBasedTestClass;

/**
 * Defines test methods for the LM class of learning algorithms.
 */
public class LmLearnerTests extends DotDriverBasedTestClass {
    @Test
    public void helloWorld() {
        LmLearner lmLearner = new LmLearner(currentTestDriver);
        lmLearner.learn();
    }
}
