
import java.rmi.Remote;
import java.rmi.RemoteException;
import java.util.ArrayList;

public interface Ucionica extends Remote {

    public String addStudent(String ime) throws RemoteException;

    public String removeStudent(String ime) throws RemoteException;

    public ArrayList<String> returnStudenti() throws RemoteException;

    public void sub(CallBackU cb) throws RemoteException;

    public void unsub(CallBackU cb) throws RemoteException;

}
