package view;

import controller.Controller;
import model.ADTs.*;
import model.PrgState;
import model.expressions.*;
import model.statements.*;
import model.types.IntType;
import model.types.RefType;
import model.types.StringType;
import model.values.BoolValue;
import model.values.IntValue;
import model.values.StringValue;
import model.values.Value;
import repository.IRepository;
import repository.Repository;

import java.util.logging.Level;
import java.util.logging.Logger;

public class Interpreter {
    private static final Logger LOGGER = Logger.getLogger(Interpreter.class.getName());

    public static void main(String[] args) {
        Logger.getLogger("").setLevel(Level.INFO);
        LOGGER.info("Starting Toy Language Interpreter...");

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


        Controller ctr1 = buildController(ex1, "log1.txt");
        Controller ctr2 = buildController(ex2, "log2.txt");
        Controller ctr3 = buildController(ex3, "log3.txt");
        Controller ctr4 = buildController(ex4, "log4.txt");
        Controller ctr5 = buildController(ex5, "log5.txt");
        Controller ctr6 = buildController(ex6, "log6.txt");
        Controller ctr7 = buildController(ex7, "log7.txt");

        TextMenu menu = new TextMenu();
        menu.addCommand(new ExitCommand("0", "Exit interpreter"));
        menu.addCommand(new RunExample("1", "File Operations Example", ctr1));
        menu.addCommand(new RunExample("2", "Arithmetic + Relational + If Example", ctr2));
        menu.addCommand(new RunExample("3", "Nested If + Compound Example", ctr3));
        menu.addCommand(new RunExample("4", "Heap: new + rH + wH", ctr4));
        menu.addCommand(new RunExample("5", "While Loop", ctr5));
        menu.addCommand(new RunExample("6", "Garbage Collector no delete", ctr6));
        menu.addCommand(new RunExample("7", "Garbage Collection with delete", ctr7));

        menu.show();
    }

    private static Controller buildController(IStmt stmt, String logFile) {
        IExeStack<IStmt> exeStack = new ExeStack<>();
        ISymbolTable<String, Value> symTable = new SymbolTable<>();
        IOut<Value> out = new Out<>();
        IHeap<Integer, Value> heap = new Heap<>();
        IFileTable fileTable = new FileTable();

        PrgState prg = new PrgState(exeStack, symTable, out, fileTable, stmt, heap);
        IRepository repo = new Repository(prg, logFile);
        return new Controller(repo);
    }
}