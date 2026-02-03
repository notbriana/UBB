package repository;

import exceptions.CollectionException;
import model.PrgState;

import java.util.List;

public interface IRepository {
    List<PrgState> getPrgList();

    void setPrgList(List<PrgState> prgList);

    void logPrgStateExec(PrgState state) throws CollectionException;
}