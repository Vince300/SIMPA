package simpa.hit.testing.core;

import org.junit.Assert;
import org.junit.Before;
import org.junit.BeforeClass;
import org.junit.Rule;
import org.junit.rules.TestName;
import simpa.hit.drivers.Driver;
import simpa.hit.drivers.mealy.FromDotMealyDriver;
import simpa.hit.main.simpa.Options;

import java.io.File;
import java.io.IOException;
import java.nio.file.Path;
import java.nio.file.Paths;

/**
 * Base class that instantiates a DotMealy driver for all of the subclass
 * test methods.
 */
public abstract class DotDriverBasedTestClass {
    @Rule
    public TestName name = new TestName();

    // The driver for the currently running test
    protected Driver currentTestDriver;

    @BeforeClass
    public static void checkPrerequisites() {
        try {
            Process p = Runtime.getRuntime().exec(new String[] { "dot", "-V" });
            p.waitFor();
        } catch (IOException e) {
            Assert.fail("GraphViz is not installed, please install it before running this test suite");
        } catch (InterruptedException e) {
            // ok, ignore
        }
    }

    @Before
    public void initializeDriver() throws IOException {
        // Path to the test file
        Path targetPath = Paths.get("data", "test", "dot", name.getMethodName() + ".dot");
        // Setup minimal options
        Options.OUTDIR = Paths.get("data", "test").toString() + File.separator;
        Options.DIRGRAPH = "dot";
        // Load the file
        File inputDotFile = new File(targetPath.toString());
        // Create the driver
        currentTestDriver = new FromDotMealyDriver(inputDotFile);
    }
}
