package com.projetdsde.driencourt_conderine;

import java.rmi.Naming;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;

public class Serveur {
    public static void main(String[] args) throws Exception {
        ICompte compte = (ICompte) UnicastRemoteObject.exportObject(new GestionCompte(), 1099);
        Registry reg = LocateRegistry.createRegistry(1099);
        Naming.rebind("Test", compte);
        System.out.println("serveur prêt");
    }
}
