/*  Soit la hiérarchie de types suivante:  *
*        A                                 *
*      /   \                               *
*     B     C                              *
*    / \   / \                             *
*   D   E F   G                            *
*            / \                           *
*           H   I                          */

/*
*  et soit la classe Box suivante:
*/

public class Box<T> {
  private T t;
  public Box(T t) { this.t = t; }
  public T get() { return this.t; }
  public void set(T t) { this.t = t; }
}

/*
*  Indiquez quelles lignes du code ci-dessous ne compilent pas. Ecrivez oui/non
*  après chaque ligne. Oui indique que la ligne compile.
*/

Box<? extends B> bd = new Box<D>( new D() ); // Oui
D d = bd.get(); // bd eagale boite de b donc compile pas 
B b = bd.get(); // Oui
bd.set( new E() ); // Non ne peut pas comsommer
Box<? super B> bd = new Box<A>( new C() ); // Oui
D d = bd.get(); // Non ne peut pas produire
B b = bd.get(); // Non ne peut pas produire
bd.set( new D() ); // oui
Box<A> aa = new Box<A>( new B() ); // Oui
Box<B> bd = new Box<D>( new D() ); // Non type de boite peut pas etre différent
Box<? extends C> ca = new Box<A>( new G() ); // non
Box<? extends C> cg = new Box<G>( new I() ); // Oui
Box<? extends C> cg = new Box<G>( new H() ); // Oui
Box<? super G> g = new Box<A>( new B() ); // Oui
Box<? super D> d = new Box<B>( new E() ); //Oui
Box<? super D> da = new Box<C>( new C() ); //Est ce que D hérite de C et est ce que C herite de C : NON