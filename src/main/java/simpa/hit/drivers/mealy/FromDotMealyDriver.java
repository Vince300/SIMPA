package simpa.hit.drivers.mealy;

import java.io.File;
import java.io.IOException;

import simpa.hit.automata.mealy.Mealy;

public class FromDotMealyDriver extends MealyDriver {

	public FromDotMealyDriver(File f) throws IOException {
		super(Mealy.importFromDot(f));
		automata.exportToDot();
	}
}
