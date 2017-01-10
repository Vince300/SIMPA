package simpa.hit.examples.efsm;

import java.util.ArrayList;
import java.util.List;

import simpa.hit.automata.State;
import simpa.hit.automata.efsm.EFSM;
import simpa.hit.automata.efsm.EFSMTransition;
import simpa.hit.automata.efsm.IOutputFunction;
import simpa.hit.automata.efsm.Parameter;
import simpa.hit.drivers.efsm.EFSMDriver.Types;

public class Dummy {

	public static EFSM getAutomata() {
		EFSM test = new EFSM("Dummy");
		State s1 = test.addState(true);
		State s2 = test.addState();
		State s3 = test.addState();
		test.addTransition(new EFSMTransition(test, s1, s2, "A", "C",
				new IOutputFunction() {
					@Override
					public List<Parameter> process(EFSM automata,
							List<Parameter> inputParameters) {
						if (inputParameters.get(0).value.equals("5")) {
							List<Parameter> p = new ArrayList<Parameter>();
							p.add(new Parameter("10", Types.NUMERIC));
							return p;
						}
						return null;
					}
				}));
		test.addTransition(new EFSMTransition(test, s2, s3, "B", "D",
				new IOutputFunction() {
					@Override
					public List<Parameter> process(EFSM automata,
							List<Parameter> inputParameters) {
						List<Parameter> p = new ArrayList<Parameter>();
						p.add(new Parameter(String.valueOf(Integer
								.parseInt(inputParameters.get(0).value) * 2),
								Types.NUMERIC));
						return p;
					}
				}));
		test.addTransition(new EFSMTransition(test, s3, s1, "A", "D",
				new IOutputFunction() {
					@Override
					public List<Parameter> process(EFSM automata,
							List<Parameter> inputParameters) {
						if (inputParameters.get(0).value.equals("1")) {
							List<Parameter> p = new ArrayList<Parameter>();
							p.add(new Parameter("0", Types.NUMERIC));
							return p;
						}
						return null;
					}
				}));
		return test;
	}
}
