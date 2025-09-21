
import java.net.MalformedURLException;
import java.rmi.*;
import java.rmi.server.UnicastRemoteObject;
import java.util.ArrayList;
import java.util.Scanner;

public class Client {

    private Ucionica u;
    private CallBackU cb;

    public Client(String ucionica) {

        Scanner scanner = new Scanner(System.in);
        try {

            u = (Ucionica) Naming.lookup("rmi://localhost:1099/" + ucionica);
            cb = new CallBackUImpl();
            u.sub(cb);

            scanner.nextLine();
            dodajUcenika("Dusan");
            dodajUcenika("Dusan1");
            dodajUcenika("Dusan2");
            dodajUcenika("Dusan3");
            scanner.nextLine();
            izbaciUcenika("Dusan3");
            vratiStudente();
            scanner.nextLine();
            izbaciUcenika("Dusan4");
            vratiStudente();

        } catch (MalformedURLException e) {
            System.out.println("Failure during RMI object creation: " + e);
        } catch (RemoteException e) {
            System.out.println("Failure during RMI object creation: " + e);
        } catch (NotBoundException e) {
            System.out.println("Failure during RMI object creation: " + e);
        }
    }

    public void dodajUcenika(String ime) throws RemoteException {

        String dodat = u.addStudent(ime);
        System.err.println("Dodat je student" + dodat);
    }

    public void izbaciUcenika(String ime) throws RemoteException {

        String izbacen = u.removeStudent(ime);
        System.err.println("Izbacen je student" + izbacen);
    }

    public void dosaoS(String ime) throws RemoteException {

        System.out.println("Dosao je:" + ime);

    }

    public void vratiStudente() throws RemoteException {

        ArrayList<String> lista = u.returnStudenti();
        System.out.println("Lista:");
        lista.forEach(i -> {
            System.out.println(i);
        });

    }

    public static void main(String args[]) {

        String ucionica = args[0];
        new Client(ucionica);
    }

    public class CallBackUImpl extends UnicastRemoteObject implements CallBackU {

        public CallBackUImpl() throws RemoteException {
            super();
        }

        @Override
        public void callback(String student) throws RemoteException {
            dosaoS(student);
        }
    }

}
