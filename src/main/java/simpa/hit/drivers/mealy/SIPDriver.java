package simpa.hit.drivers.mealy;

import simpa.hit.examples.mealy.SIPMealy;

public class SIPDriver extends MealyDriver {

	public SIPDriver() {
		super(SIPMealy.getAutomata());
	}
}
