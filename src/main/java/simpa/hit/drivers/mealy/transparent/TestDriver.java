package simpa.hit.drivers.mealy.transparent;

import simpa.hit.examples.mealy.TestMealy;

public class TestDriver extends TransparentMealyDriver {

	public TestDriver() {
		super(TestMealy.getAutomata());
	}
}
