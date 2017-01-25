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
     * Sets the current automaton for testing
     *
     * @param currentAutomaton
     */
    public void setCurrentAutomaton(Mealy currentAutomaton) {
        this.currentAutomaton = currentAutomaton;
    }

    /**
     * Checks graphviz is installed before running the test suite.
     */
    // @BeforeClass
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
        Path testFolder = getTestPath();

        // Initialize options
        initializeOptions(testFolder);

        // Load current automaton
        currentAutomaton = loadNamedAutomaton(testFolder, name.getMethodName());
    }

    /**
     * Returns the test path for the current suite.
     * @return
     */
    protected Path getTestPath() {
        return getDefaultTestPath();
    }

    /**
     * Get the path to the default test folder.
     * @return
     */
    public static Path getDefaultTestPath() {
        return Paths.get("data", "test", "dot");
    }

    /**
     * Initializes default options for algorithms.
     * @param testFolder Root folder for testing output
     */
    protected void initializeOptions(Path testFolder) {
        // Setup minimal options
        Options.OUTDIR = testFolder.getParent().toString() + File.separator;
        Options.DIRGRAPH = testFolder.getFileName().toString();
        Options.GRAPHVIZ = false;
    }

    /**
     * Cleans up a test case.
     */
    @After
    public void testCleanup() {
        currentAutomaton = null;
    }

    /**
     * Loads an automaton by its name from the given folder
     *
     * @param name
     * @return
     * @throws IOException
     */
    protected Mealy loadNamedAutomaton(Path sourceFolder, String name) throws IOException {
        // Path to the test file
        Path dotFilePath = Paths.get(sourceFolder.toString(), name + ".dot");

        // Load the automaton, if it exists
        File dotFile = dotFilePath.toFile();

        if (dotFile.exists())
            return loadAutomatonFromFile(dotFile);
        return null;
    }

    /**
     * Loads an automaton from a file
     *
     * @param file
     * @return
     * @throws IOException
     */
    protected Mealy loadAutomatonFromFile(File file) throws IOException {
        return Mealy.importFromDot(file);
    }

    /**
     * Asserts the equivalence of the given automaton with the source automaton for the current test.
     *
     * @param conjecture Actual automaton to check
     */
    protected void assertEquivalence(Mealy conjecture) {
        Assert.assertTrue("output automaton is not equivalent to input", new MealyUtils().checkEquivalence(currentAutomaton, conjecture));
    }
}
