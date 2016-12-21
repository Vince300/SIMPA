# SIMPA-TEST QA (Quality Analysis)

### o Prerequisites

- Some commands and applications must exist on your system:
  - **Perl**,
  - the **gcc** compiler,
  - the **Boost** libraries on Mac OS to run the cpp command,
  - the **tcsh** shell,
  - the **timeout** command.



### o Configuration

Now update the `$HOME/simpa-tests/envtest.csh` startup script to modify:
the environment variable pointing to the root of the SIMPA sources (root containing drivergen, hit, ID3),
the 3 environment variables that define where are the tests and their tools.
	setenv SIMPA       "$HOME/simpa-clean"
	setenv QA_TOOLS    "$HOME/simpa-tests/tools"
	setenv QA_ROOT     "$HOME/simpa-tests/root"
	setenv NEW_QA_ROOT "$HOME/simpa-tests/root"`
Then you must switch to the tcsh shell to define the environnement variables:
	~user> tcsh
	~user> source simpa-tests/envtest.csh

### o Execution

**Scenarios**
	~> cd $NEW_QA_ROOT/runtest
	~> new_run_allapp.pl -v monday  scenarios/simpa/standard.scn

The global reports will be found in the `$NEW_QA_ROOT/runtest/allapp_reports`:
	allapp_report_v3647_monday
	allapp_report_v3647_monday.xml
the number 3647 being the value of the counter incremented at each scenario execution (counter `$NEW_QA_ROOT/runtest/current_run_id`).

**One specific test**
For SIMPA, there is currently only one test : 
	cd $NEW_QA_ROOT/runtest
	cd vasco/drivers/v0
	./run_all.pl -v tuesday
The trace shows the shell command lines that can be used to replay the test.
The local reports will be found in the reports directory:
	report_tuesday
	report_tuesday.xml

**Add new cases to one test**

The `files_in_out_ref.txt` and `files_in_out_ref_light.txt` files contain the configurations on launching and checking the execution of a compiled code (here, SIMPA). The `run_all.pl` script uses the `files_in_out_ref.txt` configuration file whereas adding **-l light** option means level light and uses the `files_in_out_ref_light.txt` configuration file (as opposite to **-l full** if we want to specify explicitely the **files_in_out_ref.txt** file).
One line must contain:

	#target;   input file;  description;  launch params; output file1, reference file1 ; output file2, reference file2 ; ...
	#
	# the output file can be: stdout or stderr
	#
	#for example:
	#coder;        dtx63.tin;    encoder 6.3;  -c -r63 -v dtx63.tin dtx63.xco     ; STDOUT, dtx63.out; dtx63.xco, dtx63.rco;
	#coder;     dtx53mix.tin;    encoder 5.3;  -c -r53 -v dtx53mix.tin dtx53.xco  ; STDOUT, dtx53.out; dtx53.xco, dtx53.rco;
Looking at the comment, for the first coder execution, the test will be reported as a PASS if it runs without timeout nor negative status, and if the stdout is equal to `../ref/dtx63.out` and `outputs/dtx63.xco` is equal to `../ref/dtx63.rco`.
For example, if we want to add the following SIMPA execution to the tests:
	java main/simpa/SIMPA drivers.mealy.RandomMealyDriver --cutCombinatorial --minstates 2 --maxstates 4 --seed 9

We will work with the `files_in_out_ref_light.txt` file that we can use as draft and when all is ok we will report the new line in the `files_in_out_ref.txt` file. The new line we add to `files_in_out_ref_light.txt` is (assuming we want to se a timeout of 60 seconds):
	main/simpa/SIMPA < 60   ; ; Mealy Random --cutCombinatorial --minstates 2 --maxstates 4 --seed 9  ; drivers.mealy.RandomMealyDriver --cutCombinatorial --minstates 2 --maxstates 4 --seed 9  ; STDOUT, out1 ; STDERR out2


The launching line is:
	./run_all.pl -v friday -l light
The -l light that means light level is here to select the files_in_out_ref_light.txt parameter file.



