package simpa.hit.drivers.mealy;

import java.util.ArrayList;
import java.util.List;

import simpa.hit.automata.mealy.InputSequence;
import simpa.hit.examples.mealy.ZQPaper0730;

public class ZQPaper0730Driver extends MealyDriver {

	public ZQPaper0730Driver() {
		super(ZQPaper0730.getAutomata());
	}

	protected List<InputSequence> getForcedCE() {
		List<InputSequence> seq = new ArrayList<InputSequence>();

		InputSequence ce = new InputSequence();
		ce.addInput("a");
		ce.addInput("a");
		ce.addInput("b");
		ce.addInput("b");
		ce.addInput("b");
		ce.addInput("a");
		ce.addInput("b");
		ce.addInput("b");
		ce.addInput("a");
		seq.add(ce);

		return seq;
	}
}
