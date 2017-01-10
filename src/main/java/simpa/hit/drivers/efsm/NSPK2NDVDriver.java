package simpa.hit.drivers.efsm;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.TreeMap;

import simpa.hit.tools.Utils;
import simpa.hit.automata.efsm.Parameter;
import simpa.hit.examples.efsm.NSPK2NDV;

public class NSPK2NDVDriver extends EFSMDriver {

	public NSPK2NDVDriver() {
		super(NSPK2NDV.getAutomata());
	}

	@Override
	public HashMap<String, List<ArrayList<Parameter>>> getDefaultParamValues() {
		HashMap<String, List<ArrayList<Parameter>>> defaultParamValues = new HashMap<String, List<ArrayList<Parameter>>>();
		ArrayList<ArrayList<Parameter>> params = null;

		// m1
		{
			params = new ArrayList<ArrayList<Parameter>>();
			params.add(Utils.createArrayList(new Parameter("5", Types.NUMERIC)));
			params.add(Utils.createArrayList(new Parameter("6", Types.NUMERIC)));
			defaultParamValues.put("m1", params);
		}

		// m3
		{
			params = new ArrayList<ArrayList<Parameter>>();
			params.add(Utils
					.createArrayList(new Parameter("10", Types.NUMERIC)));
			params.add(Utils
					.createArrayList(new Parameter("11", Types.NUMERIC)));
			defaultParamValues.put("m3", params);
		}

		return defaultParamValues;
	}

	@Override
	public TreeMap<String, List<String>> getParameterNames() {
		TreeMap<String, List<String>> defaultParamNames = new TreeMap<String, List<String>>();
		defaultParamNames.put("m1", Utils.createArrayList("sendedID"));
		defaultParamNames.put("m2",
				Utils.createArrayList("receivedID", "receivedSessionID"));
		defaultParamNames.put("m3", Utils.createArrayList("sendedSessionID"));
		defaultParamNames.put("m4", Utils.createArrayList("sendedSessionID3"));
		defaultParamNames.put("KO", Utils.createArrayList("default1"));
		defaultParamNames.put("OK", Utils.createArrayList("default2"));
		defaultParamNames.put("OK2", Utils.createArrayList("default22"));
		return defaultParamNames;
	}

}
