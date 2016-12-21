package simpa.hit.drivers.mealy.transparent;

import simpa.hit.examples.mealy.LockerMealy;
import simpa.hit.examples.mealy.LockerMealy.OnError;
import simpa.hit.examples.mealy.LockerMealy.OutputPolicy;

public class HardRandomLockerMealyDriver extends TransparentMealyDriver {
	public HardRandomLockerMealyDriver(){
		super(LockerMealy.getRandomLockerMealy(OnError.RESET, OutputPolicy.UNLOCK_ONLY));
		automata.exportToDot();
	}
}
