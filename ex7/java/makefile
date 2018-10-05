all: compile jar

bin:
	mkdir bin

compile: bin
	javac -d bin src/Point.java src/Driver.java src/MainController.java src/GUI.java

jar:
	jar cfm ../gui.jar Manifest.mf -C bin .

