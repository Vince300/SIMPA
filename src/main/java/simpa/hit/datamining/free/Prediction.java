package simpa.hit.datamining.free;

import java.util.ArrayList;
import java.util.Iterator;

import simpa.hit.main.simpa.Options;

public class Prediction extends ArrayList<Condition>{
	private static final long serialVersionUID = -7461576989004249870L;
	String final_state;
	
	public Prediction (String f_state) {
		super();
		final_state = new String(f_state);
	}
	
	public Prediction (Condition c, String f_state) {
		super();
		final_state = new String(f_state);
		this.add(c);
	}
	
	public String toString() {
		String str = "";
		str += final_state+" :\n";
		Iterator<Condition> itr = this.iterator();
		if (itr.hasNext()) {
			str += "   (";
			str += itr.next().toString();
			str += ")\n";
		}
		while (itr.hasNext()) {
			str += Options.SYMBOL_OR + " (";
			str += itr.next().toString();
			str += ")\n";
		}
		return str;
	}
}
