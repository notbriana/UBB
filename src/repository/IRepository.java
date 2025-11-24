package repository;

import exceptions.CollectionException;
import model.PrgState;

public interface IRepository {
    PrgState getCrtPrg();

    void logPrgStateExec() throws CollectionException;
}
