package simpa.hit.datamining.free;

import java.util.Iterator;
import java.util.LinkedList;

import simpa.hit.main.simpa.Options;

public class Condition extends LinkedList<Tag> {
	private static final long serialVersionUID = -6467576331816693683L;

	public Condition() {
		super();
	}
	
	public Condition(Tag t) {
		super();
		this.add(t);
	}
	
	public Condition(Condition c) {
		super();
		Iterator<Tag> itr = c.iterator();
		while (itr.hasNext()) {
			this.add(itr.next());
		}
	}
	
	public String toString() {
		String str = "";
		Iterator<Tag> itr = this.iterator();
		if (itr.hasNext()) {
			str += itr.next().toString();
		}
		while (itr.hasNext()) {
			str += " " + Options.SYMBOL_AND + " ";
			str += itr.next().toString();
		}
		return str;
	}
}
