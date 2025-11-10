package repository;

import exceptions.CollectionException;
import model.PrgState;

public interface IRepository {
    PrgState getCrtPrg();

    void logPrgState(PrgState state) throws CollectionException;

    void logPrgStateExec() throws CollectionException;
}
