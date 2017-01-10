package learner.mealy;

import java.util.List;

import automata.State;
import drivers.Driver;

public class LmConjecture extends automata.mealy.Mealy {
	private static final long serialVersionUID = -6920082057724492261L;
	private List<String> inputSymbols;

	public LmConjecture(Driver d) {
		super(d.getSystemName());
		this.inputSymbols = d.getInputSymbols();
	}

	public List<String> getInputSymbols() {
		return inputSymbols;
	}
	
	/**
	 * check if a conjecture has all transitions
	 * @return true if there is a transition from any state with any input symbol
	 */
	public boolean isFullyKnown(){
		for (State s : getStates())
			for (String i : inputSymbols)
				if (getTransitionFromWithInput(s, i) == null)
					return false;
		return true;
	}
}
