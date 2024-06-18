import java.util.ArrayList;

public class ex3{
    /*
for (int i: Range.of(0, 5)) {
	...
}
*/
// for (int i: Range.of(0, i -> i + 1, i -> i < 5)) {
// 	...
// }
// for (String s: Range.of("", s -> s += "a", s -> !s.equals("aaaa"))) {
	
// }
// for (List<Integer> ls: Range.of(new ArrayList<>(); ls -> ls.append(10), s -> s.size() < 10)) {
	
    public static void main(String[] args) {
        for (int i: Range.of(0, i -> i + 1, i -> i < 5)) {
        	System.out.println(i);
        }
        for (String s: Range.of("", s -> s += "a", s -> !s.equals("aaaa"))) {
            System.out.println(s);
        }
        for (List<Integer> ls: Range.of(new ArrayList<>(), ls -> ls.append(10), s -> s.size() < 10)) {
            System.out.println(ls);
        }
    }
}

interface use{
    using(int start, int inc, boolean stop);
}

static class Range{
    static void of(use u){
        u.using();
    }
}