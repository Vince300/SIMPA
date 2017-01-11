package simpa.hit.learner.mealy.table;

import org.junit.Test;
import simpa.hit.testing.core.DotDriverBasedTestClass;
import simpa.hit.testing.core.LmLearnerWithOutput;

/**
 * Defines test methods for the LM class of learning algorithms.
 */
public class LmLearnerTests extends DotDriverBasedTestClass {
    @Test
    public void helloWorld() {
        LmLearnerWithOutput lmLearner = new LmLearnerWithOutput(currentTestDriver);
        lmLearner.learn();
        assertEquivalence(lmLearner.getLastConjecture());
    }
}
