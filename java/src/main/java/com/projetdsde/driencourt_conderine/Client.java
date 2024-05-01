package com.projetdsde.driencourt_conderine;

import java.rmi.Naming;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;

public class Client {
    public static void main(String[] args) throws Exception {
        Registry registry = LocateRegistry.getRegistry(1099);
        ICompte stub = (ICompte) registry.lookup("Test");
        stub.creerCompte("poupou","salope");
    }
}
