# SIMPA legacy software testing project [![Build Status](https://travis-ci.org/Vince300/SIMPA.svg?branch=master)](https://travis-ci.org/Vince300/SIMPA)

## Building the project

    ./gradlew assemble

## Development environment

Tested using JDK 8 with IntelliJ Idea.

## Changes from the original source

In order to compile the project outside of the (non-provided) Eclipse project, only the "hit" sources have been kept.
This constitutes the actual "SIMPA" project whose algorithms shall be tested.

Source files have been moved around in order to conform to a standard Maven/Gradle project architecture, which can be
built using the very simple `./gradlew assemble` command.

Most dependencies have been configured to be downloaded from Maven central repository, others are pulled from the *lib/*
directory as JARs. The only one left is sipunit, whose Maven repository is broken.

All of these changes have been committed inside Git, which allows tracking what has been done exactly.
 
## Assignment details

See [ASSIGNMENT.md](docs/ASSIGNMENT.md)

## SIMPA tool usage

See [SRC_USAGE.md](docs/SRC_USAGE.md)

_Note: usage instructions will be updated in order to provide a quick-start guide._
