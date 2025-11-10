package view;

import controller.Controller;
import model.ADTs.*;
import model.PrgState;
import model.expressions.ArithExp;
import model.expressions.RelationalExpression;
import model.expressions.ValueExp;
import model.expressions.VarExp;
import model.statements.*;
import model.types.IntType;
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
                                        new ArithExp('+',
                                                new ValueExp(new IntValue(2)),
                                                new ArithExp('*',
                                                        new ValueExp(new IntValue(3)),
                                                        new ValueExp(new IntValue(5)))
                                        )
                                ),
                                new CompStmt(
                                        new AssignStmt("b",
                                                new ArithExp('+',
                                                        new VarExp("a"),
                                                        new ValueExp(new IntValue(1)))
                                        ),
                                        new IfStmt(
                                                new RelationalExpression(
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
                                                new ArithExp('-',
                                                        new VarExp("x"),
                                                        new ValueExp(new IntValue(4)))),
                                        new IfStmt(
                                                new RelationalExpression(
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

        Controller ctr1 = buildController(ex1, "log1.txt");
        Controller ctr2 = buildController(ex2, "log2.txt");
        Controller ctr3 = buildController(ex3, "log3.txt");

        TextMenu menu = new TextMenu();
        menu.addCommand(new ExitCommand("0", "Exit interpreter"));
        menu.addCommand(new RunExample("1", "File Operations Example", ctr1));
        menu.addCommand(new RunExample("2", "Arithmetic + Relational + If Example", ctr2));
        menu.addCommand(new RunExample("3", "Nested If + Compound Example", ctr3));

        menu.show();
    }

    private static Controller buildController(IStmt stmt, String logFile) {
        IExeStack<IStmt> exeStack = new ExeStack<>();
        ISymbolTable<String, Value> symTable = new SymbolTable<>();
        IOut<Value> out = new Out<>();
        IFileTable fileTable = new FileTable();

        PrgState prg = new PrgState(exeStack, symTable, out, fileTable, stmt);
        IRepository repo = new Repository(prg, logFile);
        return new Controller(repo);
    }
}
