package simpa.hit.drivers.mealy;

import java.util.List;

import simpa.hit.tools.Utils;
import simpa.hit.automata.mealy.Mealy;
import simpa.hit.examples.mealy.RandomMealy;

public class RandomMealyDriver extends MealyDriver {

	public RandomMealyDriver() {
		super(new RandomMealy());
		Utils.setSeed(((RandomMealy) automata).getSeed());
	}

	public RandomMealyDriver(Mealy a) {
		super(a);
		Utils.setSeed(((RandomMealy) automata).getSeed());
	}

	public static List<String> getStatHeaders() {
		return Utils.createArrayList("States", "Inputs", "Outputs", "ARL",
				"Requests", "Duration", "Transitions");
	}

}
