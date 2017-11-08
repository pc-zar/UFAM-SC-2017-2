package paginacao;

import java.util.ArrayList;
import java.util.Arrays;

public class Main {

    public static void main(String[] args) {
        final int memoriaSize = 5;
        ArrayList<Struct> memoria = new ArrayList<Struct>();
        int qtdFifo = 0;

        String entrada = "1,1;2,1;3,1;4,1;2,1;1,1;5,1;6,1;2,1;1,1;2,1;3,1;7,1;6,1;3,1;2,1;1,1;2,1;3,1;6,1;0,0;";
        String[] aux0 = entrada.split(";");

        //retira 0,0
        aux0 = Arrays.copyOf(aux0, aux0.length-1);

        for (String auxObj: aux0) {
            String[] aux1 = auxObj.split(",");
            int processo = Integer.parseInt(aux1[0]);
            int page = Integer.parseInt(aux1[1]);

            if(!memoriaContemStruct(memoria, new Struct(processo, page))){
                qtdFifo++;
                if(memoria.size() == memoriaSize){
                    memoria.remove(0);
                }
                memoria.add(new Struct(processo, page));
            }
        }

        System.out.println(qtdFifo);
    }

    private static boolean memoriaContemStruct(ArrayList<Struct> memoria, Struct s) {
        int i = 0;
        boolean hit = false;

        while((!hit) && (i < memoria.size())){
            if (s.getProcesso() == memoria.get(i).getProcesso()
                    && s.getPagina() == memoria.get(i).getPagina()
                    && s.getBit() == memoria.get(i).getBit()){
                hit = true;
            }
            i++;
        }

        return hit;
    }

}
