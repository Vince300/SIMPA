package simpa.hit.drivers.mealy.transparent;

import java.util.ArrayList;
import java.util.Arrays;

import simpa.hit.automata.mealy.InputSequence;
import simpa.hit.examples.mealy.LockerMealy;
import simpa.hit.examples.mealy.LockerMealy.OnError;
import simpa.hit.examples.mealy.LockerMealy.OutputPolicy;

public class LockerMealyDriver extends TransparentMealyDriver {
	public LockerMealyDriver(){
		super(new LockerMealy(
				new InputSequence("a").addInput("b").addInput("a"),
				OnError.RANDOM_BACK,
				OutputPolicy.UNLOCK_ONLY,
				new ArrayList<String>(Arrays.asList(new String[]{"other"}))
				));
		automata.exportToDot();
	}
}
