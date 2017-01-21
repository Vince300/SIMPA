package common;

import org.junit.Test;
import testing.core.MealyGraphTestClass;

import java.io.IOException;
import java.nio.file.Path;
import java.nio.file.Paths;

/**
 * A class for testing shared "features" among algorithms.
 */
public class CommonTests extends MealyGraphTestClass {
    @Override
    protected Path getTestPath() {
        return Paths.get("data", "test", "common");
    }

    @Override
    public void testInitialize() throws IOException {
        initializeOptions(getTestPath());
    }

    @Test(expected = java.lang.NullPointerException.class)
    public void noTitle() throws IOException {
        loadNamedAutomaton(getTestPath(), name.getMethodName());
    }
}
