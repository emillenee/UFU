import java.util.List;

public class TotalSumVisitor implements NumberVisitor{
    int totalSum = 0;

    @Override
    public void visit(TwoElement twoElement){
        int sum = twoElement.a + twoElement.b;
        System.out.println(twoElement.a + " + " + twoElement.b + " = " + sum);
        totalSum += sum;
    }

    @Override
    public void visit(ThreeElement threeElement){
        int sum = threeElement.a + threeElement.b + threeElement.c;
        System.out.println(threeElement.a + " + " + threeElement.b + " + " + threeElement.c + " = " + sum);
        totalSum += sum;
    }

    @Override
    public void visit (List<NumberElement> elementList){
        for(NumberElement ne : elementList){
            ne.accept(this);
        }
    }

    public int getTotalSum(){
        return totalSum;
    }
}
