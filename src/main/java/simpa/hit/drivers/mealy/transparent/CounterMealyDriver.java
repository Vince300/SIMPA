package simpa.hit.drivers.mealy.transparent;

import simpa.hit.examples.mealy.CombinedMealy;
import simpa.hit.examples.mealy.CounterMealy;;

public class CounterMealyDriver extends TransparentMealyDriver {

	public CounterMealyDriver() {
		super(new CombinedMealy(new CounterMealy(3, "j"), new CounterMealy(2,"i")));
	}
}
