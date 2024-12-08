import java.util.ArrayList;
import java.util.List;

public class Ordenar {
    public static <T extends Comparar<T>> void ordenacao(List<T> a){
        Comparar elem, menor;
        int pos;
        for(int i = 0; i < a.size() - 1; i++){
            elem =  a.get(i);
            menor =  a.get(i + 1);
            pos = i+1;
            for(int j = i + 2; j < a.size(); j++){
                if(a.get(j).compara((T) menor) < 0){
                    menor =  a.get(j);
                    pos = j;
                }
            }
            if (menor.compara(elem) < 0){
                a.set(i, a.get(pos));
                a.set(pos, (T) elem);
            }
        }
    }
}
