package com.projetdsde.driencourt_conderine;
import java.io.*;
import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;
import java.util.Objects;

public class GestionCompte extends UnicastRemoteObject implements ICompte {

    public GestionCompte() throws RemoteException {
        UnicastRemoteObject.exportObject(this);
    }
    public boolean creerCompte(String pseudo, String mdp) throws RemoteException {
        try {
            String line = "";
            boolean pseudo_existe = false;
            BufferedReader br = new BufferedReader(new FileReader("java/src/main/java/com/projetdsde/driencourt_conderine/comptes.csv"));
            while((line = br.readLine()) != null) {
                String[] values = line.split(",");
                if(Objects.equals(values[0], pseudo)) {
                    System.out.println(values[1]);
                    pseudo_existe = true;
                }
            }
            if(!pseudo_existe) {
                try (BufferedWriter writer = new BufferedWriter(new FileWriter("java/src/main/java/com/projetdsde/driencourt_conderine/comptes.csv"))) {
                    writer.write(pseudo + "," + mdp);
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
        return(true);
    }

    public boolean connexion(String pseudo, String mdp) throws RemoteException {
        return(true);
    }
}
