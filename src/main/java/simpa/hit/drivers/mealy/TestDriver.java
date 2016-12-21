package simpa.hit.drivers.mealy;

import simpa.hit.examples.mealy.TestMealy;

public class TestDriver extends MealyDriver {

	public TestDriver() {
		super(TestMealy.getAutomata());
	}
}
