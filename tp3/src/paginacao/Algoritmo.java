package paginacao;

import java.util.ArrayList;

public class Algoritmo {

    public static int memoriaSize = 5;
    public static int constLru = 1917;

    private int qtdFaltas;

    public Algoritmo(int tipoAlg, String[] entrada) {
        switch (tipoAlg){
            case 1:
                setQtdFaltas(fifo(entrada));
                break;
            case 2:
                setQtdFaltas(lru(entrada));
                break;
            case 3:
                break;
            default:
                break;
        }
    }

    private int fifo(String[] entradaTratada){
        int qtdMiss = 0;
        ArrayList<Struct> memoria = new ArrayList<Struct>();

        for(int i = 0; i < entradaTratada.length; i++){
            String[] aux = entradaTratada[i].split(",");
            int processo = Integer.parseInt(aux[0]);
            int page = Integer.parseInt(aux[1]);
            Struct s = new Struct(processo, page);

            if(memoriaHitIndex(memoria, s) >= 0){
                qtdMiss++;
                if(memoria.size() == memoriaSize){
                    memoria.remove(0);
                }
                memoria.add(s);
            }
        }
        return qtdMiss;
    }

    private int lru(String[] entradaTratada){
        int qtdMiss = 0;
        ArrayList<Struct    > memoria = new ArrayList<Struct>();

        for(int i = 0; i < entradaTratada.length; i++){
            String[] aux = entradaTratada[i].split(",");
            int processo = Integer.parseInt(aux[0]);
            int page = Integer.parseInt(aux[1]);
            Struct s = new Struct(processo, page);

            if(memoriaHitIndex(memoria, s) >= 0){
                qtdMiss++;
                if(memoria.size() == memoriaSize){

                    int j = 0;

                    //verifica as structs que não foram chamados anteriormente
                    while((j < memoria.size()) && (memoria.get(j).getBit() != 0)){
                        j++;
                    }

                    //caso j chegue ao tamanho final, significa que pelo menos todas as structs foram chamadas
                    if(j != memoria.size()){
                        memoria.add(j, s);
                    } else {
                        //todas foram chamadas pelo menos uma vez
                    }
                } else {
                    memoria.add(s);
                }
            } else {
                int indexReferenciado = (memoriaHitIndex(memoria, s) * (-1)) - constLru;
                memoria.get(indexReferenciado).setBit(memoria.get(indexReferenciado).getBit() + 1);
            }
        }
        return qtdMiss;
    }

    //caso a pagina seja encontrada, a funcao retorna o index onde tal pagina foi encontrada na memoria (em negativo)
    private static int memoriaHitIndex(ArrayList<Struct> memoria, Struct s) {
        int i = 0;

        while((i >= 0) && (i < memoria.size())){
            if (s.getProcesso() == memoria.get(i).getProcesso()
                    && s.getPagina() == memoria.get(i).getPagina()
                    && s.getBit() == memoria.get(i).getBit()){
                i = (i + constLru) * (-1);
            } else {
                i++;
            }
        }
        return i;
    }

    public int getQtdFaltas() {
        return this.qtdFaltas;
    }

    private void setQtdFaltas(int qtdFaltas) {
        this.qtdFaltas = qtdFaltas;
    }
}
