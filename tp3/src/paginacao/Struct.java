package paginacao;

public class Struct {

    private int processo;
    private int pagina;
    private boolean bit;

    public Struct(int processo, int pagina) {
        setProcesso(processo);
        setPagina(pagina);
        setBit(false);
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

    public boolean getBit() {
        return bit;
    }

    public void setBit(boolean bit) {
        this.bit = bit;
    }
}
