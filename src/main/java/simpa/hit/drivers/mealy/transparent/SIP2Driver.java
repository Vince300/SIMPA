package simpa.hit.drivers.mealy.transparent;

import simpa.hit.examples.mealy.SIP2Mealy;

public class SIP2Driver extends TransparentMealyDriver {

	public SIP2Driver() {
		super(SIP2Mealy.getAutomata());
	}
}
