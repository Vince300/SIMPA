package learner.mealy.tree;

import drivers.mealy.MealyDriver;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.junit.runners.Parameterized;
import testing.core.DotDriverBasedTestClass;

import java.io.File;
import java.io.IOException;
import java.util.Collection;

/**
 * Defines test methods for the LM class of learning algorithms.
 */
@RunWith(Parameterized.class)
public class ZLearnerTests extends DotDriverBasedTestClass {
    private final File graphFile;

    /**
     * Builds the test suite
     * @return
     */
    @Parameterized.Parameters(name = "{1}")
    public static Collection<Object[]> suite() {
        return buildSuite(getDefaultTestPath());
    }

    /**
     * Runs a test for a given automaton from the initialized context
     */
    @Test()
    public void runTest() {
        ZLearnerWithOutput ZLearner = new ZLearnerWithOutput(currentTestDriver);
        ZLearner.learn();
        assertEquivalence(ZLearner.getLastConjecture());
    }

    @Override
    public void testInitialize() throws IOException {
        // Load the automaton
        setCurrentAutomaton(loadAutomatonFromFile(graphFile));

        // Create the driver from the given graphFile
        // We do not use FromDotMealyDriver because we need the actual Mealy instance.
        // Also, FromDotMealyDriver exports the input graph (why?)
        currentTestDriver = new MealyDriver(getCurrentAutomaton());
    }

    /**
     * Initializes a new instance of a ZLearner test.
     * @param graphFile The file being tested
     * @param name Test name
     */
    public ZLearnerTests(File graphFile, @SuppressWarnings("unused") String name) {
        this.graphFile = graphFile;
    }
}
