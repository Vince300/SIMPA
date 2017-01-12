package simpa.hit.testing.self;

import org.junit.Assert;
import org.junit.Test;
import simpa.hit.testing.core.MealyGraphTestClass;
import simpa.hit.testing.core.MealyUtils;

/**
 * A test class to validate the functionality provided by {@link MealyUtils}
 */
public class MealyUtilsTest extends MealyGraphTestClass {
    /**
     * Basic test: an automaton is equal to itself
     */
    @Test
    public void helloWorld() {
        Assert.assertTrue(MealyUtils.checkEquality(getCurrentAutomaton(), getCurrentAutomaton()));
    }
}
