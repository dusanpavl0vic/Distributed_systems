
import java.rmi.Remote;
import java.rmi.RemoteException;

public interface CallBackU extends Remote {

    void callback(String student) throws RemoteException;
}
