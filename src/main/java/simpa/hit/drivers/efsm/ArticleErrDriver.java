package simpa.hit.drivers.efsm;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.TreeMap;

import simpa.hit.tools.Utils;
import simpa.hit.automata.efsm.Parameter;
import simpa.hit.examples.efsm.ArticleErr;

public class ArticleErrDriver extends EFSMDriver {

	public ArticleErrDriver() {
		super(ArticleErr.getAutomata());
	}

	@Override
	public HashMap<String, List<ArrayList<Parameter>>> getDefaultParamValues() {
		HashMap<String, List<ArrayList<Parameter>>> defaultParamValues = new HashMap<String, List<ArrayList<Parameter>>>();
		ArrayList<ArrayList<Parameter>> params = null;

		// a
		{
			params = new ArrayList<ArrayList<Parameter>>();
			params.add(Utils.createArrayList(new Parameter("5", Types.NUMERIC)));
			params.add(Utils.createArrayList(new Parameter("6", Types.NUMERIC)));
			defaultParamValues.put("a", params);
		}

		// b
		{
			params = new ArrayList<ArrayList<Parameter>>();
			params.add(Utils.createArrayList(new Parameter("2", Types.NUMERIC)));
			params.add(Utils.createArrayList(new Parameter("3", Types.NUMERIC)));
			defaultParamValues.put("b", params);
		}
		return defaultParamValues;
	}

	@Override
	public TreeMap<String, List<String>> getParameterNames() {
		TreeMap<String, List<String>> defaultParamNames = new TreeMap<String, List<String>>();
		defaultParamNames.put("a", Utils.createArrayList("ap1"));
		defaultParamNames.put("b", Utils.createArrayList("bp1"));
		defaultParamNames.put("c", Utils.createArrayList("cp1"));
		defaultParamNames.put("d", Utils.createArrayList("dp1"));
		defaultParamNames.put("e", Utils.createArrayList("ep1"));
		return defaultParamNames;
	}
}
