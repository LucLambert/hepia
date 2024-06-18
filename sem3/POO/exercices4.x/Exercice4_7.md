# 4.7 Exercice
## Soient les déclarations suivantes:
```java
class A {}
class B extends A {}
class C extends A {}
class D extends A {}
class E extends A {}
class Z {
    public void f(B b) { System.out.println("B"); }
    public void f(C c) { System.out.println("C"); }
    public void f(E e) { System.out.println("E"); }
}
```
## Pour chaque ligne, précisez ce qui sera affiché ou le type d’erreur (exécution ou compilation):

```java
Z z = new Z(); 
z.f( new A() ); compilation
z.f( new B() ); B
z.f( new C() ); C
z.f( new D() ); C
z.f( "COUCOU" ); execution
```