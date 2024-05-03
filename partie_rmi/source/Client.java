import java.rmi.Naming;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;
import java.rmi.NotBoundException;
import java.net.*;
import java.io.IOException;

public class Client {
    //javac -d ../executable/ ../source/*.java; rmic GestionCompte; java Serveur 

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
        while(true){
            byte[] data = new byte[50];
            // création d'un paquet en utilisant le tableau d'octets
            packet = new DatagramPacket(data, data.length);
            // attente de la réception d'un paquet. Le paquet reçu est placé dans packet et ses données dans data.
            socket.receive(packet);
            // récupération et affichage des données (une chaîne de caractères)
            String chaine = new String(packet.getData(), 0, packet.getLength());
            String login[] = chaine.split(" ");
            String s = "2";
            boolean rep;
            if(login.length > 2){
                System.out.println(login[0] + login[1] + login[2]);
                switch (login[0]){
                    case "/cr": {
                        rep = compte.creerCompte(login[1],login[2]);
                        s = (rep ? new String("1") : new String("0"));  
                        break;
                    }
                    case "/co": {
                        rep = compte.connexion(login[1],login[2]);
                        s = (rep ? new String("1") : new String("0"));  
                        break;
                    }
                    case "/del": {
                        rep = compte.creerCompte(login[1],login[2]);
                        s = (rep ? new String("1") : new String("0"));  
                        break;
                    }
                    case "/l": {
                        rep = compte.creerCompte(login[1],login[2]);
                        s = (rep ? new String("1") : new String("0"));  
                        break;
                    }
                    default:{
                        System.out.println("Prout");
                        break;}
            }
            DatagramPacket sendPacket = new DatagramPacket(s.getBytes(), s.getBytes().length, packet.getAddress(), packet.getPort());
            socket.send(sendPacket);

            }else{
                DatagramPacket sendPacket = new DatagramPacket(s.getBytes(), s.getBytes().length, packet.getAddress(), packet.getPort());
                socket.send(sendPacket);
            }
            
        }
    }
}
