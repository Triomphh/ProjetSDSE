import java.io.*;
import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;
import java.util.Objects;

public class GestionCompte implements ICompte {

    public GestionCompte() throws RemoteException {
        UnicastRemoteObject.exportObject(this);
    }
    public boolean creerCompte(String pseudo, String mdp) throws RemoteException {
        try {
            String line = "";
            boolean pseudo_existe = false;
            BufferedReader br = new BufferedReader(new FileReader("../comptes.csv"));
            while((line = br.readLine()) != null) {
                String[] values = line.split(",");
                if(Objects.equals(values[0], pseudo)) {
                    pseudo_existe = true;
                }
            }
            if(!pseudo_existe) {
                try (FileWriter writer = new FileWriter("../comptes.csv", true)) {
                    writer.write(pseudo + "," + mdp+"\n");
                    br.close();
                    System.out.println("Compte créé !");
                    return true;
                }
            }else{
                System.out.println("Un compte avec ce pseudo existe déjà !");
                return false;
            }

        } catch (Exception e) {
            e.printStackTrace();
        }
        return(true);
    }

    public boolean supprimerCompte(String pseudo, String mdp) throws RemoteException {
        // try {
        //     String line = "";
        //     boolean pseudo_existe = false;
        //     BufferedReader br = new BufferedReader(new FileReader("../comptes.csv"));
        //     while((line = br.readLine()) != null and !pseudo_existe) {
        //         String[] values = line.split(",");
        //         if(Objects.equals(values[0], pseudo)) {
        //             System.out.println(values[1]);
        //             pseudo_existe = true;
        //         }
        //     }
        //     if(!pseudo_existe) {
        //         try (FileWriter writer = new FileWriter("../comptes.csv", true)) {
        //             writer.write(pseudo + "," + mdp+"\n");
        //             br.close();
        //             System.out.println("Compte créé !");
        //             return true;
        //         }
        //     }else{
        //         System.out.println("Un compte avec ce pseudo existe déjà !");
        //         return false;
        //     }

        // } catch (Exception e) {
        //     e.printStackTrace();
        // }
        return false;
    }

    public boolean connexion(String pseudo, String mdp) throws RemoteException {
        try {
            String line = "";
            BufferedReader br = new BufferedReader(new FileReader("../comptes.csv"));
            while((line = br.readLine()) != null) {
                String[] values = line.split(",");
                if(Objects.equals(values[0], pseudo)) {
                    return(true);
                }
            }
            return false;

        } catch (Exception e) {
            e.printStackTrace();
        }
        return(false);
    }
}
