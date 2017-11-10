package paginacao;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.Arrays;

public class Main {

    public static void main(String[] args) {

        String entrada = "";
        String fileName = "src/paginacao/files/entrada5.txt";

        try(BufferedReader br = new BufferedReader(new FileReader(fileName))) {
            StringBuilder sb = new StringBuilder();
            String line = br.readLine();

            while (line != null) {
                sb.append(line);
                sb.append(System.lineSeparator());
                line = br.readLine();
            }
            entrada = sb.toString();
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }

        String[] newEntrada = trataEntrada(entrada);
        System.out.println("QTD DE ENTRADAS: "+ newEntrada.length);

        Algoritmo fifo = new Algoritmo(1, newEntrada);
        Algoritmo lru = new Algoritmo(2, newEntrada);
        Algoritmo segundaChance = new Algoritmo(3, newEntrada);

        System.out.println("FIFO: "+fifo.getQtdFaltas());
        System.out.println("LRU: "+lru.getQtdFaltas());
        System.out.println("SEGUNDA CHANCE: "+segundaChance.getQtdFaltas());

    }

    private static String[] trataEntrada(String entrada){
        if(!primeiroCharInt(entrada)){
            entrada = entrada.substring(1);
        }

        String[] aux = entrada.split(";");

        int i = 0;
        boolean fimCadeia = false;
        while ((i < aux.length) && (!fimCadeia)){
            if(aux[i].contentEquals("0,0")){
                fimCadeia = true;
            } else {
                i++;
            }
        }

        aux = Arrays.copyOf(aux, i);
        return aux;
    }

    private static boolean primeiroCharInt(String entrada){
        int i = 0;
        String decimals = "01234556789";
        boolean okInt = false;
        while ((i < decimals.length()) && (!okInt)){
            if(entrada.charAt(0) == decimals.charAt(i)){
                okInt = true;
            } else {
                i++;
            }
        }

        return okInt;
    }

}
