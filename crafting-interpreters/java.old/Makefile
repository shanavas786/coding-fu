##
# Project Title
#
# @file
# @version 0.1

ast:
	javac -cp . -d bin/ tool/*.java
	java -cp bin/ tool.GenerateAst lox

compile: ast
	javac -cp . -d bin/ lox/*.java

run: compile
	java -cp bin/ lox.Lox

# end
