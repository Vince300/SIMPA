# SIMPA legacy software testing project [![Build Status](https://travis-ci.org/Vince300/SIMPA.svg?branch=master)](https://travis-ci.org/Vince300/SIMPA) [![codecov](https://codecov.io/gh/Vince300/SIMPA/branch/master/graph/badge.svg)](https://codecov.io/gh/Vince300/SIMPA)

## Getting started

```bash
# Building the project
./gradlew assemble

# Running the tests
./gradlew check --info
```

## Development environment

Tested using JDK 8. Developed and debugged in IntelliJ Idea 2016.

## Changes from the original source

In order to compile the project outside of the (non-provided) Eclipse project, only the "hit" sources have been kept.
This constitutes the actual "SIMPA" project whose algorithms shall be tested.

Source files have been moved around in order to conform to a standard Maven/Gradle project architecture, which can be
built using the very simple `./gradlew assemble` command.

Most dependencies have been configured to be downloaded from Maven central repository, others are pulled from the *lib/*
directory as JARs. The only one left is sipunit, whose Maven repository is broken.

All of these changes have been committed inside Git, which allows tracking what has been done exactly.

## Docs

### [Assignment details](docs/ASSIGNMENT.md)

### [SIMPA tool usage](docs/SIMPA_USAGE.md)

### [Testing report](docs/TESTING_REPORT.md)
