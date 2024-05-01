import java.rmi.Naming;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;

public class Serveur {
    public static void main(String[] args) throws Exception {
        ICompte ah = new GestionCompte();
        ICompte test = (ICompte) UnicastRemoteObject.exportObject(ah, 0);
        Registry registry = LocateRegistry.getRegistry();
        registry.rebind("Bref", test);
        System.out.println("serveur prêt");
    }
}
