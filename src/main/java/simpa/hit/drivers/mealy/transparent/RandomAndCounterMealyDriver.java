package simpa.hit.drivers.mealy.transparent;

import simpa.hit.examples.mealy.CombinedMealy;
import simpa.hit.examples.mealy.CounterMealy;
import simpa.hit.examples.mealy.RandomMealy;

public class RandomAndCounterMealyDriver extends TransparentMealyDriver {

	public RandomAndCounterMealyDriver() {
		super(new CombinedMealy(new CounterMealy(3, "counter"),RandomMealy.getConnexRandomMealy()));
	}
}
