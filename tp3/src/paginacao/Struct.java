package paginacao;

public class Struct {

    private int processo;
    private int pagina;
    private int bit;

    public Struct(int processo, int pagina) {
        setProcesso(processo);
        setPagina(pagina);
        setBit(0);
    }

    public int getProcesso() {
        return processo;
    }

    public void setProcesso(int processo) {
        this.processo = processo;
    }

    public int getPagina() {
        return pagina;
    }

    public void setPagina(int pagina) {
        this.pagina = pagina;
    }

    public int getBit() {
        return bit;
    }

    public void setBit(int bit) {
        this.bit = bit;
    }
}
