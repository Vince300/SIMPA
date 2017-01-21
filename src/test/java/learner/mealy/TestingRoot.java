package learner.mealy;

import learner.mealy.table.LmLearnerTests;
import learner.mealy.tree.ZLearnerTests;
import org.junit.runner.RunWith;
import org.junit.runners.Suite;

@RunWith(Suite.class)
@Suite.SuiteClasses({
        LmLearnerTests.class,
        ZLearnerTests.class
})
public class TestingRoot {
}
