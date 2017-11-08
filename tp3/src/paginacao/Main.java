package paginacao;

import java.util.ArrayList;
import java.util.Arrays;

public class Main {

    public static void main(String[] args) {
        String entrada = "1,1;2,1;3,1;4,1;2,1;1,1;5,1;6,1;2,1;1,1;2,1;3,1;7,1;6,1;3,1;2,1;1,1;2,1;3,1;6,1;0,0;";
        String[] aux0 = entrada.split(";");
        //retira 0,0
        aux0 = Arrays.copyOf(aux0, aux0.length-1);

        Algoritmo fifo = new Algoritmo(2, aux0);
        System.out.println(fifo.getQtdFaltas());

    }

}
