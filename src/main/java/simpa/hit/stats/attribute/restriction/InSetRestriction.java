package simpa.hit.stats.attribute.restriction;

import java.util.Arrays;
import java.util.List;

import simpa.hit.stats.StatsEntry;
import simpa.hit.stats.attribute.Attribute;


public class InSetRestriction<T extends Comparable<T>> extends Restriction {
	Attribute<T> a;
	List<T> values;

	public InSetRestriction(Attribute<T> a, T[] values) {
		this.a = a;
		this.values = Arrays.asList(values);
	}
	
	@Override
	public boolean contains(StatsEntry s) {
		return values.contains(s.get(a));
	}

	public String toString(){
		return a.getName() + " in " + values + a.getUnits().getSymbol();
	}
}
