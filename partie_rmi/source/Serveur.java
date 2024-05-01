import java.rmi.Naming;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;

public class Serveur {
    public static void main(String[] args) throws Exception {
        ICompte ah = new GestionCompte();
        Registry reg = LocateRegistry.createRegistry(4000);
        reg.rebind("Bref", ah);
        System.out.println("serveur prêt");
    }
}