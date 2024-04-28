package com.projetdsde.driencourt_conderine;

import com.opencsv.CSVReader;

import java.io.FileNotFoundException;
import java.io.FileReader;

public class Main {
    public static void main(String[] args) throws FileNotFoundException {
        try {

            // Create an object of filereader
            // class with CSV file as a parameter.
            FileReader filereader = new FileReader("/home/flo/IdeaProjects/ProjetSDSE2/java/src/main/java/com/projetdsde/driencourt_conderine/comptes.csv");

            // create csvReader object passing
            // file reader as a parameter
            CSVReader csvReader = new CSVReader(filereader);
            String[] nextRecord;

            // we are going to read data line by line
            while ((nextRecord = csvReader.readNext()) != null) {
                for (String cell : nextRecord) {
                    System.out.print(cell + "\t");
                }
                System.out.println();
            }
        }
        catch (Exception e) {
            e.printStackTrace();
        }


    }

}
