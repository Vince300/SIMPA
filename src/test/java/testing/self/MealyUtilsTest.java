package testing.self;

import org.junit.Assert;
import org.junit.Test;
import testing.core.MealyGraphTestClass;
import testing.core.MealyUtils;

import java.io.IOException;
import java.nio.file.Path;
import java.nio.file.Paths;

/**
 * A test class to validate the functionality provided by {@link MealyUtils}
 */
public class MealyUtilsTest extends MealyGraphTestClass {
    @Override
    protected Path getTestPath() {
        return Paths.get("data", "test", "utils");
    }

    /**
     * Basic test: an automaton is equal to itself
     */
    @Test
    public void helloWorld() {
        Assert.assertTrue(new MealyUtils().checkEquality(getCurrentAutomaton(), getCurrentAutomaton()));
    }

    /**
     * Test for found bug: automaton with no initial state
     */
    @Test
    public void noInitialState() throws IOException {
        Assert.assertTrue(new MealyUtils().checkEquality(getCurrentAutomaton(), getCurrentAutomaton()));
    }

    /**
     * Test automaton equality when one has no initial state
     */
    @Test
    public void initialStateIndependentEquality() throws IOException {
        Assert.assertTrue(new MealyUtils().checkEquality(loadNamedAutomaton(getTestPath(), "helloWorld"),
                loadNamedAutomaton(getTestPath(), "noInitialState")));
    }
}
