package simpa.hit.tools.loggers;

import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.Map;

import simpa.hit.learner.efsm.table.LiControlTable;
import simpa.hit.learner.efsm.table.LiDataTable;
import simpa.hit.learner.efsm.tree.ZXObservationNode;
import simpa.hit.learner.mealy.table.LmControlTable;
import simpa.hit.learner.mealy.tree.ZObservationNode;
import simpa.hit.main.simpa.Options;
import simpa.hit.automata.efsm.ParameterizedInput;
import simpa.hit.automata.efsm.ParameterizedOutput;
import simpa.hit.detection.Reflection;
import simpa.hit.drivers.efsm.real.GenericDriver;

public class LogManager {
	private static DateFormat tfm = new SimpleDateFormat("[HH:mm:ss:SSS] ");

	public static final int STEPOTHER = -1;
	public static final int STEPNDV = 0;
	public static final int STEPNBP = 1;
	public static final int STEPNCR = 2;
	public static final int STEPNDF = 3;

	static ArrayList<ILogger> loggers = new ArrayList<ILogger>();
	static XSSLogger xssLogger;
	
	private static String prefix = "";

	public static void addLogger(ILogger logger) {
		loggers.add(logger);
	}
	
	public static void delLogger(ILogger logger){
		loggers.remove(logger);
	}
	
	public static void clearsLoggers(){
		loggers.clear();
	}

	public static void end() {
		logConsole("End");
		for (ILogger l : loggers)
			l.logEnd();
		if(Options.XSS_DETECTION){
			xssLogger.logEnd();
		}
		// System.exit(0);
	}
	
	public static void logFatalError(String s) {
		for (ILogger l : loggers)
			l.logFatalError(prefix+s);
	}

	public static void logControlTable(LmControlTable ct) {
		for (ILogger l : loggers)
			l.logControlTable(ct);
	}

	public static void logControlTable(LiControlTable ct) {
		for (ILogger l : loggers)
			l.logControlTable(ct);
	}

	public static void logDataTable(LiDataTable dt) {
		for (ILogger l : loggers)
			l.logDataTable(dt);
	}

	public static void logConsole(String s) {
		if (!Options.TEST) {
			System.out.flush();
			//System.out.println(tfm.format(new Date()) + s);
			System.out.println(prefix + s);
		}
	}

	public static void logError(String s) {
		System.err.flush();
		System.err.println(tfm.format(new Date()) + prefix + s);
	}

	public static void logException(String s, Exception e) {
		System.err.flush();
		System.err.println(tfm.format(new Date()) + prefix + s);
		e.printStackTrace(System.err);
	}

	public static void logInfo(String s) {
		for (ILogger l : loggers)
			l.logInfo(prefix + s);
	}

	public static void logRequest(ParameterizedInput pi, ParameterizedOutput po) {
		for (ILogger l : loggers)
			l.logRequest(pi, po);
	}

	public static void logRequest(String input, String output) {
		for (ILogger l : loggers)
			l.logRequest(input, output);
	}

	public static void logRequest(String input, String output, int n) {
		for (ILogger l : loggers)
			l.logRequest(input, output, n);
	}

	public static void start() {
		for (ILogger l : loggers)
			l.logStart();
		if(Options.XSS_DETECTION){
			xssLogger = new XSSLogger();
			xssLogger.logStart();
		}
	}

	public static void logReset() {
		for (ILogger l : loggers)
			l.logReset();
	}

	public static void logStat(String s) {
		for (ILogger l : loggers)
			l.logStat(prefix + s);
	}

	public static void logLine() {
		for (ILogger l : loggers)
			l.logLine();
	}

	public static void logStep(int step, Object o) {
		for (ILogger l : loggers)
			l.logStep(step, o);
	}

	public static void logTransition(String trans) {
		for (ILogger l : loggers)
			l.logTransition(prefix + trans);
	}

	public static void logData(String data) {
		for (ILogger l : loggers)
			l.logData(prefix + data);
	}

	public static void logImage(String path) {
		for (ILogger l : loggers)
			l.logImage(path);
	}

	public static void logConcrete(String data) {
		for (ILogger l : loggers)
			l.logConcrete(prefix + data);
	}

	public static void logSymbolsParameters(Map<String, Integer> params) {
		for (ILogger l : loggers)
			l.logParameters(params);
	}

	public static void logObservationTree(ZObservationNode root) {
		for (ILogger l : loggers)
			if (Options.GRAPHVIZ)
				l.logObservationTree(root);
	}

	public static void logXObservationTree(ZXObservationNode root) {
		for (ILogger l : loggers)
			if (Options.GRAPHVIZ)
				l.logXObservationTree(root);
	}
	
	/**
	 * Logs a reflection found in the web application.
	 * Print the input sequence triggering the reflection
	 * @param r The data representing the reflection
	 * @param driver The GenericDriver used to translate abstract symbols into concrete requests
	 */
	public static void logFoundReflection(Reflection r, GenericDriver driver){
		xssLogger.logFoundReflection(r, driver);
	}

	/**
	 * Logs a XSS found in the web application. Print the input sequence
	 * used to introduce the payload and observe the result
	 *
	 * @param r The data representing the sequence used
	 * @param driver The GenericDriver used to translate abstract symbols into
	 * concrete requests
	 */
	public static void logFoundXSS(Reflection r, GenericDriver driver) {
		xssLogger.logFoundXSS(r, driver);
	}

	public static void setPrefix(String s){
		prefix = s;
	}
	
	public static String getPrefix(){
		return prefix;
	}
}
