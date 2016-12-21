package simpa.hit.learner;

import simpa.hit.learner.efsm.table.LiLearner;
import simpa.hit.learner.mealy.rivestSchapire.RivestSchapireLearner;
import simpa.hit.learner.mealy.table.LmLearner;
import simpa.hit.learner.mealy.tree.ZLearner;
import simpa.hit.learner.mealy.combinatorial.CombinatorialLearner;
import simpa.hit.learner.mealy.combinatorial.CutterCombinatorialLearner;
import simpa.hit.learner.mealy.noReset.NoResetLearner;
import simpa.hit.main.simpa.Options;
import simpa.hit.stats.StatsEntry;
import simpa.hit.stats.attribute.Attribute;
import simpa.hit.tools.loggers.LogManager;
import simpa.hit.automata.Automata;
import simpa.hit.drivers.Driver;
import simpa.hit.drivers.mealy.MealyDriver;

public abstract class Learner {
	protected boolean addtolog = true;

	public void stopLog() {
		addtolog = false;
	}

	public void startLog() {
		addtolog = true;
	}

	public abstract Automata createConjecture();

	public abstract void learn();
	
	public StatsEntry getStats(){
		return null;
	}
	
	public void logStats(){
		StatsEntry s = getStats();
		if (s == null){
			LogManager.logInfo("unable to get simpa.hit.learner simpa.hit.stats");
			return;
		}
		LogManager.logLine();
		for (Attribute<?> a : s.getAttributes()){
			LogManager.logStat(a.getName() + " : " + s.get(a) + " " + a.getUnits());
		}
		LogManager.logLine();
	}

	public static Learner getLearnerFor(Driver driver) throws Exception {
		switch (driver.type) {
		case SCAN:
			return new ZLearner(driver);
		case EFSM:
			return new LiLearner(driver);
		case MEALY:
			if (Options.TREEINFERENCE)
				return new ZLearner(driver);
			else if (Options.COMBINATORIALINFERENCE)
				return new CombinatorialLearner((MealyDriver)driver);
			else if (Options.CUTTERCOMBINATORIALINFERENCE)
					return new CutterCombinatorialLearner((MealyDriver)driver);
			else if (Options.RIVESTSCHAPIREINFERENCE)
				return new RivestSchapireLearner((MealyDriver)driver);
			else if (Options.NORESETINFERENCE)
				return new NoResetLearner((MealyDriver)driver);
			else if (Options.LMINFERENCE)
				return new LmLearner(driver);
		default:
			throw new RuntimeException("there is no driver to use");
		}
	}
}
