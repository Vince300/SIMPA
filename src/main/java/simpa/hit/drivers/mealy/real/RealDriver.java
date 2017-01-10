package simpa.hit.drivers.mealy.real;

import java.util.List;

import simpa.hit.drivers.mealy.MealyDriver;

public abstract class RealDriver extends MealyDriver {

	protected List<String> outputSymbols = null;

	public RealDriver(String name) {
		super(name);
		type = DriverType.MEALY;
	}

	public abstract List<String> getInputSymbols();

	public List<String> getOutputSymbols() {
		return outputSymbols;
	}

	public abstract String execute(String input);

}
