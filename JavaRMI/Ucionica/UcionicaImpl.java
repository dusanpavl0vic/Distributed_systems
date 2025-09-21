
import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;
import java.util.ArrayList;

public class UcionicaImpl extends UnicastRemoteObject implements Ucionica {

    private ArrayList<String> studenti;
    private ArrayList<CallBackU> calls;

    public UcionicaImpl() throws RemoteException {
        super();
        studenti = new ArrayList<String>();
        calls = new ArrayList<CallBackU>();
    }

    @Override
    public String addStudent(String ime) throws RemoteException {
        studenti.add(ime);
        obavestiUcenike(ime);
        return ime;
    }

    @Override
    public String removeStudent(String ime) throws RemoteException {

        boolean nema = false;
        for (int i = 0; i < studenti.size(); i++) {
            if (studenti.get(i).equals(ime)) {
                studenti.remove(i);
                nema = true;
            }
        }

        if (nema == false) {
            System.out.println("Taj student ne postoji");
            return "";
        }

        return ime;
    }

    @Override
    public ArrayList<String> returnStudenti() throws RemoteException {
        return studenti;
    }

    @Override
    public void sub(CallBackU cb) throws RemoteException {
        calls.add(cb);
    }

    @Override
    public void unsub(CallBackU cb) throws RemoteException {
        calls.remove(cb);
    }

    private void obavestiUcenike(String ime) {
        try {
            for (CallBackU cb : calls) {
                cb.callback(ime);
            }
        } catch (Exception e) {

        }
    }
}
