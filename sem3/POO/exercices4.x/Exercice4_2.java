public class Exercice4_2{
    public enum Day {
        Monday, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday;

        public int dayOfWeek(){
            switch(this){
                case Monday: 
                    return 1;
                case Tuesday: 
                    return 2;
                case Wednesday: 
                    return 3;
                case Thursday: 
                    return 4;
                case Friday: 
                    return 5;
                case Saturday: 
                    return 6;
                case Sunday: 
                    return 7;
                default:
                    return 0;
            }
        }

    }
    
    public static void main(String[] args){
        for(Day d: Day.values() ) {
            System.out.println(d + " is the day number: " + d.dayOfWeek() );
        }
    }
    
}