package drivers.mealy.transparent;

import examples.mealy.SIP2Mealy;

public class SIP2Driver extends TransparentMealyDriver {

	public SIP2Driver() {
		super(SIP2Mealy.getAutomata());
	}
}
