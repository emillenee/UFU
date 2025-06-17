import java.util.List;

public class MultiVisitor implements NumberVisitor{
    @Override
    public void visit(TwoElement twoElement){
        int mult = twoElement.a * twoElement.b;
        System.out.println(twoElement.a + " x " + twoElement.b + " = " + mult);
    }

    @Override
    public void visit(ThreeElement threeElement){
        int mult = threeElement.a * threeElement.b * threeElement.c;
        System.out.println(threeElement.a + " x " + threeElement.b + " x " + threeElement.c + " = " + mult);
    }

    @Override
    public void visit (List<NumberElement> elementList){
        for(NumberElement ne : elementList){
            ne.accept(this);
        }
    }
}
