package simpa.hit.drivers.mealy.transparent;

import simpa.hit.examples.mealy.LockerMealy;
import simpa.hit.examples.mealy.LockerMealy.OnError;
import simpa.hit.examples.mealy.LockerMealy.OutputPolicy;

public class EasyRandomLockerMealyDriver extends TransparentMealyDriver {
	public EasyRandomLockerMealyDriver(){
		super(LockerMealy.getRandomLockerMealy(OnError.STAY_IN_PLACE, OutputPolicy.UNLOCK_GOOD_BAD));
		automata.exportToDot();
	}
}
