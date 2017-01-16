package testing.self;

import org.junit.Assert;
import org.junit.Test;
import testing.core.MealyGraphTestClass;
import testing.core.MealyUtils;

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
