package simpa.hit.drivers.mealy.transparent;

import simpa.hit.examples.mealy.CombinedMealy;
import simpa.hit.examples.mealy.CounterMealy;;

public class CombinedMealyDriver extends TransparentMealyDriver {

	public CombinedMealyDriver() {
		super(new CombinedMealy(new CounterMealy(2, "i"),new CounterMealy(3, "j")));
	}
}
