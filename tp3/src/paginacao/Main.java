package paginacao;

import java.util.Arrays;

public class Main {

    public static void main(String[] args) {
        //criando array com 8000 elementos para representar a memoria
        final int memoriaSize = 8000;
        int[] memoria = new int[memoriaSize];

        for(int i = 0; i < memoriaSize; i++){
            memoria[i] = -1;
        }

        //inicializando string de referencia
        CadeiaReferencia cr;
        cr = new CadeiaReferencia();

        System.out.println("Size: "+cr.getCadeia().size());

        for(int i = 0; i < cr.getCadeia().size(); i++){
            System.out.println(cr.getCadeia().get(i));
        }

        for(int i = 0; i < cr.getCadeia().size(); i++){
            int j = 0;
            int processo = cr.getCadeia().get(i);
            int page = cr.getCadeia().get(i + 1);

            //algoritmo caminha pela memoria procurando por lugar livre
            while(memoria[j] != -1){
                j++;
            }

            memoria[j] = processo;
            memoria[j + 1] = page;

        }

    }

}
