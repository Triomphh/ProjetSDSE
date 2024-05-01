import java.rmi.Naming;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;
import java.rmi.NotBoundException;
import java.net.*;
import java.io.IOException;

public class Client {
    //localhost:4002
    public static void main(String[] args) throws NotBoundException, RemoteException, MalformedURLException, IOException{
        ////////////// TEST RMI ////////////////////////////////////////////////////////////////////////////////////////
        ICompte compte = (ICompte) Naming.lookup("rmi://localhost:4000/Bref");
        //boolean test = compte.creerCompte(args[0], args[1]);
        // if(test) System.out.println("compte créé avec succès");
        
        // else System.out.println("impossible de créer le compte : le pseudo existe déjà.");
        //////////// PARTIE UDP //////////////////////////////////////////////////////////////////////////////////////
        DatagramPacket packet;
        // création d'une socket liée au port 7777
        DatagramSocket socket = new DatagramSocket(7777);
        // tableau de 15 octets qui contiendra les données reçues
        byte[] data = new byte[50];
        // création d'un paquet en utilisant le tableau d'octets
        packet = new DatagramPacket(data, data.length);
        // attente de la réception d'un paquet. Le paquet reçu est placé dans packet et ses données dans data.
        socket.receive(packet);
        // récupération et affichage des données (une chaîne de caractères)
        socket.send(packet);
        String chaine = new String(packet.getData(), 0, packet.getLength());
        System.out.println(" recu : "+chaine);
    }
}
