package paginacao;

import java.util.ArrayList;
import java.util.Collections;

public class Algoritmo {

    //qtd de Quadros
    public static int memoriaSize = 8000;
    public static int constLru = 1999;

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
                setQtdFaltas(segundaChance(entrada));
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

            /*caso a função retorne algum inteiro maior ou igual a zero,
            significa que o processo terá que ser inserido na memória*/
            if(memoriaHitIndex(memoria, s) >= 0){
                qtdMiss++;
                /*se a memória estiver cheia, remove o primeiro elemento do array
                antes de adicionar o novo processo
                */
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
        ArrayList<Struct> memoria = new ArrayList<Struct>();
        ArrayList<Integer> listaBitEnvelhecimento = new ArrayList<Integer>();

        for(int i = 0; i < entradaTratada.length; i++){
            String[] aux = entradaTratada[i].split(",");

            int processo = Integer.parseInt(aux[0]);
            int page = Integer.parseInt(aux[1]);
            Struct s = new Struct(processo, page);

            if(memoriaHitIndex(memoria, s) >= 0){
                qtdMiss++;
                if(memoria.size() == memoriaSize){
                    //varre a memoria e diz qual é o index mais antigo (mais à esquerda), e com menor bit
                    int indexMenorBit = listaBitEnvelhecimento.indexOf(Collections.min(listaBitEnvelhecimento));
                    memoria.remove(indexMenorBit);
                }
                memoria.add(s);
            } else {
                //caso tal processo já esteja em memoria, simular seu envelhecimento
                int indexReferenciado = (memoriaHitIndex(memoria, s) * (-1)) - constLru;
                memoria.get(indexReferenciado).setBit(memoria.get(indexReferenciado).getBit() + 1);
            }

            listaBitEnvelhecimento.clear();
            for(int j = 0; j < memoria.size(); j++){
                listaBitEnvelhecimento.add(memoria.get(j).getBit());
            }

        }
        return qtdMiss;
    }

    private int segundaChance(String[] entradaTratada){
        int qtdMiss = 0;
        ArrayList<Struct> memoria = new ArrayList<Struct>();
        ArrayList<Integer> listaBitSegundaChance = new ArrayList<Integer>();

        for(int i = 0; i < entradaTratada.length; i++){
            String[] aux = entradaTratada[i].split(",");
            int processo = Integer.parseInt(aux[0]);
            int page = Integer.parseInt(aux[1]);
            Struct s = new Struct(processo, page);

            if(memoriaHitIndex(memoria, s) >= 0){
                qtdMiss++;
                if(memoria.size() == memoriaSize){
                    int j = 0;
                    while((j < memoria.size()) && memoria.get(j).getBit() != 0){
                        j++;
                    }

                    if(j < memoria.size()){
                        memoria.get(j).setBit(0);
                    } else {
                        //todos foram referenciados
                        //zerar todos
                        for(int k = 0; k < memoria.size(); k++){
                            memoria.get(k).setBit(0);
                        }
                    }
                    //remove primeiro zero que ve pela frente
                    int indexMenorBit = listaBitSegundaChance.indexOf(Collections.min(listaBitSegundaChance));
                    memoria.remove(indexMenorBit);
                }
                memoria.add(s);
            } else {
                int indexReferenciado = (memoriaHitIndex(memoria, s) * (-1)) - constLru;
                if(memoria.get(indexReferenciado).getBit() == 0){
                    memoria.get(indexReferenciado).setBit(1);
                }
            }

            listaBitSegundaChance.clear();
            for(int j = 0; j < memoria.size(); j++){
                listaBitSegundaChance.add(memoria.get(j).getBit());
            }

        }
        return qtdMiss;
    }

    //caso a pagina seja encontrada, a funcao retorna o index onde tal pagina foi encontrada na memoria (em negativo)
    private static int memoriaHitIndex(ArrayList<Struct> memoria, Struct s) {
        int i = 0;

        while((i >= 0) && (i < memoria.size())){
            if (s.getProcesso() == memoria.get(i).getProcesso()
                    && s.getPagina() == memoria.get(i).getPagina()){
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
