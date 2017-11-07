package paginacao;

import java.util.ArrayList;
import java.util.Random;

public class CadeiaReferencia {

    private ArrayList<Integer> cadeia;

    public CadeiaReferencia() {
        this.cadeia = generateRandomCadeia();
    }

    public ArrayList<Integer> getCadeia() {
        return this.cadeia;
    }

    private ArrayList<Integer> generateRandomCadeia(){
        int i = 0;
        ArrayList<Integer> randomArrayList = new ArrayList();
        boolean notEoA = true;
        Random randomGenerator = new Random();

        while(notEoA){
            int randomProcesso = randomGenerator.nextInt(80);
            int randomPage = randomGenerator.nextInt(80);

            if(randomProcesso == 0 && randomPage == 0){
                notEoA = false;
            } else {
                randomArrayList.add(i, randomProcesso);
                randomArrayList.add(i + 1, randomPage);
                i = i + 2;
            }
        }

        return randomArrayList;
    }
}
