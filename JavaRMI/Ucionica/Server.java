
import java.io.IOException;
import java.net.MalformedURLException;
import java.rmi.Naming;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;

public class Server {

    public Server(String brojUcionice) {
        try {
            LocateRegistry.createRegistry(1099);
            System.out.println("Java RMI registry created.");
        } catch (RemoteException e) {
            System.out.println("Java RMI registry already exists.");
        }

        try {
            UcionicaImpl u = new UcionicaImpl();

            Naming.rebind("rmi://localhost:1099/" + brojUcionice, u);
        } catch (RemoteException e) {
            System.out.println("Failure during RMI object creation: " + e);
        } catch (MalformedURLException e) {
            System.out.println("Failure during Name registration: " + e);
        }

    }

    public static void main(String[] args) {

        String ucionica = args[0];

        new Server(ucionica);
        System.out.println("Server started.");

        try {
            System.in.read();
        } catch (IOException e) {

        }

    }
}
