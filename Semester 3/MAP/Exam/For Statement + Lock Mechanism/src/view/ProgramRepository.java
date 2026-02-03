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

import java.util.ArrayList;
import java.util.List;

public class ProgramRepository {

    private final List<String> programNames = new ArrayList<>();
    private final List<Controller> controllers = new ArrayList<>();

    public ProgramRepository() {
        initPrograms();
    }

    private void initPrograms() {
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

        IStmt forExample =
                new CompStmt(
                        new VarDeclStmt("a", new RefType(new IntType())),
                        new CompStmt(
                                new VarDeclStmt("v", new IntType()),
                                new CompStmt(
                                        new NewStmt("a", new ValueExp(new IntValue(20))),
                                        new CompStmt(
                                                new ForStmt(
                                                        "v",
                                                        new ValueExp(new IntValue(0)),
                                                        new ValueExp(new IntValue(3)),
                                                        new ArithExp(
                                                                new VarExp("v"),
                                                                new ValueExp(new IntValue(1)),
                                                                "+"
                                                        ),
                                                        new ForkStmt(
                                                                new CompStmt(
                                                                        new PrintStmt(new VarExp("v")),
                                                                        new AssignStmt(
                                                                                "v",
                                                                                new ArithExp(
                                                                                        new VarExp("v"),
                                                                                        new ReadHeapExp(new VarExp("a")),
                                                                                        "*"
                                                                                )
                                                                        )
                                                                )
                                                        )
                                                ),
                                                new PrintStmt(
                                                        new ReadHeapExp(new VarExp("a"))
                                                )
                                        )
                                )
                        )
                );


        IStmt lockExample =
                new CompStmt(
                        new VarDeclStmt("v1", new RefType(new IntType())),
                        new CompStmt(
                                new VarDeclStmt("v2", new RefType(new IntType())),
                                new CompStmt(
                                        new VarDeclStmt("x", new IntType()),
                                        new CompStmt(
                                                new VarDeclStmt("q", new IntType()),
                                                new CompStmt(
                                                        new NewStmt("v1", new ValueExp(new IntValue(20))),
                                                        new CompStmt(
                                                                new NewStmt("v2", new ValueExp(new IntValue(30))),
                                                                new CompStmt(
                                                                        new NewLockStmt("x"),

                                                                        new CompStmt(
                                                                                new ForkStmt(
                                                                                        new CompStmt(
                                                                                                new ForkStmt(
                                                                                                        new CompStmt(
                                                                                                                new LockStmt("x"),
                                                                                                                new CompStmt(
                                                                                                                        new WriteHeapStmt(
                                                                                                                                "v1",
                                                                                                                                new ArithExp(
                                                                                                                                        new ReadHeapExp(new VarExp("v1")),
                                                                                                                                        new ValueExp(new IntValue(1)),
                                                                                                                                        "-"
                                                                                                                                )
                                                                                                                        ),
                                                                                                                        new UnlockStmt("x")
                                                                                                                )
                                                                                                        )
                                                                                                ),
                                                                                                new CompStmt(
                                                                                                        new LockStmt("x"),
                                                                                                        new CompStmt(
                                                                                                                new WriteHeapStmt(
                                                                                                                        "v1",
                                                                                                                        new ArithExp(
                                                                                                                                new ReadHeapExp(new VarExp("v1")),
                                                                                                                                new ValueExp(new IntValue(10)),
                                                                                                                                "*"
                                                                                                                        )
                                                                                                                ),
                                                                                                                new UnlockStmt("x")
                                                                                                        )
                                                                                                )
                                                                                        )
                                                                                ),

                                                                                new CompStmt(
                                                                                        new NewLockStmt("q"),
                                                                                        new CompStmt(
                                                                                                new ForkStmt(
                                                                                                        new CompStmt(
                                                                                                                new ForkStmt(
                                                                                                                        new CompStmt(
                                                                                                                                new LockStmt("q"),
                                                                                                                                new CompStmt(
                                                                                                                                        new WriteHeapStmt(
                                                                                                                                                "v2",
                                                                                                                                                new ArithExp(
                                                                                                                                                        new ReadHeapExp(new VarExp("v2")),
                                                                                                                                                        new ValueExp(new IntValue(5)),
                                                                                                                                                        "+"
                                                                                                                                                )
                                                                                                                                        ),
                                                                                                                                        new UnlockStmt("q")
                                                                                                                                )
                                                                                                                        )
                                                                                                                ),
                                                                                                                new CompStmt(
                                                                                                                        new LockStmt("q"),
                                                                                                                        new CompStmt(
                                                                                                                                new WriteHeapStmt(
                                                                                                                                        "v2",
                                                                                                                                        new ArithExp(
                                                                                                                                                new ReadHeapExp(new VarExp("v2")),
                                                                                                                                                new ValueExp(new IntValue(10)),
                                                                                                                                                "*"
                                                                                                                                        )
                                                                                                                                ),
                                                                                                                                new UnlockStmt("q")
                                                                                                                        )
                                                                                                                )
                                                                                                        )
                                                                                                ),

                                                                                                new CompStmt(
                                                                                                        new NopStmt(),
                                                                                                        new CompStmt(
                                                                                                                new NopStmt(),
                                                                                                                new CompStmt(
                                                                                                                        new NopStmt(),
                                                                                                                        new CompStmt(
                                                                                                                                new NopStmt(),

                                                                                                                                new CompStmt(
                                                                                                                                        new CompStmt(
                                                                                                                                                new LockStmt("x"),
                                                                                                                                                new CompStmt(
                                                                                                                                                        new PrintStmt(
                                                                                                                                                                new ReadHeapExp(new VarExp("v1"))
                                                                                                                                                        ),
                                                                                                                                                        new UnlockStmt("x")
                                                                                                                                                )
                                                                                                                                        ),
                                                                                                                                        new CompStmt(
                                                                                                                                                new LockStmt("q"),
                                                                                                                                                new CompStmt(
                                                                                                                                                        new PrintStmt(
                                                                                                                                                                new ReadHeapExp(new VarExp("v2"))
                                                                                                                                                        ),
                                                                                                                                                        new UnlockStmt("q")
                                                                                                                                                )
                                                                                                                                        )
                                                                                                                                )
                                                                                                                        )
                                                                                                                )
                                                                                                        )
                                                                                                )
                                                                                        )
                                                                                )
                                                                        )
                                                                )
                                                        )
                                                )
                                        )
                                )
                        )
                );





        IStmt ex12 = new CompStmt(
                new VarDeclStmt("v", new IntType()),
                new AssignStmt("v", new ValueExp(new BoolValue(true)))
        );

        addController(ex1, "Example 1: File Operations", "log1.txt");
        addController(ex2, "Example 2: Arithmetic + If", "log2.txt");
        addController(ex3, "Example 3: Nested If + Compound", "log3.txt");
        addController(ex4, "Example 4: Heap: new + rH + wH", "log4.txt");
        addController(ex5, "Example 5: While Loop", "log5.txt");
        addController(ex6, "Example 6: Garbage Collector no delete", "log6.txt");
        addController(ex7, "Example 7: Garbage Collection with delete", "log7.txt");
        addController(ex8, "Example 8: Fork Ex lab 8", "log8.txt");
        addController(ex9, "Example 9: Simple Fork Example", "log9.txt");
        addController(ex10, "Example 10: Nested Fork Example", "log10.txt");
        addController(forExample, "Example for stmt", "logFor.txt");
        addController(lockExample, "Example lock", "logLock.txt");
        addController(ex12, "Example 11: Type Error Example", "logInvalid.txt");


    }

    private void addController(IStmt stmt, String name, String logFile) {
        try {
            ISymbolTable<String, Type> typeEnv = new SymbolTable<>();
            stmt.typecheck(typeEnv);

            IExeStack<IStmt> exeStack = new ExeStack<>();
            ISymbolTable<String, Value> symTable = new SymbolTable<>();
            IOut<Value> out = new Out<>();
            IHeap<Integer, Value> heap = new Heap<>();
            IFileTable fileTable = new FileTable();
            ILockTable lockTable = new LockTable();


            PrgState prg = new PrgState(exeStack, symTable, out, fileTable, stmt, heap, lockTable);
            IRepository repo = new Repository(prg, logFile);
            Controller ctr = new Controller(repo);

            programNames.add(name);
            controllers.add(ctr);

        } catch (TypeMismatchException | UndefinedVariableException | CollectionException e) {
            System.err.println("Failed to add program " + name + ": " + e.getMessage());
        }
    }

    public List<String> getProgramNames() {
        return programNames;
    }

    public Controller getController(int index) {
        return controllers.get(index);
    }

    public int size() {
        return controllers.size();
    }
}
