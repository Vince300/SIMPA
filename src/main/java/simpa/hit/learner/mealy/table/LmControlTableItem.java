package simpa.hit.learner.mealy.table;

import simpa.hit.main.simpa.Options;
import simpa.hit.automata.mealy.Mealy;

public class LmControlTableItem {
	private String outputSymbol;

	public LmControlTableItem(String outputSymbol) {
		this.outputSymbol = outputSymbol;
	}

	public String getOutputSymbol() {
		return outputSymbol;
	}

	public boolean isOmegaSymbol() {
		return outputSymbol.length() == 0;
	}

	@Override
	public String toString() {
		return outputSymbol.equals(Mealy.OMEGA) ? Options.SYMBOL_OMEGA_UP
				: outputSymbol;
	}
}
