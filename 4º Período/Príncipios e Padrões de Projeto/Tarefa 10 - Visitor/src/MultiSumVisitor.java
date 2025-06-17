import java.util.List;

public class MultiSumVisitor implements NumberVisitor{
    int totalMultSum = 0;

    @Override
    public void visit(TwoElement twoElement){
        int mult = twoElement.a * twoElement.b;
        System.out.println(twoElement.a + " x " + twoElement.b + " = " + mult);
        totalMultSum += mult;
    }

    @Override
    public void visit(ThreeElement threeElement){
        int mult = threeElement.a * threeElement.b * threeElement.c;
        System.out.println(threeElement.a + " x " + threeElement.b + " x " + threeElement.c + " = " + mult);
        totalMultSum += mult;
    }

    @Override
    public void visit (List<NumberElement> elementList){
        for(NumberElement ne : elementList){
            ne.accept(this);
        }
    }

    public int getTotalSum(){
        return totalMultSum;
    }
}
