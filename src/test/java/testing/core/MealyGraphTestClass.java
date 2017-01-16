package testing.core;

import org.junit.*;
import org.junit.rules.TestName;
import automata.mealy.Mealy;
import main.simpa.Options;

import java.io.File;
import java.io.IOException;
import java.nio.file.Path;
import java.nio.file.Paths;

/**
 * A class for tests based on Mealy automatons.
 */
public abstract class MealyGraphTestClass {
    @Rule
    public TestName name = new TestName();

    // The current automaton being tested
    private Mealy currentAutomaton;

    /**
     * Get the automaton for the current test.
     *
     * @return automaton
     */
    protected Mealy getCurrentAutomaton() {
        if (currentAutomaton == null)
            throw new RuntimeException("no automaton for the current test");
        return currentAutomaton;
    }

    /**
     * Get a value indicating if there is an automaton for the current test.
     *
     * @return true if there is an automaton
     */
    protected boolean hasCurrentAutomaton() {
        return currentAutomaton != null;
    }

    /**
     * Checks graphviz is installed before running the test suite.
     */
    @BeforeClass
    public static void checkPrerequisites() {
        try {
            Process p = Runtime.getRuntime().exec(new String[]{"dot", "-V"});
            p.waitFor();
        } catch (IOException e) {
            Assert.fail("GraphViz is not installed, please install it before running this test suite");
        } catch (InterruptedException e) {
            // ok, ignore
        }
    }

    /**
     * Loads, if available, the current automaton for the currently running test/
     *
     * @throws IOException Could not load the input automaton
     */
    @Before
    public void testInitialize() throws IOException {
        // Setup minimal options
        Options.OUTDIR = Paths.get("data", "test").toString() + File.separator;
        Options.DIRGRAPH = "dot";

        // Load current automaton
        currentAutomaton = loadNamedAutomaton(name.getMethodName());
    }

    /**
     * Cleans up a test case.
     */
    @After
    public void testCleanup() {
        currentAutomaton = null;
    }

    /**
     * Loads an automaton by its name from the data/test/dot folder
     *
     * @param name
     * @return
     * @throws IOException
     */
    protected Mealy loadNamedAutomaton(String name) throws IOException {
        // Path to the test file
        Path dotFilePath = Paths.get("data", "test", "dot", name + ".dot");

        // Load the automaton, if it exists
        File dotFile = dotFilePath.toFile();

        if (dotFile.exists())
            return Mealy.importFromDot(dotFile);
        return null;
    }

    /**
     * Asserts the equivalence of the given automaton with the source automaton for the current test.
     *
     * @param conjecture Actual automaton to check
     */
    protected void assertEquivalence(Mealy conjecture) {
        Assert.assertTrue("output automaton is not equivalent to input", MealyUtils.checkEquivalence(currentAutomaton, conjecture));
    }
}
