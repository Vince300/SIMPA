package simpa.hit.drivers.mealy.transparent;

import simpa.hit.drivers.mealy.MealyDriver;
import simpa.hit.automata.mealy.Mealy;
import simpa.hit.automata.State;

public class TransparentMealyDriver extends MealyDriver {
	public TransparentMealyDriver(Mealy automata){
		super(automata);
	}
	
	public Mealy getAutomata(){
		return automata;
	}
	
	public State getCurrentState(){
		return currentState;
	}
	
	public void setCurrentState(State s){
		currentState = s;
	}
}
