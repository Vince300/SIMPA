package learner.mealy.noReset;

import java.util.ArrayList;
import java.util.Comparator;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Set;

import automata.State;
import automata.mealy.InputSequence;
import automata.mealy.Mealy;
import automata.mealy.MealyTransition;
import automata.mealy.OutputSequence;
import drivers.mealy.MealyDriver;
import drivers.mealy.transparent.TransparentMealyDriver;
import learner.Learner;
import learner.mealy.LmConjecture;
import learner.mealy.LmTrace;
import learner.mealy.noReset.dataManager.DataManager;
import learner.mealy.noReset.dataManager.FullyQualifiedState;
import main.simpa.Options;
import tools.AdenilsoSimaoTool;
import tools.Utils;
import tools.loggers.LogManager;

public class NoResetLearner extends Learner {
	private MealyDriver driver;
	private DataManager dataManager;
	private NoResetStatsEntry stats;
	protected ArrayList<InputSequence> W;
	private int n;//the maximum number of states

	public NoResetLearner(MealyDriver d){
		driver = d;
	}

	public void learn(){
		List<InputSequence> W = Options.CHARACTERIZATION_SET;
		if (W == null){
			W = computeCharacterizationSet(driver);
			class InputSequenceComparator implements Comparator<InputSequence>{
				@Override
				public int compare(InputSequence o1, InputSequence o2) {
					int diff = o1.getLength() - o2.getLength();
					return diff;
				}
			}
			W.sort(new InputSequenceComparator());
		}
		learn(W);
	}

	public void learn(List<InputSequence> W){
		LogManager.logStep(LogManager.STEPOTHER,"Inferring the system");
		LogManager.logConsole("Inferring the system with W="+W+" and n="+Options.STATE_NUMBER_BOUND);

		n = Options.STATE_NUMBER_BOUND;
		stats = new NoResetStatsEntry(W, driver, n);

		this.W = new ArrayList<InputSequence>(W);
		StringBuilder logW = new StringBuilder("Using characterization set : [");
		for (InputSequence w : this.W){
			logW.append(w + ", ");
		}
		logW.append("]");
		LogManager.logInfo(logW.toString());

		long start = System.nanoTime();

		//GlobalTrace trace = new GlobalTrace(driver);
		dataManager = new DataManager(driver, this.W, n);

		//start of the algorithm
		localize(dataManager, W);

		while (!dataManager.isFullyKnown()){
			Runtime runtime = Runtime.getRuntime();
			runtime.gc();
			stats.updateMemory((int) (runtime.totalMemory() - runtime.freeMemory()));

			LogManager.logLine();
			int qualifiedStatePos;
			LmTrace sigma;
			if (dataManager.getC(dataManager.traceSize()) != null){
				FullyQualifiedState q = dataManager.getC(dataManager.traceSize());
				LogManager.logInfo("We already know the current state (q = " + q + ")");	
				InputSequence alpha = dataManager.getShortestAlpha(q);
				dataManager.apply(alpha);
				assert dataManager.updateCKVT();
				assert dataManager.getC(dataManager.traceSize()) != null;
				qualifiedStatePos = dataManager.traceSize();
				FullyQualifiedState quallifiedState = dataManager.getC(qualifiedStatePos);
				Set<String> X = dataManager.getxNotInR(quallifiedState);
				if (X.isEmpty()){
					LogManager.logInfo("We discovered the missing transition when we applied alpha");
					continue;//we already are in a known state (because we applied alpha) so we didn't need to localize
				}
				String x=X.iterator().next(); //here we CHOOSE to take the first
				LogManager.logInfo("We choose x = " + x + " in " + X);		
				String o = dataManager.apply(x);
				sigma = new LmTrace(x,o);
				LogManager.logInfo("So sigma = " + sigma);	
				assert dataManager.getC(dataManager.traceSize()) == null : "we are trying to qualify this state, that should not be already done.";
			}else{
				LogManager.logInfo("We don't know the current state");	
				qualifiedStatePos = dataManager.traceSize()-1;
				while (dataManager.getC(qualifiedStatePos) == null)
					qualifiedStatePos --;
				LogManager.logInfo("last qualified state is " + dataManager.getC(qualifiedStatePos));
				sigma = dataManager.getSubtrace(qualifiedStatePos,dataManager.traceSize());
				LogManager.logInfo("We got sigma = "+ sigma);
			}
			FullyQualifiedState q = dataManager.getC(qualifiedStatePos);
			List<InputSequence> allowed_W = dataManager.getwNotInK(q, sigma);
			InputSequence w = allowed_W.get(0); //here we CHOOSE to take the first.
			if (Options.LOG_LEVEL != Options.LogLevel.LOW)
				LogManager.logInfo("We choose w = " + w + " in " + allowed_W);		
			int newStatePos = dataManager.traceSize();
			dataManager.apply(w);
			if (Options.LOG_LEVEL != Options.LogLevel.LOW)
				LogManager.logInfo("We found that " + q + " followed by " + sigma + "gives " +dataManager.getSubtrace(newStatePos, dataManager.traceSize()));
			dataManager.addPartiallyKnownTrace(q, sigma, dataManager.getSubtrace(newStatePos, dataManager.traceSize()));
			if (Options.TEST)
				dataManager.updateCKVT();
			if (dataManager.getC(dataManager.traceSize()) == null){
				localize(dataManager, W);
				if (Options.TEST)
					dataManager.updateCKVT();
			}
			assert dataManager.updateCKVT();
		}
		float duration = (float)(System.nanoTime() - start)/ 1000000000;
		stats.setDuration(duration);
		Runtime runtime = Runtime.getRuntime();
		runtime.gc();
		stats.updateMemory((int) (runtime.totalMemory() - runtime.freeMemory()));
		stats.setTraceLength(dataManager.traceSize());
		stats.updateWithConjecture(dataManager.getConjecture());
		if (Options.LOG_LEVEL == Options.LogLevel.ALL || Options.TEST)
			LogManager.logConsole(dataManager.readableTrace());
		dataManager.getConjecture().exportToDot();
		if (driver instanceof TransparentMealyDriver) {
			if (AdenilsoSimaoTool.isToolPresent()) {
				int minTraceLength = AdenilsoSimaoTool.minLengthForExhaustivAutomata(
						((TransparentMealyDriver) driver).getAutomata(), dataManager.getTrace().getInputsProjection());
				if (minTraceLength > dataManager.traceSize())
					throw new RuntimeException("error in learning, there is another automata which produce the same trace");
				stats.setMinTraceLength(minTraceLength);
			}else{
				LogManager.logConsole("info: AdenilsoSimaoTool 'n-complete-exhaustive' tool is missing, "
						              + "the minLengthForExhaustivAutomata() will not be computed.");
				LogManager.logInfo("info: AdenilsoSimaoTool 'n-complete-exhaustive' tool is missing, "
						              + "the minLengthForExhaustivAutomata() will not be computed.");
			}
		}else{
			stats.setMinTraceLength(-2);
		}
		// The transition count should be stopped
		driver.stopLog();
		if (driver instanceof TransparentMealyDriver){
			TransparentMealyDriver d = (TransparentMealyDriver) driver;
			if (checkExact(d.getAutomata(), d.getCurrentState())){
				LogManager.logConsole("The computed conjecture is exact");
				LogManager.logInfo("The computed conjecture is exact");
			}else{
				LogManager.logConsole("The computed conjecture is not correct");
				LogManager.logInfo("The computed conjecture is not correct");
			}	
		}else{
			if (checkRandomWalk()){
				LogManager.logConsole("The computed conjecture seems to be consistent with the driver");
				LogManager.logInfo("The computed conjecture seems to be consistent with the driver");
			}else{
				LogManager.logConsole("The computed conjecture is not correct");
				LogManager.logInfo("The computed conjecture is not correct");
			}
		}
		
	}

	public LmConjecture createConjecture() {
		LmConjecture c = dataManager.getConjecture();
		LogManager.logInfo("Conjecture has " + c.getStateCount()
		+ " states and " + c.getTransitionCount() + " transitions : ");
		return c;
	}

	public NoResetStatsEntry getStats(){
		return stats;
	}

	/**
	 * 
	 * @param trace omega the global trace of the automata, will be completed \in (IO)*
	 * @param inputSequences a subset of the characterization state \subset W \subset I*
	 * @return the position of the fully identified state in the GlobalTrace
	 */
	private int localize(DataManager dataManager, List<InputSequence> inputSequences){
		int startTracePos = dataManager.traceSize();
		LogManager.logInfo("Localizing...");
		List<OutputSequence> WResponses = localize_intern(dataManager, inputSequences);
		FullyQualifiedState s = dataManager.getFullyQualifiedState(WResponses);
		dataManager.setC(dataManager.traceSize()-WResponses.get(WResponses.size()-1).getLength(), s);
		stats.setLocalizeSequenceLength(dataManager.traceSize() - startTracePos);
		stats.increaseLocalizeCallNb();
		return dataManager.traceSize() - WResponses.get(inputSequences.size()-1).getLength();

	}

	private List<OutputSequence> localize_intern(DataManager dataManager, List<InputSequence> inputSequences){
		if (inputSequences.size() == 1){
			List<OutputSequence> WResponses = new ArrayList<OutputSequence>();
			WResponses.add(dataManager.apply(inputSequences.get(0)));
			return WResponses;
		}
		LogManager.logInfo("Localizer : Localize with " + inputSequences);

		ArrayList<InputSequence> Z1 = new ArrayList<InputSequence>(inputSequences);
		Z1.remove(Z1.size()-1);
		ArrayList<List<OutputSequence>> localizerResponses = new ArrayList<List<OutputSequence>>();
		if (Options.LOG_LEVEL != Options.LogLevel.LOW)
			LogManager.logInfo("Localizer : Applying " + (2*n-1) + " times localize(" + Z1 + ")");
		for (int i = 0; i < 2*n - 1; i++){
			localizerResponses.add(localize_intern(dataManager, Z1));
		}

		int j = n;
		boolean isLoop = false;
		while (!isLoop){
			j--;
			assert (j>=0) : "no loop was found";
			isLoop = true;
			for (int m = 0; m < n-1; m++){
				if (!localizerResponses.get(j+m).equals(localizerResponses.get(n+m))){
					isLoop = false;
					if (Options.LOG_LEVEL != Options.LogLevel.LOW)
						LogManager.logInfo("Tried size " + (n-j) +" : it's not a loop : ["+(j+m)+"] = (" + Z1 + " → " + localizerResponses.get(j+m) +
								") ≠ [" + (n+m) + "] = (" + Z1 + " → " + localizerResponses.get(n+m) + ")");
					break;
				}
			}
		}
		if (Options.LOG_LEVEL != Options.LogLevel.LOW)
			LogManager.logInfo("Localizer : Found a loop of size " + (n-j));
		if (Options.LOG_LEVEL == Options.LogLevel.ALL)
			LogManager.logInfo("Localizer : We know that applying localize_intern(" + Z1 + ") will produce " + localizerResponses.get(j+n-1));

		List<OutputSequence> WResponses = localizerResponses.get(j+n-1);
		List<InputSequence> Z2 = new ArrayList<InputSequence>(Z1);
		Z2.remove(Z2.size()-1);
		Z2.add(inputSequences.get(inputSequences.size()-1));
		List<OutputSequence> Z2Responses = localize_intern(dataManager, Z2);
		WResponses.add(Z2Responses.get(Z2Responses.size()-1));
		StringBuilder s = new StringBuilder();
		for (int i = 0; i < inputSequences.size(); i++){
			s.append(new LmTrace(inputSequences.get(i),WResponses.get(i)) + ", ");
		}
		if (Options.LOG_LEVEL != Options.LogLevel.LOW)
			LogManager.logInfo("Localizer : Before " + inputSequences.get(inputSequences.size()-1) + " we were in " + s);
		assert WResponses.size() == inputSequences.size();
		return WResponses;
	}

	private boolean checkRandomWalk(){
		LogManager.logStep(LogManager.STEPOTHER, "checking the computed conjecture with Random Walk");
		NoResetMealyDriver generatedDriver = new NoResetMealyDriver(dataManager.getConjecture());
		generatedDriver.stopLog();
		generatedDriver.setCurrentState(dataManager.getC(dataManager.traceSize()).getState());

		//Now the two automata are in same state.
		//We can do a random walk

		int max_try = driver.getInputSymbols().size() * n * 10;
		dataManager = null;//we use directly the driver for the walk so dataManager is not up to date;
		driver.stopLog();
		for (int j = 0; j < max_try; j++){
			int rand = Utils.randInt(driver.getInputSymbols().size());
			String input = driver.getInputSymbols().get(rand);
			if (!driver.execute(input).equals(generatedDriver.execute(input)))
				return false;
		}

		return true;
	}

	/**
	 * check if the computed conjecture is equivalent to the given automata
	 * the control is made by walking in the given automata in order to follow each transitions and comparing the two outputs and checking that only one state of th conjecture  can be associated to a state of the given automata.
	 * @param automata a connex automata
	 * @param currentState the state in the automata which is supposed to be equivalent to the current state of the driver
	 * @return true if the two automata are equivalent
	 */
	public boolean checkExact(Mealy automata, State currentState){
		LogManager.logStep(LogManager.STEPOTHER, "checking the computed conjecture is exactly equivalent");
		class FoundState {
			public State computedState; //a state in the conjecture
			public List<String> uncheckedTransitions;
			public FoundState(State s, List<String> I){
				computedState = s;
				uncheckedTransitions = new ArrayList<String>(I);
			}
			public String toString(){return computedState + " but transitions " + uncheckedTransitions + "have not been checked";}
		}
		//currentFoundState is maintained in order that currentFoundState.computedState is the current state in conjecture
		FoundState currentFoundState = new FoundState(dataManager.getC(dataManager.traceSize()).getState(),driver.getInputSymbols());
		//assigned is a table to associate a FoundState to each state in the given automata
		Map<State,FoundState> assigned = new HashMap<State,FoundState>();
		assigned.put(currentState, currentFoundState);
		State uncheckedState = currentState; //a state with an unchecked transition
		List<String> path = new ArrayList<String>();//the path from the current state to uncheckeState

		//now we iterate over all unchecked transitions
		while (uncheckedState != null) {		
			FoundState uncheckedFoundState = assigned.get(uncheckedState);
			LogManager.logInfo("Applying " + path + "in order to go in state " + uncheckedState + " and then try " + uncheckedFoundState.uncheckedTransitions.get(0));
			path.add(uncheckedFoundState.uncheckedTransitions.get(0));

			//we follow path in driver (the conjecture) and the given automata
			for (String i : path){
				currentFoundState.uncheckedTransitions.remove(i);
				MealyTransition t = automata.getTransitionFromWithInput(currentState, i);
				currentState = t.getTo();
				String o = dataManager.apply(i);
				if (! o.equals(t.getOutput())){
					LogManager.logInfo("expected output was " + t.getOutput());
					return false;
				}
				currentFoundState = assigned.get(currentState);
				if (currentFoundState == null){
					currentFoundState = new FoundState(dataManager.getC(dataManager.traceSize()).getState(), driver.getInputSymbols());
					assigned.put(currentState, currentFoundState);
				} else if (currentFoundState.computedState != dataManager.getC(dataManager.traceSize()).getState()){
					LogManager.logInfo("it was expected to arrive in " + t.getTo());
					return false;
				}
			}
			//now we've applied an unchecked transition (which is now checked)

			//and then we compute a new path to go to another state with unchecked transitions
			class Node {public List<String> path; public State state;}
			LinkedList<Node> nodes = new LinkedList<Node>();
			Node node = new Node();
			node.path = new ArrayList<String>();
			node.state = currentState;
			nodes.add(node);

			Map<State, Boolean> crossed = new HashMap<State, Boolean>();//this map is used to store the node crossed during the path searching (avoid going to the same state by two different path)
			for (State s : automata.getStates())
				crossed.put(s,false);
			uncheckedState = null;
			path = null;
			while (!nodes.isEmpty()){
				node = nodes.pollFirst();
				if (!assigned.get(node.state).uncheckedTransitions.isEmpty()){
					uncheckedState = node.state;
					path = node.path;
					break;
				}
				if (crossed.get(node.state))
					continue;
				for (String i : driver.getInputSymbols()){
					Node newNode = new Node();
					newNode.path = new ArrayList<String>(node.path);
					newNode.path.add(i);
					newNode.state = automata.getTransitionFromWithInput(node.state, i).getTo();
					nodes.add(newNode);
					crossed.put(node.state, true);
				}
			}
		}

		return true;
	}

	private static List<InputSequence> computeCharacterizationSet(
			MealyDriver driver) {
		if (driver instanceof TransparentMealyDriver){
			return computeCharacterizationSet((TransparentMealyDriver) driver);
		} else {
			throw new RuntimeException("unable to compute W");
		}
	}

	private static List<InputSequence> computeCharacterizationSet(TransparentMealyDriver driver){
		LogManager.logStep(LogManager.STEPOTHER, "computing characterization set");
		Mealy automata = driver.getAutomata();
		List<InputSequence> W = new ArrayList<InputSequence>();
		List<State> distinguishedStates = new ArrayList<State>();
		for (State s1 : automata.getStates()){
			if (Options.LOG_LEVEL != Options.LogLevel.LOW)
				LogManager.logInfo("adding state " + s1);
			for (State s2 : distinguishedStates){
				boolean haveSameOutputs = true;
				for (InputSequence w : W){
					if (!apply(w,automata,s1).equals(apply(w,automata,s2))){
						haveSameOutputs = false;
					}
				}
				if (haveSameOutputs){
					if (Options.LOG_LEVEL != Options.LogLevel.LOW)
						LogManager.logInfo(s1 + " and " + s2 + " have the same outputs for W=" + W);
					addDistinctionSequence(automata, driver.getInputSymbols(), s1, s2, W);
					if (Options.LOG_LEVEL == Options.LogLevel.ALL)
						LogManager.logInfo("W is now " + W);
				}
			}
			distinguishedStates.add(s1);
		}
		if (automata.getStateCount() == 1)
			W.add(new InputSequence(driver.getInputSymbols().get(0)));
		return W;
	}

	/**
	 * compute a distinction sequence for the two states
	 * it may be a new distinction sequence or an append of an existing distinction sequence 
	 * @param automata
	 * @param inputSymbols
	 * @param s1
	 * @param s2
	 * @param w2
	 */
	private static void addDistinctionSequence(Mealy automata,
			List<String> inputSymbols, State s1, State s2,
			List<InputSequence> W) {
		//first we try to add an input symbol to the existing W
		for (InputSequence w : W){
			for (String i : inputSymbols){
				InputSequence testw = new InputSequence();
				testw.addInputSequence(w);
				testw.addInput(i);
				if (!apply(testw, automata, s1).equals(apply(testw,automata,s2))){
					w.addInput(i);
					return;
				}
			}
		}
		//then we try to compute a w from scratch
		LinkedList<InputSequence> testW = new LinkedList<InputSequence>();
		for (String i : inputSymbols)
			testW.add(new InputSequence(i));
		while (true){
			InputSequence testw = testW.pollFirst();
			if (apply(testw, automata, s1).equals(apply(testw,automata,s2))){
				if (testw.getLength() > automata.getStateCount()){
					LogManager.logInfo("unable to get find a w to distinguish " + s1 + " and " + s2
							+ ".Those states may be equivalent");
					throw new RuntimeException("unable to distinguish two states for W set");
				}
				for (String i : inputSymbols){
					InputSequence newTestw = new InputSequence();
					newTestw.addInputSequence(testw);
					newTestw.addInput(i);
					testW.add(newTestw);
				}
			}else{
				for (int i = 0; i < W.size(); i++){
					InputSequence w = W.get(i);
					if (testw.startsWith(w)){
						W.remove(w);
					}
				}
				W.add(testw);
				return;
			}

		}
	}

	// Initial attempt to compute a better W set, but currently disused because inefficient 
	private static List<InputSequence> computeCharacterizationSetNaiv(TransparentMealyDriver driver){
		LogManager.logStep(LogManager.STEPOTHER, "computing characterization set");
		Mealy automata = driver.getAutomata();
		automata.exportToDot();
		List<InputSequence> W = new ArrayList<InputSequence>();
		for (String i : driver.getInputSymbols()){
			W.add(new InputSequence(i));
		}
		boolean isCaracterizationSet = false;
		while (!isCaracterizationSet){
			if (Options.LOG_LEVEL == Options.LogLevel.ALL)
				LogManager.logInfo("computing caracterization set : W is now " + W);
			isCaracterizationSet = true;
			for (State s1 : automata.getStates()){
				for (State s2 : automata.getStates()){
					if (s1.equals(s2))
						break;//we do not need to test s1 -> s2 AND s2 -> s1
					List<InputSequence> haveSameOutput = new ArrayList<InputSequence>();//the W elements for which s1 and s2 have the same output
					for (InputSequence w : W){
						if (apply(w,automata,s1).equals(apply(w,automata,s2))){
							haveSameOutput.add(w);
						}
					}
					if (haveSameOutput.size() == W.size()){
						isCaracterizationSet = false;
						InputSequence toSplit = haveSameOutput.get(0);//here we choose to take the first element so it may be interesting to randomize that
						W.remove(toSplit);
						for (String i : driver.getInputSymbols()){
							InputSequence newW = new InputSequence();
							newW.addInputSequence(toSplit);
							newW.addInput(i);
							if (!apply(newW,automata,s1).equals(apply(newW,automata,s2))){
								W.add(newW);
								break;
							}
						}
						for (String i : driver.getInputSymbols()){
							InputSequence newW = new InputSequence();
							newW.addInputSequence(toSplit);
							newW.addInput(i);
							W.add(newW);
						}
					}
				}
			}
		}

		return W;
	}

	private static OutputSequence apply(InputSequence I, Mealy m, State s){
		OutputSequence O = new OutputSequence();
		for (String i : I.sequence){
			MealyTransition t = m.getTransitionFromWithInput(s, i);
			s = t.getTo();
			O.addOutput(t.getOutput());
		}
		return O;
	}

}
