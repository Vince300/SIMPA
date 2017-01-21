package learner.mealy;

import learner.mealy.combinatorial.CombinatorialLearnerTests;
import learner.mealy.noReset.NoResetLearnerTests;
import learner.mealy.rivestSchapire.RivestSchapireLearnerTests;
import learner.mealy.table.LmLearnerTests;
import learner.mealy.tree.ZLearnerTests;
import org.junit.runner.RunWith;
import org.junit.runners.Suite;

@RunWith(Suite.class)
@Suite.SuiteClasses({
        CombinatorialLearnerTests.class,
        NoResetLearnerTests.class,
        RivestSchapireLearnerTests.class,
        LmLearnerTests.class,
        ZLearnerTests.class
})
public class TestingRoot {
}
