package simpa.hit.learner.mealy.table;

import java.util.Collections;
import java.util.Comparator;
import java.util.List;

import simpa.hit.learner.Learner;
import simpa.hit.learner.mealy.LmConjecture;
import simpa.hit.tools.loggers.LogManager;
import simpa.hit.automata.State;
import simpa.hit.automata.mealy.InputSequence;
import simpa.hit.automata.mealy.MealyTransition;
import simpa.hit.automata.mealy.OutputSequence;
import simpa.hit.drivers.Driver;
import simpa.hit.drivers.mealy.MealyDriver;

public class LmLearner extends Learner {
	private MealyDriver driver;
	private LmControlTable cTable;

	public LmLearner(Driver driver) {
		this.driver = (MealyDriver) driver;
		this.cTable = new LmControlTable(driver.getInputSymbols());
	}

	private void completeTable() {
		for (int i = 0; i < cTable.getCountOfRowsInS(); i++)
			fillTablesForRow(cTable.getRowInS(i));
		for (int i = 0; i < cTable.getCountOfRowsInR(); i++)
			fillTablesForRow(cTable.getRowInR(i));
	}

	private void fillTablesForRow(LmControlTableRow ctr) {
		InputSequence querie = null;
		for (int i = 0; i < ctr.getColumnCount(); i++) {
			if (ctr.getColumn(i).getOutputSymbol() == null) {
				driver.reset();
				querie = ctr.getIS();
				querie.addInputSequence(ctr.getInputSequence(i));
				InputSequence is = new InputSequence();
				OutputSequence os = new OutputSequence();
				for (int j = 0; j < querie.sequence.size(); j++) {
					String pi = new String(querie.sequence.get(j));
					is.addInput(pi);
					String po = driver.execute(pi);
					os.addOutput(po);
				}
				LmControlTableItem cti = new LmControlTableItem(os
						.getIthSuffix(ctr.getColSuffixSize(i)).toString());
				ctr.setAtColumn(i, cti);
			}
		}
	}

	public LmConjecture createConjecture() {
		if (addtolog)
			LogManager.logConsole("Building the conjecture");
		LmConjecture c = new LmConjecture(driver);
		for (int i = 0; i < cTable.getCountOfRowsInS(); i++) {
			c.addState(new State("S" + i, cTable.getRowInS(i).isEpsilon()));
		}
		List<LmControlTableRow> allRows = cTable.getAllRows();
		Collections.sort(allRows, new Comparator<LmControlTableRow>() {
			@Override
			public int compare(LmControlTableRow o1, LmControlTableRow o2) {
				return o1.getIS().sequence.size() - o2.getIS().sequence.size();
			}
		});
		for (LmControlTableRow ctr : allRows) {
			if (!ctr.isEpsilon()) {
				int iFrom = cTable.getFromState(ctr);
				int iTo = cTable.getToState(ctr);
				State from = c.getState(iFrom);
				State to = c.getState(iTo);
				String inputSymbol = ctr.getLastPI();
				LmControlTableItem controlItem = cTable.getRowInS(iFrom)
						.getColumn(
								cTable.getInputSymbols().indexOf(inputSymbol));

				if (!controlItem.isOmegaSymbol()) {
					c.addTransition(new MealyTransition(c, from, to,
							inputSymbol, controlItem.getOutputSymbol()));
				}
			}
		}
/*		for (int i = c.getTransitionCount() - 1; i >= 0; i--) {
			for (int j = i - 1; j >= 0; j--) {
				MealyTransition t1 = c.getTransition(i);
				MealyTransition t2 = c.getTransition(j);
				if (t1.getInput().equals(t2.getInput())
						&& t1.getOutput().equals(t2.getOutput())
						&& (t1.getFrom().equals(t2.getFrom()))
						&& (t1.getTo().equals(t2.getTo()))) {
					c.removeTransition(i);
					break;
				}
			}
		}*/

		LogManager.logInfo("Conjecture has " + c.getStateCount()
				+ " states and " + c.getTransitionCount() + " transitions : ");
		for (MealyTransition t : c.getTransitions()) {
			LogManager.logTransition(t.toString());
		}
		LogManager.logLine();

		if (addtolog)
			LogManager.logConsole("Exporting conjecture");
		c.exportToDot();

		return c;
	}

	private void handleNonClosed(int iRow) {
		InputSequence origPis = cTable.getRowInR(iRow).getIS();
		cTable.addRowInS(cTable.removeRowInR(iRow));
		for (int i = 0; i < cTable.getInputSymbolsCount(); i++) {
			InputSequence pis = origPis.clone();
			pis.addInput(new String(cTable.getInputSymbol(i)));
			LmControlTableRow newControlRow = new LmControlTableRow(pis,
					cTable.E);
			cTable.addRowInR(newControlRow);
		}
		completeTable();
	}

	public void learn() {
		LogManager.logConsole("Inferring the system");
// RG: changed Karim's use of finished that repeated CE search after final conjecture.
//		boolean finished = false;
		boolean potentialNewNonClosedRows = true;
		InputSequence ce = null;
		completeTable();
		LogManager.logControlTable(cTable);
		while (true /*!finished*/) {
			potentialNewNonClosedRows = true;
//			finished = true;
			while (potentialNewNonClosedRows) {
				potentialNewNonClosedRows = false;
				int alreadyNonClosed = 0;
				for (int nonClosedRow : cTable.getNonClosedRows()) {
					potentialNewNonClosedRows=true;
//					finished = false;
					LogManager.logStep(LogManager.STEPNCR,
							cTable.R.get(nonClosedRow).getIS());
					handleNonClosed(nonClosedRow - (alreadyNonClosed++));
					LogManager.logControlTable(cTable);
				}
			}
			stopLog();
			LmConjecture conj = createConjecture();
			startLog();
			if (!driver.isCounterExample(ce, conj))
				ce = driver.getCounterExample(conj);
			else
				LogManager.logInfo("Previous counter example : " + ce
						+ " is still a counter example for the new conjecture");
			if (ce != null) {
//				finished = false;
				int suffixLength = 1;
				do {
					cTable.addColumnInE(ce.getIthSuffix(suffixLength));
					completeTable();
					if (!cTable.getNonClosedRows().isEmpty())
						break;
					suffixLength++;
				} while (suffixLength <= ce.getLength());
				if (cTable.getNonClosedRows().isEmpty())
// RG: this should not happen with Lm. Test could be converted to assert once we are sure.
					LogManager.logInfo("Counter example failed to exhibit new state");
				LogManager.logControlTable(cTable);
			}
			else
//				finished = true;
				break;
		}
	}
}
