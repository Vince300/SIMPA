package simpa.hit.testing.core;

import simpa.hit.drivers.Driver;
import simpa.hit.drivers.mealy.MealyDriver;

import java.io.IOException;

/**
 * Base class that instantiates a DotMealy driver for all of the subclass
 * test methods.
 */
public abstract class DotDriverBasedTestClass extends MealyGraphTestClass {
    // The driver for the currently running test
    protected Driver currentTestDriver;

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
