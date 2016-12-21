package simpa.hit.learner.mealy.noReset;

import simpa.hit.automata.State;
import simpa.hit.automata.mealy.Mealy;
import simpa.hit.drivers.mealy.MealyDriver;
import simpa.hit.tools.loggers.LogManager;

public class NoResetMealyDriver extends MealyDriver {

	public NoResetMealyDriver(Mealy automata) {
		super(automata);
	}

	@Override
	public void reset(){
		LogManager.logError("Tried to reset the driver");
	}
	
	public void setCurrentState(State s){
		assert automata.getStates().contains(s);
		currentState = s;
	}

}
