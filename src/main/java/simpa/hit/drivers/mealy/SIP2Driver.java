package simpa.hit.drivers.mealy;

import simpa.hit.examples.mealy.SIP2Mealy;

public class SIP2Driver extends MealyDriver {

	public SIP2Driver() {
		super(SIP2Mealy.getAutomata());
	}
}
