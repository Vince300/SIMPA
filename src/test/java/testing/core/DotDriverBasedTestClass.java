package testing.core;

import drivers.Driver;
import drivers.mealy.MealyDriver;
import org.apache.log4j.ConsoleAppender;
import org.apache.log4j.Logger;
import org.apache.log4j.TTCCLayout;

import java.io.File;
import java.io.IOException;
import java.nio.file.Path;
import java.util.ArrayList;

/**
 * Base class that instantiates a DotMealy driver for all of the subclass
 * test methods.
 */
public abstract class DotDriverBasedTestClass extends MealyGraphTestClass {
    // The driver for the currently running test
    protected MealyDriver currentTestDriver;

    /**
     * Finds all input .dot files in a directory.
     *
     * @param path
     * @param testCases
     */
    private static void findTestCases(Path path, ArrayList<File> testCases) {
        File root = path.toFile();
        File[] list = root.listFiles();

        if (list != null) {
            for (File f : list) {
                if (f.isDirectory()) {
                    findTestCases(f.toPath(), testCases);
                } else {
                    String fpath = f.getPath();
                    if (fpath.endsWith(".dot")
                            && !fpath.endsWith("_inf.dot")
                            && !f.toPath().getFileName().toString().startsWith("Vtree")) {
                        // Only add .dot files without a skip file
                        if (!(new File(fpath + ".skip")).exists())
                            testCases.add(f);
                    }
                }
            }
        }
    }

    /**
     * Builds a test suite from the .dot files found in the specified directory.
     * @param rootDirectory The directory to be scanned for files
     * @return A list of arrays which contain each a File instance pointing to the
     *         corresponding test case, and a String which can be used as the test name.
     */
    protected static ArrayList<Object[]> buildSuite(Path rootDirectory) {
        ArrayList<Object[]> tests = new ArrayList<>();

        // Set root log4j to console and debug
        Logger.getRootLogger().addAppender(new ConsoleAppender(new TTCCLayout()));

        // Enumerates files in the codegen directory
        ArrayList<File> testCases = new ArrayList<>();
        findTestCases(rootDirectory, testCases);

        // Create test cases
        for (File file : testCases) {
            tests.add(new Object[] { file, rootDirectory.relativize(file.toPath()).toString() });
        }
        return tests;
    }

    /**
     * Initializes the test driver for the current test.
     *
     * @throws IOException
     */
    @Override
    public void testInitialize() throws IOException {
        // Load the automaton
        super.testInitialize();

        // Create the driver
        // We do not use FromDotMealyDriver because we need the actual Mealy instance.
        // Also, FromDotMealyDriver exports the input graph (why?)
        currentTestDriver = new MealyDriver(getCurrentAutomaton());
    }
}
