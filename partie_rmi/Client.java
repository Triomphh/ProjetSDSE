import java.rmi.Naming;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;

public class Client {
    //localhost:4002
    public static void main(String[] args) throws Exception{
        Registry registry = LocateRegistry.getRegistry();
        ICompte compte = (ICompte) registry.lookup("Bref");
        compte.creerCompte(args[0], args[1]);
    }
}
