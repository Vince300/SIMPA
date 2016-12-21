package simpa.hit.drivers.mealy.transparent;

import simpa.hit.examples.mealy.SIPMealy;

public class SIPDriver extends TransparentMealyDriver {

	public SIPDriver() {
		super(SIPMealy.getAutomata());
	}
}
