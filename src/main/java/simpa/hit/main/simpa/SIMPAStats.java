package simpa.hit.main.simpa;

import java.io.File;
import java.io.IOException;
import java.text.SimpleDateFormat;
import java.util.Date;

import simpa.hit.tools.Stats;
import simpa.hit.tools.Utils;
import simpa.hit.tools.loggers.LogManager;

public class SIMPAStats {
	public final static String name = "SIMPAStats";

	private static void welcome() {
		System.out.println(name + " - "
				+ new SimpleDateFormat("MM/dd/yyyy").format(new Date()));
		System.out.println();
	}

	public static void main(String[] args) throws IOException {
		//Options.STAT = true;
		welcome();
		String dir = Options.OUTDIR;

		try {
			Stats stat = new Stats("global.csv");
			stat.setHeaders(Utils.createArrayList("State", "Requests",
					"Duration", "Transitions"));
			int[] states = { 50, 100, 200, 300, 500, 750, 1000, 2000, 3000, 5000, 7500, 10000 };
			for (int i : states) {
				Options.MINSTATES = i;
				Options.MAXSTATES = i;

				System.out.println("|+] State = " + i);

				SIMPATestMealy.main(args);

				stat.addRecord(Utils.createArrayList(
						String.valueOf(i),
						String.valueOf(Utils.meanOfCSVField(Options.DIRTEST
								+ File.separator + "simpa.hit.stats.csv", 5)),
						String.valueOf(Utils.meanOfCSVField(Options.DIRTEST
								+ File.separator + "simpa.hit.stats.csv", 6)),
						String.valueOf(Utils.meanOfCSVField(Options.DIRTEST
								+ File.separator + "simpa.hit.stats.csv", 7))));

				Options.OUTDIR = dir;
			}
			stat.close();
		} catch (Exception e) {
			LogManager.logException("Unexpected error at test", e);
		}
	}
}
