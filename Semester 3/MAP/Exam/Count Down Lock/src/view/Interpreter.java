package view;

import controller.Controller;
import exceptions.CollectionException;
import exceptions.TypeMismatchException;
import exceptions.UndefinedVariableException;
import model.ADTs.*;
import model.PrgState;
import model.expressions.*;
import model.statements.*;
import model.types.IntType;
import model.types.RefType;
import model.types.StringType;
import model.types.Type;
import model.values.BoolValue;
import model.values.IntValue;
import model.values.StringValue;
import model.values.Value;
import repository.IRepository;
import repository.Repository;


public class Interpreter {

    public static void main(String[] args) {
        System.out.println("TOY LANGUAGE INTERPRETER");

        IStmt ex1 = new CompStmt(
                new VarDeclStmt("varf", new StringType()),
                new CompStmt(
                        new AssignStmt("varf", new ValueExp(new StringValue("test.in"))),
                        new CompStmt(
                                new OpenRFile(new VarExp("varf")),
                                new CompStmt(
                                        new VarDeclStmt("varc", new IntType()),
                                        new CompStmt(
                                                new ReadFile(new VarExp("varf"), "varc"),
                                                new CompStmt(
                                                        new PrintStmt(new VarExp("varc")),
                                                        new CompStmt(
                                                                new ReadFile(new VarExp("varf"), "varc"),
                                                                new CompStmt(
                                                                        new PrintStmt(new VarExp("varc")),
                                                                        new CloseRFile(new VarExp("varf"))
                                                                )
                                                        )
                                                )
                                        )
                                )
                        )
                )
        );

        IStmt ex2 = new CompStmt(
                new VarDeclStmt("a", new IntType()),
                new CompStmt(
                        new VarDeclStmt("b", new IntType()),
                        new CompStmt(
                                new AssignStmt("a",
                                        new ArithExp(
                                                new ValueExp(new IntValue(2)),
                                                new ArithExp(
                                                        new ValueExp(new IntValue(3)),
                                                        new ValueExp(new IntValue(5)),
                                                        "*"
                                                ),
                                                "+"
                                        )
                                ),
                                new CompStmt(
                                        new AssignStmt("b",
                                                new ArithExp(
                                                        new VarExp("a"),
                                                        new ValueExp(new IntValue(1)),
                                                        "+"
                                                )
                                        ),
                                        new IfStmt(
                                                new RelExp(
                                                        new VarExp("b"),
                                                        new VarExp("a"),
                                                        "<"
                                                ),
                                                new PrintStmt(new ValueExp(new BoolValue(true))),
                                                new PrintStmt(new ValueExp(new BoolValue(false)))
                                        )
                                )
                        )
                )
        );

        IStmt ex3 = new CompStmt(
                new VarDeclStmt("x", new IntType()),
                new CompStmt(
                        new VarDeclStmt("y", new IntType()),
                        new CompStmt(
                                new AssignStmt("x", new ValueExp(new IntValue(10))),
                                new CompStmt(
                                        new AssignStmt("y",
                                                new ArithExp(
                                                        new VarExp("x"),
                                                        new ValueExp(new IntValue(4)),
                                                        "-"
                                                )),
                                        new IfStmt(
                                                new RelExp(
                                                        new VarExp("x"),
                                                        new VarExp("y"),
                                                        ">="
                                                ),
                                                new CompStmt(
                                                        new PrintStmt(new VarExp("x")),
                                                        new PrintStmt(new VarExp("y"))
                                                ),
                                                new CompStmt(
                                                        new PrintStmt(new ValueExp(new IntValue(0))),
                                                        new PrintStmt(new ValueExp(new IntValue(-1)))
                                                )
                                        )
                                )
                        )
                )
        );

        IStmt ex4 = new CompStmt(
                new VarDeclStmt("v", new RefType(new IntType())),
                new CompStmt(
                        new NewStmt("v", new ValueExp(new IntValue(20))),
                        new CompStmt(
                                new PrintStmt(new ReadHeapExp(new VarExp("v"))),
                                new CompStmt(
                                        new WriteHeapStmt("v", new ValueExp(new IntValue(30))),
                                        new PrintStmt(
                                                new ArithExp(
                                                        new ReadHeapExp(new VarExp("v")),
                                                        new ValueExp(new IntValue(5)),
                                                        "+"
                                                )
                                        )
                                )
                        )
                )
        );

        IStmt ex5 = new CompStmt(
                new VarDeclStmt("v", new IntType()),
                new CompStmt(
                        new AssignStmt("v", new ValueExp(new IntValue(4))),
                        new CompStmt(
                                new WhileStmt(
                                        new RelExp(
                                                new VarExp("v"),
                                                new ValueExp(new IntValue(0)),
                                                ">"
                                        ),
                                        new CompStmt(
                                                new PrintStmt(new VarExp("v")),
                                                new AssignStmt("v",
                                                        new ArithExp(
                                                                new VarExp("v"),
                                                                new ValueExp(new IntValue(1)),
                                                                "-"
                                                        )
                                                )
                                        )
                                ),
                                new PrintStmt(new VarExp("v"))
                        )
                )
        );

        IStmt ex6 = new CompStmt(
                new VarDeclStmt("v", new RefType(new IntType())),
                new CompStmt(
                        new NewStmt("v", new ValueExp(new IntValue(20))),
                        new CompStmt(
                                new VarDeclStmt("a", new RefType(new RefType(new IntType()))),
                                new CompStmt(
                                        new NewStmt("a", new VarExp("v")),
                                        new CompStmt(
                                                new NewStmt("v", new ValueExp(new IntValue(30))),
                                                new PrintStmt(
                                                        new ReadHeapExp(new ReadHeapExp(new VarExp("a")))
                                                )
                                        )
                                )
                        )
                )
        );

        IStmt ex7 = new CompStmt(
                new VarDeclStmt("v", new RefType(new IntType())),
                new CompStmt(
                        new NewStmt("v", new ValueExp(new IntValue(20))),
                        new CompStmt(
                                new VarDeclStmt("a", new RefType(new IntType())),
                                new CompStmt(
                                        new NewStmt("a", new ValueExp(new IntValue(30))),
                                        new CompStmt(
                                                new NewStmt("v", new ValueExp(new IntValue(40))),
                                                new CompStmt(
                                                        new PrintStmt(new ReadHeapExp(new VarExp("v"))),
                                                        new PrintStmt(new ReadHeapExp(new VarExp("a")))
                                                )
                                        )
                                )
                        )
                )
        );

        IStmt ex8 = new CompStmt(
                new VarDeclStmt("v", new IntType()),
                new CompStmt(
                        new VarDeclStmt("a", new RefType(new IntType())),
                        new CompStmt(
                                new AssignStmt("v", new ValueExp(new IntValue(10))),
                                new CompStmt(
                                        new NewStmt("a", new ValueExp(new IntValue(22))),
                                        new CompStmt(
                                                new ForkStmt(
                                                        new CompStmt(
                                                                new WriteHeapStmt("a", new ValueExp(new IntValue(30))),
                                                                new CompStmt(
                                                                        new AssignStmt("v", new ValueExp(new IntValue(32))),
                                                                        new CompStmt(
                                                                                new PrintStmt(new VarExp("v")),
                                                                                new PrintStmt(new ReadHeapExp(new VarExp("a")))
                                                                        )
                                                                )
                                                        )
                                                ),
                                                new CompStmt(
                                                        new PrintStmt(new VarExp("v")),
                                                        new PrintStmt(new ReadHeapExp(new VarExp("a")))
                                                )
                                        )
                                )
                        )
                )
        );

        IStmt ex9 = new CompStmt(
                new VarDeclStmt("a", new IntType()),
                new CompStmt(
                        new AssignStmt("a", new ValueExp(new IntValue(10))),
                        new CompStmt(
                                new ForkStmt(
                                        new CompStmt(
                                                new AssignStmt("a", new ValueExp(new IntValue(20))),
                                                new PrintStmt(new VarExp("a"))
                                        )
                                ),
                                new PrintStmt(new VarExp("a"))
                        )
                )
        );

        IStmt ex10 = new CompStmt(
                new VarDeclStmt("a", new IntType()),
                new CompStmt(
                        new AssignStmt("a", new ValueExp(new IntValue(10))),
                        new CompStmt(
                                new ForkStmt(
                                        new CompStmt(
                                                new VarDeclStmt("b", new IntType()),
                                                new CompStmt(
                                                        new AssignStmt("b", new ValueExp(new IntValue(20))),
                                                        new CompStmt(
                                                                new ForkStmt(
                                                                        new CompStmt(
                                                                                new VarDeclStmt("c", new IntType()),
                                                                                new CompStmt(
                                                                                        new AssignStmt("c", new ValueExp(new IntValue(30))),
                                                                                        new PrintStmt(new VarExp("c"))
                                                                                )
                                                                        )
                                                                ),
                                                                new PrintStmt(new VarExp("b"))
                                                        )
                                                )
                                        )
                                ),
                                new PrintStmt(new VarExp("a"))
                        )
                )
        );

        IStmt exInvalid = new CompStmt(
                new VarDeclStmt("v", new IntType()),
                new AssignStmt("v", new ValueExp(new BoolValue(true)))
        );

        IStmt exValid = new CompStmt(
                new VarDeclStmt("v", new IntType()),
                new AssignStmt("v", new ValueExp(new IntValue(7))));

        Controller ctr1 = typeCheckAndBuild(ex1, "log1.txt", "Example 1");
        Controller ctr2 = typeCheckAndBuild(ex2, "log2.txt", "Example 2");
        Controller ctr3 = typeCheckAndBuild(ex3, "log3.txt", "Example 3");
        Controller ctr4 = typeCheckAndBuild(ex4, "log4.txt", "Example 4");
        Controller ctr5 = typeCheckAndBuild(ex5, "log5.txt", "Example 5");
        Controller ctr6 = typeCheckAndBuild(ex6, "log6.txt", "Example 6");
        Controller ctr7 = typeCheckAndBuild(ex7, "log7.txt", "Example 7");
        Controller ctr8 = typeCheckAndBuild(ex8, "log8.txt", "Example 8");
        Controller ctr9 = typeCheckAndBuild(ex9, "log9.txt", "Example 9");
        Controller ctr10 = typeCheckAndBuild(ex10, "log10.txt", "Example 10");
        Controller ctrInvalid = typeCheckAndBuild(exInvalid, "logInvalid.txt", "Invalid Example");

        System.out.println("\nType checking complete! Building menu...\n");

        TextMenu menu = new TextMenu();
        menu.addCommand(new ExitCommand("0", "Exit interpreter"));

        if (ctr1 != null) menu.addCommand(new RunExample("1", "File Operations Example", ctr1));
        if (ctr2 != null) menu.addCommand(new RunExample("2", "Arithmetic + Relational + If Example", ctr2));
        if (ctr3 != null) menu.addCommand(new RunExample("3", "Nested If + Compound Example", ctr3));
        if (ctr4 != null) menu.addCommand(new RunExample("4", "Heap: new + rH + wH", ctr4));
        if (ctr5 != null) menu.addCommand(new RunExample("5", "While Loop", ctr5));
        if (ctr6 != null) menu.addCommand(new RunExample("6", "Garbage Collector no delete", ctr6));
        if (ctr7 != null) menu.addCommand(new RunExample("7", "Garbage Collection with delete", ctr7));
        if (ctr8 != null) menu.addCommand(new RunExample("8", "Fork Ex lab 8", ctr8));
        if (ctr9 != null) menu.addCommand(new RunExample("9", "Simple Fork Example", ctr9));
        if (ctr10 != null) menu.addCommand(new RunExample("10", "Nested Fork Example", ctr10));
        if (ctrInvalid != null) menu.addCommand(new RunExample("11", "Type Error Example", ctrInvalid));


        menu.show();
    }

    private static Controller typeCheckAndBuild(IStmt stmt, String logFile, String exampleName) {
        try {
            System.out.print("Type checking " + exampleName + "\n");
            ISymbolTable<String, Type> typeEnv = new SymbolTable<>();
            stmt.typecheck(typeEnv);
            System.out.println("PASSED");

            return buildController(stmt, logFile);

        } catch (TypeMismatchException e) {
            System.out.println("FAILED");
            System.err.println("TYPE ERROR: " + e.getMessage());
            return null;

        } catch (UndefinedVariableException e) {
            System.out.println("FAILED");
            System.err.println("UNDEFINED VARIABLE: " + e.getMessage());
            return null;

        } catch (CollectionException e) {
            System.out.println("FAILED");
            System.err.println("ERROR: " + e.getMessage());
            return null;
        }
    }

    private static Controller buildController(IStmt stmt, String logFile) {
        IExeStack<IStmt> exeStack = new ExeStack<>();
        ISymbolTable<String, Value> symTable = new SymbolTable<>();
        IOut<Value> out = new Out<>();
        IHeap<Integer, Value> heap = new Heap<>();
        IFileTable fileTable = new FileTable();
        ILatchTable latchTable = new LatchTable();

        PrgState prg = new PrgState(exeStack, symTable, out, fileTable, stmt, heap, latchTable);
        IRepository repo = new Repository(prg, logFile);
        return new Controller(repo);
    }
}