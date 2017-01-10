package simpa.hit.learner.efsm;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.FileWriter;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.Writer;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.TreeMap;

import simpa.hit.main.simpa.Options;
import simpa.hit.tools.ASLanEntity;
import simpa.hit.tools.GraphViz;
import simpa.hit.tools.Utils;
import simpa.hit.tools.XMLModel;
import simpa.hit.tools.loggers.LogManager;
import simpa.hit.automata.State;
import simpa.hit.automata.efsm.EFSMTransition;
import simpa.hit.automata.efsm.EFSMTransition.Label;
import simpa.hit.datamining.free.FreeARFF;
import simpa.hit.datamining.free.TreeNode;
import simpa.hit.datamining.weka.WekaARFF;
import simpa.hit.datamining.weka.WekaTreeNode;
import simpa.hit.drivers.Driver;
import simpa.hit.drivers.efsm.EFSMDriver;

public class LiConjecture extends simpa.hit.automata.efsm.EFSM {
	private static final long serialVersionUID = 6592229434557819171L;

	private List<String> inputSymbols;
	private TreeMap<String, List<String>> paramNames;
	private Map<String, Label> labels;
	public List<String> gSymbols;

	public LiConjecture(Driver d) {
		super(d.getSystemName());
		this.inputSymbols = d.getInputSymbols();
		this.paramNames = ((EFSMDriver) d).getParameterNames();
		if (paramNames == null) {
			LogManager.logException("No parameter names defined",
					new Exception());
			System.exit(0);
		}
	}

	public List<String> getParamNames(String inputSymbol) {
		return paramNames.get(inputSymbol);
	}

	public List<String> getInputSymbols() {
		return inputSymbols;
	}

	public Label getLabelForTransition(EFSMTransition t) {
		return labels.get(t.toString());
	}

	public void exportToRawDot() {
		LogManager.logConsole("Exporting raw conjecture");
		Writer writer = null;
		File file = null;
		File dir = new File(Options.OUTDIR + Options.DIRGRAPH);
		try {
			if (!dir.isDirectory() && !dir.mkdirs())
				throw new IOException("unable to create " + dir.getName()
						+ " directory");

			file = new File(dir.getPath() + File.separatorChar + name
					+ ".raw.dot");
			writer = new BufferedWriter(new FileWriter(file));
			writer.write("digraph G {\n");
			for (EFSMTransition t : getTransitions()) {
				writer.write("\t" + t.toRawDot() + "\n");
			}
			writer.write("}\n");
			writer.close();
			LogManager.logInfo("Raw conjecture has been exported to "
					+ file.getName());
			File imagePath = GraphViz.dotToFile(file.getPath());
			if (imagePath != null)
				LogManager.logImage(imagePath.getPath());
		} catch (IOException e) {
			LogManager.logException("Error writing dot file", e);
		}
	}
	
	public void fillVar(EFSMTransition t, Label label){
		if (Options.WEKA){
			String dataFile = WekaARFF.generateFileForVar(t, paramNames);
			dataFile = WekaARFF.filterFileForVar(dataFile);
			dataFile = WekaARFF.handleConstantOutput(dataFile, label);
			dataFile = WekaARFF.handleRelatedDataForOutput(dataFile);
			dataFile = WekaARFF.handleDifferentOutput(dataFile, label, t);		
			
		}else{
			String dataFile = FreeARFF.generateFileForVar(t, paramNames);
			dataFile = FreeARFF.handleConstantOutput(dataFile, label);
			dataFile = FreeARFF.handleRelatedDataForOutput(dataFile);
			dataFile = FreeARFF.handleDifferentOutput(dataFile, label, t);			
		}		 
	}

	private void fillPredicate(List<EFSMTransition> list,
			Map<String, Label> labels) {
		if (list.size() > 1) {
			if (Options.WEKA){				
				String dataFile = WekaARFF.generateFileForPredicate(list, paramNames);
				dataFile = WekaARFF.filterFileForPredicate(dataFile);
				dataFile = WekaARFF.handleRelatedDataForPredicate(dataFile);
				WekaTreeNode node = WekaARFF.handlePredicate(dataFile);
				if(node != null){
					for(EFSMTransition t : list){
						for(String pred : node.getPredicatesFor(t.getTo()+t.getOutput())){
							labels.get(t.toString()).addPredicate(pred);
						}
					}
				}
				
			}else{
				String dataFile = simpa.hit.datamining.free.Classifier.generateFileForPredicate(list, paramNames);
				dataFile = simpa.hit.datamining.free.Classifier.filterArff(dataFile);
				TreeNode node = simpa.hit.datamining.free.Classifier.Classify(dataFile, -1);
				if(node != null){
					for(EFSMTransition t : list){
						for(String pred : node.getPredicatesFor(t.getTo()+t.getOutput())){
							labels.get(t.toString()).addPredicate(pred);
						}
					}
				}
			}
			
		}
	}

	@Override
	public void exportToDot() {
		LogManager.logConsole("Cleaning and exporting the final conjecture");
		Writer writer = null;
		File file = null;
		File dir = new File(Options.OUTDIR + Options.DIRGRAPH);
			LogManager.logInfo("Exporting final conjecture to file");
			try {
				if (Utils.createDir(dir)) {
					file = new File(dir.getPath() + File.separatorChar + name
							+ ".dot");
					writer = new BufferedWriter(new FileWriter(file));
					writer.write("digraph G {\n");

					labels = new HashMap<String, Label>();
					Label newLabel = null;

					for (EFSMTransition t : getTransitions()) {
						newLabel = t.initializeLabel(paramNames);
						fillVar(t, newLabel);
						labels.put(t.toString(), newLabel);
					}

					for (State s : states) {
						for (String input : inputSymbols) {
							fillPredicate(getTransitionFromWithInput(s, input),
									labels);
						}
					}
					gSymbols = WekaARFF.getGlobalSymbols();

					for (EFSMTransition t : getTransitions()){
						writer.write("\t" + t.getFrom() + " -> " + t.getTo() + "[label=\"" + labels.get(t.toString()).toDotString() + "\"];" + "\n");            	
					}
					writer.write("}\n");
					if (writer != null) writer.close();
					LogManager.logInfo("Conjecture has been exported to "
							+ file.getName());
					File imagePath = GraphViz.dotToFile(file.getPath());
					if (imagePath != null)
						LogManager.logImage(imagePath.getPath());
				} else
					LogManager.logError("unable to create " + dir.getName()
							+ " directory");
			} catch (IOException e) {
				LogManager.logException("Error exporting conjecture to dot", e);
			}
	}

	public static void serialize(LiConjecture o, String filename) {
		FileOutputStream fos = null;
		ObjectOutputStream oos = null;
		try {
			fos = new FileOutputStream(Options.OUTDIR + Options.DIRGRAPH + File.separator
					+ filename);
			oos = new ObjectOutputStream(fos);
			oos.writeObject(o);
			oos.flush();
			oos.close();
			fos.close();
		} catch (Exception e) {
			LogManager.logException("Error serializing generated EFSM", e);
		}
	}

	public static LiConjecture deserialize(String filename) {
		Object o = null;
		File f = new File(Options.OUTDIR + Options.DIRGRAPH + File.separator + filename);
		LogManager.logStep(LogManager.STEPOTHER, "Loading LiConjecture from "
				+ f.getName());
		try {
			FileInputStream fis = new FileInputStream(f.getAbsolutePath());
			ObjectInputStream ois = new ObjectInputStream(fis);
			o = ois.readObject();
			ois.close();
			fis.close();
		} catch (Exception e) {
			LogManager.logException("Error deserializing generated EFSM", e);
		}
		return (LiConjecture) o;
	}

	public void exportToAslan() {
		LogManager.logConsole("Converting conjecture to ASLan++");

		ASLanEntity entity = new ASLanEntity(name);
		entity.loadFromEFSM(this);

		serialize(this, "saved_efsm");

		Writer writer = null;
		File file = null;
		try {
			File dir = new File(Options.OUTDIR + Options.DIRASLAN);
			if (Utils.createDir(dir)) {
				file = new File(dir.getPath() + File.separatorChar
						+ name.replace(" ", "_").toUpperCase() + ".aslan++");
				writer = new BufferedWriter(new FileWriter(file));
				writer.write(entity.toString());
				if (writer != null)
					writer.close();
				LogManager.logInfo("Conjecture has been exported to "
						+ file.getName());
			} else
				LogManager.logError("unable to create " + dir.getName()
						+ " directory");
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	public void exportToXML() {
		LogManager.logConsole("Converting conjecture to XML");

		XMLModel m = new XMLModel(name);
		m.loadFromEFSM(this);

		Writer writer = null;
		File file = null;
		try {
			File dir = new File(Options.OUTDIR + Options.DIRASLAN);
			if (Utils.createDir(dir)) {
				file = new File(dir.getPath() + File.separatorChar
						+ name.replace(" ", "_").toUpperCase() + ".xml");
				writer = new BufferedWriter(new FileWriter(file));
				writer.write(m.toString());
				if (writer != null)
					writer.close();
				LogManager.logInfo("Conjecture has been exported to "
						+ file.getName());
			} else
				LogManager.logError("unable to create " + dir.getName()
						+ " directory");
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
}
