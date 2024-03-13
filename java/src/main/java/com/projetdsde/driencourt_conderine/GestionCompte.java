package java.src.main.java.com.projetdsde.driencourt_conderine;
import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;

public class GestionCompte extends UnicastRemoteObject implements ICompte {

    private GestionCompte() throws RemoteException {
        super();
    }
    public boolean creerCompte(String pseudo, String mdp) throws RemoteException {
        
        return(true);
    }

    public boolean supprimerCompte(String pseudo, String mdp) throws RemoteException {
        return(true);
    }

    public boolean connexion(String pseudo, String mdp) throws RemoteException {
        return(true);
    }
}