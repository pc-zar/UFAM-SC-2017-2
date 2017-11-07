package paginacao;

import java.util.ArrayList;

public class Main {

    public static void main(String[] args) {
        final int memoriaSize = 5;
        ArrayList<Struct> memoria = new ArrayList<Struct>();
        int qtdFifo = 0;
        String entrada = "1,1;2,1;3,1;4,1;2,1;1,1;5,1;6,1;2,1;1,1;2,1;3,1;7,1;6,1;3,1;2,1;1,1;2,1;3,1;6,1;0,0;";
        String[] aux0 = entrada.split(";");

        for (String auxObj: aux0) {
            String[] aux1 = auxObj.split(",");
            int processo = Integer.parseInt(aux1[0]);
            int page = Integer.parseInt(aux1[1]);

            Struct strCand = new Struct(processo, page);

            if(!memoria.contains(strCand)){
                qtdFifo++;
                if(memoria.size() >= memoriaSize){
                    memoria.remove(0);
                }
                memoria.add(new Struct(processo, page));
            }
        }
    }

}
