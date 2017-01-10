package simpa.hit.examples.efsm;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.Serializable;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Set;
import java.util.TreeMap;

import simpa.hit.main.simpa.Options;
import simpa.hit.tools.Utils;
import simpa.hit.tools.loggers.LogManager;
import simpa.hit.automata.State;
import simpa.hit.automata.efsm.EFSM;
import simpa.hit.automata.efsm.EFSMTransition;
import simpa.hit.automata.efsm.GeneratedOutputFunction;
import simpa.hit.automata.efsm.Parameter;
import simpa.hit.drivers.efsm.EFSMDriver.Types;

public class RandomEFSM extends EFSM implements Serializable {
	private static final long serialVersionUID = -4610287835922347376L;

	private List<String> inputSymbols = null;
	private List<String> outputSymbols = null;
	private Map<String, Integer> arity = null;
	private HashMap<String, List<ArrayList<Parameter>>> dpv = null;
	private int simpleCount = 0, ndvCount = 0;

	private void generateSymbols() {
		int nbSym = 0;
		arity = new HashMap<String, Integer>();
		inputSymbols = new ArrayList<String>();
		nbSym = Utils.randIntBetween(Options.MININPUTSYM, Options.MAXINPUTSYM);
		for (int i = 0; i < nbSym; i++) {
			inputSymbols.add("in" + i);
			arity.put("in" + i, Utils.randIntBetween(Options.MINPARAMETER,
					Options.MAXPARAMETER));
		}
		outputSymbols = new ArrayList<String>();
		nbSym = Utils.randIntBetween(Options.MININPUTSYM, Options.MAXINPUTSYM);
		for (int i = 0; i < nbSym; i++) {
			outputSymbols.add("out" + i);
			arity.put("out" + i, Utils.randIntBetween(Options.MINPARAMETER,
					Options.MAXPARAMETER));
		}
		LogManager.logSymbolsParameters(arity);
	}

	public RandomEFSM() {
		super("Random");
		LogManager.logStep(LogManager.STEPOTHER, "Generating random EFSM");
		generateSymbols();
		createStates();
		createTransitions();
		fixUnreachableStates();
		fixDeadEndStates();
		createDefaultParameterValues();
		createSimpleGuards();
		createNdvGuards();
		makeItDetermnistic();
		makeItObservable();
		exportToDot();
		RandomEFSM.serialize(this);
	}

	public static void serialize(RandomEFSM o) {
		FileOutputStream fos = null;
		ObjectOutputStream oos = null;
		try {
			fos = new FileOutputStream(Options.OUTDIR + o.getName()
					+ ".serialized");
			oos = new ObjectOutputStream(fos);
			oos.writeObject(o);
			oos.flush();
			oos.close();
			fos.close();
		} catch (Exception e) {
			LogManager.logException("Error serializing generated EFSM", e);
		}
	}

	public static RandomEFSM deserialize(String filename) {
		Object o = null;
		File f = new File(filename);
		LogManager.logStep(LogManager.STEPOTHER,
				"Loading RandomEFSM from " + f.getName());
		try {
			FileInputStream fis = new FileInputStream(filename);
			ObjectInputStream ois = new ObjectInputStream(fis);
			o = ois.readObject();
			ois.close();
			fis.close();
		} catch (Exception e) {
			LogManager.logException("Error deserializing generated EFSM", e);
		}
		return (RandomEFSM) o;
	}

	private void createDefaultParameterValues() {
		dpv = new HashMap<String, List<ArrayList<Parameter>>>();
		for (String symb : inputSymbols) {
			ArrayList<ArrayList<Parameter>> l = new ArrayList<ArrayList<Parameter>>();
			ArrayList<Parameter> ll = new ArrayList<Parameter>();
			for (int i = 0; i < arity.get(symb); i++) {
				ll.add(new Parameter(String.valueOf(Options.DOMAINSIZE * 10
						+ (i + 1)), Types.NUMERIC));
			}
			l.add(ll);
			dpv.put(symb, l);
		}
	}

	private void createSimpleGuards() {
		for (EFSMTransition t : transitions) {
			if (Utils.randBoolWithPercent(Options.SIMPLEGUARDPERCENT)) {
				LogManager.logInfo("Creating EQUALSTOVALUE guard for state "
						+ t.getFrom() + " with input " + t.getInput());
				ArrayList<Parameter> newParameters = t.randomizeGuard();
				simpleCount++;
				List<ArrayList<Parameter>> existingParameters = dpv.get(t
						.getInput());
				boolean alreadyExists = false;
				for (ArrayList<Parameter> existingParameter : existingParameters) {
					boolean equals = true;
					for (int i = 0; i < newParameters.size(); i++) {
						if (!newParameters.get(i).value
								.equals(existingParameter.get(i).value)) {
							equals = false;
							break;
						}
					}
					if (equals) {
						alreadyExists = true;
						break;
					}
				}
				if (!alreadyExists)
					existingParameters.add(newParameters);
			}
		}
	}

	private boolean isCleanForGenerateGuard(EFSMTransition t) {
		return !t.getFrom().isInitial() && !t.getGuard().checkNdv
				&& !t.generateNdv && !t.getFrom().equals(t.getTo());
	}

	private boolean isCleanForCheckingGuard(EFSMTransition t) {
		return !t.getFrom().isInitial() && !t.getGuard().checkNdv
				&& !t.generateNdv
				&& (getTransitionTo(t.getFrom(), false).size() == 1);
	}

	private void createNdvGuards() {
		int nbNdv = 0;
		for (EFSMTransition t : transitions) {
			if (isCleanForGenerateGuard(t)
					&& Utils.randBoolWithPercent(Options.NDVGUARDPERCENT * 2)) {
				State gen = goRandomStepsFrom(
						Utils.randIntBetween(Options.NDVMINTRANSTOCHECK,
								Options.NDVMAXTRANSTOCHECK) - 1, t.getTo());
				EFSMTransition check = Utils.randIn(getTransitionFrom(gen,
						false));
				if (isCleanForCheckingGuard(check)) {
					LogManager.logInfo("State " + t.getFrom()
							+ " generates a Ndv" + nbNdv);
					t.generateNdv(nbNdv);
					LogManager.logInfo("State " + gen + " will check Ndv"
							+ nbNdv);
					check.checkNdv(nbNdv);
					nbNdv++;
					ndvCount++;
				}
			}
		}
	}

	private State goRandomStepsFrom(int nbSteps, State s) {
		State tmp = s;
		List<EFSMTransition> l = new ArrayList<EFSMTransition>();
		while (nbSteps > 0) {
			for (EFSMTransition t : transitions) {
				if (t.getFrom().equals(tmp) && !t.getTo().equals(tmp))
					l.add(t);
			}
			tmp = l.get(Utils.randInt(l.size())).getTo();
			l.clear();
			nbSteps--;
		}
		return tmp;
	}

	private List<List<EFSMTransition>> getGroupedTransitions() {
		List<List<EFSMTransition>> res = new ArrayList<List<EFSMTransition>>();
		List<EFSMTransition> l = new ArrayList<EFSMTransition>();
		l.addAll(transitions);
		while (!l.isEmpty()) {
			List<EFSMTransition> g = new ArrayList<EFSMTransition>();
			EFSMTransition first = l.remove(0);
			g.add(first);
			for (int j = l.size() - 1; j >= 0; j--) {
				if (first.getFrom().equals(l.get(j).getFrom())
						&& first.getInput().equals(l.get(j).getInput())) {
					g.add(l.remove(j));
				}
			}
			res.add(g);
		}
		return res;
	}

	private void makeItDetermnistic() {
		List<List<EFSMTransition>> groups = getGroupedTransitions();
		for (List<EFSMTransition> group : groups) {
			if (group.size() > 1) {
				group.get(1).setGuard(group.get(0).getGuard().clone().not());
			}
			for (int i = 2; i < group.size(); i++) {
				group.get(i).setGuard(group.get(i).getGuard().alwaysFalse());
			}
		}
	}

	private void makeItObservable() {
		List<List<EFSMTransition>> groups = getGroupedTransitions();
		for (List<EFSMTransition> group : groups) {
			if (group.size() > 0) {
				ArrayList<String> remainingOutputSymbols = new ArrayList<String>();
				remainingOutputSymbols.addAll(outputSymbols);
				remainingOutputSymbols.remove(group.get(0).getOutput());
				for (int i = 1; i < group.size(); i++) {
					if (remainingOutputSymbols.contains(group.get(i)
							.getOutput()))
						remainingOutputSymbols.remove(group.get(i).getOutput());
					else {
						String newOutputSymbol = Utils
								.randIn(remainingOutputSymbols);
						if (newOutputSymbol == null) {
							group.get(i).getGuard().alwaysFalse();
						} else {
							group.get(i).setOutput(newOutputSymbol);
							remainingOutputSymbols.remove(newOutputSymbol);
						}
					}
				}
			}
		}
	}

	private List<String> getOutputForThisInput(State s, String input) {
		List<EFSMTransition> ts = getTransitionFromWithInput(s, input);
		List<String> outs = new ArrayList<String>();
		for (EFSMTransition t : ts) {
			outs.add(t.getOutput());
		}
		return outs;
	}

	/*
	 * Fixe unreachable states by adding transition
	 */
	private void fixUnreachableStates() {
		Set<State> unreachables = new HashSet<State>();
		Set<State> reachables = new HashSet<State>();
		classifyStatesUnreachable(reachables, unreachables);

		LogManager.logInfo("Those states are unreachables : " + unreachables);

		while (unreachables.size() > 0) {

			State s = unreachables.iterator().next();
			State from = Utils.randIn(reachables);

			// List with the number of outgoing transition from state "from" for
			// each input symbol
			List<Integer> nbTransWithInput = new ArrayList<Integer>();
			for (int i = 0; i < inputSymbols.size(); i++)
				nbTransWithInput.add(0);
			for (EFSMTransition t : transitions) {
				if (t.getFrom().equals(from)) {
					int idx = inputSymbols.indexOf(t.getInput());
					nbTransWithInput.set(idx, nbTransWithInput.get(idx) + 1);
				}
			}

			// Get the input symbol with the minimum of occurences
			int minIn = 0;
			for (int i = 1; i < nbTransWithInput.size(); i++)
				if (nbTransWithInput.get(minIn) > nbTransWithInput.get(i))
					minIn = i;

			String in = inputSymbols.get(minIn);

			// List with the number of outgoing transition from state "from"
			// with the input symbol "in"
			List<Integer> nbTransWithOutput = new ArrayList<Integer>();
			for (int i = 0; i < inputSymbols.size(); i++)
				nbTransWithOutput.add(0);
			for (EFSMTransition t : transitions) {
				if (t.getFrom().equals(from) && t.getInput().equals(in)) {
					int idx = outputSymbols.indexOf(t.getOutput());
					nbTransWithOutput.set(idx, nbTransWithOutput.get(idx) + 1);
				}
			}

			// Get the output symbol with the minimum of occurences
			int minOut = 0;
			for (int i = 1; i < nbTransWithOutput.size(); i++)
				if (nbTransWithOutput.get(minOut) > nbTransWithOutput.get(i))
					minOut = i;

			String out = outputSymbols.get(minOut);

			// Create the transition if the simpa.hit.automata can stay deterministic
			if (nbTransWithOutput.get(minOut) >= 2) {
				LogManager.logInfo("State " + s + " will stay unreachable");
			} else {
				LogManager.logInfo("States " + s
						+ " have been fixed adding transition to " + from
						+ " to " + s);
				addTransition(new EFSMTransition(this, from, s, in, out,
						new GeneratedOutputFunction(arity.get(in),
								arity.get(out))));
				reachables.add(s);
			}

			classifyStatesUnreachable(reachables, unreachables);
		}
	}

	private void fixDeadEndStates() {
		Set<State> deadend = new HashSet<State>();
		Set<State> notdeadend = new HashSet<State>();
		classifyDeadEndStates(deadend, notdeadend);
		LogManager.logInfo("Those states are deadend : " + deadend);
		for (State s : deadend) {
			Set<State> others = new HashSet<State>();
			others.addAll(states);
			others.remove(s);
			State to = Utils.randIn(others);
			if (to != null) {
				String in = Utils.randIn(inputSymbols);
				String out = Utils.randIn(outputSymbols);
				addTransition(new EFSMTransition(this, s, to, in, out,
						new GeneratedOutputFunction(arity.get(in),
								arity.get(out))));
				LogManager.logInfo("States " + s + " have been fixed");
			}
		}
	}

	private void classifyDeadEndStates(Set<State> deadend, Set<State> notdeadend) {
		deadend.clear();
		notdeadend.clear();
		for (EFSMTransition t : transitions) {
			if (!t.getFrom().equals(t.getTo()))
				notdeadend.add(t.getFrom());
		}
		deadend.addAll(states);
		deadend.removeAll(notdeadend);
	}

	private void classifyStatesUnreachable(Set<State> reach, Set<State> unreach) {
		Set<State> newreachable = new HashSet<State>();
		reach.clear();
		unreach.clear();
		reach.add(getInitialState());
		newreachable.add(getInitialState());
		do {
			HashSet<State> tmp = new HashSet<State>();
			for (State s : newreachable) {
				for (EFSMTransition t : transitions) {
					if (t.getFrom().equals(s))
						tmp.add(t.getTo());
				}
			}
			newreachable = tmp;
			newreachable.removeAll(reach);
			reach.addAll(newreachable);
		} while (newreachable.size() > 0);
		unreach.addAll(states);
		unreach.removeAll(reach);
	}

	private void createTransitions() {
		String in = null, out = null;
		int nbTrans = 0;
		List<String> previous = new ArrayList<String>();
		for (State s1 : states) {
			previous.clear();
			nbTrans = 0;
			for (State s2 : states) {
				if (Utils.randBoolWithPercent(Options.TRANSITIONPERCENT
						/ states.size())
						&& nbTrans < 2) {
					boolean added = false;
					nbTrans++;
					while (!added) {
						in = Utils.randIn(inputSymbols);
						List<String> outExists = getOutputForThisInput(s1, in);
						if (outExists.size() == outputSymbols.size())
							continue;
						do
							out = Utils.randIn(outputSymbols);
						while (previous.contains(in + "|" + out));
						addTransition(new EFSMTransition(this, s1, s2, in, out,
								new GeneratedOutputFunction(arity.get(in),
										arity.get(out))));
						previous.add(in + "|" + out);
						added = true;
					}
				}
			}
		}
	}

	private void createStates() {
		int nbStates = Utils.randIntBetween(Options.MINSTATES,
				Options.MAXSTATES);
		for (int i = 0; i < nbStates; i++)
			addState(i == 0);
		LogManager.logInfo("Number of states : " + nbStates);
	}

	public HashMap<String, List<ArrayList<Parameter>>> getDefaultParamValues() {
		return dpv;
	}

	public TreeMap<String, List<String>> getDefaultParamNames() {
		TreeMap<String, List<String>> res = new TreeMap<String, List<String>>();
		for (String symbol : arity.keySet()) {
			List<String> names = new ArrayList<String>();
			for (int i = 0; i < arity.get(symbol); i++)
				names.add(symbol + "p" + i);
			res.put(symbol, names);
		}
		return res;
	}

	public int getSimpleGuardCount() {
		return simpleCount;
	}

	public int getNdvGuardCount() {
		return ndvCount;
	}
}
