package paginacao;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.Arrays;
import java.util.Scanner;

public class Paginacao {

    public static void main(String[] args) {

        Scanner s;
        try {
            s = new Scanner(new BufferedReader(new FileReader((new Scanner(System.in)).next())).readLine());

        } catch (IOException e) {
            s = new Scanner((new Scanner((new Scanner(System.in)).next())).nextLine());

        }

        String entrada = s.nextLine();
        String[] aux0 = entrada.split(";");
        aux0 = Arrays.copyOf(aux0, aux0.length-1);

        Algoritmo fifo = new Algoritmo(1, aux0);
        Algoritmo lru = new Algoritmo(2, aux0);
        Algoritmo segundaChance = new Algoritmo(3, aux0);

        System.out.println("FIFO: "+fifo.getQtdFaltas());
        System.out.println("LRU: "+lru.getQtdFaltas());
        System.out.println("SEGUNDA CHANCE: "+segundaChance.getQtdFaltas());
    }

}
