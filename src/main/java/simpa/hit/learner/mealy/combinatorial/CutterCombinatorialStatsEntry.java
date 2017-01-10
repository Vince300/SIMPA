package simpa.hit.learner.mealy.combinatorial;

import simpa.hit.drivers.mealy.MealyDriver;

public class CutterCombinatorialStatsEntry extends CombinatorialStatsEntry {

	public CutterCombinatorialStatsEntry(String line) {
		super(line);
	}

	protected CutterCombinatorialStatsEntry(MealyDriver d) {
		super(d);
		traceLength = 0;
	}

	public void addTraceLength(int l){
		traceLength += l;
	}
}
