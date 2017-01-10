package simpa.hit.examples.efsm;

import java.security.SecureRandom;
import java.util.ArrayList;
import java.util.List;

import simpa.hit.automata.State;
import simpa.hit.automata.efsm.EFSM;
import simpa.hit.automata.efsm.EFSMTransition;
import simpa.hit.automata.efsm.IOutputFunction;
import simpa.hit.automata.efsm.Parameter;
import simpa.hit.drivers.efsm.EFSMDriver.Types;

public class NSPK {

	public static EFSM getAutomata() {
		EFSM test = new EFSM("NSPK");
		State s1 = test.addState(true);
		State s2 = test.addState();
		State s3 = test.addState();
		test.addTransition(new EFSMTransition(test, s1, s2, "m1", "m2",
				new IOutputFunction() {
					@Override
					public List<Parameter> process(EFSM automata,
							List<Parameter> inputParameters) {
						List<Parameter> p = new ArrayList<Parameter>();
						int n = new SecureRandom().nextInt(1000);
						automata.setMemory("n", String.valueOf(n));
						p.add(new Parameter(inputParameters.get(0).value,
								Types.NUMERIC));
						p.add(new Parameter(String.valueOf(n), Types.NUMERIC));
						return p;
					}
				}));
		test.addTransition(new EFSMTransition(test, s2, s3, "m3", "OK",
				new IOutputFunction() {
					@Override
					public List<Parameter> process(EFSM automata,
							List<Parameter> inputParameters) {
						if (inputParameters.get(0).value.equals(automata
								.getMemory("n"))) {
							List<Parameter> p = new ArrayList<Parameter>();
							p.add(new Parameter("1", Types.NUMERIC));
							return p;
						} else
							return null;
					}
				}));
		test.addTransition(new EFSMTransition(test, s2, s2, "m3", "KO",
				new IOutputFunction() {
					@Override
					public List<Parameter> process(EFSM automata,
							List<Parameter> inputParameters) {
						if (!(inputParameters.get(0).value.equals(automata
								.getMemory("n")))) {
							List<Parameter> p = new ArrayList<Parameter>();
							p.add(new Parameter("0", Types.NUMERIC));
							return p;
						} else
							return null;
					}
				}));
		test.addTransition(new EFSMTransition(test, s3, s2, "m1", "m2",
				new IOutputFunction() {
					@Override
					public List<Parameter> process(EFSM automata,
							List<Parameter> inputParameters) {
						List<Parameter> p = new ArrayList<Parameter>();
						int n = new SecureRandom().nextInt(1000);
						automata.setMemory("n", String.valueOf(n));
						p.add(new Parameter(inputParameters.get(0).value,
								Types.NUMERIC));
						p.add(new Parameter(String.valueOf(n), Types.NUMERIC));
						return p;
					}
				}));
		return test;
	}
}
