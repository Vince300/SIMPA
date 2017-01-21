package testing.self;

import org.junit.Assert;
import org.junit.Test;
import testing.core.MealyGraphTestClass;
import testing.core.MealyUtils;

import java.io.IOException;
import java.nio.file.Paths;

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

    /**
     * Test for found bug: automaton with no initial state
     */
    @Test
    public void noInitialState() throws IOException {
        setCurrentAutomaton(loadNamedAutomaton(Paths.get("data", "test", "misc"), "noInitialState"));
        Assert.assertTrue(MealyUtils.checkEquality(getCurrentAutomaton(), getCurrentAutomaton()));
    }
}
