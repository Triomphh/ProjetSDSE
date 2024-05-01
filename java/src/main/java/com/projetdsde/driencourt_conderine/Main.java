package com.projetdsde.driencourt_conderine;

import com.opencsv.CSVReader;
import com.opencsv.CSVReaderBuilder;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.rmi.RemoteException;
import java.util.Arrays;
import java.util.List;
import java.util.Objects;

public class Main {
    public static void main(String[] args) throws FileNotFoundException, RemoteException {
        GestionCompte compte = new GestionCompte();
        compte.creerCompte("flo","tamere");
       // https://www.youtube.com/watch?v=-Aud0cDh-J8
    }

}
