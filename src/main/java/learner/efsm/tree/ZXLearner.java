package learner.efsm.tree;

import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.Deque;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import learner.Learner;
import learner.mealy.LmConjecture;
import learner.mealy.Node;
import main.simpa.Options;
import tools.loggers.LogManager;
import automata.State;
import automata.mealy.InputSequence;
import automata.mealy.MealyTransition;
import drivers.Driver;
import drivers.efsm.real.ScanDriver;

public class ZXLearner extends Learner {
	private ScanDriver driver;
	private List<InputSequence> z;
	private List<String> i;
	private ZXObservationNode u;
	private List<ZXObservationNode> states;

	public ZXLearner(Driver driver) {
		this.driver = (ScanDriver) driver;

		this.i = new ArrayList<String>();
		this.z = new ArrayList<InputSequence>();

		// an observation tree U, initialized with {e}.
		this.u = new ZXObservationNode();

		LogManager.logConsole("Options : I -> " + i.toString());
		LogManager.logConsole("Options : Z -> " + z.toString());
		LogManager.logConsole("Options : Urls -> " + Options.URLS);
	}

	private LmConjecture fixPointConsistency(LmConjecture K) {
		InputSequence inconsistency;

		// 1. while there exists a witness w for state q in U such that its
		// input projection is not in Z
		do {
			inconsistency = findInconsistency(K);
			if (inconsistency != null) {
				// 4. Z' = Z U {w|I} and I' = I U inp(w)
				// 6. Z = Z' and I = I'
				z = extendInputSequencesWith(z, inconsistency);
				i = extendInputSymbolsWith(inconsistency);

				// 5. Build_quotient(A, I', Z', U) returning an updated
				// observation tree and quotient
				K = buildQuotient(z);
			}
		} while (inconsistency != null);

		// 7. Return the last labelled observation tree (global) and quotient.
		return K;
	}
	
	private String getTracesFromNode(Node n, List<InputSequence> seqs){
		StringBuilder s = new StringBuilder();
		for(InputSequence seq : seqs){
			s.append(getTraceFromNode(n, seq));
		}
		return s.toString();
	}
	
	private String getTraceFromNode(Node n, InputSequence seq){
		StringBuilder s = new StringBuilder();
		for(String i : seq.sequence){
			n = n.childBy(i);
			if (n == null) return "|";
			else s.append(n.output);
		}
		return s.toString();
	}

	private LmConjecture buildQuotient(List<InputSequence> z) {
		LogManager.logInfo("Build Quotient");
		LogManager.logInfo("Z : " + z.toString());
		LogManager.logInfo("I : " + i.toString());
		Deque<Node> queue = null;
		ZXObservationNode currentNode = null;

		// 1. q0 := e, Q : = {q0}
		this.states = new ArrayList<ZXObservationNode>();
		
		//1.5 CachedEquivalent
		Map<String, Node> cache = new HashMap<String, Node>();


		// 2. for (each state u of U being traversed during Breadth First Search
		queue = new ArrayDeque<Node>();
		queue.add(u);
		currentNode = null;
		while (!queue.isEmpty()) {
			currentNode = (ZXObservationNode) queue.pollFirst();

			// 2. such that u has no labelled predecessor
			if (noLabelledPred(currentNode)) {
				// 4. Extend_Node(A, u, Z),
				extendNodeWithInputSeqs(currentNode, z);

				// 5. if (u is Z-equivalent to a traversed state w of U)
				ZXObservationNode w = (ZXObservationNode) cache.get(getTracesFromNode(currentNode, z));
				if (w != null) {
					// 6. Label u with w
					currentNode.label = w.state;
					currentNode.state = -1;
				} else {
					// 8. Add u into Q
					addState(currentNode);
					// 9. Extend_Node(A, u, I)
					extendNodeWithSymbols(currentNode, i);
					// 9.5
					cache.put(getTracesFromNode(currentNode, z), currentNode);
				}
			}else{
				currentNode.label = -1;
				currentNode.state = -1;
			}
			queue.addAll(currentNode.children.values());
		}

		// 11. for (each transition (u, ab, v), such that neither state u nor
		// any of its predecessors is labelled)
		// 12. begin
		// 13. if (v is not labelled)
		// 14. Add transition (u, ab, v) to K
		// 15. else
		// 16. Add transition (u, ab, w), where w = label(v), to K.
		// 17. end
		LmConjecture ret = createConjecture();

		// NEEDED ?
		// 18. for each node u labelled with u label its successor nodes such
		// that for each transition (u, ab, v), if there is a transition (u,
		// ab, w) in K, then label(v) = w, else v is not labelled.
		labelNodes(ret);

		return ret;
	}

	public void learn() {
		LogManager.logConsole("Inferring the system");
		InputSequence ce;

		// 1. Build-quotient(A, I, Z, {€}) returning U and K = (Q, q0, I, O, hK)
		LmConjecture Z_Q = buildQuotient(z);

		// 2. Fix_Point_Consistency(A, I, Z, U, K)
		Z_Q = fixPointConsistency(Z_Q);

		System.out.println();
	}

	private boolean noLabelledPred(ZXObservationNode node) {
		boolean noLabelledPred = true;
		while (node.parent != null) {
			ZXObservationNode parent = (ZXObservationNode) node.parent;
			if (parent.isLabelled())
				return false;
			node = parent;
		}
		return noLabelledPred;
	}

	private void addState(ZXObservationNode node) {
		node.state = states.size();

		// ADDED
		node.label = -1;

		states.add(node);
	}

	private void extendNodeWithInputSeqs(Node node, List<InputSequence> Z) {
		for (InputSequence seq : Z) {
			askInputSequenceToNode(node, seq);
		}
	}

	private void extendNodeWithSymbols(Node node, List<String> symbols) {
		for (String symbol : symbols) {
			askInputSequenceToNode(node, new InputSequence(symbol));
		}
	}

	private List<String> extendInputSymbolsWith(InputSequence ce) {
		List<String> ret = new ArrayList<String>(i);
		for (String sym : ce.sequence) {
			if (!ret.contains(sym))
				ret.add(sym);
		}
		return ret;
	}

	private List<InputSequence> extendInputSequencesWith(
			List<InputSequence> into, InputSequence seq) {
		List<InputSequence> ret = new ArrayList<InputSequence>();
		boolean exists = false;
		for (InputSequence s : into) {
			ret.add(s);
			if (s.equals(seq))
				exists = true;
		}
		if (!exists && seq.getLength() > 0)
			ret.add(seq);
		return ret;
	}

	private void labelNodes(LmConjecture q) {
		LogManager.logInfo("Labeling nodes");
		labelNodesRec(q, u, q.getInitialState(), false);
		//LogManager.logObservationTree(u);
	}

	private void labelNodesRec(LmConjecture q, ZXObservationNode node, State s,
			boolean label) {
		if (label)
			node.label = s.getId();
		if (node.isLabelled())
			label = true;
		if (!node.children.isEmpty()) {
			for (Node n : node.children.values()) {
				MealyTransition t = q.getTransitionFromWithInput(s, n.input);
				if (t != null)
					labelNodesRec(q, (ZXObservationNode) n, t.getTo(), label);
			}
		}
	}

	private InputSequence findInconsistency(LmConjecture c) {
		LogManager.logInfo("Searching inconsistency");
		InputSequence ce = findInconsistencyRec(c, c.getInitialState(), u,
				new InputSequence());
		if (ce != null)
			LogManager.logInfo("Inconsistency found : " + ce);
		else
			LogManager.logInfo("No inconsistency found");
		return ce;
	}

	private InputSequence findInconsistencyRec(LmConjecture c, State s,
			ZXObservationNode node, InputSequence ce) {
		for (Node n : node.children.values()) {
			if (!((ZXObservationNode) n).isState())
				ce.addInput(n.input);
			MealyTransition t = c.getTransitionFromWithInput(s, n.input);
			if (t != null && t.getOutput().equals(n.output)) {
				InputSequence otherCE = findInconsistencyRec(c, t.getTo(),
						(ZXObservationNode) n, ce);
				if (otherCE != null) {
					boolean processed = false;
					for (InputSequence seq : z) {
						if (seq.equals(ce)) {
							processed = true;
							break;
						}
					}
					if (!processed && ce.getLength() > 0)
						return otherCE;
				}
			} else {
				boolean processed = false;
				for (InputSequence seq : z) {
					if (seq.equals(ce)) {
						processed = true;
						break;
					}
				}
				if (ce.getLength() == 1 && !processed)
					return ce;
				else {
					if (ce.getLength() > 1)
						return ce.removeFirstInput();
				}
			}
			if (!((ZXObservationNode) n).isState())
				ce.removeLastInput();
		}
		return null;
	}

	private void askInputSequenceToNode(Node node, InputSequence sequence) {
		Node currentNode = node;
		InputSequence seq = sequence.clone();
		InputSequence previousSeq = getPreviousInputSequenceFromNode(currentNode);
		while (seq.getLength() > 0
				&& currentNode.childBy(seq.getFirstSymbol()) != null) {
			currentNode = currentNode.childBy(seq.getFirstSymbol());
			previousSeq.addInput(seq.getFirstSymbol());
			seq.removeFirstInput();
		}
		if (seq.getLength() > 0) {
			driver.reset();
			for (String input : previousSeq.sequence) {
				//driver.execute(input);
			}
			for (String input : seq.sequence) {
				//if (currentNode.childBy(input) != null)
				//	currentNode = currentNode.childBy(input);
				//else
					//currentNode = currentNode.addChild(new ZXObservationNode(
					//		input, driver.execute(input)));
			}
		}
	}

	private InputSequence getPreviousInputSequenceFromNode(Node node) {
		Node currentNode = node;
		InputSequence seq = new InputSequence();
		while (currentNode.parent != null) {
			seq.prependInput(currentNode.input);
			currentNode = currentNode.parent;
		}
		return seq;
	}

	public LmConjecture createConjecture() {
		LogManager.logInfo("Building conjecture");
		//LogManager.logObservationTree(u);

		LmConjecture c = new LmConjecture(driver);

		for (int i = 0; i < states.size(); i++)
			c.addState(new State("S" + i, i == 0));

		for (ZXObservationNode s : states) {
			for (String input : i) {
				ZXObservationNode child = (ZXObservationNode) s.childBy(input);
				if (!child.output.isEmpty()) {
					if (child.isState())
						c.addTransition(new MealyTransition(c, c
								.getState(s.state), c.getState(child.state),
								input, child.output));
					else{
						c.addTransition(new MealyTransition(c,
								c.getState(s.state),
								c.getState(child.label),
								input, child.output));
					}
				}
			}
		}

		LogManager.logInfo("Z : " + z);
		LogManager.logInfo("I : " + i);

		LogManager.logInfo("Conjecture has " + c.getStateCount()
				+ " states and " + c.getTransitionCount() + " transitions : ");
		for (MealyTransition t : c.getTransitions())
			LogManager.logTransition(t.toString());
		LogManager.logLine();
		
		System.out.print("      states : " + c.getStateCount() + "\r");
		System.out.flush();

		c.exportToDot();

		return c;
	}
}
