package simpa.hit.learner.mealy.combinatorial.node;

import java.util.ArrayList;
import java.util.List;

import simpa.hit.automata.State;
import simpa.hit.drivers.mealy.MealyDriver;

public class ArrayTreeNodeWithConjecture extends TreeNodeWithConjecture{
	private List<ArrayTreeNodeWithConjecture> children;

	public ArrayTreeNodeWithConjecture(MealyDriver d){
		super(d);
		children = new ArrayList<ArrayTreeNodeWithConjecture>();
	}

	private ArrayTreeNodeWithConjecture(ArrayTreeNodeWithConjecture parent, State s) {
		super(parent,s);
		children = new ArrayList<ArrayTreeNodeWithConjecture>();
	}

	public ArrayTreeNodeWithConjecture getOnlyChild() {
		assert haveForcedChild();
		return children.get(0);
	}
	
	public ArrayTreeNodeWithConjecture getChild(State s){
		for (ArrayTreeNodeWithConjecture c : children)
			if (c.getState().equals(s))
				return c;
		return null;
	}

	public void cut() {
		assert children.isEmpty();
		super.cut();
	}

	public ArrayTreeNodeWithConjecture addForcedChild(State to) {
		assert children.isEmpty();
		ArrayTreeNodeWithConjecture child = new ArrayTreeNodeWithConjecture(this, to);
		children.add(child);
		setForcedChild();
		return child;
	}

	public ArrayTreeNodeWithConjecture addChild(String i, String o, State q) {
		ArrayTreeNodeWithConjecture child = new ArrayTreeNodeWithConjecture(this, q);
		child.addTransition(getState(), q, i, o);
		children.add(child);
		return child;
	}
	
	public TreeNode removeChild(State q){
		for (ArrayTreeNodeWithConjecture n : children){
			if (n.getState().equals(q))
				children.remove(n);
			return n;
		}
		return null;
	}
}
